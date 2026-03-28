// GarageInfoFrame.cpp
#include "GarageInfoFrame.h"

GarageInfoFrame::GarageInfoFrame(wxWindow* parent, DatabaseManager* db)
    : wxFrame(parent, wxID_ANY, wxT("Информация о гараже"), wxDefaultPosition, wxSize(800, 600)), m_db(db) {
    
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    
    // Выбор гаража
    wxBoxSizer* selectSizer = new wxBoxSizer(wxHORIZONTAL);
    selectSizer->Add(new wxStaticText(this, wxID_ANY, wxT("Выберите гараж:")), 0, wxALIGN_CENTER | wxRIGHT, 10);
    m_garageCombo = new wxComboBox(this, wxID_ANY, "", wxDefaultPosition, wxSize(200, -1), 0, nullptr, wxCB_READONLY);
    selectSizer->Add(m_garageCombo, 0, wxEXPAND);
    mainSizer->Add(selectSizer, 0, wxALL, 10);
    
    // Характеристики
    wxStaticBoxSizer* infoSizer = new wxStaticBoxSizer(wxVERTICAL, this, wxT("Характеристики"));
    wxFlexGridSizer* grid = new wxFlexGridSizer(2, 10, 10);
    
    grid->Add(new wxStaticText(this, wxID_ANY, wxT("Номер бокса:")), 0, wxALIGN_RIGHT);
    m_numberCtrl = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
    grid->Add(m_numberCtrl, 1, wxEXPAND);
    
    grid->Add(new wxStaticText(this, wxID_ANY, wxT("Местоположение:")), 0, wxALIGN_RIGHT);
    m_locationCtrl = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
    grid->Add(m_locationCtrl, 1, wxEXPAND);
    
    grid->Add(new wxStaticText(this, wxID_ANY, wxT("Ширина (м):")), 0, wxALIGN_RIGHT);
    m_widthCtrl = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
    grid->Add(m_widthCtrl, 1, wxEXPAND);
    
    grid->Add(new wxStaticText(this, wxID_ANY, wxT("Высота (м):")), 0, wxALIGN_RIGHT);
    m_heightCtrl = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
    grid->Add(m_heightCtrl, 1, wxEXPAND);
    
    grid->Add(new wxStaticText(this, wxID_ANY, wxT("Статус:")), 0, wxALIGN_RIGHT);
    m_statusText = new wxStaticText(this, wxID_ANY, "");
    grid->Add(m_statusText, 1, wxEXPAND);
    
    infoSizer->Add(grid, 1, wxEXPAND | wxALL, 10);
    mainSizer->Add(infoSizer, 0, wxEXPAND | wxALL, 10);
    
    // История аренды
    wxStaticBoxSizer* historySizer = new wxStaticBoxSizer(wxVERTICAL, this, wxT("История аренды"));
    m_historyList = new wxListCtrl(this, wxID_ANY, wxDefaultPosition, wxDefaultSize,
                                    wxLC_REPORT | wxLC_SINGLE_SEL);
    m_historyList->AppendColumn(wxT("Арендатор"), wxLIST_FORMAT_LEFT, 200);
    m_historyList->AppendColumn(wxT("Начало"), wxLIST_FORMAT_LEFT, 100);
    m_historyList->AppendColumn(wxT("Окончание"), wxLIST_FORMAT_LEFT, 100);
    m_historyList->AppendColumn(wxT("Статус"), wxLIST_FORMAT_LEFT, 100);
    historySizer->Add(m_historyList, 1, wxEXPAND | wxALL, 5);
    mainSizer->Add(historySizer, 1, wxEXPAND | wxALL, 10);
    
    SetSizer(mainSizer);
    
    LoadGarages();
    m_garageCombo->Bind(wxEVT_COMBOBOX, &GarageInfoFrame::OnGarageSelected, this);
}

void GarageInfoFrame::LoadGarages() {
    m_garageCombo->Clear();
    m_garageIds.clear();
    
    sqlite3* db = m_db->GetDB();
    if (!db) return;
    
    sqlite3_stmt* stmt;
    const char* sql = "SELECT id, personal_numbers, location FROM Garage ORDER BY personal_numbers";
    
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
        wxCommandEvent evt;
        OnGarageSelected(evt);
    }
}

void GarageInfoFrame::OnGarageSelected(wxCommandEvent& event) {
    int idx = m_garageCombo->GetSelection();
    if (idx == wxNOT_FOUND) return;
    
    int garageId = m_garageIds[idx];
    LoadGarageInfo(garageId);
    LoadRentalHistory(garageId);
}

void GarageInfoFrame::LoadGarageInfo(int garageId) {
    sqlite3* db = m_db->GetDB();
    if (!db) return;
    
    sqlite3_stmt* stmt;
    wxString sql = wxString::Format(
        "SELECT personal_numbers, location, width_garage, height_garage, status_garage "
        "FROM Garage WHERE id=%d", garageId);
    
    if (sqlite3_prepare_v2(db, sql.utf8_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            m_numberCtrl->SetValue(wxString::FromUTF8((const char*)sqlite3_column_text(stmt, 0)));
            m_locationCtrl->SetValue(wxString::FromUTF8((const char*)sqlite3_column_text(stmt, 1)));
            m_widthCtrl->SetValue(wxString::Format("%.2f м", sqlite3_column_double(stmt, 2)));
            m_heightCtrl->SetValue(wxString::Format("%.2f м", sqlite3_column_double(stmt, 3)));
            int status = sqlite3_column_int(stmt, 4);
            
            wxString statusStr;
            switch(status) {
                case 1: statusStr = wxT("Свободен"); break;
                case 2: statusStr = wxT("Занят"); break;
                case 3: statusStr = wxT("Ремонт"); break;
                default: statusStr = wxT("Неизвестно");
            }
            m_statusText->SetLabel(statusStr);
        }
        sqlite3_finalize(stmt);
    }
}

void GarageInfoFrame::LoadRentalHistory(int garageId) {
    m_historyList->DeleteAllItems();
    
    sqlite3* db = m_db->GetDB();
    if (!db) return;
    
    sqlite3_stmt* stmt;
    wxString sql = wxString::Format(
        "SELECT t.surname || ' ' || t.name || ' ' || t.patronymic, "
        "la.start_date, la.end_date, la.status "
        "FROM Lease_Agreement la "
        "JOIN Tenant t ON t.id = la.tenant_id "
        "WHERE la.garage_id=%d "
        "ORDER BY la.start_date DESC", garageId);
    
    if (sqlite3_prepare_v2(db, sql.utf8_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        int index = 0;
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            wxString tenant = wxString::FromUTF8((const char*)sqlite3_column_text(stmt, 0));
            wxString startDate = wxString::FromUTF8((const char*)sqlite3_column_text(stmt, 1));
            wxString endDate = wxString::FromUTF8((const char*)sqlite3_column_text(stmt, 2));
            int status = sqlite3_column_int(stmt, 3);
            
            wxString statusStr = status == 1 ? wxT("Активен") : (status == 0 ? wxT("Завершён") : wxT("Расторгнут"));
            
            long itemIndex = m_historyList->InsertItem(index, tenant);
            m_historyList->SetItem(itemIndex, 1, startDate);
            m_historyList->SetItem(itemIndex, 2, endDate);
            m_historyList->SetItem(itemIndex, 3, statusStr);
            index++;
        }
        sqlite3_finalize(stmt);
    }
}