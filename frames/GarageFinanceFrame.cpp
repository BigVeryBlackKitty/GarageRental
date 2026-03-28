// GarageFinanceFrame.cpp
#include "GarageFinanceFrame.h"

GarageFinanceFrame::GarageFinanceFrame(wxWindow* parent, DatabaseManager* db)
    : wxFrame(parent, wxID_ANY, wxT("Финансовая статистика гаражей"), wxDefaultPosition, wxSize(700, 500)), m_db(db) {
    
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    
    m_listCtrl = new wxListCtrl(this, wxID_ANY, wxDefaultPosition, wxDefaultSize,
                                 wxLC_REPORT | wxLC_SINGLE_SEL);
    
    m_listCtrl->AppendColumn("ID", wxLIST_FORMAT_LEFT, 50);
    m_listCtrl->AppendColumn(wxT("Номер гаража"), wxLIST_FORMAT_LEFT, 120);
    m_listCtrl->AppendColumn(wxT("Общий доход"), wxLIST_FORMAT_LEFT, 150);
    m_listCtrl->AppendColumn(wxT("Кол-во аренд"), wxLIST_FORMAT_LEFT, 100);
    
    mainSizer->Add(m_listCtrl, 1, wxEXPAND | wxALL, 10);
    
    wxBoxSizer* totalSizer = new wxBoxSizer(wxHORIZONTAL);
    totalSizer->Add(new wxStaticText(this, wxID_ANY, wxT("Общий доход со всех гаражей:")), 0, wxRIGHT, 10);
    m_totalIncomeText = new wxStaticText(this, wxID_ANY, "0.00 ₽");
    totalSizer->Add(m_totalIncomeText, 0);
    mainSizer->Add(totalSizer, 0, wxALL | wxALIGN_RIGHT, 10);
    
    SetSizer(mainSizer);
    
    LoadData();
    Bind(wxEVT_CLOSE_WINDOW, &GarageFinanceFrame::OnClose, this);
}

void GarageFinanceFrame::LoadData() {
    m_listCtrl->DeleteAllItems();
    
    std::vector<std::vector<wxString>> data = m_db->GetGarageFinance();
    double totalIncome = 0;
    
    int index = 0;
    for (const auto& row : data) {
        double income = 0;
        row[2].ToDouble(&income);
        totalIncome += income;
        
        long itemIndex = m_listCtrl->InsertItem(index, row[0]);
        m_listCtrl->SetItem(itemIndex, 1, row[1]);
        m_listCtrl->SetItem(itemIndex, 2, wxString::Format("%.2f ₽", income));
        m_listCtrl->SetItem(itemIndex, 3, row[3]);
        index++;
    }
    
    m_totalIncomeText->SetLabel(wxString::Format("%.2f ₽", totalIncome));
}

void GarageFinanceFrame::OnClose(wxCloseEvent& event) {
    Destroy();
}