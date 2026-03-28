// GarageOccupancyFrame.cpp
#include "GarageOccupancyFrame.h"

GarageOccupancyFrame::GarageOccupancyFrame(wxWindow* parent, DatabaseManager* db)
    : wxFrame(parent, wxID_ANY, wxT("Занятость гаражей"), wxDefaultPosition, wxSize(500, 300)), m_db(db) {
    
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    
    m_grid = new wxGrid(this, wxID_ANY);
    m_grid->CreateGrid(4, 2);
    m_grid->SetColLabelValue(0, wxT("Показатель"));
    m_grid->SetColLabelValue(1, wxT("Количество"));
    m_grid->SetRowLabelSize(0);
    
    m_grid->SetCellValue(0, 0, wxT("Свободные боксы"));
    m_grid->SetCellValue(1, 0, wxT("Занятые боксы"));
    m_grid->SetCellValue(2, 0, wxT("В ремонте"));
    m_grid->SetCellValue(3, 0, wxT("Всего боксов"));
    
    for (int i = 0; i < 4; i++) {
        m_grid->SetReadOnly(i, 0, true);
        m_grid->SetReadOnly(i, 1, true);
    }
    
    mainSizer->Add(m_grid, 1, wxEXPAND | wxALL, 10);
    
    m_summaryText = new wxStaticText(this, wxID_ANY, "");
    mainSizer->Add(m_summaryText, 0, wxALL | wxALIGN_CENTER, 10);
    
    SetSizer(mainSizer);
    
    LoadData();
    Bind(wxEVT_CLOSE_WINDOW, &GarageOccupancyFrame::OnClose, this);
}

void GarageOccupancyFrame::LoadData() {
    std::vector<std::vector<wxString>> data = m_db->GetGarageOccupancy();
    
    if (data.empty()) return;
    
    const auto& row = data[0];
    int free = wxAtoi(row[0]);
    int occupied = wxAtoi(row[1]);
    int repair = wxAtoi(row[2]);
    int total = wxAtoi(row[3]);
    
    m_grid->SetCellValue(0, 1, wxString::Format("%d", free));
    m_grid->SetCellValue(1, 1, wxString::Format("%d", occupied));
    m_grid->SetCellValue(2, 1, wxString::Format("%d", repair));
    m_grid->SetCellValue(3, 1, wxString::Format("%d", total));
    
    double occupancyRate = total > 0 ? (double)occupied / total * 100 : 0;
    m_summaryText->SetLabel(wxString::Format(wxT("Загрузка: %.1f%%"), occupancyRate));
}

void GarageOccupancyFrame::OnClose(wxCloseEvent& event) {
    Destroy();
}