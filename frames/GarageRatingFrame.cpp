// GarageRatingFrame.cpp
#include "GarageRatingFrame.h"

GarageRatingFrame::GarageRatingFrame(wxWindow* parent, DatabaseManager* db)
    : wxFrame(parent, wxID_ANY, wxT("Рейтинг гаражей"), wxDefaultPosition, wxSize(600, 500)), m_db(db) {
    
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    
    m_listCtrl = new wxListCtrl(this, wxID_ANY, wxDefaultPosition, wxDefaultSize,
                                 wxLC_REPORT | wxLC_SINGLE_SEL);
    
    m_listCtrl->AppendColumn(wxT("Место"), wxLIST_FORMAT_LEFT, 60);
    m_listCtrl->AppendColumn(wxT("Номер гаража"), wxLIST_FORMAT_LEFT, 120);
    m_listCtrl->AppendColumn(wxT("Доход"), wxLIST_FORMAT_LEFT, 150);
    m_listCtrl->AppendColumn(wxT("Кол-во аренд"), wxLIST_FORMAT_LEFT, 100);
    
    mainSizer->Add(m_listCtrl, 1, wxEXPAND | wxALL, 10);
    
    SetSizer(mainSizer);
    
    LoadData();
    Bind(wxEVT_CLOSE_WINDOW, &GarageRatingFrame::OnClose, this);
}

void GarageRatingFrame::LoadData() {
    m_listCtrl->DeleteAllItems();
    
    std::vector<std::vector<wxString>> data = m_db->GetGarageRating();
    
    int index = 0;
    for (const auto& row : data) {
        long itemIndex = m_listCtrl->InsertItem(index, row[0]);
        m_listCtrl->SetItem(itemIndex, 1, row[1]);
        m_listCtrl->SetItem(itemIndex, 2, wxString::Format("%.2f ₽", wxAtof(row[2])));
        m_listCtrl->SetItem(itemIndex, 3, row[3]);
        index++;
    }
}

void GarageRatingFrame::OnClose(wxCloseEvent& event) {
    Destroy();
}