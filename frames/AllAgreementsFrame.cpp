// AllAgreementsFrame.cpp
#include "AllAgreementsFrame.h"

AllAgreementsFrame::AllAgreementsFrame(wxWindow* parent, DatabaseManager* db)
    : wxFrame(parent, wxID_ANY, wxT("Список договоров аренды"), wxDefaultPosition, wxSize(1000, 600)), m_db(db) {
    
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    
    m_listCtrl = new wxListCtrl(this, wxID_ANY, wxDefaultPosition, wxDefaultSize,
                                 wxLC_REPORT | wxLC_SINGLE_SEL);
    
    m_listCtrl->AppendColumn("№ договора", wxLIST_FORMAT_LEFT, 120);
    m_listCtrl->AppendColumn(wxT("Арендатор"), wxLIST_FORMAT_LEFT, 200);
    m_listCtrl->AppendColumn(wxT("Гараж"), wxLIST_FORMAT_LEFT, 80);
    m_listCtrl->AppendColumn(wxT("Начало"), wxLIST_FORMAT_LEFT, 100);
    m_listCtrl->AppendColumn(wxT("Окончание"), wxLIST_FORMAT_LEFT, 100);
    m_listCtrl->AppendColumn(wxT("Сумма"), wxLIST_FORMAT_LEFT, 100);
    m_listCtrl->AppendColumn(wxT("Статус"), wxLIST_FORMAT_LEFT, 100);
    
    mainSizer->Add(m_listCtrl, 1, wxEXPAND | wxALL, 10);
    SetSizer(mainSizer);
    
    LoadData();
    Bind(wxEVT_CLOSE_WINDOW, &AllAgreementsFrame::OnClose, this);
}

void AllAgreementsFrame::LoadData() {
    m_listCtrl->DeleteAllItems();
    
    sqlite3* db = m_db->GetDB();
    if (!db) return;
    
    sqlite3_stmt* stmt;
    const char* sql = 
        "SELECT la.personal_numbers, t.surname || ' ' || t.name, g.personal_numbers, "
        "la.start_date, la.end_date, la.total_amount, la.status "
        "FROM Lease_Agreement la "
        "JOIN Tenant t ON t.id = la.tenant_id "
        "JOIN Garage g ON g.id = la.garage_id "
        "ORDER BY la.created_at DESC";
    
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        int index = 0;
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            wxString contractNum = wxString::FromUTF8((const char*)sqlite3_column_text(stmt, 0));
            wxString tenant = wxString::FromUTF8((const char*)sqlite3_column_text(stmt, 1));
            wxString garage = wxString::FromUTF8((const char*)sqlite3_column_text(stmt, 2));
            wxString startDate = wxString::FromUTF8((const char*)sqlite3_column_text(stmt, 3));
            wxString endDate = wxString::FromUTF8((const char*)sqlite3_column_text(stmt, 4));
            double amount = sqlite3_column_double(stmt, 5);
            int status = sqlite3_column_int(stmt, 6);
            
            wxString statusStr = status == 1 ? wxT("Активен") : (status == 0 ? wxT("Завершён") : wxT("Расторгнут"));
            
            long itemIndex = m_listCtrl->InsertItem(index, contractNum);
            m_listCtrl->SetItem(itemIndex, 1, tenant);
            m_listCtrl->SetItem(itemIndex, 2, garage);
            m_listCtrl->SetItem(itemIndex, 3, startDate);
            m_listCtrl->SetItem(itemIndex, 4, endDate);
            m_listCtrl->SetItem(itemIndex, 5, wxString::Format("%.2f ₽", amount));
            m_listCtrl->SetItem(itemIndex, 6, statusStr);
            index++;
        }
        sqlite3_finalize(stmt);
    }
}

void AllAgreementsFrame::OnClose(wxCloseEvent& event) {
    Destroy();
}