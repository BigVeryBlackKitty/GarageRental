// AllTenantsFrame.cpp
#include "AllTenantsFrame.h"

AllTenantsFrame::AllTenantsFrame(wxWindow* parent, DatabaseManager* db)
    : wxFrame(parent, wxID_ANY, wxT("Список арендаторов"), wxDefaultPosition, wxSize(800, 500)), m_db(db) {

    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    m_listCtrl = new wxListCtrl(this, wxID_ANY, wxDefaultPosition, wxDefaultSize,
                                 wxLC_REPORT | wxLC_SINGLE_SEL);

    m_listCtrl->AppendColumn("ID",         wxLIST_FORMAT_LEFT,  50);
    m_listCtrl->AppendColumn(wxT("Фамилия"),    wxLIST_FORMAT_LEFT, 150);
    m_listCtrl->AppendColumn(wxT("Имя"),        wxLIST_FORMAT_LEFT, 120);
    m_listCtrl->AppendColumn(wxT("Отчество"),   wxLIST_FORMAT_LEFT, 150);
    m_listCtrl->AppendColumn(wxT("Телефон"),    wxLIST_FORMAT_LEFT, 130);
    m_listCtrl->AppendColumn("Email",      wxLIST_FORMAT_LEFT, 180);

    mainSizer->Add(m_listCtrl, 1, wxEXPAND | wxALL, 10);
    SetSizer(mainSizer);

    LoadData();
    Bind(wxEVT_CLOSE_WINDOW, &AllTenantsFrame::OnClose, this);
}

void AllTenantsFrame::LoadData() {
    m_listCtrl->DeleteAllItems();

    sqlite3* db = m_db->GetDB();
    if (!db) return;

    sqlite3_stmt* stmt;
    const char* sql =
        "SELECT id, surname, name, patronymic, phone_num, email "
        "FROM Tenant ORDER BY surname, name";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        int index = 0;
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            int    id         = sqlite3_column_int(stmt, 0);
            wxString surname  = wxString::FromUTF8((const char*)sqlite3_column_text(stmt, 1));
            wxString name     = wxString::FromUTF8((const char*)sqlite3_column_text(stmt, 2));
            wxString patr     = wxString::FromUTF8((const char*)sqlite3_column_text(stmt, 3));
            wxString phone    = wxString::FromUTF8((const char*)sqlite3_column_text(stmt, 4));
            wxString email    = wxString::FromUTF8((const char*)sqlite3_column_text(stmt, 5));

            long item = m_listCtrl->InsertItem(index, wxString::Format("%d", id));
            m_listCtrl->SetItem(item, 1, surname);
            m_listCtrl->SetItem(item, 2, name);
            m_listCtrl->SetItem(item, 3, patr);
            m_listCtrl->SetItem(item, 4, phone);
            m_listCtrl->SetItem(item, 5, email);
            index++;
        }
        sqlite3_finalize(stmt);
    }
}

void AllTenantsFrame::OnClose(wxCloseEvent& event) {
    Destroy();
}
