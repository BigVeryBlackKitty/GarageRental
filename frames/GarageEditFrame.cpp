// GarageEditFrame.cpp
#include "GarageEditFrame.h"
#include <wx/msgdlg.h>

GarageEditFrame::GarageEditFrame(wxWindow* parent, DatabaseManager* db, int garageId)
    : wxFrame(parent, wxID_ANY, garageId == -1 ? wxT("Добавление гаража") : wxT("Редактирование гаража"),
              wxDefaultPosition, wxSize(500, 400)), m_db(db), m_garageId(garageId) {
    
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    wxFlexGridSizer* grid = new wxFlexGridSizer(2, 10, 10);
    
    // Номер бокса
    grid->Add(new wxStaticText(this, wxID_ANY, wxT("Номер бокса:*")));
    m_numberCtrl = new wxTextCtrl(this, wxID_ANY);
    grid->Add(m_numberCtrl, 1, wxEXPAND);
    
    // Местоположение
    grid->Add(new wxStaticText(this, wxID_ANY, wxT("Местоположение:")));
    m_locationCtrl = new wxTextCtrl(this, wxID_ANY);
    grid->Add(m_locationCtrl, 1, wxEXPAND);
    
    // Ширина
    grid->Add(new wxStaticText(this, wxID_ANY, wxT("Ширина (м):")));
    m_widthCtrl = new wxTextCtrl(this, wxID_ANY, "0.0");
    grid->Add(m_widthCtrl, 1, wxEXPAND);
    
    // Высота
    grid->Add(new wxStaticText(this, wxID_ANY, wxT("Высота (м):")));
    m_heightCtrl = new wxTextCtrl(this, wxID_ANY, "0.0");
    grid->Add(m_heightCtrl, 1, wxEXPAND);
    
    // Статус
    grid->Add(new wxStaticText(this, wxID_ANY, wxT("Статус:")));
    m_statusChoice = new wxChoice(this, wxID_ANY);
    m_statusChoice->Append(wxT("Свободен"));
    m_statusChoice->Append(wxT("Занят"));
    m_statusChoice->Append(wxT("Ремонт"));
    m_statusChoice->SetSelection(0);
    grid->Add(m_statusChoice, 1, wxEXPAND);
    
    mainSizer->Add(grid, 1, wxEXPAND | wxALL, 10);
    
    // Кнопки
    wxBoxSizer* btnSizer = new wxBoxSizer(wxHORIZONTAL);
    m_saveBtn = new wxButton(this, wxID_ANY, wxT("Сохранить"));
    m_cancelBtn = new wxButton(this, wxID_ANY, wxT("Отмена"));
    btnSizer->Add(m_saveBtn, 0, wxALL, 5);
    btnSizer->Add(m_cancelBtn, 0, wxALL, 5);
    mainSizer->Add(btnSizer, 0, wxALIGN_CENTER | wxALL, 10);
    
    SetSizer(mainSizer);
    
    if (m_garageId != -1) {
        LoadGarageData();
    }
    
    m_saveBtn->Bind(wxEVT_BUTTON, &GarageEditFrame::OnSave, this);
    m_cancelBtn->Bind(wxEVT_BUTTON, &GarageEditFrame::OnCancel, this);
}

void GarageEditFrame::LoadGarageData() {
    sqlite3* db = m_db->GetDB();
    if (!db) return;
    
    sqlite3_stmt* stmt;
    wxString sql = wxString::Format(
        "SELECT personal_numbers, location, width_garage, height_garage, status_garage "
        "FROM Garage WHERE id=%d", m_garageId);
    
    if (sqlite3_prepare_v2(db, sql.utf8_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            m_numberCtrl->SetValue(wxString::FromUTF8((const char*)sqlite3_column_text(stmt, 0)));
            m_locationCtrl->SetValue(wxString::FromUTF8((const char*)sqlite3_column_text(stmt, 1)));
            m_widthCtrl->SetValue(wxString::Format("%.2f", sqlite3_column_double(stmt, 2)));
            m_heightCtrl->SetValue(wxString::Format("%.2f", sqlite3_column_double(stmt, 3)));
            int status = sqlite3_column_int(stmt, 4);
            m_statusChoice->SetSelection(status - 1);
        }
        sqlite3_finalize(stmt);
    }
}

bool GarageEditFrame::ValidateForm() {
    if (m_numberCtrl->GetValue().IsEmpty()) {
        wxMessageBox(wxT("Введите номер бокса"), wxT("Ошибка"), wxOK | wxICON_WARNING);
        return false;
    }
    
    double width, height;
    if (!m_widthCtrl->GetValue().ToDouble(&width) || width < 0) {
        wxMessageBox(wxT("Введите корректную ширину"), wxT("Ошибка"), wxOK | wxICON_WARNING);
        return false;
    }
    
    if (!m_heightCtrl->GetValue().ToDouble(&height) || height < 0) {
        wxMessageBox(wxT("Введите корректную высоту"), wxT("Ошибка"), wxOK | wxICON_WARNING);
        return false;
    }
    
    return true;
}

void GarageEditFrame::SaveNewGarage() {
    double width, height;
    m_widthCtrl->GetValue().ToDouble(&width);
    m_heightCtrl->GetValue().ToDouble(&height);
    int status = m_statusChoice->GetSelection() + 1;
    
    if (m_db->AddGarage(
        m_numberCtrl->GetValue(),
        m_locationCtrl->GetValue(),
        width, height, status
    )) {
        wxMessageBox(wxT("Гараж успешно добавлен!"), wxT("Успех"), wxOK | wxICON_INFORMATION);
        Close();
    } else {
        wxMessageBox(wxT("Ошибка при добавлении гаража"), wxT("Ошибка"), wxOK | wxICON_ERROR);
    }
}

void GarageEditFrame::UpdateExistingGarage() {
    double width, height;
    m_widthCtrl->GetValue().ToDouble(&width);
    m_heightCtrl->GetValue().ToDouble(&height);
    int status = m_statusChoice->GetSelection() + 1;
    
    if (m_db->UpdateGarage(
        m_garageId,
        m_numberCtrl->GetValue(),
        m_locationCtrl->GetValue(),
        width, height, status
    )) {
        wxMessageBox(wxT("Данные гаража обновлены!"), wxT("Успех"), wxOK | wxICON_INFORMATION);
        Close();
    } else {
        wxMessageBox(wxT("Ошибка при обновлении данных"), wxT("Ошибка"), wxOK | wxICON_ERROR);
    }
}

void GarageEditFrame::OnSave(wxCommandEvent& event) {
    if (!ValidateForm()) return;
    
    if (m_garageId == -1) {
        SaveNewGarage();
    } else {
        UpdateExistingGarage();
    }
}

void GarageEditFrame::OnCancel(wxCommandEvent& event) {
    Close();
}