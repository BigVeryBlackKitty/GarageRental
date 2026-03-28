// AllPaymentsFrame.h
#pragma once

#include <wx/wx.h>
#include <wx/listctrl.h>
#include "../database/DatabaseManager.h"

class AllPaymentsFrame : public wxFrame {
public:
    AllPaymentsFrame(wxWindow* parent, DatabaseManager* db);
    
private:
    DatabaseManager* m_db;
    wxListCtrl* m_listCtrl;
    
    void LoadData();
    void OnClose(wxCloseEvent& event);
};