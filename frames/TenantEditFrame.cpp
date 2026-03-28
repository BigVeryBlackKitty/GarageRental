// TenantEditFrame.cpp
#include "TenantEditFrame.h"
#include <wx/msgdlg.h>

TenantEditFrame::TenantEditFrame(wxWindow* parent, DatabaseManager* db, int tenantId)
    : wxFrame(parent, wxID_ANY, tenantId == -1 ? wxT("Добавление арендатора") : wxT("Редактирование арендатора"),
              wxDefaultPosition, wxSize(500, 400)), m_db(db), m_tenantId(tenantId) {
    
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    wxFlexGridSizer* grid = new wxFlexGridSizer(2, 10, 10);
    
    // Фамилия
    grid->Add(new wxStaticText(this, wxID_ANY, wxT("Фамилия:*")));
    m_surnameCtrl = new wxTextCtrl(this, wxID_ANY);
    grid->Add(m_surnameCtrl, 1, wxEXPAND);
    
    // Имя
    grid->Add(new wxStaticText(this, wxID_ANY, wxT("Имя:*")));
    m_nameCtrl = new wxTextCtrl(this, wxID_ANY);
    grid->Add(m_nameCtrl, 1, wxEXPAND);
    
    // Отчество
    grid->Add(new wxStaticText(this, wxID_ANY, wxT("Отчество:")));
    m_patronymicCtrl = new wxTextCtrl(this, wxID_ANY);
    grid->Add(m_patronymicCtrl, 1, wxEXPAND);
    
    // Телефон
    grid->Add(new wxStaticText(this, wxID_ANY, wxT("Телефон:*")));
    m_phoneCtrl = new wxTextCtrl(this, wxID_ANY);
    grid->Add(m_phoneCtrl, 1, wxEXPAND);
    
    // Email
    grid->Add(new wxStaticText(this, wxID_ANY, "Email:"));
    m_emailCtrl = new wxTextCtrl(this, wxID_ANY);
    grid->Add(m_emailCtrl, 1, wxEXPAND);
    
    mainSizer->Add(grid, 1, wxEXPAND | wxALL, 10);
    
    // Кнопки
    wxBoxSizer* btnSizer = new wxBoxSizer(wxHORIZONTAL);
    m_saveBtn = new wxButton(this, wxID_ANY, wxT("Сохранить"));
    m_cancelBtn = new wxButton(this, wxID_ANY, wxT("Отмена"));
    btnSizer->Add(m_saveBtn, 0, wxALL, 5);
    btnSizer->Add(m_cancelBtn, 0, wxALL, 5);
    mainSizer->Add(btnSizer, 0, wxALIGN_CENTER | wxALL, 10);
    
    SetSizer(mainSizer);
    
    // Загрузка данных для редактирования
    if (m_tenantId != -1) {
        LoadTenantData();
    }
    
    // События
    m_saveBtn->Bind(wxEVT_BUTTON, &TenantEditFrame::OnSave, this);
    m_cancelBtn->Bind(wxEVT_BUTTON, &TenantEditFrame::OnCancel, this);
}

void TenantEditFrame::LoadTenantData() {
    sqlite3* db = m_db->GetDB();
    if (!db) return;
    
    sqlite3_stmt* stmt;
    wxString sql = wxString::Format("SELECT surname, name, patronymic, phone_num, email FROM Tenant WHERE id=%d", m_tenantId);
    
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

bool TenantEditFrame::ValidateForm() {
    if (m_surnameCtrl->GetValue().IsEmpty()) {
        wxMessageBox(wxT("Введите фамилию"), wxT("Ошибка"), wxOK | wxICON_WARNING);
        return false;
    }
    if (m_nameCtrl->GetValue().IsEmpty()) {
        wxMessageBox(wxT("Введите имя"), wxT("Ошибка"), wxOK | wxICON_WARNING);
        return false;
    }
    if (m_phoneCtrl->GetValue().IsEmpty()) {
        wxMessageBox(wxT("Введите телефон"), wxT("Ошибка"), wxOK | wxICON_WARNING);
        return false;
    }
    return true;
}

void TenantEditFrame::SaveNewTenant() {
    if (m_db->AddTenant(
        m_surnameCtrl->GetValue(),
        m_nameCtrl->GetValue(),
        m_patronymicCtrl->GetValue(),
        m_phoneCtrl->GetValue(),
        m_emailCtrl->GetValue()
    )) {
        wxMessageBox(wxT("Арендатор успешно добавлен!"), wxT("Успех"), wxOK | wxICON_INFORMATION);
        Close();
    } else {
        wxMessageBox(wxT("Ошибка при добавлении арендатора"), wxT("Ошибка"), wxOK | wxICON_ERROR);
    }
}

void TenantEditFrame::UpdateExistingTenant() {
    if (m_db->UpdateTenant(
        m_tenantId,
        m_surnameCtrl->GetValue(),
        m_nameCtrl->GetValue(),
        m_patronymicCtrl->GetValue(),
        m_phoneCtrl->GetValue(),
        m_emailCtrl->GetValue()
    )) {
        wxMessageBox(wxT("Данные арендатора обновлены!"), wxT("Успех"), wxOK | wxICON_INFORMATION);
        Close();
    } else {
        wxMessageBox(wxT("Ошибка при обновлении данных"), wxT("Ошибка"), wxOK | wxICON_ERROR);
    }
}

void TenantEditFrame::OnSave(wxCommandEvent& event) {
    if (!ValidateForm()) return;
    
    if (m_tenantId == -1) {
        SaveNewTenant();
    } else {
        UpdateExistingTenant();
    }
}

void TenantEditFrame::OnCancel(wxCommandEvent& event) {
    Close();
}