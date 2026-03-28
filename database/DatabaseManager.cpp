// database/DatabaseManager.cpp
#include "DatabaseManager.h"
#include <wx/filename.h>
#include <wx/dir.h>
#include <wx/log.h>
#include <wx/file.h>
#include <algorithm>
#include <wx/msgdlg.h>

wxBEGIN_EVENT_TABLE(DatabaseManager, wxEvtHandler)
EVT_TIMER(wxID_ANY, DatabaseManager::OnAutoBackupTimer)
wxEND_EVENT_TABLE()

DatabaseManager::DatabaseManager()
    : m_db(nullptr), m_autoBackupTimer(nullptr),
    m_autoBackupEnabled(false), m_autoBackupInterval(24) {
}

DatabaseManager::~DatabaseManager() {
    StopAutoBackup();
    Disconnect();
}

bool DatabaseManager::Connect(const wxString& dbPath) {
    if (m_db) Disconnect();

    int rc = sqlite3_open(dbPath.utf8_str(), &m_db);
    if (rc != SQLITE_OK) {
        wxLogError(wxT("Не удалось открыть базу данных: %s"), sqlite3_errmsg(m_db));
        m_db = nullptr;
        return false;
    }

    m_dbPath = dbPath;
    return true;
}

void DatabaseManager::Disconnect() {
    if (m_db) {
        sqlite3_close(m_db);
        m_db = nullptr;
    }
}

bool DatabaseManager::ExecuteQuery(const wxString& sql) {
    if (!m_db) return false;

    char* errMsg = nullptr;
    int rc = sqlite3_exec(m_db, sql.utf8_str(), nullptr, nullptr, &errMsg);

    if (rc != SQLITE_OK) {
        wxLogError(wxT("SQL ошибка: %s"), errMsg);
        sqlite3_free(errMsg);
        return false;
    }
    return true;
}

sqlite3_stmt* DatabaseManager::PrepareStatement(const wxString& sql) {
    if (!m_db) return nullptr;

    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(m_db, sql.utf8_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        wxLogError(wxT("Ошибка подготовки запроса: %s"), sqlite3_errmsg(m_db));
        return nullptr;
    }
    return stmt;
}

// ========== Backup System ==========
bool DatabaseManager::Backup(const wxString& backupPath) {
    if (!m_db) {
        wxLogError(wxT("База данных не подключена"));
        return false;
    }

    sqlite3* backupDb = nullptr;

    int rc = sqlite3_open(backupPath.utf8_str(), &backupDb);
    if (rc != SQLITE_OK) {
        wxLogError(wxT("Не удалось создать файл резервной копии: %s"), sqlite3_errmsg(backupDb));
        sqlite3_close(backupDb);
        return false;
    }

    sqlite3_backup* backup = sqlite3_backup_init(backupDb, "main", m_db, "main");
    if (backup == nullptr) {
        wxLogError(wxT("Ошибка инициализации резервного копирования: %s"), sqlite3_errmsg(backupDb));
        sqlite3_close(backupDb);
        return false;
    }

    rc = sqlite3_backup_step(backup, -1);
    if (rc != SQLITE_DONE) {
        wxLogError(wxT("Ошибка при копировании базы данных: %s"), sqlite3_errmsg(backupDb));
        sqlite3_backup_finish(backup);
        sqlite3_close(backupDb);
        return false;
    }

    sqlite3_backup_finish(backup);
    sqlite3_close(backupDb);

    return true;
}

bool DatabaseManager::BackupWithRotation(const wxString& backupDir, int maxBackups) {
    wxDateTime now = wxDateTime::Now();
    wxString backupName = wxString::Format(wxT("backup_%s.db"),
        now.Format(wxT("%Y%m%d_%H%M%S")));
    wxString backupPath = backupDir + wxFileName::GetPathSeparator() + backupName;

    if (!Backup(backupPath)) {
        return false;
    }

    DeleteOldBackups(backupDir, maxBackups);
    return true;
}

std::vector<BackupInfo> DatabaseManager::GetBackupList(const wxString& backupDir) {
    std::vector<BackupInfo> backups;

    wxDir dir(backupDir);
    if (!dir.IsOpened()) return backups;

    wxString filename;
    bool cont = dir.GetFirst(&filename, wxT("backup_*.db"), wxDIR_FILES);

    while (cont) {
        wxString fullPath = backupDir + wxFileName::GetPathSeparator() + filename;
        wxFileName file(fullPath);

        BackupInfo info;
        info.path = fullPath;
        info.name = filename;
        info.size = file.GetSize().GetValue();

        // Парсим дату из имени файла: backup_20250328_143022.db
        wxString dateStr = filename.Mid(7, 15);
        if (dateStr.Length() == 15) {
            int year = wxAtoi(dateStr.Mid(0, 4));
            int month = wxAtoi(dateStr.Mid(4, 2));
            int day = wxAtoi(dateStr.Mid(6, 2));
            int hour = wxAtoi(dateStr.Mid(9, 2));
            int minute = wxAtoi(dateStr.Mid(11, 2));
            int second = wxAtoi(dateStr.Mid(13, 2));

            // Исправлено: преобразуем month (int) в wxDateTime::Month
            info.createdAt.Set(year, (wxDateTime::Month)(month - 1), day, hour, minute, second);
        }

        backups.push_back(info);
        cont = dir.GetNext(&filename);
    }

    std::sort(backups.begin(), backups.end(),
        [](const BackupInfo& a, const BackupInfo& b) {
            return a.createdAt > b.createdAt;
        });

    return backups;
}

bool DatabaseManager::RestoreFromBackup(const wxString& backupPath) {
    if (!wxFileExists(backupPath)) {
        wxLogError(wxT("Файл резервной копии не найден: %s"), backupPath);
        return false;
    }

    wxString currentBackup = m_dbPath + wxT(".current_backup");

    // Исправлено: используем wxRenameFile вместо wxFileName::RenameFile
    if (!wxRenameFile(m_dbPath, currentBackup)) {
        wxLogError(wxT("Не удалось создать резервную копию текущей базы данных"));
        return false;
    }

    if (!wxCopyFile(backupPath, m_dbPath, true)) {
        wxLogError(wxT("Не удалось восстановить базу данных"));
        wxRenameFile(currentBackup, m_dbPath);
        return false;
    }

    Disconnect();
    if (!Connect(m_dbPath)) {
        wxLogError(wxT("Не удалось переподключиться к базе данных"));
        wxRenameFile(currentBackup, m_dbPath);
        return false;
    }

    wxRemoveFile(currentBackup);
    return true;
}

bool DatabaseManager::DeleteOldBackups(const wxString& backupDir, int keepCount) {
    std::vector<BackupInfo> backups = GetBackupList(backupDir);

    if ((int)backups.size() <= keepCount) {
        return true;
    }

    for (size_t i = keepCount; i < backups.size(); i++) {
        wxRemoveFile(backups[i].path);
    }

    return true;
}

// ========== Auto Backup Schedule ==========
void DatabaseManager::StartAutoBackup(int intervalHours, const wxString& backupDir) {
    StopAutoBackup();

    m_autoBackupInterval = intervalHours;
    m_autoBackupDir = backupDir;
    m_autoBackupEnabled = true;

    m_autoBackupTimer = new wxTimer(this, wxID_ANY);
    m_autoBackupTimer->Start(intervalHours * 60 * 60 * 1000);
}

void DatabaseManager::StopAutoBackup() {
    if (m_autoBackupTimer) {
        m_autoBackupTimer->Stop();
        delete m_autoBackupTimer;
        m_autoBackupTimer = nullptr;
    }
    m_autoBackupEnabled = false;
}

void DatabaseManager::SetAutoBackupEnabled(bool enabled) {
    if (enabled && !m_autoBackupEnabled && !m_autoBackupDir.IsEmpty()) {
        StartAutoBackup(m_autoBackupInterval, m_autoBackupDir);
    }
    else if (!enabled && m_autoBackupEnabled) {
        StopAutoBackup();
    }
}

void DatabaseManager::OnAutoBackupTimer(wxTimerEvent& event) {
    PerformAutoBackup();
}

void DatabaseManager::PerformAutoBackup() {
    if (!m_autoBackupEnabled || m_autoBackupDir.IsEmpty()) return;
    BackupWithRotation(m_autoBackupDir, 3);
}

// ========== Data Export/Import ==========
bool DatabaseManager::ExportData(const wxString& exportPath) {
    wxFile file(exportPath, wxFile::write);
    if (!file.IsOpened()) return false;

    wxString dump;
    dump << wxT("-- Export Date: ") << wxDateTime::Now().Format(wxT("%Y-%m-%d %H:%M:%S")) << wxT("\n\n");

    // Tenant
    dump << wxT("-- Table: Tenant\n");
    sqlite3_stmt* stmt = PrepareStatement(wxT("SELECT * FROM Tenant"));
    if (stmt) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            dump << wxString::Format(wxT("INSERT INTO Tenant VALUES (%d, '%s', '%s', '%s', '%s', '%s', %d, '%s');\n"),
                sqlite3_column_int(stmt, 0),
                wxString::FromUTF8((const char*)sqlite3_column_text(stmt, 1)),
                wxString::FromUTF8((const char*)sqlite3_column_text(stmt, 2)),
                wxString::FromUTF8((const char*)sqlite3_column_text(stmt, 3)),
                wxString::FromUTF8((const char*)sqlite3_column_text(stmt, 4)),
                wxString::FromUTF8((const char*)sqlite3_column_text(stmt, 5)),
                sqlite3_column_int(stmt, 6),
                wxString::FromUTF8((const char*)sqlite3_column_text(stmt, 7)));
        }
        sqlite3_finalize(stmt);
    }

    dump << wxT("\n");

    // Garage
    dump << wxT("-- Table: Garage\n");
    stmt = PrepareStatement(wxT("SELECT * FROM Garage"));
    if (stmt) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            dump << wxString::Format(wxT("INSERT INTO Garage VALUES (%d, '%s', '%s', %f, %f, %d, '%s');\n"),
                sqlite3_column_int(stmt, 0),
                wxString::FromUTF8((const char*)sqlite3_column_text(stmt, 1)),
                wxString::FromUTF8((const char*)sqlite3_column_text(stmt, 2)),
                sqlite3_column_double(stmt, 3),
                sqlite3_column_double(stmt, 4),
                sqlite3_column_int(stmt, 5),
                wxString::FromUTF8((const char*)sqlite3_column_text(stmt, 6)));
        }
        sqlite3_finalize(stmt);
    }

    dump << wxT("\n");

    // Lease_Agreement
    dump << wxT("-- Table: Lease_Agreement\n");
    stmt = PrepareStatement(wxT("SELECT * FROM Lease_Agreement"));
    if (stmt) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            dump << wxString::Format(wxT("INSERT INTO Lease_Agreement VALUES (%d, '%s', %d, %d, '%s', '%s', %f, %f, %d, '%s');\n"),
                sqlite3_column_int(stmt, 0),
                wxString::FromUTF8((const char*)sqlite3_column_text(stmt, 1)),
                sqlite3_column_int(stmt, 2),
                sqlite3_column_int(stmt, 3),
                wxString::FromUTF8((const char*)sqlite3_column_text(stmt, 4)),
                wxString::FromUTF8((const char*)sqlite3_column_text(stmt, 5)),
                sqlite3_column_double(stmt, 6),
                sqlite3_column_double(stmt, 7),
                sqlite3_column_int(stmt, 8),
                wxString::FromUTF8((const char*)sqlite3_column_text(stmt, 9)));
        }
        sqlite3_finalize(stmt);
    }

    dump << wxT("\n");

    // Payment
    dump << wxT("-- Table: Payment\n");
    stmt = PrepareStatement(wxT("SELECT * FROM Payment"));
    if (stmt) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            dump << wxString::Format(wxT("INSERT INTO Payment VALUES (%d, '%s', %d, %d, %f, '%s', %d, %d);\n"),
                sqlite3_column_int(stmt, 0),
                wxString::FromUTF8((const char*)sqlite3_column_text(stmt, 1)),
                sqlite3_column_int(stmt, 2),
                sqlite3_column_int(stmt, 3),
                sqlite3_column_double(stmt, 4),
                wxString::FromUTF8((const char*)sqlite3_column_text(stmt, 5)),
                sqlite3_column_int(stmt, 6),
                sqlite3_column_int(stmt, 7));
        }
        sqlite3_finalize(stmt);
    }

    file.Write(dump);
    file.Close();
    return true;
}

bool DatabaseManager::ImportData(const wxString& importPath) {
    if (!wxFileExists(importPath)) return false;

    wxFile file(importPath, wxFile::read);
    if (!file.IsOpened()) return false;

    wxString content;
    file.ReadAll(&content);
    file.Close();

    char* errMsg = nullptr;
    int rc = sqlite3_exec(m_db, content.utf8_str(), nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        wxLogError(wxT("Ошибка импорта: %s"), errMsg);
        sqlite3_free(errMsg);
        return false;
    }

    return true;
}

bool DatabaseManager::LoadData() {
    if (!m_db) return false;
    return ExecuteQuery(wxT("PRAGMA integrity_check"));
}

bool DatabaseManager::SaveData() {
    if (!m_db) return false;
    return ExecuteQuery(wxT("PRAGMA synchronous = FULL"));
}

// ========== Tenant ==========
bool DatabaseManager::AddTenant(const wxString& surname, const wxString& name, const wxString& patronymic,
    const wxString& phone, const wxString& email) {
    wxString sql = wxString::Format(
        wxT("INSERT INTO Tenant (surname, name, patronymic, phone_num, email, created_at, isOverdue) "
            "VALUES ('%s', '%s', '%s', '%s', '%s', DATE('now'), 0)"),
        surname, name, patronymic, phone, email);
    return ExecuteQuery(sql);
}

bool DatabaseManager::UpdateTenant(int id, const wxString& surname, const wxString& name,
    const wxString& patronymic, const wxString& phone, const wxString& email) {
    wxString sql = wxString::Format(
        wxT("UPDATE Tenant SET surname='%s', name='%s', patronymic='%s', phone_num='%s', email='%s' WHERE id=%d"),
        surname, name, patronymic, phone, email, id);
    return ExecuteQuery(sql);
}

bool DatabaseManager::DeleteTenant(int id) {
    wxString sql = wxString::Format(wxT("DELETE FROM Tenant WHERE id=%d"), id);
    return ExecuteQuery(sql);
}

bool DatabaseManager::GetTenant(int id, wxString& surname, wxString& name, wxString& patronymic,
    wxString& phone, wxString& email, int& isOverdue) {
    sqlite3_stmt* stmt;
    wxString sql = wxString::Format(wxT("SELECT surname, name, patronymic, phone_num, email, isOverdue FROM Tenant WHERE id=%d"), id);

    if (sqlite3_prepare_v2(m_db, sql.utf8_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        return false;
    }

    if (sqlite3_step(stmt) != SQLITE_ROW) {
        sqlite3_finalize(stmt);
        return false;
    }

    surname = wxString::FromUTF8((const char*)sqlite3_column_text(stmt, 0));
    name = wxString::FromUTF8((const char*)sqlite3_column_text(stmt, 1));
    patronymic = wxString::FromUTF8((const char*)sqlite3_column_text(stmt, 2));
    phone = wxString::FromUTF8((const char*)sqlite3_column_text(stmt, 3));
    email = wxString::FromUTF8((const char*)sqlite3_column_text(stmt, 4));
    isOverdue = sqlite3_column_int(stmt, 5);

    sqlite3_finalize(stmt);
    return true;
}

// ========== Garage ==========
bool DatabaseManager::AddGarage(const wxString& personalNumbers, const wxString& location,
    double width, double height, int status) {
    wxString sql = wxString::Format(
        wxT("INSERT INTO Garage (personal_numbers, location, width_garage, height_garage, status_garage, created_at) "
            "VALUES ('%s', '%s', %f, %f, %d, DATE('now'))"),
        personalNumbers, location, width, height, status);
    return ExecuteQuery(sql);
}

bool DatabaseManager::UpdateGarage(int id, const wxString& personalNumbers, const wxString& location,
    double width, double height, int status) {
    wxString sql = wxString::Format(
        wxT("UPDATE Garage SET personal_numbers='%s', location='%s', width_garage=%f, height_garage=%f, status_garage=%d WHERE id=%d"),
        personalNumbers, location, width, height, status, id);
    return ExecuteQuery(sql);
}

bool DatabaseManager::DeleteGarage(int id) {
    wxString sql = wxString::Format(wxT("DELETE FROM Garage WHERE id=%d"), id);
    return ExecuteQuery(sql);
}

bool DatabaseManager::GetGarage(int id, wxString& personalNumbers, wxString& location,
    double& width, double& height, int& status) {
    sqlite3_stmt* stmt;
    wxString sql = wxString::Format(wxT("SELECT personal_numbers, location, width_garage, height_garage, status_garage FROM Garage WHERE id=%d"), id);

    if (sqlite3_prepare_v2(m_db, sql.utf8_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        return false;
    }

    if (sqlite3_step(stmt) != SQLITE_ROW) {
        sqlite3_finalize(stmt);
        return false;
    }

    personalNumbers = wxString::FromUTF8((const char*)sqlite3_column_text(stmt, 0));
    location = wxString::FromUTF8((const char*)sqlite3_column_text(stmt, 1));
    width = sqlite3_column_double(stmt, 2);
    height = sqlite3_column_double(stmt, 3);
    status = sqlite3_column_int(stmt, 4);

    sqlite3_finalize(stmt);
    return true;
}

// ========== Lease Agreement ==========
bool DatabaseManager::AddAgreement(const wxString& contractNumber, int tenantId, int garageId,
    const wxString& startDate, const wxString& endDate,
    double monthlyPrice, double totalAmount) {
    wxString sql = wxString::Format(
        wxT("INSERT INTO Lease_Agreement (personal_numbers, tenant_id, garage_id, start_date, end_date, "
            "monthly_price, total_amount, status, created_at) "
            "VALUES ('%s', %d, %d, '%s', '%s', %f, %f, 1, DATE('now'))"),
        contractNumber, tenantId, garageId, startDate, endDate, monthlyPrice, totalAmount);

    if (!ExecuteQuery(sql)) return false;

    wxString updateGarage = wxString::Format(wxT("UPDATE Garage SET status_garage=2 WHERE id=%d"), garageId);
    return ExecuteQuery(updateGarage);
}

bool DatabaseManager::UpdateAgreement(int id, const wxString& startDate, const wxString& endDate,
    double monthlyPrice, double totalAmount, int status) {
    wxString sql = wxString::Format(
        wxT("UPDATE Lease_Agreement SET start_date='%s', end_date='%s', monthly_price=%f, total_amount=%f, status=%d WHERE id=%d"),
        startDate, endDate, monthlyPrice, totalAmount, status, id);
    return ExecuteQuery(sql);
}

bool DatabaseManager::CloseAgreement(int id) {
    wxString sql = wxString::Format(wxT("UPDATE Lease_Agreement SET status=0 WHERE id=%d"), id);

    if (!ExecuteQuery(sql)) return false;

    sqlite3_stmt* stmt = PrepareStatement(wxString::Format(wxT("SELECT garage_id FROM Lease_Agreement WHERE id=%d"), id));
    int garageId = -1;
    if (stmt && sqlite3_step(stmt) == SQLITE_ROW) {
        garageId = sqlite3_column_int(stmt, 0);
    }
    sqlite3_finalize(stmt);

    if (garageId != -1) {
        wxString updateGarage = wxString::Format(wxT("UPDATE Garage SET status_garage=1 WHERE id=%d"), garageId);
        return ExecuteQuery(updateGarage);
    }
    return true;
}

bool DatabaseManager::ExtendAgreement(int id, const wxString& newEndDate, double additionalAmount) {
    wxString sql = wxString::Format(
        wxT("UPDATE Lease_Agreement SET end_date='%s', total_amount=total_amount+%f WHERE id=%d"),
        newEndDate, additionalAmount, id);
    return ExecuteQuery(sql);
}

// ========== Payment ==========
bool DatabaseManager::AddPayment(int agreementId, int payerId, double amount,
    const wxString& paymentDate, int paymentType, const wxString& receiptNumber) {
    wxString sql = wxString::Format(
        wxT("INSERT INTO Payment (agreement_id, payer_id, payment_amount, payment_date, payment_type, status_payment, receipt_number) "
            "VALUES (%d, %d, %f, '%s', %d, 1, '%s')"),
        agreementId, payerId, amount, paymentDate, paymentType, receiptNumber);
    return ExecuteQuery(sql);
}

// ========== Reports ==========
std::vector<std::vector<wxString>> DatabaseManager::GetDebtors() {
    std::vector<std::vector<wxString>> result;

    wxString sql = wxT(
        "SELECT t.id, t.surname || ' ' || t.name || ' ' || t.patronymic as full_name, "
        "t.phone_num, t.email, "
        "COALESCE(SUM(la.total_amount), 0) - COALESCE(SUM(p.payment_amount), 0) as debt "
        "FROM Tenant t "
        "LEFT JOIN Lease_Agreement la ON la.tenant_id = t.id AND la.status = 1 "
        "LEFT JOIN Payment p ON p.payer_id = t.id "
        "GROUP BY t.id "
        "HAVING debt > 0");

    sqlite3_stmt* stmt = PrepareStatement(sql);
    if (stmt) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            std::vector<wxString> row;
            row.push_back(wxString::Format(wxT("%d"), sqlite3_column_int(stmt, 0)));
            row.push_back(wxString::FromUTF8((const char*)sqlite3_column_text(stmt, 1)));
            row.push_back(wxString::FromUTF8((const char*)sqlite3_column_text(stmt, 2)));
            row.push_back(wxString::FromUTF8((const char*)sqlite3_column_text(stmt, 3)));
            row.push_back(wxString::Format(wxT("%.2f"), sqlite3_column_double(stmt, 4)));
            result.push_back(row);
        }
        sqlite3_finalize(stmt);
    }
    return result;
}

std::vector<std::vector<wxString>> DatabaseManager::GetGarageOccupancy() {
    std::vector<std::vector<wxString>> result;

    wxString sql = wxT(
        "SELECT "
        "COUNT(CASE WHEN status_garage = 1 THEN 1 END) as free, "
        "COUNT(CASE WHEN status_garage = 2 THEN 1 END) as occupied, "
        "COUNT(CASE WHEN status_garage = 3 THEN 1 END) as repair, "
        "COUNT(*) as total "
        "FROM Garage");

    sqlite3_stmt* stmt = PrepareStatement(sql);
    if (stmt && sqlite3_step(stmt) == SQLITE_ROW) {
        std::vector<wxString> row;
        row.push_back(wxString::Format(wxT("%d"), sqlite3_column_int(stmt, 0)));
        row.push_back(wxString::Format(wxT("%d"), sqlite3_column_int(stmt, 1)));
        row.push_back(wxString::Format(wxT("%d"), sqlite3_column_int(stmt, 2)));
        row.push_back(wxString::Format(wxT("%d"), sqlite3_column_int(stmt, 3)));
        result.push_back(row);
    }
    sqlite3_finalize(stmt);
    return result;
}

std::vector<std::vector<wxString>> DatabaseManager::GetGarageFinance() {
    std::vector<std::vector<wxString>> result;

    wxString sql = wxT(
        "SELECT g.id, g.personal_numbers, "
        "COALESCE(SUM(la.total_amount), 0) as total_income, "
        "COUNT(la.id) as rental_count "
        "FROM Garage g "
        "LEFT JOIN Lease_Agreement la ON la.garage_id = g.id "
        "GROUP BY g.id");

    sqlite3_stmt* stmt = PrepareStatement(sql);
    if (stmt) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            std::vector<wxString> row;
            row.push_back(wxString::Format(wxT("%d"), sqlite3_column_int(stmt, 0)));
            row.push_back(wxString::FromUTF8((const char*)sqlite3_column_text(stmt, 1)));
            row.push_back(wxString::Format(wxT("%.2f"), sqlite3_column_double(stmt, 2)));
            row.push_back(wxString::Format(wxT("%d"), sqlite3_column_int(stmt, 3)));
            result.push_back(row);
        }
        sqlite3_finalize(stmt);
    }
    return result;
}

std::vector<std::vector<wxString>> DatabaseManager::GetGarageRating() {
    std::vector<std::vector<wxString>> result;

    wxString sql = wxT(
        "SELECT g.id, g.personal_numbers, "
        "COALESCE(SUM(la.total_amount), 0) as total_income, "
        "COUNT(la.id) as rental_count "
        "FROM Garage g "
        "LEFT JOIN Lease_Agreement la ON la.garage_id = g.id "
        "GROUP BY g.id "
        "ORDER BY total_income DESC "
        "LIMIT 10");

    sqlite3_stmt* stmt = PrepareStatement(sql);
    if (stmt) {
        int rank = 1;
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            std::vector<wxString> row;
            row.push_back(wxString::Format(wxT("%d"), rank++));
            row.push_back(wxString::FromUTF8((const char*)sqlite3_column_text(stmt, 1)));
            row.push_back(wxString::Format(wxT("%.2f"), sqlite3_column_double(stmt, 2)));
            row.push_back(wxString::Format(wxT("%d"), sqlite3_column_int(stmt, 3)));
            result.push_back(row);
        }
        sqlite3_finalize(stmt);
    }
    return result;
}

double DatabaseManager::GetReturnRate() {
    wxString sql = wxT(
        "SELECT "
        "COUNT(CASE WHEN status_payment = 1 THEN 1 END) * 1.0 / NULLIF(COUNT(*), 0) * 100 as return_rate "
        "FROM Payment");

    sqlite3_stmt* stmt = PrepareStatement(sql);
    double rate = 0.0;
    if (stmt && sqlite3_step(stmt) == SQLITE_ROW) {
        rate = sqlite3_column_double(stmt, 0);
    }
    sqlite3_finalize(stmt);
    return rate;
}