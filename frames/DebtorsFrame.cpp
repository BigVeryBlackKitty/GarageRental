// DebtorsFrame.cpp
#include "DebtorsFrame.h"

DebtorsFrame::DebtorsFrame(wxWindow* parent, DatabaseManager* db)
    : wxFrame(parent, wxID_ANY, wxT("Просмотр должников"), wxDefaultPosition, wxSize(800, 500)), m_db(db) {
    
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    
    m_listCtrl = new wxListCtrl(this, wxID_ANY, wxDefaultPosition, wxDefaultSize,
                                 wxLC_REPORT | wxLC_SINGLE_SEL);
    
    m_listCtrl->AppendColumn("ID", wxLIST_FORMAT_LEFT, 50);
    m_listCtrl->AppendColumn(wxT("ФИО"), wxLIST_FORMAT_LEFT, 200);
    m_listCtrl->AppendColumn(wxT("Телефон"), wxLIST_FORMAT_LEFT, 120);
    m_listCtrl->AppendColumn("Email", wxLIST_FORMAT_LEFT, 150);
    m_listCtrl->AppendColumn(wxT("Задолженность"), wxLIST_FORMAT_LEFT, 120);
    
    mainSizer->Add(m_listCtrl, 1, wxEXPAND | wxALL, 10);
    
    // Итоговая сумма долга
    wxBoxSizer* totalSizer = new wxBoxSizer(wxHORIZONTAL);
    totalSizer->Add(new wxStaticText(this, wxID_ANY, wxT("Общая задолженность:")), 0, wxRIGHT, 10);
    m_totalDebtText = new wxStaticText(this, wxID_ANY, "0.00 ₽");
    totalSizer->Add(m_totalDebtText, 0);
    mainSizer->Add(totalSizer, 0, wxALL | wxALIGN_RIGHT, 10);
    
    SetSizer(mainSizer);
    
    LoadData();
    Bind(wxEVT_CLOSE_WINDOW, &DebtorsFrame::OnClose, this);
}

void DebtorsFrame::LoadData() {
    m_listCtrl->DeleteAllItems();
    
    sqlite3* db = m_db->GetDB();
    if (!db) return;
    
    std::vector<std::vector<wxString>> debtors = m_db->GetDebtors();
    double totalDebt = 0;
    
    int index = 0;
    for (const auto& row : debtors) {
        double debt = 0;
        row[4].ToDouble(&debt);
        totalDebt += debt;
        
        long itemIndex = m_listCtrl->InsertItem(index, row[0]);
        m_listCtrl->SetItem(itemIndex, 1, row[1]);
        m_listCtrl->SetItem(itemIndex, 2, row[2]);
        m_listCtrl->SetItem(itemIndex, 3, row[3]);
        m_listCtrl->SetItem(itemIndex, 4, wxString::Format("%.2f ₽", debt));
        index++;
    }
    
    m_totalDebtText->SetLabel(wxString::Format("%.2f ₽", totalDebt));
    if (totalDebt > 0) {
        m_totalDebtText->SetForegroundColour(*wxRED);
    }
}

void DebtorsFrame::OnClose(wxCloseEvent& event) {
    Destroy();
}