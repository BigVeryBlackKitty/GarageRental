// PaymentFrame.cpp
#include "PaymentFrame.h"
#include <wx/msgdlg.h>

PaymentFrame::PaymentFrame(wxWindow* parent, DatabaseManager* db)
    : wxFrame(parent, wxID_ANY, wxT("Приём оплаты"), wxDefaultPosition, wxSize(600, 500)), m_db(db) {
    
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    wxFlexGridSizer* grid = new wxFlexGridSizer(2, 10, 10);
    
    // Выбор договора
    grid->Add(new wxStaticText(this, wxID_ANY, wxT("Договор аренды:*")));
    m_agreementCombo = new wxComboBox(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, 0, nullptr, wxCB_READONLY);
    grid->Add(m_agreementCombo, 1, wxEXPAND);
    
    // Информация об арендаторе
    grid->Add(new wxStaticText(this, wxID_ANY, wxT("Арендатор:")));
    m_tenantInfo = new wxStaticText(this, wxID_ANY, "");
    grid->Add(m_tenantInfo, 1, wxEXPAND);
    
    // Задолженность
    grid->Add(new wxStaticText(this, wxID_ANY, wxT("Задолженность:")));
    m_debtInfo = new wxStaticText(this, wxID_ANY, "");
    grid->Add(m_debtInfo, 1, wxEXPAND);
    
    // Сумма платежа
    grid->Add(new wxStaticText(this, wxID_ANY, wxT("Сумма платежа:*")));
    m_amountCtrl = new wxTextCtrl(this, wxID_ANY);
    grid->Add(m_amountCtrl, 1, wxEXPAND);
    
    // Дата платежа
    grid->Add(new wxStaticText(this, wxID_ANY, wxT("Дата платежа:*")));
    m_paymentDate = new wxDatePickerCtrl(this, wxID_ANY, wxDateTime::Now());
    grid->Add(m_paymentDate, 1, wxEXPAND);
    
    // Тип платежа
    grid->Add(new wxStaticText(this, wxID_ANY, wxT("Тип платежа:*")));
    m_paymentType = new wxChoice(this, wxID_ANY);
    m_paymentType->Append(wxT("Наличные"));
    m_paymentType->Append(wxT("Карта"));
    m_paymentType->Append(wxT("Перевод"));
    m_paymentType->SetSelection(0);
    grid->Add(m_paymentType, 1, wxEXPAND);
    
    // Номер квитанции
    grid->Add(new wxStaticText(this, wxID_ANY, "№ квитанции:"));
    m_receiptCtrl = new wxTextCtrl(this, wxID_ANY);
    grid->Add(m_receiptCtrl, 1, wxEXPAND);
    
    mainSizer->Add(grid, 1, wxEXPAND | wxALL, 10);
    
    // Кнопки
    wxBoxSizer* btnSizer = new wxBoxSizer(wxHORIZONTAL);
    m_payBtn = new wxButton(this, wxID_ANY, wxT("Оплатить"));
    m_cancelBtn = new wxButton(this, wxID_ANY, wxT("Отмена"));
    btnSizer->Add(m_payBtn, 0, wxALL, 5);
    btnSizer->Add(m_cancelBtn, 0, wxALL, 5);
    mainSizer->Add(btnSizer, 0, wxALIGN_CENTER | wxALL, 10);
    
    SetSizer(mainSizer);
    
    LoadActiveAgreements();
    
    m_agreementCombo->Bind(wxEVT_COMBOBOX, &PaymentFrame::OnAgreementSelected, this);
    m_payBtn->Bind(wxEVT_BUTTON, &PaymentFrame::OnPay, this);
    m_cancelBtn->Bind(wxEVT_BUTTON, &PaymentFrame::OnCancel, this);
}

void PaymentFrame::LoadActiveAgreements() {
    m_agreementCombo->Clear();
    m_agreementIds.clear();
    m_debts.clear();
    
    sqlite3* db = m_db->GetDB();
    if (!db) return;
    
    sqlite3_stmt* stmt;
    const char* sql = 
        "SELECT la.id, la.personal_numbers, t.surname || ' ' || t.name, "
        "la.total_amount, COALESCE(SUM(p.payment_amount), 0) as paid "
        "FROM Lease_Agreement la "
        "JOIN Tenant t ON t.id = la.tenant_id "
        "LEFT JOIN Payment p ON p.agreement_id = la.id "
        "WHERE la.status = 1 "
        "GROUP BY la.id";
    
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            int id = sqlite3_column_int(stmt, 0);
            wxString contractNum = wxString::FromUTF8((const char*)sqlite3_column_text(stmt, 1));
            wxString tenant = wxString::FromUTF8((const char*)sqlite3_column_text(stmt, 2));
            double total = sqlite3_column_double(stmt, 3);
            double paid = sqlite3_column_double(stmt, 4);
            double debt = total - paid;
            
            wxString display = wxString::Format("%s - %s (долг: %.2f ₽)", contractNum, tenant, debt);
            m_agreementCombo->Append(display);
            m_agreementIds.push_back(id);
            m_debts.push_back(debt);
        }
        sqlite3_finalize(stmt);
    }
    
    if (m_agreementCombo->GetCount() > 0) {
        m_agreementCombo->SetSelection(0);
        wxCommandEvent evt;
        OnAgreementSelected(evt);
    }
}

void PaymentFrame::LoadAgreementInfo(int agreementId) {
    sqlite3* db = m_db->GetDB();
    if (!db) return;
    
    sqlite3_stmt* stmt;
    wxString sql = wxString::Format(
        "SELECT t.surname || ' ' || t.name, "
        "la.total_amount, COALESCE(SUM(p.payment_amount), 0) as paid "
        "FROM Lease_Agreement la "
        "JOIN Tenant t ON t.id = la.tenant_id "
        "LEFT JOIN Payment p ON p.agreement_id = la.id "
        "WHERE la.id = %d "
        "GROUP BY la.id", agreementId);
    
    if (sqlite3_prepare_v2(db, sql.utf8_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            wxString tenant = wxString::FromUTF8((const char*)sqlite3_column_text(stmt, 0));
            double total = sqlite3_column_double(stmt, 1);
            double paid = sqlite3_column_double(stmt, 2);
            double debt = total - paid;
            
            m_tenantInfo->SetLabel(tenant);
            m_debtInfo->SetLabel(wxString::Format("%.2f ₽", debt));
            if (debt > 0) {
                m_debtInfo->SetForegroundColour(*wxRED);
            } else {
                m_debtInfo->SetForegroundColour(*wxGREEN);
            }
        }
        sqlite3_finalize(stmt);
    }
}

void PaymentFrame::OnAgreementSelected(wxCommandEvent& event) {
    int idx = m_agreementCombo->GetSelection();
    if (idx != wxNOT_FOUND) {
        LoadAgreementInfo(m_agreementIds[idx]);
    }
}

bool PaymentFrame::ValidateForm() {
    int idx = m_agreementCombo->GetSelection();
    if (idx == wxNOT_FOUND) {
        wxMessageBox(wxT("Выберите договор"), wxT("Ошибка"), wxOK | wxICON_WARNING);
        return false;
    }
    
    double amount;
    if (!m_amountCtrl->GetValue().ToDouble(&amount) || amount <= 0) {
        wxMessageBox(wxT("Введите корректную сумму платежа"), wxT("Ошибка"), wxOK | wxICON_WARNING);
        return false;
    }
    
    if (amount > m_debts[idx]) {
        if (wxMessageBox(wxString::Format(wxT("Сумма платежа (%.2f ₽) превышает задолженность (%.2f ₽).\nПродолжить?"), 
                         amount, m_debts[idx]), wxT("Предупреждение"), wxYES_NO | wxICON_WARNING) != wxYES) {
            return false;
        }
    }
    
    return true;
}

void PaymentFrame::OnPay(wxCommandEvent& event) {
    if (!ValidateForm()) return;
    
    int idx = m_agreementCombo->GetSelection();
    int agreementId = m_agreementIds[idx];
    
    double amount;
    m_amountCtrl->GetValue().ToDouble(&amount);
    
    wxString paymentDate = m_paymentDate->GetValue().FormatISODate();
    int paymentType = m_paymentType->GetSelection() + 1;
    wxString receiptNumber = m_receiptCtrl->GetValue();
    
    // Получаем payer_id (tenant_id) из договора
    sqlite3* db = m_db->GetDB();
    int payerId = -1;
    sqlite3_stmt* stmt;
    wxString sql = wxString::Format("SELECT tenant_id FROM Lease_Agreement WHERE id=%d", agreementId);
    
    if (sqlite3_prepare_v2(db, sql.utf8_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            payerId = sqlite3_column_int(stmt, 0);
        }
        sqlite3_finalize(stmt);
    }
    
    if (payerId != -1) {
        if (m_db->AddPayment(agreementId, payerId, amount, paymentDate, paymentType, receiptNumber)) {
            wxMessageBox(wxT("Платеж успешно проведён!"), wxT("Успех"), wxOK | wxICON_INFORMATION);
            Close();
        } else {
            wxMessageBox(wxT("Ошибка при проведении платежа"), wxT("Ошибка"), wxOK | wxICON_ERROR);
        }
    }
}

void PaymentFrame::OnCancel(wxCommandEvent& event) {
    Close();
}