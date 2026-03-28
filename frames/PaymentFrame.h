// PaymentFrame.h
#pragma once

#include <wx/wx.h>
#include <wx/datectrl.h>
#include "../database/DatabaseManager.h"

class PaymentFrame : public wxFrame {
public:
    PaymentFrame(wxWindow* parent, DatabaseManager* db);
    
private:
    DatabaseManager* m_db;
    
    wxComboBox* m_agreementCombo;
    wxStaticText* m_tenantInfo;
    wxStaticText* m_debtInfo;
    wxTextCtrl* m_amountCtrl;
    wxDatePickerCtrl* m_paymentDate;
    wxChoice* m_paymentType;
    wxTextCtrl* m_receiptCtrl;
    wxButton* m_payBtn;
    wxButton* m_cancelBtn;
    
    std::vector<int> m_agreementIds;
    std::vector<double> m_debts;
    
    void OnAgreementSelected(wxCommandEvent& event);
    void OnPay(wxCommandEvent& event);
    void OnCancel(wxCommandEvent& event);
    void LoadActiveAgreements();
    void LoadAgreementInfo(int agreementId);
    bool ValidateForm();
};