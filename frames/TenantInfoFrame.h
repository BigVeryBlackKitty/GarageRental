// TenantInfoFrame.h
#pragma once

#include <wx/wx.h>
#include <wx/listctrl.h>
#include "../database/DatabaseManager.h"

class TenantInfoFrame : public wxFrame {
public:
    TenantInfoFrame(wxWindow* parent, DatabaseManager* db);
    
private:
    DatabaseManager* m_db;
    wxComboBox* m_tenantCombo;
    wxTextCtrl* m_surnameCtrl;
    wxTextCtrl* m_nameCtrl;
    wxTextCtrl* m_patronymicCtrl;
    wxTextCtrl* m_phoneCtrl;
    wxTextCtrl* m_emailCtrl;
    wxListCtrl* m_agreementList;
    wxListCtrl* m_paymentList;
    wxStaticText* m_debtText;
    
    std::vector<int> m_tenantIds;
    
    void OnTenantSelected(wxCommandEvent& event);
    void LoadTenants();
    void LoadTenantInfo(int tenantId);
    void LoadAgreements(int tenantId);
    void LoadPayments(int tenantId);
    void CalculateDebt(int tenantId);
};