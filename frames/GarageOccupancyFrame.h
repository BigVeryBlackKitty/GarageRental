// GarageOccupancyFrame.h
#pragma once

#include <wx/wx.h>
#include <wx/grid.h>
#include "../database/DatabaseManager.h"

class GarageOccupancyFrame : public wxFrame {
public:
    GarageOccupancyFrame(wxWindow* parent, DatabaseManager* db);
    
private:
    DatabaseManager* m_db;
    wxGrid* m_grid;
    wxStaticText* m_summaryText;
    
    void LoadData();
    void OnClose(wxCloseEvent& event);
};