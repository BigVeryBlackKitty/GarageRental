// AllPaymentsFrame.cpp
#include "AllPaymentsFrame.h"

AllPaymentsFrame::AllPaymentsFrame(wxWindow* parent, DatabaseManager* db)
    : wxFrame(parent, wxID_ANY, wxT("История платежей"), wxDefaultPosition, wxSize(1000, 600)), m_db(db) {
    
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    
    m_listCtrl = new wxListCtrl(this, wxID_ANY, wxDefaultPosition, wxDefaultSize,
                                 wxLC_REPORT | wxLC_SINGLE_SEL);
    
    m_listCtrl->AppendColumn("№ квитанции", wxLIST_FORMAT_LEFT, 120);
    m_listCtrl->AppendColumn(wxT("Арендатор"), wxLIST_FORMAT_LEFT, 200);
    m_listCtrl->AppendColumn(wxT("Договор"), wxLIST_FORMAT_LEFT, 120);
    m_listCtrl->AppendColumn(wxT("Сумма"), wxLIST_FORMAT_LEFT, 100);
    m_listCtrl->AppendColumn(wxT("Дата"), wxLIST_FORMAT_LEFT, 100);
    m_listCtrl->AppendColumn(wxT("Тип"), wxLIST_FORMAT_LEFT, 100);
    m_listCtrl->AppendColumn(wxT("Статус"), wxLIST_FORMAT_LEFT, 100);
    
    mainSizer->Add(m_listCtrl, 1, wxEXPAND | wxALL, 10);
    SetSizer(mainSizer);
    
    LoadData();
    Bind(wxEVT_CLOSE_WINDOW, &AllPaymentsFrame::OnClose, this);
}

void AllPaymentsFrame::LoadData() {
    m_listCtrl->DeleteAllItems();
    
    sqlite3* db = m_db->GetDB();
    if (!db) return;
    
    sqlite3_stmt* stmt;
    const char* sql = 
        "SELECT p.receipt_number, t.surname || ' ' || t.name, "
        "la.personal_numbers, p.payment_amount, p.payment_date, "
        "p.payment_type, p.status_payment "
        "FROM Payment p "
        "JOIN Tenant t ON t.id = p.payer_id "
        "JOIN Lease_Agreement la ON la.id = p.agreement_id "
        "ORDER BY p.payment_date DESC";
    
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        int index = 0;
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            wxString receipt = wxString::FromUTF8((const char*)sqlite3_column_text(stmt, 0));
            wxString tenant = wxString::FromUTF8((const char*)sqlite3_column_text(stmt, 1));
            wxString contract = wxString::FromUTF8((const char*)sqlite3_column_text(stmt, 2));
            double amount = sqlite3_column_double(stmt, 3);
            wxString date = wxString::FromUTF8((const char*)sqlite3_column_text(stmt, 4));
            int type = sqlite3_column_int(stmt, 5);
            int status = sqlite3_column_int(stmt, 6);
            
            wxString typeStr = type == 1 ? wxT("Наличные") : (type == 2 ? wxT("Карта") : wxT("Перевод"));
            wxString statusStr = status == 1 ? wxT("Успешно") : wxT("Ошибка");
            
            long itemIndex = m_listCtrl->InsertItem(index, receipt);
            m_listCtrl->SetItem(itemIndex, 1, tenant);
            m_listCtrl->SetItem(itemIndex, 2, contract);
            m_listCtrl->SetItem(itemIndex, 3, wxString::Format("%.2f ₽", amount));
            m_listCtrl->SetItem(itemIndex, 4, date);
            m_listCtrl->SetItem(itemIndex, 5, typeStr);
            m_listCtrl->SetItem(itemIndex, 6, statusStr);
            index++;
        }
        sqlite3_finalize(stmt);
    }
}

void AllPaymentsFrame::OnClose(wxCloseEvent& event) {
    Destroy();
}