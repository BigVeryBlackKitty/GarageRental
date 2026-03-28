// GarageFinanceFrame.h
#pragma once

#include <wx/wx.h>
#include <wx/listctrl.h>
#include "../database/DatabaseManager.h"

class GarageFinanceFrame : public wxFrame {
public:
    GarageFinanceFrame(wxWindow* parent, DatabaseManager* db);
    
private:
    DatabaseManager* m_db;
    wxListCtrl* m_listCtrl;
    wxStaticText* m_totalIncomeText;
    
    void LoadData();
    void OnClose(wxCloseEvent& event);
};