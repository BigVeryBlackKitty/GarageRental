// Tenant.h
#pragma once

#include <wx/wx.h>

struct Tenant {
    int id;
    wxString surname;
    wxString name;
    wxString patronymic;
    wxString phone_num;
    wxString email;
    wxString created_at;
    int isOverdue;
    
    wxString GetFullName() const {
        return surname + " " + name + " " + patronymic;
    }
};