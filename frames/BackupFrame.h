// BackupFrame.h
#pragma once

#include <wx/wx.h>
#include <wx/filepicker.h>
#include "../database/DatabaseManager.h"

class BackupFrame : public wxFrame {
public:
    BackupFrame(wxWindow* parent, DatabaseManager* db);

private:
    DatabaseManager* m_db;

    wxDirPickerCtrl* m_backupDirPicker;
    wxTextCtrl* m_backupNameCtrl;
    wxStaticText* m_currentDbPathText;
    wxStaticText* m_backupSizeText;
    wxGauge* m_progressGauge;
    wxButton* m_createBackupBtn;
    wxButton* m_cancelBtn;

    void OnCreateBackup(wxCommandEvent& event);
    void OnCancel(wxCommandEvent& event);
    void OnDirectoryChanged(wxFileDirPickerEvent& event);
    void UpdateBackupInfo();
    wxString GenerateBackupFileName();
    void ShowBackupResult(bool success, const wxString& backupPath);
};