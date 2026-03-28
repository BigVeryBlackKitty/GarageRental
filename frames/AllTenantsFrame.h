// AllTenantsFrame.h
#pragma once

#include <wx/wx.h>
#include <wx/listctrl.h>
#include "../database/DatabaseManager.h"

class AllTenantsFrame : public wxFrame {
public:
    AllTenantsFrame(wxWindow* parent, DatabaseManager* db);
    
private:
    DatabaseManager* m_db;
    wxListCtrl* m_listCtrl;
    
    void LoadData();
    void OnClose(wxCloseEvent& event);
};