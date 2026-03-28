// NewAgreementFrame.cpp
#include "NewAgreementFrame.h"
#include <wx/msgdlg.h>
#include <wx/numformatter.h>
#include <wx/dateevt.h>

NewAgreementFrame::NewAgreementFrame(wxWindow* parent, DatabaseManager* db)
    : wxFrame(parent, wxID_ANY, wxT("Новый договор аренды"), wxDefaultPosition, wxSize(500, 500)), m_db(db) {
    
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    wxFlexGridSizer* grid = new wxFlexGridSizer(2, 10, 10);
    
    // Номер договора
    grid->Add(new wxStaticText(this, wxID_ANY, wxT("Номер договора:")));
    m_contractNumber = new wxTextCtrl(this, wxID_ANY);
    grid->Add(m_contractNumber, 1, wxEXPAND);
    
    // Арендатор
    grid->Add(new wxStaticText(this, wxID_ANY, wxT("Арендатор:")));
    m_tenantCombo = new wxComboBox(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, 0, nullptr, wxCB_READONLY);
    grid->Add(m_tenantCombo, 1, wxEXPAND);
    
    // Гараж
    grid->Add(new wxStaticText(this, wxID_ANY, wxT("Гаражный бокс:")));
    m_garageCombo = new wxComboBox(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, 0, nullptr, wxCB_READONLY);
    grid->Add(m_garageCombo, 1, wxEXPAND);
    
    // Дата начала
    grid->Add(new wxStaticText(this, wxID_ANY, wxT("Дата начала:")));
    m_startDate = new wxDatePickerCtrl(this, wxID_ANY, wxDateTime::Now());
    grid->Add(m_startDate, 1, wxEXPAND);
    
    // Дата окончания
    grid->Add(new wxStaticText(this, wxID_ANY, wxT("Дата окончания:")));
    m_endDate = new wxDatePickerCtrl(this, wxID_ANY, wxDateTime::Now() + wxTimeSpan::Days(30));
    grid->Add(m_endDate, 1, wxEXPAND);
    
    // Стоимость в месяц
    grid->Add(new wxStaticText(this, wxID_ANY, wxT("Стоимость (₽/мес):")));
    m_monthlyPrice = new wxTextCtrl(this, wxID_ANY, "5000");
    grid->Add(m_monthlyPrice, 1, wxEXPAND);
    
    // Сумма договора
    grid->Add(new wxStaticText(this, wxID_ANY, wxT("Сумма договора:")));
    m_totalAmount = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
    grid->Add(m_totalAmount, 1, wxEXPAND);
    
    mainSizer->Add(grid, 1, wxEXPAND | wxALL, 10);
    
    // Кнопки
    wxBoxSizer* btnSizer = new wxBoxSizer(wxHORIZONTAL);
    m_saveBtn = new wxButton(this, wxID_ANY, wxT("Сохранить"));
    m_cancelBtn = new wxButton(this, wxID_ANY, wxT("Отмена"));
    btnSizer->Add(m_saveBtn, 0, wxALL, 5);
    btnSizer->Add(m_cancelBtn, 0, wxALL, 5);
    mainSizer->Add(btnSizer, 0, wxALIGN_CENTER | wxALL, 10);
    
    SetSizer(mainSizer);
    
    // Загрузка данных
    LoadTenants();
    LoadFreeGarages();
    GenerateContractNumber();
    
    // События
    m_saveBtn->Bind(wxEVT_BUTTON, &NewAgreementFrame::OnSave, this);
    m_cancelBtn->Bind(wxEVT_BUTTON, &NewAgreementFrame::OnCancel, this);
    m_monthlyPrice->Bind(wxEVT_TEXT, &NewAgreementFrame::OnCalculateTotal, this);
    m_startDate->Bind(wxEVT_DATE_CHANGED, &NewAgreementFrame::OnCalculateTotal, this);
    m_endDate->Bind(wxEVT_DATE_CHANGED, &NewAgreementFrame::OnCalculateTotal, this);
    m_garageCombo->Bind(wxEVT_COMBOBOX, &NewAgreementFrame::OnGarageSelected, this);
    
    CalculateTotal();
}

void NewAgreementFrame::LoadTenants() {
    m_tenantCombo->Clear();
    m_tenantIds.clear();
    
    sqlite3* db = m_db->GetDB();
    if (!db) return;
    
    sqlite3_stmt* stmt;
    const char* sql = "SELECT id, surname, name, patronymic, phone_num FROM Tenant";
    
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            int id = sqlite3_column_int(stmt, 0);
            wxString fullName = wxString::Format("%s %s %s (%s)",
                wxString::FromUTF8((const char*)sqlite3_column_text(stmt, 1)),
                wxString::FromUTF8((const char*)sqlite3_column_text(stmt, 2)),
                wxString::FromUTF8((const char*)sqlite3_column_text(stmt, 3)),
                wxString::FromUTF8((const char*)sqlite3_column_text(stmt, 4)));
            
            m_tenantCombo->Append(fullName);
            m_tenantIds.push_back(id);
        }
        sqlite3_finalize(stmt);
    }
    
    if (m_tenantCombo->GetCount() > 0) {
        m_tenantCombo->SetSelection(0);
    }
}

void NewAgreementFrame::LoadFreeGarages() {
    m_garageCombo->Clear();
    m_garageIds.clear();
    
    sqlite3* db = m_db->GetDB();
    if (!db) return;
    
    sqlite3_stmt* stmt;
    const char* sql = "SELECT id, personal_numbers, location FROM Garage WHERE status_garage = 1";
    
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            int id = sqlite3_column_int(stmt, 0);
            wxString display = wxString::Format("%s (%s)",
                wxString::FromUTF8((const char*)sqlite3_column_text(stmt, 1)),
                wxString::FromUTF8((const char*)sqlite3_column_text(stmt, 2)));
            
            m_garageCombo->Append(display);
            m_garageIds.push_back(id);
        }
        sqlite3_finalize(stmt);
    }
    
    if (m_garageCombo->GetCount() > 0) {
        m_garageCombo->SetSelection(0);
    }
}

void NewAgreementFrame::GenerateContractNumber() {
    wxDateTime now = wxDateTime::Now();
    wxString number = wxString::Format("AG-%04d-%03d", now.GetYear(), rand() % 1000);
    m_contractNumber->SetValue(number);
}

void NewAgreementFrame::CalculateTotal() {
    wxDateTime start = m_startDate->GetValue();
    wxDateTime end = m_endDate->GetValue();
    
    if (!start.IsValid() || !end.IsValid() || start > end) {
        m_totalAmount->SetValue("0.00");
        return;
    }
    
    // Количество месяцев
    int months = (end.GetYear() - start.GetYear()) * 12 + (end.GetMonth() - start.GetMonth()) + 1;
    if (months < 0) months = 0;
    
    double monthlyPrice = 0.0;
    m_monthlyPrice->GetValue().ToDouble(&monthlyPrice);
    
    double total = monthlyPrice * months;
    m_totalAmount->SetValue(wxString::Format("%.2f", total));
}

void NewAgreementFrame::OnCalculateTotal(wxCommandEvent& event) {
    CalculateTotal();
}

void NewAgreementFrame::OnGarageSelected(wxCommandEvent& event) {
    // Можно подгрузить цену для выбранного гаража (если есть разные цены)
    CalculateTotal();
}

bool NewAgreementFrame::ValidateForm() {
    if (m_contractNumber->GetValue().IsEmpty()) {
        wxMessageBox(wxT("Введите номер договора"), wxT("Ошибка"), wxOK | wxICON_WARNING);
        return false;
    }
    
    if (m_tenantCombo->GetSelection() == wxNOT_FOUND) {
        wxMessageBox(wxT("Выберите арендатора"), wxT("Ошибка"), wxOK | wxICON_WARNING);
        return false;
    }
    
    if (m_garageCombo->GetSelection() == wxNOT_FOUND) {
        wxMessageBox(wxT("Выберите гаражный бокс"), wxT("Ошибка"), wxOK | wxICON_WARNING);
        return false;
    }
    
    wxDateTime start = m_startDate->GetValue();
    wxDateTime end = m_endDate->GetValue();
    
    if (!start.IsValid() || !end.IsValid()) {
        wxMessageBox(wxT("Выберите даты аренды"), wxT("Ошибка"), wxOK | wxICON_WARNING);
        return false;
    }
    
    if (start > end) {
        wxMessageBox(wxT("Дата окончания не может быть раньше даты начала"), wxT("Ошибка"), wxOK | wxICON_WARNING);
        return false;
    }
    
    double monthlyPrice;
    m_monthlyPrice->GetValue().ToDouble(&monthlyPrice);
    if (monthlyPrice <= 0) {
        wxMessageBox(wxT("Укажите корректную стоимость аренды"), wxT("Ошибка"), wxOK | wxICON_WARNING);
        return false;
    }
    
    return true;
}

void NewAgreementFrame::OnSave(wxCommandEvent& event) {
    if (!ValidateForm()) return;
    
    int tenantIndex = m_tenantCombo->GetSelection();
    int garageIndex = m_garageCombo->GetSelection();
    
    int tenantId = m_tenantIds[tenantIndex];
    int garageId = m_garageIds[garageIndex];
    
    wxString startDate = m_startDate->GetValue().FormatISODate();
    wxString endDate = m_endDate->GetValue().FormatISODate();
    
    double monthlyPrice;
    m_monthlyPrice->GetValue().ToDouble(&monthlyPrice);
    
    double totalAmount;
    m_totalAmount->GetValue().ToDouble(&totalAmount);
    
    if (m_db->AddAgreement(m_contractNumber->GetValue(), tenantId, garageId,
                            startDate, endDate, monthlyPrice, totalAmount)) {
        wxMessageBox(wxT("Договор аренды успешно создан!"), wxT("Успех"), wxOK | wxICON_INFORMATION);
        Close();
    } else {
        wxMessageBox(wxT("Ошибка при сохранении договора"), wxT("Ошибка"), wxOK | wxICON_ERROR);
    }
}

void NewAgreementFrame::OnCancel(wxCommandEvent& event) {
    Close();
}