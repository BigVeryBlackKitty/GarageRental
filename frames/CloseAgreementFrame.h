// CloseAgreementFrame.h
#pragma once

#include <wx/wx.h>
#include <wx/listctrl.h>
#include "../database/DatabaseManager.h"

class CloseAgreementFrame : public wxFrame {
public:
    CloseAgreementFrame(wxWindow* parent, DatabaseManager* db);
    
private:
    DatabaseManager* m_db;
    wxComboBox* m_agreementCombo;
    wxStaticText* m_infoText;
    wxButton* m_closeBtn;
    wxButton* m_cancelBtn;
    
    std::vector<int> m_agreementIds;
    
    void OnAgreementSelected(wxCommandEvent& event);
    void OnCloseAgreement(wxCommandEvent& event);
    void OnCancel(wxCommandEvent& event);
    void LoadActiveAgreements();
    void LoadAgreementInfo(int agreementId);
};