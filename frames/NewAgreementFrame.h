// NewAgreementFrame.h
#pragma once

#include <wx/wx.h>
#include <wx/datectrl.h>
#include "../database/DatabaseManager.h"

class NewAgreementFrame : public wxFrame {
public:
    NewAgreementFrame(wxWindow* parent, DatabaseManager* db);
    
private:
    DatabaseManager* m_db;
    
    wxTextCtrl* m_contractNumber;
    wxComboBox* m_tenantCombo;
    wxComboBox* m_garageCombo;
    wxDatePickerCtrl* m_startDate;
    wxDatePickerCtrl* m_endDate;
    wxTextCtrl* m_monthlyPrice;
    wxTextCtrl* m_totalAmount;
    wxButton* m_saveBtn;
    wxButton* m_cancelBtn;
    
    std::vector<int> m_tenantIds;
    std::vector<int> m_garageIds;
    
    void OnSave(wxCommandEvent& event);
    void OnCancel(wxCommandEvent& event);
    void OnCalculateTotal(wxCommandEvent& event);
    void OnGarageSelected(wxCommandEvent& event);
    void LoadTenants();
    void LoadFreeGarages();
    void GenerateContractNumber();
    void CalculateTotal();
    bool ValidateForm();
};