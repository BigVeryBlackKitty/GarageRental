// DatabaseManager.cpp
#include "DatabaseManager.h"
#include <wx/filename.h>

DatabaseManager::DatabaseManager() : m_db(nullptr) {}

DatabaseManager::~DatabaseManager() {
    Disconnect();
}

bool DatabaseManager::Connect(const wxString& dbPath) {
    if (m_db) Disconnect();
    
    int rc = sqlite3_open(dbPath.utf8_str(), &m_db);
    if (rc != SQLITE_OK) {
        wxLogError("Cannot open database: %s", sqlite3_errmsg(m_db));
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
        wxLogError("SQL error: %s", errMsg);
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
        wxLogError("Prepare failed: %s", sqlite3_errmsg(m_db));
        return nullptr;
    }
    return stmt;
}

// ========== Tenant ==========
bool DatabaseManager::AddTenant(const wxString& surname, const wxString& name, const wxString& patronymic,
                                 const wxString& phone, const wxString& email) {
    wxString sql = wxString::Format(
        "INSERT INTO Tenant (surname, name, patronymic, phone_num, email, created_at, isOverdue) "
        "VALUES ('%s', '%s', '%s', '%s', '%s', DATE('now'), 0)",
        surname, name, patronymic, phone, email
    );
    return ExecuteQuery(sql);
}

bool DatabaseManager::UpdateTenant(int id, const wxString& surname, const wxString& name,
                                    const wxString& patronymic, const wxString& phone, const wxString& email) {
    wxString sql = wxString::Format(
        "UPDATE Tenant SET surname='%s', name='%s', patronymic='%s', phone_num='%s', email='%s' WHERE id=%d",
        surname, name, patronymic, phone, email, id
    );
    return ExecuteQuery(sql);
}

bool DatabaseManager::DeleteTenant(int id) {
    wxString sql = wxString::Format("DELETE FROM Tenant WHERE id=%d", id);
    return ExecuteQuery(sql);
}

// ========== Garage ==========
bool DatabaseManager::AddGarage(const wxString& personalNumbers, const wxString& location,
                                 double width, double height, int status) {
    wxString sql = wxString::Format(
        "INSERT INTO Garage (personal_numbers, location, width_garage, height_garage, status_garage, created_at) "
        "VALUES ('%s', '%s', %f, %f, %d, DATE('now'))",
        personalNumbers, location, width, height, status
    );
    return ExecuteQuery(sql);
}

bool DatabaseManager::UpdateGarage(int id, const wxString& personalNumbers, const wxString& location,
                                    double width, double height, int status) {
    wxString sql = wxString::Format(
        "UPDATE Garage SET personal_numbers='%s', location='%s', width_garage=%f, height_garage=%f, status_garage=%d WHERE id=%d",
        personalNumbers, location, width, height, status, id
    );
    return ExecuteQuery(sql);
}

bool DatabaseManager::DeleteGarage(int id) {
    wxString sql = wxString::Format("DELETE FROM Garage WHERE id=%d", id);
    return ExecuteQuery(sql);
}

// ========== Lease Agreement ==========
bool DatabaseManager::AddAgreement(const wxString& contractNumber, int tenantId, int garageId,
                                    const wxString& startDate, const wxString& endDate,
                                    double monthlyPrice, double totalAmount) {
    wxString sql = wxString::Format(
        "INSERT INTO Lease_Agreement (personal_numbers, tenant_id, garage_id, start_date, end_date, "
        "monthly_price, total_amount, status, created_at) "
        "VALUES ('%s', %d, %d, '%s', '%s', %f, %f, 1, DATE('now'))",
        contractNumber, tenantId, garageId, startDate, endDate, monthlyPrice, totalAmount
    );
    
    if (!ExecuteQuery(sql)) return false;
    
    // Обновляем статус гаража на "занят" (2)
    wxString updateGarage = wxString::Format("UPDATE Garage SET status_garage=2 WHERE id=%d", garageId);
    return ExecuteQuery(updateGarage);
}

bool DatabaseManager::CloseAgreement(int id) {
    wxString sql = wxString::Format(
        "UPDATE Lease_Agreement SET status=0 WHERE id=%d", id
    );
    
    if (!ExecuteQuery(sql)) return false;
    
    // Получаем garage_id
    sqlite3_stmt* stmt = PrepareStatement(wxString::Format("SELECT garage_id FROM Lease_Agreement WHERE id=%d", id));
    int garageId = -1;
    if (stmt && sqlite3_step(stmt) == SQLITE_ROW) {
        garageId = sqlite3_column_int(stmt, 0);
    }
    sqlite3_finalize(stmt);
    
    if (garageId != -1) {
        wxString updateGarage = wxString::Format("UPDATE Garage SET status_garage=1 WHERE id=%d", garageId);
        return ExecuteQuery(updateGarage);
    }
    return true;
}

bool DatabaseManager::ExtendAgreement(int id, const wxString& newEndDate, double additionalAmount) {
    wxString sql = wxString::Format(
        "UPDATE Lease_Agreement SET end_date='%s', total_amount=total_amount+%f WHERE id=%d",
        newEndDate, additionalAmount, id
    );
    return ExecuteQuery(sql);
}

// ========== Payment ==========
bool DatabaseManager::AddPayment(int agreementId, int payerId, double amount,
                                  const wxString& paymentDate, int paymentType, const wxString& receiptNumber) {
    wxString sql = wxString::Format(
        "INSERT INTO Payment (agreement_id, payer_id, payment_amount, payment_date, payment_type, status_payment, receipt_number) "
        "VALUES (%d, %d, %f, '%s', %d, 1, '%s')",
        agreementId, payerId, amount, paymentDate, paymentType, receiptNumber
    );
    return ExecuteQuery(sql);
}

// ========== Reports ==========
std::vector<std::vector<wxString>> DatabaseManager::GetDebtors() {
    std::vector<std::vector<wxString>> result;
    
    wxString sql = 
        "SELECT t.id, t.surname || ' ' || t.name || ' ' || t.patronymic as full_name, "
        "t.phone_num, t.email, "
        "SUM(la.total_amount) - COALESCE(SUM(p.payment_amount), 0) as debt "
        "FROM Tenant t "
        "LEFT JOIN Lease_Agreement la ON la.tenant_id = t.id AND la.status = 1 "
        "LEFT JOIN Payment p ON p.payer_id = t.id "
        "GROUP BY t.id "
        "HAVING debt > 0";
    
    sqlite3_stmt* stmt = PrepareStatement(sql);
    if (stmt) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            std::vector<wxString> row;
            row.push_back(wxString::Format("%d", sqlite3_column_int(stmt, 0)));
            row.push_back(wxString::FromUTF8((const char*)sqlite3_column_text(stmt, 1)));
            row.push_back(wxString::FromUTF8((const char*)sqlite3_column_text(stmt, 2)));
            row.push_back(wxString::FromUTF8((const char*)sqlite3_column_text(stmt, 3)));
            row.push_back(wxString::Format("%.2f", sqlite3_column_double(stmt, 4)));
            result.push_back(row);
        }
        sqlite3_finalize(stmt);
    }
    return result;
}

std::vector<std::vector<wxString>> DatabaseManager::GetGarageOccupancy() {
    std::vector<std::vector<wxString>> result;
    
    wxString sql = 
        "SELECT "
        "COUNT(CASE WHEN status_garage = 1 THEN 1 END) as free, "
        "COUNT(CASE WHEN status_garage = 2 THEN 1 END) as occupied, "
        "COUNT(CASE WHEN status_garage = 3 THEN 1 END) as repair, "
        "COUNT(*) as total "
        "FROM Garage";
    
    sqlite3_stmt* stmt = PrepareStatement(sql);
    if (stmt && sqlite3_step(stmt) == SQLITE_ROW) {
        std::vector<wxString> row;
        row.push_back(wxString::Format("%d", sqlite3_column_int(stmt, 0)));
        row.push_back(wxString::Format("%d", sqlite3_column_int(stmt, 1)));
        row.push_back(wxString::Format("%d", sqlite3_column_int(stmt, 2)));
        row.push_back(wxString::Format("%d", sqlite3_column_int(stmt, 3)));
        result.push_back(row);
    }
    sqlite3_finalize(stmt);
    return result;
}

std::vector<std::vector<wxString>> DatabaseManager::GetGarageFinance() {
    std::vector<std::vector<wxString>> result;
    
    wxString sql = 
        "SELECT g.id, g.personal_numbers, "
        "SUM(la.total_amount) as total_income, "
        "COUNT(la.id) as rental_count "
        "FROM Garage g "
        "LEFT JOIN Lease_Agreement la ON la.garage_id = g.id "
        "GROUP BY g.id";
    
    sqlite3_stmt* stmt = PrepareStatement(sql);
    if (stmt) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            std::vector<wxString> row;
            row.push_back(wxString::Format("%d", sqlite3_column_int(stmt, 0)));
            row.push_back(wxString::FromUTF8((const char*)sqlite3_column_text(stmt, 1)));
            row.push_back(wxString::Format("%.2f", sqlite3_column_double(stmt, 2)));
            row.push_back(wxString::Format("%d", sqlite3_column_int(stmt, 3)));
            result.push_back(row);
        }
        sqlite3_finalize(stmt);
    }
    return result;
}

std::vector<std::vector<wxString>> DatabaseManager::GetGarageRating() {
    std::vector<std::vector<wxString>> result;
    
    wxString sql = 
        "SELECT g.id, g.personal_numbers, "
        "SUM(la.total_amount) as total_income, "
        "COUNT(la.id) as rental_count "
        "FROM Garage g "
        "LEFT JOIN Lease_Agreement la ON la.garage_id = g.id "
        "GROUP BY g.id "
        "ORDER BY total_income DESC "
        "LIMIT 10";
    
    sqlite3_stmt* stmt = PrepareStatement(sql);
    if (stmt) {
        int rank = 1;
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            std::vector<wxString> row;
            row.push_back(wxString::Format("%d", rank++));
            row.push_back(wxString::FromUTF8((const char*)sqlite3_column_text(stmt, 1)));
            row.push_back(wxString::Format("%.2f", sqlite3_column_double(stmt, 2)));
            row.push_back(wxString::Format("%d", sqlite3_column_int(stmt, 3)));
            result.push_back(row);
        }
        sqlite3_finalize(stmt);
    }
    return result;
}

double DatabaseManager::GetReturnRate() {
    wxString sql = 
        "SELECT "
        "COUNT(CASE WHEN status_payment = 1 THEN 1 END) * 1.0 / COUNT(*) * 100 as return_rate "
        "FROM Payment";
    
    sqlite3_stmt* stmt = PrepareStatement(sql);
    double rate = 0.0;
    if (stmt && sqlite3_step(stmt) == SQLITE_ROW) {
        rate = sqlite3_column_double(stmt, 0);
    }
    sqlite3_finalize(stmt);
    return rate;
}