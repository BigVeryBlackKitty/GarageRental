// BackupFrame.cpp
#include "BackupFrame.h"
#include <wx/msgdlg.h>
#include <wx/filename.h>
#include <wx/datetime.h>
#include <wx/file.h>

BackupFrame::BackupFrame(wxWindow* parent, DatabaseManager* db)
    : wxFrame(parent, wxID_ANY, wxT("Резервное копирование базы данных"),
        wxDefaultPosition, wxSize(600, 450)), m_db(db) {

    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    // ========== Информация о текущей базе данных ==========
    wxStaticBoxSizer* infoSizer = new wxStaticBoxSizer(wxVERTICAL, this, wxT("Информация о базе данных"));

    wxString currentPath = m_db->GetDBPath();
    m_currentDbPathText = new wxStaticText(this, wxID_ANY,
        wxT("Текущая БД: ") + currentPath);
    infoSizer->Add(m_currentDbPathText, 0, wxALL, 10);

    // Размер базы данных
    wxFileName dbFile(currentPath);
    if (dbFile.FileExists()) {
        wxULongLong size = dbFile.GetSize();
        wxString sizeStr;
        if (size > 1024 * 1024) {
            sizeStr = wxString::Format(wxT("%.2f МБ"), size.ToDouble() / (1024 * 1024));
        }
        else if (size > 1024) {
            sizeStr = wxString::Format(wxT("%.2f КБ"), size.ToDouble() / 1024);
        }
        else {
            sizeStr = wxString::Format(wxT("%llu Б"), size.GetValue());
        }
        m_backupSizeText = new wxStaticText(this, wxID_ANY, wxT("Размер БД: ") + sizeStr);
        infoSizer->Add(m_backupSizeText, 0, wxALL, 10);
    }

    mainSizer->Add(infoSizer, 0, wxEXPAND | wxALL, 10);

    // ========== Параметры резервной копии ==========
    wxStaticBoxSizer* backupSizer = new wxStaticBoxSizer(wxVERTICAL, this, wxT("Параметры резервной копии"));

    wxBoxSizer* dirSizer = new wxBoxSizer(wxHORIZONTAL);
    dirSizer->Add(new wxStaticText(this, wxID_ANY, wxT("Папка для сохранения:")), 0, wxALIGN_CENTER | wxRIGHT, 10);
    m_backupDirPicker = new wxDirPickerCtrl(this, wxID_ANY, wxGetCwd(),
        wxT("Выберите папку для резервной копии"),
        wxDefaultPosition, wxSize(350, -1));
    dirSizer->Add(m_backupDirPicker, 1, wxEXPAND);
    backupSizer->Add(dirSizer, 0, wxEXPAND | wxALL, 10);

    // Имя файла резервной копии
    wxBoxSizer* nameSizer = new wxBoxSizer(wxHORIZONTAL);
    nameSizer->Add(new wxStaticText(this, wxID_ANY, wxT("Имя файла:")), 0, wxALIGN_CENTER | wxRIGHT, 10);
    m_backupNameCtrl = new wxTextCtrl(this, wxID_ANY, GenerateBackupFileName());
    nameSizer->Add(m_backupNameCtrl, 1, wxEXPAND);
    backupSizer->Add(nameSizer, 0, wxEXPAND | wxALL, 10);

    // Прогресс
    m_progressGauge = new wxGauge(this, wxID_ANY, 100, wxDefaultPosition, wxDefaultSize);
    m_progressGauge->SetValue(0);
    backupSizer->Add(m_progressGauge, 0, wxEXPAND | wxALL, 10);

    mainSizer->Add(backupSizer, 0, wxEXPAND | wxALL, 10);

    // ========== Предупреждение ==========
    wxStaticText* warningText = new wxStaticText(this, wxID_ANY,
        wxT("Рекомендуется создавать резервные копии перед важными изменениями.\n")
        wxT("Резервная копия содержит все данные: клиентов, договоры, платежи."));
    warningText->SetForegroundColour(*wxBLUE);
    mainSizer->Add(warningText, 0, wxALL | wxALIGN_CENTER, 10);

    // ========== Кнопки ==========
    wxBoxSizer* btnSizer = new wxBoxSizer(wxHORIZONTAL);
    m_createBackupBtn = new wxButton(this, wxID_ANY, wxT("Создать резервную копию"));
    m_cancelBtn = new wxButton(this, wxID_ANY, wxT("Закрыть"));
    btnSizer->Add(m_createBackupBtn, 0, wxALL, 5);
    btnSizer->Add(m_cancelBtn, 0, wxALL, 5);
    mainSizer->Add(btnSizer, 0, wxALIGN_CENTER | wxALL, 10);

    SetSizer(mainSizer);

    // ========== События ==========
    m_createBackupBtn->Bind(wxEVT_BUTTON, &BackupFrame::OnCreateBackup, this);
    m_cancelBtn->Bind(wxEVT_BUTTON, &BackupFrame::OnCancel, this);
    m_backupDirPicker->Bind(wxEVT_DIRPICKER_CHANGED, &BackupFrame::OnDirectoryChanged, this);

    UpdateBackupInfo();
}

wxString BackupFrame::GenerateBackupFileName() {
    wxDateTime now = wxDateTime::Now();
    wxString dateStr = now.Format(wxT("%Y-%m-%d_%H-%M-%S"));
    return wxString::Format(wxT("garage_rental_backup_%s.db"), dateStr);
}

void BackupFrame::UpdateBackupInfo() {
    wxFileName dbFile(m_db->GetDBPath());
    if (dbFile.FileExists()) {
        wxULongLong size = dbFile.GetSize();
        wxString sizeStr;
        if (size > 1024 * 1024) {
            sizeStr = wxString::Format(wxT("%.2f МБ"), size.ToDouble() / (1024 * 1024));
        }
        else if (size > 1024) {
            sizeStr = wxString::Format(wxT("%.2f КБ"), size.ToDouble() / 1024);
        }
        else {
            sizeStr = wxString::Format(wxT("%llu Б"), size.GetValue());
        }
        if (m_backupSizeText) {
            m_backupSizeText->SetLabel(wxT("Размер БД: ") + sizeStr);
        }
    }
}

void BackupFrame::OnCreateBackup(wxCommandEvent& event) {
    // Получаем выбранную папку
    wxString backupDir = m_backupDirPicker->GetPath();
    if (backupDir.IsEmpty()) {
        wxMessageBox(wxT("Выберите папку для сохранения резервной копии"),
            wxT("Ошибка"), wxOK | wxICON_WARNING);
        return;
    }

    // Получаем имя файла
    wxString backupName = m_backupNameCtrl->GetValue();
    if (backupName.IsEmpty()) {
        backupName = GenerateBackupFileName();
    }

    // Добавляем расширение .db если его нет
    if (!backupName.EndsWith(wxT(".db"))) {
        backupName += wxT(".db");
    }

    // Формируем полный путь
    wxString backupPath = backupDir + wxFileName::GetPathSeparator() + backupName;

    // Проверяем, существует ли уже такой файл
    if (wxFileExists(backupPath)) {
        int result = wxMessageBox(wxString::Format(
            wxT("Файл '%s' уже существует.\nПерезаписать?"), backupName),
            wxT("Подтверждение"), wxYES_NO | wxICON_QUESTION);
        if (result != wxYES) {
            return;
        }
    }

    // Показываем прогресс
    m_progressGauge->SetValue(50);
    m_createBackupBtn->Enable(false);
    this->SetCursor(wxCURSOR_WAIT);

    // Выполняем резервное копирование
    bool success = m_db->Backup(backupPath);

    m_progressGauge->SetValue(100);
    m_createBackupBtn->Enable(true);
    this->SetCursor(wxCURSOR_DEFAULT);

    // Показываем результат
    ShowBackupResult(success, backupPath);

    // Сбрасываем прогресс
    m_progressGauge->SetValue(0);
}

void BackupFrame::ShowBackupResult(bool success, const wxString& backupPath) {
    if (success) {
        wxFileName backupFile(backupPath);
        wxULongLong size = backupFile.GetSize();
        wxString sizeStr;
        if (size > 1024 * 1024) {
            sizeStr = wxString::Format(wxT("%.2f МБ"), size.ToDouble() / (1024 * 1024));
        }
        else if (size > 1024) {
            sizeStr = wxString::Format(wxT("%.2f КБ"), size.ToDouble() / 1024);
        }
        else {
            sizeStr = wxString::Format(wxT("%llu Б"), size.GetValue());
        }

        wxString message = wxString::Format(
            wxT("Резервная копия успешно создана!\n\n")
            wxT("Файл: %s\n")
            wxT("Размер: %s\n")
            wxT("Время создания: %s\n\n")
            wxT("Рекомендуется хранить копии в надёжном месте."),
            backupPath, sizeStr, wxDateTime::Now().Format(wxT("%H:%M:%S")));

        wxMessageBox(message, wxT("Успех"), wxOK | wxICON_INFORMATION);

        // Предлагаем открыть папку с копией
        int openFolder = wxMessageBox(wxT("Открыть папку с резервной копией?"),
            wxT("Открыть папку"), wxYES_NO | wxICON_QUESTION);
        if (openFolder == wxYES) {
            wxString dir = wxFileName(backupPath).GetPath();
            wxExecute(wxString::Format(wxT("explorer \"%s\""), dir));
        }

        // Генерируем новое имя для следующей копии
        m_backupNameCtrl->SetValue(GenerateBackupFileName());

    }
    else {
        wxMessageBox(wxT("Ошибка при создании резервной копии!\n\n")
            wxT("Возможные причины:\n")
            wxT("- Недостаточно места на диске\n")
            wxT("- Нет прав на запись в выбранную папку\n")
            wxT("- База данных повреждена"),
            wxT("Ошибка"), wxOK | wxICON_ERROR);
    }
}

void BackupFrame::OnDirectoryChanged(wxFileDirPickerEvent& event) {
    m_backupNameCtrl->SetValue(GenerateBackupFileName());
}

void BackupFrame::OnCancel(wxCommandEvent& event) {
    Close();
}