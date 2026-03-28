// GarageEditFrame.h
#pragma once

#include <wx/wx.h>
#include "../database/DatabaseManager.h"

class GarageEditFrame : public wxFrame {
public:
    GarageEditFrame(wxWindow* parent, DatabaseManager* db, int garageId = -1);
    
private:
    DatabaseManager* m_db;
    int m_garageId;
    
    wxTextCtrl* m_numberCtrl;
    wxTextCtrl* m_locationCtrl;
    wxTextCtrl* m_widthCtrl;
    wxTextCtrl* m_heightCtrl;
    wxChoice* m_statusChoice;
    wxButton* m_saveBtn;
    wxButton* m_cancelBtn;
    
    void OnSave(wxCommandEvent& event);
    void OnCancel(wxCommandEvent& event);
    void LoadGarageData();
    bool ValidateForm();
    void SaveNewGarage();
    void UpdateExistingGarage();
};