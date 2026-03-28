// Payment.h
#pragma once

#include <wx/wx.h>

struct Payment {
    int id;
    wxString receipt_number;
    int payer_id;
    int agreement_id;
    double payment_amount;
    wxString payment_date;
    int payment_type;
    int status_payment;
    
    wxString GetPaymentTypeString() const {
        switch(payment_type) {
            case 1: return wxT("Наличные");
            case 2: return wxT("Карта");
            case 3: return wxT("Перевод");
            default: return wxT("Неизвестно");
        }
    }
    
    wxString GetStatusString() const {
        switch(status_payment) {
            case 1: return wxT("Успешно");
            case 0: return wxT("Ошибка");
            default: return wxT("Неизвестно");
        }
    }
};