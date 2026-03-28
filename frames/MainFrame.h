// MainFrame.h
#pragma once

#include <wx/wx.h>
#include "database/DatabaseManager.h"

class MainFrame : public wxFrame {
public:
    MainFrame(wxWindow* parent, wxWindowID id = wxID_ANY,
              const wxString& title = wxT("Корпоративная система управления гаражами"),
              const wxPoint& pos = wxDefaultPosition,
              const wxSize& size = wxSize(900, 500), long style = wxDEFAULT_FRAME_STYLE);
    
    ~MainFrame();
    
    void SetDatabaseManager(DatabaseManager* db) { m_db = db; }
    
private:
    DatabaseManager* m_db;
    
    // UI элементы
    wxButton* m_button45;  // Добавить клиента
    wxButton* m_button20;  // Редактировать клиента
    wxButton* m_button21;  // Информация о клиенте
    wxButton* m_button22;  // Все клиенты
    
    wxButton* m_button19;  // Новый договор
    wxButton* m_button38;  // Продлить договор
    wxButton* m_button23;  // Редактировать договор
    wxButton* m_button24;  // Все договоры
    wxButton* m_button31;  // Информация о договоре
    wxButton* m_buttonCloseRental;  // Закончить аренду (добавить!)
    
    wxButton* m_button27;  // Добавить гараж
    wxButton* m_button28;  // Удалить гараж
    wxButton* m_button281; // Редактировать гараж
    wxButton* m_button29;  // Все гаражи
    wxButton* m_button30;  // Информация о гараже
    
    wxButton* m_button32;  // Добавить чек
    wxButton* m_button36;  // Редактировать чек
    wxButton* m_button33;  // История оплат клиента
    wxButton* m_button35;  // Все оплаты
    wxButton* m_button34;  // Возврат средств
    
    // MenuBar
    wxMenuBar* m_menubar5;
    wxMenu* Database;
    wxMenu* report;
    wxMenu* garageMenu;
    wxMenu* clientMenu;
    wxMenu* Service;
    wxMenu* Reference;
    
    // Обработчики кнопок
    void OnAddTenant(wxCommandEvent& event);
    void OnEditTenant(wxCommandEvent& event);
    void OnTenantInfo(wxCommandEvent& event);
    void OnAllTenants(wxCommandEvent& event);
    
    void OnNewAgreement(wxCommandEvent& event);
    void OnExtendAgreement(wxCommandEvent& event);
    void OnEditAgreement(wxCommandEvent& event);
    void OnAllAgreements(wxCommandEvent& event);
    void OnAgreementInfo(wxCommandEvent& event);
    void OnCloseRental(wxCommandEvent& event);
    
    void OnAddGarage(wxCommandEvent& event);
    void OnDeleteGarage(wxCommandEvent& event);
    void OnEditGarage(wxCommandEvent& event);
    void OnAllGarages(wxCommandEvent& event);
    void OnGarageInfo(wxCommandEvent& event);
    
    void OnAddPayment(wxCommandEvent& event);
    void OnEditPayment(wxCommandEvent& event);
    void OnPaymentHistory(wxCommandEvent& event);
    void OnAllPayments(wxCommandEvent& event);
    void OnRefundPayment(wxCommandEvent& event);
    
    // Обработчики меню
    void OnLoadData(wxCommandEvent& event);
    void OnSaveData(wxCommandEvent& event);
    void OnBackup(wxCommandEvent& event);
    
    void OnGarageOccupancyReport(wxCommandEvent& event);
    void OnGarageFinanceReport(wxCommandEvent& event);
    void OnGarageRatingReport(wxCommandEvent& event);
    
    void OnDebtorsReport(wxCommandEvent& event);
    void OnReturnRateReport(wxCommandEvent& event);
    
    void OnLogView(wxCommandEvent& event);
    void OnHelp(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
};