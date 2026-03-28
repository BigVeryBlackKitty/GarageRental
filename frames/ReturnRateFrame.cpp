// ReturnRateFrame.cpp
#include "ReturnRateFrame.h"

ReturnRateFrame::ReturnRateFrame(wxWindow* parent, DatabaseManager* db)
    : wxFrame(parent, wxID_ANY, wxT("Процент возврата платежей"), wxDefaultPosition, wxSize(400, 200)), m_db(db) {
    
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    
    wxBoxSizer* rateSizer = new wxBoxSizer(wxHORIZONTAL);
    rateSizer->Add(new wxStaticText(this, wxID_ANY, wxT("Процент успешных платежей:")), 0, wxRIGHT, 10);
    m_rateText = new wxStaticText(this, wxID_ANY, "0%");
    rateSizer->Add(m_rateText, 0);
    mainSizer->Add(rateSizer, 0, wxALL | wxALIGN_CENTER, 20);
    
    m_gauge = new wxGauge(this, wxID_ANY, 100, wxDefaultPosition, wxSize(300, 30));
    mainSizer->Add(m_gauge, 0, wxALL | wxALIGN_CENTER, 10);
    
    SetSizer(mainSizer);
    
    LoadData();
    Bind(wxEVT_CLOSE_WINDOW, &ReturnRateFrame::OnClose, this);
}

void ReturnRateFrame::LoadData() {
    double rate = m_db->GetReturnRate();
    m_rateText->SetLabel(wxString::Format("%.1f%%", rate));
    m_gauge->SetValue((int)rate);
}

void ReturnRateFrame::OnClose(wxCloseEvent& event) {
    Destroy();
}