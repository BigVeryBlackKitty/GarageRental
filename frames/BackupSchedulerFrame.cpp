// frames/BackupSchedulerFrame.cpp
#include "BackupSchedulerFrame.h"
#include <wx/msgdlg.h>
#include <wx/config.h>

BackupSchedulerFrame::BackupSchedulerFrame(wxWindow* parent, DatabaseManager* db)
    : wxFrame(parent, wxID_ANY, wxT("Настройка автоматического резервного копирования"),
        wxDefaultPosition, wxSize(550, 450)), m_db(db) {

    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    // Интервал
    wxStaticBoxSizer* intervalSizer = new wxStaticBoxSizer(wxVERTICAL, this, wxT("Расписание"));

    wxFlexGridSizer* grid = new wxFlexGridSizer(2, 10, 10);
    grid->Add(new wxStaticText(this, wxID_ANY, wxT("Интервал:")), 0, wxALIGN_CENTER_VERTICAL);

    m_intervalChoice = new wxChoice(this, wxID_ANY);
    m_intervalChoice->Append(wxT("Каждый час"));
    m_intervalChoice->Append(wxT("Каждые 6 часов"));
    m_intervalChoice->Append(wxT("Каждые 12 часов"));
    m_intervalChoice->Append(wxT("Каждый день"));
    m_intervalChoice->Append(wxT("Каждые 3 дня"));
    m_intervalChoice->Append(wxT("Каждую неделю"));
    m_intervalChoice->Append(wxT("Каждый месяц"));
    m_intervalChoice->SetSelection(3);
    grid->Add(m_intervalChoice, 1, wxEXPAND);

    intervalSizer->Add(grid, 0, wxEXPAND | wxALL, 10);

    wxStaticText* infoText = new wxStaticText(this, wxID_ANY,
        wxT("Автоматически будет создано и храниться последние 3 резервные копии.\n")
        wxT("Старые копии будут автоматически удаляться."));
    infoText->SetForegroundColour(*wxBLUE);
    intervalSizer->Add(infoText, 0, wxALL | wxALIGN_CENTER, 10);

    mainSizer->Add(intervalSizer, 0, wxEXPAND | wxALL, 10);

    // Папка
    wxStaticBoxSizer* dirSizer = new wxStaticBoxSizer(wxVERTICAL, this, wxT("Папка для резервных копий"));

    wxBoxSizer* dirBox = new wxBoxSizer(wxHORIZONTAL);
    dirBox->Add(new wxStaticText(this, wxID_ANY, wxT("Папка:")), 0, wxALIGN_CENTER | wxRIGHT, 10);
    m_backupDirPicker = new wxDirPickerCtrl(this, wxID_ANY, wxGetCwd(),
        wxT("Выберите папку"), wxDefaultPosition, wxSize(350, -1));
    dirBox->Add(m_backupDirPicker, 1, wxEXPAND);
    dirSizer->Add(dirBox, 0, wxEXPAND | wxALL, 10);

    mainSizer->Add(dirSizer, 0, wxEXPAND | wxALL, 10);

    // Статус
    wxStaticBoxSizer* statusSizer = new wxStaticBoxSizer(wxVERTICAL, this, wxT("Статус"));

    m_enableAutoBackup = new wxCheckBox(this, wxID_ANY, wxT("Включить автоматическое резервное копирование"));
    statusSizer->Add(m_enableAutoBackup, 0, wxALL, 10);

    m_statusText = new wxStaticText(this, wxID_ANY, wxT(""));
    statusSizer->Add(m_statusText, 0, wxALL | wxALIGN_CENTER, 5);

    mainSizer->Add(statusSizer, 0, wxEXPAND | wxALL, 10);

    // Кнопки
    wxBoxSizer* btnSizer = new wxBoxSizer(wxHORIZONTAL);
    m_createNowBtn = new wxButton(this, wxID_ANY, wxT("Создать копию сейчас"));
    m_saveBtn = new wxButton(this, wxID_ANY, wxT("Сохранить настройки"));
    m_closeBtn = new wxButton(this, wxID_ANY, wxT("Закрыть"));

    btnSizer->Add(m_createNowBtn, 0, wxALL, 5);
    btnSizer->Add(m_saveBtn, 0, wxALL, 5);
    btnSizer->Add(m_closeBtn, 0, wxALL, 5);
    mainSizer->Add(btnSizer, 0, wxALIGN_CENTER | wxALL, 10);

    SetSizer(mainSizer);

    LoadSettings();

    m_saveBtn->Bind(wxEVT_BUTTON, &BackupSchedulerFrame::OnSave, this);
    m_closeBtn->Bind(wxEVT_BUTTON, &BackupSchedulerFrame::OnClose, this);
    m_createNowBtn->Bind(wxEVT_BUTTON, &BackupSchedulerFrame::OnCreateNow, this);
    m_enableAutoBackup->Bind(wxEVT_CHECKBOX, &BackupSchedulerFrame::OnEnableChanged, this);
}

void BackupSchedulerFrame::LoadSettings() {
    wxConfigBase* config = wxConfigBase::Get();

    int interval = config->Read(wxT("Backup/Interval"), 24);
    wxString dir = config->Read(wxT("Backup/Directory"), wxGetCwd());
    bool enabled = config->Read(wxT("Backup/Enabled"), false);

    if (interval <= 1) m_intervalChoice->SetSelection(0);
    else if (interval <= 6) m_intervalChoice->SetSelection(1);
    else if (interval <= 12) m_intervalChoice->SetSelection(2);
    else if (interval <= 24) m_intervalChoice->SetSelection(3);
    else if (interval <= 72) m_intervalChoice->SetSelection(4);
    else if (interval <= 168) m_intervalChoice->SetSelection(5);
    else m_intervalChoice->SetSelection(6);

    m_backupDirPicker->SetPath(dir);
    m_enableAutoBackup->SetValue(enabled);

    UpdateStatus();
}

void BackupSchedulerFrame::SaveSettings() {
    wxConfigBase* config = wxConfigBase::Get();

    int intervalHours = 24;
    switch (m_intervalChoice->GetSelection()) {
    case 0: intervalHours = 1; break;
    case 1: intervalHours = 6; break;
    case 2: intervalHours = 12; break;
    case 3: intervalHours = 24; break;
    case 4: intervalHours = 72; break;
    case 5: intervalHours = 168; break;
    case 6: intervalHours = 720; break;
    }

    config->Write(wxT("Backup/Interval"), intervalHours);
    config->Write(wxT("Backup/Directory"), m_backupDirPicker->GetPath());
    config->Write(wxT("Backup/Enabled"), m_enableAutoBackup->IsChecked());
    config->Flush();

    if (m_enableAutoBackup->IsChecked()) {
        m_db->StartAutoBackup(intervalHours, m_backupDirPicker->GetPath());
    }
    else {
        m_db->StopAutoBackup();
    }

    UpdateStatus();
    wxMessageBox(wxT("Настройки сохранены"), wxT("Успех"), wxOK | wxICON_INFORMATION);
}

void BackupSchedulerFrame::UpdateStatus() {
    if (m_db->IsAutoBackupEnabled()) {
        int interval = m_db->GetAutoBackupInterval();
        wxString intervalStr;
        if (interval < 24) {
            intervalStr = wxString::Format(wxT("%d часов"), interval);
        }
        else if (interval == 24) {
            intervalStr = wxT("1 день");
        }
        else if (interval < 168) {
            intervalStr = wxString::Format(wxT("%d дней"), interval / 24);
        }
        else {
            intervalStr = wxString::Format(wxT("%d недель"), interval / 168);
        }
        m_statusText->SetLabel(wxString::Format(wxT("Автокопирование ВКЛЮЧЕНО (каждые %s)"), intervalStr));
        m_statusText->SetForegroundColour(*wxGREEN);
    }
    else {
        m_statusText->SetLabel(wxT("Автокопирование ОТКЛЮЧЕНО"));
        m_statusText->SetForegroundColour(*wxRED);
    }
}

void BackupSchedulerFrame::OnEnableChanged(wxCommandEvent& event) {
    UpdateStatus();
}

void BackupSchedulerFrame::OnSave(wxCommandEvent& event) {
    SaveSettings();
}

void BackupSchedulerFrame::OnClose(wxCommandEvent& event) {
    Close();
}

void BackupSchedulerFrame::OnCreateNow(wxCommandEvent& event) {
    wxString backupDir = m_backupDirPicker->GetPath();
    if (backupDir.IsEmpty()) {
        wxMessageBox(wxT("Выберите папку для резервной копии"), wxT("Ошибка"), wxOK | wxICON_WARNING);
        return;
    }

    if (m_db->BackupWithRotation(backupDir, 3)) {
        wxMessageBox(wxT("Резервная копия успешно создана!"), wxT("Успех"), wxOK | wxICON_INFORMATION);
    }
    else {
        wxMessageBox(wxT("Ошибка при создании резервной копии"), wxT("Ошибка"), wxOK | wxICON_ERROR);
    }
}