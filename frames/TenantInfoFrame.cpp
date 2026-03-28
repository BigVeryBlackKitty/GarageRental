// TenantInfoFrame.cpp
#include "TenantInfoFrame.h"

TenantInfoFrame::TenantInfoFrame(wxWindow* parent, DatabaseManager* db)
    : wxFrame(parent, wxID_ANY, wxT("Информация об арендаторе"), wxDefaultPosition, wxSize(900, 700)), m_db(db) {
    
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    
    // Выбор арендатора
    wxBoxSizer* selectSizer = new wxBoxSizer(wxHORIZONTAL);
    selectSizer->Add(new wxStaticText(this, wxID_ANY, wxT("Выберите арендатора:")), 0, wxALIGN_CENTER | wxRIGHT, 10);
    m_tenantCombo = new wxComboBox(this, wxID_ANY, "", wxDefaultPosition, wxSize(300, -1), 0, nullptr, wxCB_READONLY);
    selectSizer->Add(m_tenantCombo, 0, wxEXPAND);
    mainSizer->Add(selectSizer, 0, wxALL, 10);
    
    // Личная информация
    wxStaticBoxSizer* infoSizer = new wxStaticBoxSizer(wxVERTICAL, this, wxT("Личная информация"));
    wxFlexGridSizer* grid = new wxFlexGridSizer(2, 10, 10);
    
    grid->Add(new wxStaticText(this, wxID_ANY, wxT("Фамилия:")), 0, wxALIGN_RIGHT);
    m_surnameCtrl = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
    grid->Add(m_surnameCtrl, 1, wxEXPAND);
    
    grid->Add(new wxStaticText(this, wxID_ANY, wxT("Имя:")), 0, wxALIGN_RIGHT);
    m_nameCtrl = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
    grid->Add(m_nameCtrl, 1, wxEXPAND);
    
    grid->Add(new wxStaticText(this, wxID_ANY, wxT("Отчество:")), 0, wxALIGN_RIGHT);
    m_patronymicCtrl = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
    grid->Add(m_patronymicCtrl, 1, wxEXPAND);
    
    grid->Add(new wxStaticText(this, wxID_ANY, wxT("Телефон:")), 0, wxALIGN_RIGHT);
    m_phoneCtrl = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
    grid->Add(m_phoneCtrl, 1, wxEXPAND);
    
    grid->Add(new wxStaticText(this, wxID_ANY, "Email:"), 0, wxALIGN_RIGHT);
    m_emailCtrl = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
    grid->Add(m_emailCtrl, 1, wxEXPAND);
    
    infoSizer->Add(grid, 1, wxEXPAND | wxALL, 10);
    mainSizer->Add(infoSizer, 0, wxEXPAND | wxALL, 10);
    
    // Долг
    wxBoxSizer* debtSizer = new wxBoxSizer(wxHORIZONTAL);
    debtSizer->Add(new wxStaticText(this, wxID_ANY, wxT("Задолженность:")), 0, wxRIGHT, 10);
    m_debtText = new wxStaticText(this, wxID_ANY, "0.00 ₽");
    debtSizer->Add(m_debtText, 0);
    mainSizer->Add(debtSizer, 0, wxALL, 10);
    
    // Договоры аренды
    wxStaticBoxSizer* agreementSizer = new wxStaticBoxSizer(wxVERTICAL, this, wxT("Договоры аренды"));
    m_agreementList = new wxListCtrl(this, wxID_ANY, wxDefaultPosition, wxDefaultSize,
                                      wxLC_REPORT | wxLC_SINGLE_SEL);
    m_agreementList->AppendColumn("№ договора", wxLIST_FORMAT_LEFT, 120);
    m_agreementList->AppendColumn(wxT("Гараж"), wxLIST_FORMAT_LEFT, 80);
    m_agreementList->AppendColumn(wxT("Начало"), wxLIST_FORMAT_LEFT, 100);
    m_agreementList->AppendColumn(wxT("Окончание"), wxLIST_FORMAT_LEFT, 100);
    m_agreementList->AppendColumn(wxT("Статус"), wxLIST_FORMAT_LEFT, 100);
    agreementSizer->Add(m_agreementList, 1, wxEXPAND | wxALL, 5);
    mainSizer->Add(agreementSizer, 1, wxEXPAND | wxALL, 10);
    
    // Платежи
    wxStaticBoxSizer* paymentSizer = new wxStaticBoxSizer(wxVERTICAL, this, wxT("История платежей"));
    m_paymentList = new wxListCtrl(this, wxID_ANY, wxDefaultPosition, wxDefaultSize,
                                    wxLC_REPORT | wxLC_SINGLE_SEL);
    m_paymentList->AppendColumn(wxT("Дата"), wxLIST_FORMAT_LEFT, 100);
    m_paymentList->AppendColumn(wxT("Сумма"), wxLIST_FORMAT_LEFT, 100);
    m_paymentList->AppendColumn(wxT("Тип"), wxLIST_FORMAT_LEFT, 100);
    m_paymentList->AppendColumn(wxT("Статус"), wxLIST_FORMAT_LEFT, 100);
    paymentSizer->Add(m_paymentList, 1, wxEXPAND | wxALL, 5);
    mainSizer->Add(paymentSizer, 1, wxEXPAND | wxALL, 10);
    
    SetSizer(mainSizer);
    
    LoadTenants();
    m_tenantCombo->Bind(wxEVT_COMBOBOX, &TenantInfoFrame::OnTenantSelected, this);
}

void TenantInfoFrame::LoadTenants() {
    m_tenantCombo->Clear();
    m_tenantIds.clear();
    
    sqlite3* db = m_db->GetDB();
    if (!db) return;
    
    sqlite3_stmt* stmt;
    const char* sql = "SELECT id, surname, name, patronymic FROM Tenant ORDER BY surname";
    
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            int id = sqlite3_column_int(stmt, 0);
            wxString name = wxString::Format("%s %s %s",
                wxString::FromUTF8((const char*)sqlite3_column_text(stmt, 1)),
                wxString::FromUTF8((const char*)sqlite3_column_text(stmt, 2)),
                wxString::FromUTF8((const char*)sqlite3_column_text(stmt, 3)));
            
            m_tenantCombo->Append(name);
            m_tenantIds.push_back(id);
        }
        sqlite3_finalize(stmt);
    }
    
    if (m_tenantCombo->GetCount() > 0) {
        m_tenantCombo->SetSelection(0);
        wxCommandEvent evt;
        OnTenantSelected(evt);
    }
}

void TenantInfoFrame::OnTenantSelected(wxCommandEvent& event) {
    int idx = m_tenantCombo->GetSelection();
    if (idx == wxNOT_FOUND) return;
    
    int tenantId = m_tenantIds[idx];
    LoadTenantInfo(tenantId);
    LoadAgreements(tenantId);
    LoadPayments(tenantId);
    CalculateDebt(tenantId);
}

void TenantInfoFrame::LoadTenantInfo(int tenantId) {
    sqlite3* db = m_db->GetDB();
    if (!db) return;
    
    sqlite3_stmt* stmt;
    wxString sql = wxString::Format("SELECT surname, name, patronymic, phone_num, email FROM Tenant WHERE id=%d", tenantId);
    
    if (sqlite3_prepare_v2(db, sql.utf8_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            m_surnameCtrl->SetValue(wxString::FromUTF8((const char*)sqlite3_column_text(stmt, 0)));
            m_nameCtrl->SetValue(wxString::FromUTF8((const char*)sqlite3_column_text(stmt, 1)));
            m_patronymicCtrl->SetValue(wxString::FromUTF8((const char*)sqlite3_column_text(stmt, 2)));
            m_phoneCtrl->SetValue(wxString::FromUTF8((const char*)sqlite3_column_text(stmt, 3)));
            m_emailCtrl->SetValue(wxString::FromUTF8((const char*)sqlite3_column_text(stmt, 4)));
        }
        sqlite3_finalize(stmt);
    }
}

void TenantInfoFrame::LoadAgreements(int tenantId) {
    m_agreementList->DeleteAllItems();
    
    sqlite3* db = m_db->GetDB();
    if (!db) return;
    
    sqlite3_stmt* stmt;
    wxString sql = wxString::Format(
        "SELECT la.personal_numbers, g.personal_numbers, la.start_date, la.end_date, la.status "
        "FROM Lease_Agreement la "
        "JOIN Garage g ON g.id = la.garage_id "
        "WHERE la.tenant_id=%d "
        "ORDER BY la.created_at DESC", tenantId);
    
    if (sqlite3_prepare_v2(db, sql.utf8_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        int index = 0;
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            wxString contractNum = wxString::FromUTF8((const char*)sqlite3_column_text(stmt, 0));
            wxString garageNum = wxString::FromUTF8((const char*)sqlite3_column_text(stmt, 1));
            wxString startDate = wxString::FromUTF8((const char*)sqlite3_column_text(stmt, 2));
            wxString endDate = wxString::FromUTF8((const char*)sqlite3_column_text(stmt, 3));
            int status = sqlite3_column_int(stmt, 4);
            
            wxString statusStr = status == 1 ? wxT("Активен") : (status == 0 ? wxT("Завершён") : wxT("Расторгнут"));
            
            long itemIndex = m_agreementList->InsertItem(index, contractNum);
            m_agreementList->SetItem(itemIndex, 1, garageNum);
            m_agreementList->SetItem(itemIndex, 2, startDate);
            m_agreementList->SetItem(itemIndex, 3, endDate);
            m_agreementList->SetItem(itemIndex, 4, statusStr);
            index++;
        }
        sqlite3_finalize(stmt);
    }
}

void TenantInfoFrame::LoadPayments(int tenantId) {
    m_paymentList->DeleteAllItems();
    
    sqlite3* db = m_db->GetDB();
    if (!db) return;
    
    sqlite3_stmt* stmt;
    wxString sql = wxString::Format(
        "SELECT payment_date, payment_amount, payment_type, status_payment "
        "FROM Payment WHERE payer_id=%d "
        "ORDER BY payment_date DESC", tenantId);
    
    if (sqlite3_prepare_v2(db, sql.utf8_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        int index = 0;
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            wxString date = wxString::FromUTF8((const char*)sqlite3_column_text(stmt, 0));
            double amount = sqlite3_column_double(stmt, 1);
            int type = sqlite3_column_int(stmt, 2);
            int status = sqlite3_column_int(stmt, 3);
            
            wxString typeStr = type == 1 ? wxT("Наличные") : (type == 2 ? wxT("Карта") : wxT("Перевод"));
            wxString statusStr = status == 1 ? wxT("Успешно") : wxT("Ошибка");
            
            long itemIndex = m_paymentList->InsertItem(index, date);
            m_paymentList->SetItem(itemIndex, 1, wxString::Format("%.2f ₽", amount));
            m_paymentList->SetItem(itemIndex, 2, typeStr);
            m_paymentList->SetItem(itemIndex, 3, statusStr);
            index++;
        }
        sqlite3_finalize(stmt);
    }
}

void TenantInfoFrame::CalculateDebt(int tenantId) {
    sqlite3* db = m_db->GetDB();
    if (!db) return;
    
    sqlite3_stmt* stmt;
    wxString sql = wxString::Format(
        "SELECT COALESCE(SUM(la.total_amount), 0) - COALESCE(SUM(p.payment_amount), 0) as debt "
        "FROM Tenant t "
        "LEFT JOIN Lease_Agreement la ON la.tenant_id = t.id AND la.status = 1 "
        "LEFT JOIN Payment p ON p.payer_id = t.id "
        "WHERE t.id = %d", tenantId);
    
    double debt = 0.0;
    if (sqlite3_prepare_v2(db, sql.utf8_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            debt = sqlite3_column_double(stmt, 0);
        }
        sqlite3_finalize(stmt);
    }
    
    m_debtText->SetLabel(wxString::Format("%.2f ₽", debt));
    if (debt > 0) {
        m_debtText->SetForegroundColour(*wxRED);
    } else {
        m_debtText->SetForegroundColour(*wxGREEN);
    }
}