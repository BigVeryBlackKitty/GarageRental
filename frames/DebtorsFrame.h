// DebtorsFrame.h
#pragma once

#include <wx/wx.h>
#include <wx/listctrl.h>
#include "../database/DatabaseManager.h"

class DebtorsFrame : public wxFrame {
public:
    DebtorsFrame(wxWindow* parent, DatabaseManager* db);
    
private:
    DatabaseManager* m_db;
    wxListCtrl* m_listCtrl;
    wxStaticText* m_totalDebtText;
    
    void LoadData();
    void OnClose(wxCloseEvent& event);
};