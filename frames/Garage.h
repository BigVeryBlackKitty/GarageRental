// Garage.h
#pragma once

#include <wx/wx.h>

struct Garage {
    int id;
    wxString personal_numbers;
    wxString location;
    double width_garage;
    double height_garage;
    int status_garage;
    wxString created_at;
    
    wxString GetStatusString() const {
        switch(status_garage) {
            case 1: return wxT("Свободен");
            case 2: return wxT("Занят");
            case 3: return wxT("Ремонт");
            default: return wxT("Неизвестно");
        }
    }
};