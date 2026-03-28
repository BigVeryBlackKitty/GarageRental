// GarageInfoFrame.h
#pragma once

#include <wx/wx.h>
#include <wx/listctrl.h>
#include "../database/DatabaseManager.h"

class GarageInfoFrame : public wxFrame {
public:
    GarageInfoFrame(wxWindow* parent, DatabaseManager* db);
    
private:
    DatabaseManager* m_db;
    wxComboBox* m_garageCombo;
    wxTextCtrl* m_numberCtrl;
    wxTextCtrl* m_locationCtrl;
    wxTextCtrl* m_widthCtrl;
    wxTextCtrl* m_heightCtrl;
    wxStaticText* m_statusText;
    wxListCtrl* m_historyList;
    
    std::vector<int> m_garageIds;
    
    void OnGarageSelected(wxCommandEvent& event);
    void LoadGarages();
    void LoadGarageInfo(int garageId);
    void LoadRentalHistory(int garageId);
};