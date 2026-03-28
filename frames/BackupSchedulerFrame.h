// frames/BackupSchedulerFrame.h
#pragma once

#include <wx/wx.h>
#include <wx/spinctrl.h>
#include <wx/filepicker.h>
#include "../database/DatabaseManager.h"

class BackupSchedulerFrame : public wxFrame {
public:
    BackupSchedulerFrame(wxWindow* parent, DatabaseManager* db);

private:
    DatabaseManager* m_db;

    wxChoice* m_intervalChoice;
    wxDirPickerCtrl* m_backupDirPicker;
    wxCheckBox* m_enableAutoBackup;
    wxStaticText* m_statusText;
    wxButton* m_saveBtn;
    wxButton* m_closeBtn;
    wxButton* m_createNowBtn;

    void OnSave(wxCommandEvent& event);
    void OnClose(wxCommandEvent& event);
    void OnCreateNow(wxCommandEvent& event);
    void OnEnableChanged(wxCommandEvent& event);
    void LoadSettings();
    void SaveSettings();
    void UpdateStatus();
};