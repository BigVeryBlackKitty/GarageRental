// AllGaragesFrame.cpp
#include "AllGaragesFrame.h"

AllGaragesFrame::AllGaragesFrame(wxWindow* parent, DatabaseManager* db)
    : wxFrame(parent, wxID_ANY, wxT("Список гаражей"), wxDefaultPosition, wxSize(900, 500)), m_db(db) {
    
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    
    m_listCtrl = new wxListCtrl(this, wxID_ANY, wxDefaultPosition, wxDefaultSize,
                                 wxLC_REPORT | wxLC_SINGLE_SEL);
    
    m_listCtrl->AppendColumn("ID", wxLIST_FORMAT_LEFT, 50);
    m_listCtrl->AppendColumn(wxT("Номер"), wxLIST_FORMAT_LEFT, 100);
    m_listCtrl->AppendColumn(wxT("Местоположение"), wxLIST_FORMAT_LEFT, 150);
    m_listCtrl->AppendColumn(wxT("Ширина (м)"), wxLIST_FORMAT_LEFT, 80);
    m_listCtrl->AppendColumn(wxT("Высота (м)"), wxLIST_FORMAT_LEFT, 80);
    m_listCtrl->AppendColumn(wxT("Статус"), wxLIST_FORMAT_LEFT, 100);
    
    mainSizer->Add(m_listCtrl, 1, wxEXPAND | wxALL, 10);
    SetSizer(mainSizer);
    
    LoadData();
    Bind(wxEVT_CLOSE_WINDOW, &AllGaragesFrame::OnClose, this);
}

void AllGaragesFrame::LoadData() {
    m_listCtrl->DeleteAllItems();
    
    sqlite3* db = m_db->GetDB();
    if (!db) return;
    
    sqlite3_stmt* stmt;
    const char* sql = "SELECT id, personal_numbers, location, width_garage, height_garage, status_garage FROM Garage";
    
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        int index = 0;
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            int id = sqlite3_column_int(stmt, 0);
            wxString number = wxString::FromUTF8((const char*)sqlite3_column_text(stmt, 1));
            wxString location = wxString::FromUTF8((const char*)sqlite3_column_text(stmt, 2));
            double width = sqlite3_column_double(stmt, 3);
            double height = sqlite3_column_double(stmt, 4);
            int status = sqlite3_column_int(stmt, 5);
            
            wxString statusStr;
            switch(status) {
                case 1: statusStr = wxT("Свободен"); break;
                case 2: statusStr = wxT("Занят"); break;
                case 3: statusStr = wxT("Ремонт"); break;
                default: statusStr = wxT("Неизвестно");
            }
            
            long itemIndex = m_listCtrl->InsertItem(index, wxString::Format("%d", id));
            m_listCtrl->SetItem(itemIndex, 1, number);
            m_listCtrl->SetItem(itemIndex, 2, location);
            m_listCtrl->SetItem(itemIndex, 3, wxString::Format("%.2f", width));
            m_listCtrl->SetItem(itemIndex, 4, wxString::Format("%.2f", height));
            m_listCtrl->SetItem(itemIndex, 5, statusStr);
            m_listCtrl->SetItemData(itemIndex, id);
            index++;
        }
        sqlite3_finalize(stmt);
    }
}

void AllGaragesFrame::OnClose(wxCloseEvent& event) {
    Destroy();
}