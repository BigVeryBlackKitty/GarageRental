// ReturnRateFrame.h
#pragma once

#include <wx/wx.h>
#include "../database/DatabaseManager.h"

class ReturnRateFrame : public wxFrame {
public:
    ReturnRateFrame(wxWindow* parent, DatabaseManager* db);
    
private:
    DatabaseManager* m_db;
    wxStaticText* m_rateText;
    wxGauge* m_gauge;
    
    void LoadData();
    void OnClose(wxCloseEvent& event);
};