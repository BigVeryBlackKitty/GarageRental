// LeaseAgreement.h
#pragma once

#include <wx/wx.h>

struct LeaseAgreement {
    int id;
    wxString contract_number;
    int tenant_id;
    int garage_id;
    wxString start_date;
    wxString end_date;
    double monthly_price;
    double total_amount;
    int status;
    wxString created_at;
    
    wxString GetStatusString() const {
        switch(status) {
            case 1: return wxT("Активен");
            case 0: return wxT("Завершён");
            case 2: return wxT("Расторгнут");
            default: return wxT("Неизвестно");
        }
    }
};