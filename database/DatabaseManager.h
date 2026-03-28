// database/DatabaseManager.h
#pragma once

#include <wx/wx.h>
#include <sqlite3.h>
#include <vector>
#include <wx/timer.h>

struct BackupInfo {
    wxString path;
    wxString name;
    wxDateTime createdAt;
    wxULongLong size;
};

class DatabaseManager : public wxEvtHandler {
public:
    DatabaseManager();
    ~DatabaseManager();

    bool Connect(const wxString& dbPath);
    void Disconnect();
    bool IsConnected() const { return m_db != nullptr; }

    sqlite3* GetDB() { return m_db; }
    wxString GetDBPath() const { return m_dbPath; }

    // ========== Backup System ==========
    bool Backup(const wxString& backupPath);
    bool BackupWithRotation(const wxString& backupDir, int maxBackups = 3);
    std::vector<BackupInfo> GetBackupList(const wxString& backupDir);
    bool RestoreFromBackup(const wxString& backupPath);
    bool DeleteOldBackups(const wxString& backupDir, int keepCount = 3);

    // ========== Auto Backup Schedule ==========
    void StartAutoBackup(int intervalHours, const wxString& backupDir);
    void StopAutoBackup();
    void SetAutoBackupEnabled(bool enabled);
    bool IsAutoBackupEnabled() const { return m_autoBackupEnabled; }
    int GetAutoBackupInterval() const { return m_autoBackupInterval; }
    wxString GetAutoBackupDir() const { return m_autoBackupDir; }

    // ========== Data Export/Import ==========
    bool ExportData(const wxString& exportPath);
    bool ImportData(const wxString& importPath);
    bool LoadData();      // ДОБАВЛЕНО
    bool SaveData();      // ДОБАВЛЕНО

    // ========== Tenant ==========
    bool AddTenant(const wxString& surname, const wxString& name, const wxString& patronymic,
        const wxString& phone, const wxString& email);
    bool UpdateTenant(int id, const wxString& surname, const wxString& name, const wxString& patronymic,
        const wxString& phone, const wxString& email);
    bool DeleteTenant(int id);
    bool GetTenant(int id, wxString& surname, wxString& name, wxString& patronymic,
        wxString& phone, wxString& email, int& isOverdue);  // ДОБАВЛЕНО

    // ========== Garage ==========
    bool AddGarage(const wxString& personalNumbers, const wxString& location,
        double width, double height, int status);
    bool UpdateGarage(int id, const wxString& personalNumbers, const wxString& location,
        double width, double height, int status);
    bool DeleteGarage(int id);
    bool GetGarage(int id, wxString& personalNumbers, wxString& location,
        double& width, double& height, int& status);  // ДОБАВЛЕНО

    // ========== Lease Agreement ==========
    bool AddAgreement(const wxString& contractNumber, int tenantId, int garageId,
        const wxString& startDate, const wxString& endDate,
        double monthlyPrice, double totalAmount);
    bool UpdateAgreement(int id, const wxString& startDate, const wxString& endDate,
        double monthlyPrice, double totalAmount, int status);  // ДОБАВЛЕНО
    bool CloseAgreement(int id);
    bool ExtendAgreement(int id, const wxString& newEndDate, double additionalAmount);  // ДОБАВЛЕНО

    // ========== Payment ==========
    bool AddPayment(int agreementId, int payerId, double amount,
        const wxString& paymentDate, int paymentType, const wxString& receiptNumber);

    // ========== Reports ==========
    std::vector<std::vector<wxString>> GetDebtors();
    std::vector<std::vector<wxString>> GetGarageOccupancy();
    std::vector<std::vector<wxString>> GetGarageFinance();
    std::vector<std::vector<wxString>> GetGarageRating();
    double GetReturnRate();

private:
    sqlite3* m_db;
    wxString m_dbPath;

    // Auto backup
    wxTimer* m_autoBackupTimer;
    bool m_autoBackupEnabled;
    int m_autoBackupInterval;
    wxString m_autoBackupDir;

    void OnAutoBackupTimer(wxTimerEvent& event);
    void PerformAutoBackup();

    bool ExecuteQuery(const wxString& sql);
    sqlite3_stmt* PrepareStatement(const wxString& sql);

    wxDECLARE_EVENT_TABLE();
};