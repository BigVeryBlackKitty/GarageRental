// TenantEditFrame.h
#pragma once

#include <wx/wx.h>
#include "../database/DatabaseManager.h"

class TenantEditFrame : public wxFrame {
public:
    TenantEditFrame(wxWindow* parent, DatabaseManager* db, int tenantId = -1);
    
private:
    DatabaseManager* m_db;
    int m_tenantId;
    
    wxTextCtrl* m_surnameCtrl;
    wxTextCtrl* m_nameCtrl;
    wxTextCtrl* m_patronymicCtrl;
    wxTextCtrl* m_phoneCtrl;
    wxTextCtrl* m_emailCtrl;
    wxButton* m_saveBtn;
    wxButton* m_cancelBtn;
    
    void OnSave(wxCommandEvent& event);
    void OnCancel(wxCommandEvent& event);
    void LoadTenantData();
    bool ValidateForm();
    void SaveNewTenant();
    void UpdateExistingTenant();
};