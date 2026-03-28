// DatabaseManager.h
#pragma once

#include <wx/wx.h>
#include <sqlite3.h>
#include <vector>

class DatabaseManager {
public:
    DatabaseManager();
    ~DatabaseManager();
    
    bool Connect(const wxString& dbPath);
    void Disconnect();
    bool IsConnected() const { return m_db != nullptr; }
    
    sqlite3* GetDB() { return m_db; }
    
    // ========== Tenant ==========
    bool AddTenant(const wxString& surname, const wxString& name, const wxString& patronymic,
                   const wxString& phone, const wxString& email);
    bool UpdateTenant(int id, const wxString& surname, const wxString& name, const wxString& patronymic,
                      const wxString& phone, const wxString& email);
    bool DeleteTenant(int id);
    bool GetTenant(int id, wxString& surname, wxString& name, wxString& patronymic,
                   wxString& phone, wxString& email, int& isOverdue);
    
    // ========== Garage ==========
    bool AddGarage(const wxString& personalNumbers, const wxString& location,
                   double width, double height, int status);
    bool UpdateGarage(int id, const wxString& personalNumbers, const wxString& location,
                      double width, double height, int status);
    bool DeleteGarage(int id);
    bool GetGarage(int id, wxString& personalNumbers, wxString& location,
                   double& width, double& height, int& status);
    
    // ========== Lease Agreement ==========
    bool AddAgreement(const wxString& contractNumber, int tenantId, int garageId,
                      const wxString& startDate, const wxString& endDate,
                      double monthlyPrice, double totalAmount);
    bool UpdateAgreement(int id, const wxString& startDate, const wxString& endDate,
                         double monthlyPrice, double totalAmount, int status);
    bool CloseAgreement(int id);
    bool ExtendAgreement(int id, const wxString& newEndDate, double additionalAmount);
    
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
    
    bool ExecuteQuery(const wxString& sql);
    sqlite3_stmt* PrepareStatement(const wxString& sql);
};