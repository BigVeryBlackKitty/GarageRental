// CloseAgreementFrame.cpp
#include "CloseAgreementFrame.h"
#include <wx/msgdlg.h>

CloseAgreementFrame::CloseAgreementFrame(wxWindow* parent, DatabaseManager* db)
    : wxFrame(parent, wxID_ANY, wxT("Завершение аренды"), wxDefaultPosition, wxSize(600, 400)), m_db(db) {
    
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    
    // Выбор договора
    wxBoxSizer* selectSizer = new wxBoxSizer(wxHORIZONTAL);
    selectSizer->Add(new wxStaticText(this, wxID_ANY, wxT("Выберите договор:")), 0, wxALIGN_CENTER | wxRIGHT, 10);
    m_agreementCombo = new wxComboBox(this, wxID_ANY, "", wxDefaultPosition, wxSize(300, -1), 0, nullptr, wxCB_READONLY);
    selectSizer->Add(m_agreementCombo, 0, wxEXPAND);
    mainSizer->Add(selectSizer, 0, wxALL, 10);
    
    // Информация о договоре
    wxStaticBoxSizer* infoSizer = new wxStaticBoxSizer(wxVERTICAL, this, wxT("Информация о договоре"));
    m_infoText = new wxStaticText(this, wxID_ANY, "");
    m_infoText->Wrap(500);
    infoSizer->Add(m_infoText, 1, wxALL, 10);
    mainSizer->Add(infoSizer, 1, wxEXPAND | wxALL, 10);
    
    // Предупреждение
    wxStaticText* warningText = new wxStaticText(this, wxID_ANY, 
        wxT("Внимание! После завершения аренды:\n")
        "- Договор будет помечен как завершённый\n"
        "- Гараж станет свободным\n"
        "- Все неоплаченные суммы останутся задолженностью");
    warningText->SetForegroundColour(*wxRED);
    mainSizer->Add(warningText, 0, wxALL, 10);
    
    // Кнопки
    wxBoxSizer* btnSizer = new wxBoxSizer(wxHORIZONTAL);
    m_closeBtn = new wxButton(this, wxID_ANY, wxT("Завершить аренду"));
    m_cancelBtn = new wxButton(this, wxID_ANY, wxT("Отмена"));
    btnSizer->Add(m_closeBtn, 0, wxALL, 5);
    btnSizer->Add(m_cancelBtn, 0, wxALL, 5);
    mainSizer->Add(btnSizer, 0, wxALIGN_CENTER | wxALL, 10);
    
    SetSizer(mainSizer);
    
    LoadActiveAgreements();
    m_agreementCombo->Bind(wxEVT_COMBOBOX, &CloseAgreementFrame::OnAgreementSelected, this);
    m_closeBtn->Bind(wxEVT_BUTTON, &CloseAgreementFrame::OnCloseAgreement, this);
    m_cancelBtn->Bind(wxEVT_BUTTON, &CloseAgreementFrame::OnCancel, this);
}

void CloseAgreementFrame::LoadActiveAgreements() {
    m_agreementCombo->Clear();
    m_agreementIds.clear();
    
    sqlite3* db = m_db->GetDB();
    if (!db) return;
    
    sqlite3_stmt* stmt;
    const char* sql = 
        "SELECT la.id, la.personal_numbers, t.surname || ' ' || t.name, g.personal_numbers, "
        "la.start_date, la.end_date "
        "FROM Lease_Agreement la "
        "JOIN Tenant t ON t.id = la.tenant_id "
        "JOIN Garage g ON g.id = la.garage_id "
        "WHERE la.status = 1";
    
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            int id = sqlite3_column_int(stmt, 0);
            wxString contractNum = wxString::FromUTF8((const char*)sqlite3_column_text(stmt, 1));
            wxString tenant = wxString::FromUTF8((const char*)sqlite3_column_text(stmt, 2));
            wxString garage = wxString::FromUTF8((const char*)sqlite3_column_text(stmt, 3));
            
            wxString display = wxString::Format("%s - %s (гараж %s)", contractNum, tenant, garage);
            m_agreementCombo->Append(display);
            m_agreementIds.push_back(id);
        }
        sqlite3_finalize(stmt);
    }
    
    if (m_agreementCombo->GetCount() > 0) {
        m_agreementCombo->SetSelection(0);
        wxCommandEvent evt;
        OnAgreementSelected(evt);
    } else {
        m_infoText->SetLabel(wxT("Нет активных договоров"));
        m_closeBtn->Enable(false);
    }
}

void CloseAgreementFrame::LoadAgreementInfo(int agreementId) {
    sqlite3* db = m_db->GetDB();
    if (!db) return;
    
    sqlite3_stmt* stmt;
    wxString sql = wxString::Format(
        "SELECT la.personal_numbers, t.surname || ' ' || t.name, g.personal_numbers, "
        "la.start_date, la.end_date, la.total_amount, "
        "COALESCE(SUM(p.payment_amount), 0) as paid "
        "FROM Lease_Agreement la "
        "JOIN Tenant t ON t.id = la.tenant_id "
        "JOIN Garage g ON g.id = la.garage_id "
        "LEFT JOIN Payment p ON p.agreement_id = la.id "
        "WHERE la.id = %d "
        "GROUP BY la.id", agreementId);
    
    if (sqlite3_prepare_v2(db, sql.utf8_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            wxString contractNum = wxString::FromUTF8((const char*)sqlite3_column_text(stmt, 0));
            wxString tenant = wxString::FromUTF8((const char*)sqlite3_column_text(stmt, 1));
            wxString garage = wxString::FromUTF8((const char*)sqlite3_column_text(stmt, 2));
            wxString startDate = wxString::FromUTF8((const char*)sqlite3_column_text(stmt, 3));
            wxString endDate = wxString::FromUTF8((const char*)sqlite3_column_text(stmt, 4));
            double total = sqlite3_column_double(stmt, 5);
            double paid = sqlite3_column_double(stmt, 6);
            double debt = total - paid;
            
            wxString info;
            info.Printf(wxT("Номер договора: %s\nАрендатор: %s\nГараж: %s\n")
                       wxT("Период: %s - %s\nОбщая сумма: %.2f ₽\nОплачено: %.2f ₽\n")
                       wxT("Задолженность: %.2f ₽\n"),
                       contractNum, tenant, garage, startDate, endDate, total, paid, debt);
            
            if (debt > 0) {
                info += "\nВнимание! У арендатора есть задолженность!";
            }
            
            m_infoText->SetLabel(info);
        }
        sqlite3_finalize(stmt);
    }
}

void CloseAgreementFrame::OnAgreementSelected(wxCommandEvent& event) {
    int idx = m_agreementCombo->GetSelection();
    if (idx != wxNOT_FOUND) {
        LoadAgreementInfo(m_agreementIds[idx]);
    }
}

void CloseAgreementFrame::OnCloseAgreement(wxCommandEvent& event) {
    int idx = m_agreementCombo->GetSelection();
    if (idx == wxNOT_FOUND) {
        wxMessageBox(wxT("Выберите договор"), wxT("Ошибка"), wxOK | wxICON_WARNING);
        return;
    }
    
    int agreementId = m_agreementIds[idx];
    
    if (wxMessageBox(wxT("Вы уверены, что хотите завершить аренду?"),
                     wxT("Подтверждение"), wxYES_NO | wxICON_QUESTION) == wxYES) {
        if (m_db->CloseAgreement(agreementId)) {
            wxMessageBox(wxT("Аренда успешно завершена!"), wxT("Успех"), wxOK | wxICON_INFORMATION);
            Close();
        } else {
            wxMessageBox(wxT("Ошибка при завершении аренды"), wxT("Ошибка"), wxOK | wxICON_ERROR);
        }
    }
}

void CloseAgreementFrame::OnCancel(wxCommandEvent& event) {
    Close();
}