// main.cpp
#include <wx/wx.h>
#include <wx/stdpaths.h>
#include <wx/filename.h>
#include <locale.h>
#include "frames/MainFrame.h"
#include "database/DatabaseManager.h"

class GarageRentalApp : public wxApp {
public:
    virtual bool OnInit() override {
        // Установка русской локали
        setlocale(LC_ALL, "ru_RU.UTF-8");

        DatabaseManager* db = new DatabaseManager();

        // Получаем путь к папке, где находится EXE файл
        wxString exePath = wxStandardPaths::Get().GetExecutablePath();
        wxString exeDir = wxFileName(exePath).GetPath();
        wxString dbPath = exeDir + "/garage_rental.db";

        // Проверяем существование файла
        if (!wxFileExists(dbPath)) {
            wxMessageBox(wxString::Format(
                "Файл базы данных не найден!\n"
                "Искали: %s\n\n"
                "Убедитесь, что файл garage_rental.db находится в папке с программой.",
                dbPath), "Ошибка", wxOK | wxICON_ERROR);
            delete db;
            return false;
        }

        if (!db->Connect(dbPath)) {
            wxMessageBox("Не удалось подключиться к базе данных!",
                "Ошибка", wxOK | wxICON_ERROR);
            delete db;
            return false;
        }

        MainFrame* frame = new MainFrame(nullptr);
        frame->SetDatabaseManager(db);
        frame->Show(true);

        return true;
    }
};

wxIMPLEMENT_APP(GarageRentalApp);