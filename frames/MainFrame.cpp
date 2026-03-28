// MainFrame.cpp
#include "MainFrame.h"
#include "frames/TenantEditFrame.h"
#include "frames/TenantInfoFrame.h"
#include "frames/AllTenantsFrame.h"
#include "frames/GarageEditFrame.h"
#include "frames/GarageInfoFrame.h"
#include "frames/AllGaragesFrame.h"
#include "frames/NewAgreementFrame.h"
#include "frames/CloseAgreementFrame.h"
#include "frames/AllAgreementsFrame.h"
#include "frames/PaymentFrame.h"
#include "frames/AllPaymentsFrame.h"
#include "frames/DebtorsFrame.h"
#include "frames/GarageOccupancyFrame.h"
#include "frames/GarageFinanceFrame.h"
#include "frames/GarageRatingFrame.h"
#include "frames/ReturnRateFrame.h"
#include <wx/msgdlg.h>

MainFrame::MainFrame(wxWindow* parent, wxWindowID id, const wxString& title,
                     const wxPoint& pos, const wxSize& size, long style)
    : wxFrame(parent, id, title, pos, size, style), m_db(nullptr) {

    // ─── Menu bar ───────────────────────────────────────────────
    m_menubar5 = new wxMenuBar();

    // Assign explicit unique IDs to avoid wxIsStockID assertion
    int idLoadData    = wxNewId();
    int idSaveData    = wxNewId();
    int idBackup      = wxNewId();
    int idOccupancy   = wxNewId();
    int idFinance     = wxNewId();
    int idRating      = wxNewId();
    int idDebtors     = wxNewId();
    int idReturn      = wxNewId();
    int idLog         = wxNewId();
    int idHelp        = wxNewId();
    int idAbout       = wxNewId();

    Database = new wxMenu();
    Database->Append(idLoadData, wxT("Загрузить данные"));
    Database->Append(idSaveData, wxT("Сохранить данные"));
    Database->AppendSeparator();
    Database->Append(idBackup,   wxT("Резервная копия"));
    m_menubar5->Append(Database, wxT("База данных"));

    report = new wxMenu();
    report->Append(idOccupancy, wxT("Занятость гаражей"));
    report->Append(idFinance,   wxT("Финансы по гаражам"));
    report->Append(idRating,    wxT("Рейтинг гаражей"));
    report->AppendSeparator();
    report->Append(idDebtors,   wxT("Должники"));
    report->Append(idReturn,    wxT("Возврат средств"));
    m_menubar5->Append(report, wxT("Отчёты"));

    Service = new wxMenu();
    Service->Append(idLog, wxT("Журнал событий"));
    m_menubar5->Append(Service, wxT("Сервис"));

    Reference = new wxMenu();
    Reference->Append(idHelp,  wxT("Справка"));
    Reference->Append(idAbout, wxT("О программе"));
    m_menubar5->Append(Reference, wxT("Справка"));

    SetMenuBar(m_menubar5);

    // ─── Main layout ─────────────────────────────────────────────
    wxBoxSizer* rootSizer = new wxBoxSizer(wxVERTICAL);

    wxBoxSizer* rowSizer = new wxBoxSizer(wxHORIZONTAL);

    // ── Clients block ──────────────────────────────────────────
    wxStaticBoxSizer* clientBox = new wxStaticBoxSizer(wxVERTICAL, this, wxT("Арендаторы"));

    m_button45  = new wxButton(clientBox->GetStaticBox(), wxID_ANY, wxT("Добавить"));
    m_button20  = new wxButton(clientBox->GetStaticBox(), wxID_ANY, wxT("Редактировать"));
    m_button21  = new wxButton(clientBox->GetStaticBox(), wxID_ANY, wxT("Информация"));
    m_button22  = new wxButton(clientBox->GetStaticBox(), wxID_ANY, wxT("Все арендаторы"));

    clientBox->Add(m_button45,  0, wxEXPAND | wxALL, 4);
    clientBox->Add(m_button20,  0, wxEXPAND | wxALL, 4);
    clientBox->Add(m_button21,  0, wxEXPAND | wxALL, 4);
    clientBox->Add(m_button22,  0, wxEXPAND | wxALL, 4);
    rowSizer->Add(clientBox, 1, wxEXPAND | wxALL, 8);

    // ── Agreements block ───────────────────────────────────────
    wxStaticBoxSizer* dogovorBox = new wxStaticBoxSizer(wxVERTICAL, this, wxT("Договоры аренды"));

    m_button19          = new wxButton(dogovorBox->GetStaticBox(), wxID_ANY, wxT("Новый договор"));
    m_button38          = new wxButton(dogovorBox->GetStaticBox(), wxID_ANY, wxT("Продлить договор"));
    m_button23          = new wxButton(dogovorBox->GetStaticBox(), wxID_ANY, wxT("Редактировать"));
    m_button24          = new wxButton(dogovorBox->GetStaticBox(), wxID_ANY, wxT("Все договоры"));
    m_button31          = new wxButton(dogovorBox->GetStaticBox(), wxID_ANY, wxT("Информация"));
    m_buttonCloseRental = new wxButton(dogovorBox->GetStaticBox(), wxID_ANY, wxT("Закончить аренду"));

    dogovorBox->Add(m_button19,          0, wxEXPAND | wxALL, 4);
    dogovorBox->Add(m_button38,          0, wxEXPAND | wxALL, 4);
    dogovorBox->Add(m_button23,          0, wxEXPAND | wxALL, 4);
    dogovorBox->Add(m_button24,          0, wxEXPAND | wxALL, 4);
    dogovorBox->Add(m_button31,          0, wxEXPAND | wxALL, 4);
    dogovorBox->Add(m_buttonCloseRental, 0, wxEXPAND | wxALL, 4);
    rowSizer->Add(dogovorBox, 1, wxEXPAND | wxALL, 8);

    // ── Garages block ──────────────────────────────────────────
    wxStaticBoxSizer* garageBox = new wxStaticBoxSizer(wxVERTICAL, this, wxT("Гаражи"));

    m_button27  = new wxButton(garageBox->GetStaticBox(), wxID_ANY, wxT("Добавить гараж"));
    m_button28  = new wxButton(garageBox->GetStaticBox(), wxID_ANY, wxT("Удалить гараж"));
    m_button281 = new wxButton(garageBox->GetStaticBox(), wxID_ANY, wxT("Редактировать"));
    m_button29  = new wxButton(garageBox->GetStaticBox(), wxID_ANY, wxT("Все гаражи"));
    m_button30  = new wxButton(garageBox->GetStaticBox(), wxID_ANY, wxT("Информация"));

    garageBox->Add(m_button27,  0, wxEXPAND | wxALL, 4);
    garageBox->Add(m_button28,  0, wxEXPAND | wxALL, 4);
    garageBox->Add(m_button281, 0, wxEXPAND | wxALL, 4);
    garageBox->Add(m_button29,  0, wxEXPAND | wxALL, 4);
    garageBox->Add(m_button30,  0, wxEXPAND | wxALL, 4);
    rowSizer->Add(garageBox, 1, wxEXPAND | wxALL, 8);

    // ── Payments block ─────────────────────────────────────────
    wxStaticBoxSizer* payBox = new wxStaticBoxSizer(wxVERTICAL, this, wxT("Оплаты"));

    m_button32 = new wxButton(payBox->GetStaticBox(), wxID_ANY, wxT("Принять оплату"));
    m_button36 = new wxButton(payBox->GetStaticBox(), wxID_ANY, wxT("Редактировать"));
    m_button33 = new wxButton(payBox->GetStaticBox(), wxID_ANY, wxT("История оплат"));
    m_button35 = new wxButton(payBox->GetStaticBox(), wxID_ANY, wxT("Все оплаты"));
    m_button34 = new wxButton(payBox->GetStaticBox(), wxID_ANY, wxT("Возврат средств"));

    payBox->Add(m_button32, 0, wxEXPAND | wxALL, 4);
    payBox->Add(m_button36, 0, wxEXPAND | wxALL, 4);
    payBox->Add(m_button33, 0, wxEXPAND | wxALL, 4);
    payBox->Add(m_button35, 0, wxEXPAND | wxALL, 4);
    payBox->Add(m_button34, 0, wxEXPAND | wxALL, 4);
    rowSizer->Add(payBox, 1, wxEXPAND | wxALL, 8);

    rootSizer->Add(rowSizer, 1, wxEXPAND);
    SetSizer(rootSizer);
    SetMinSize(wxSize(800, 320));

    // ─── Button events ───────────────────────────────────────────
    m_button45->Bind(wxEVT_BUTTON,  &MainFrame::OnAddTenant,      this);
    m_button20->Bind(wxEVT_BUTTON,  &MainFrame::OnEditTenant,     this);
    m_button21->Bind(wxEVT_BUTTON,  &MainFrame::OnTenantInfo,     this);
    m_button22->Bind(wxEVT_BUTTON,  &MainFrame::OnAllTenants,     this);

    m_button19->Bind(wxEVT_BUTTON,          &MainFrame::OnNewAgreement,   this);
    m_button38->Bind(wxEVT_BUTTON,          &MainFrame::OnExtendAgreement,this);
    m_button23->Bind(wxEVT_BUTTON,          &MainFrame::OnEditAgreement,  this);
    m_button24->Bind(wxEVT_BUTTON,          &MainFrame::OnAllAgreements,  this);
    m_button31->Bind(wxEVT_BUTTON,          &MainFrame::OnAgreementInfo,  this);
    m_buttonCloseRental->Bind(wxEVT_BUTTON, &MainFrame::OnCloseRental,    this);

    m_button27->Bind(wxEVT_BUTTON,  &MainFrame::OnAddGarage,      this);
    m_button28->Bind(wxEVT_BUTTON,  &MainFrame::OnDeleteGarage,   this);
    m_button281->Bind(wxEVT_BUTTON, &MainFrame::OnEditGarage,     this);
    m_button29->Bind(wxEVT_BUTTON,  &MainFrame::OnAllGarages,     this);
    m_button30->Bind(wxEVT_BUTTON,  &MainFrame::OnGarageInfo,     this);

    m_button32->Bind(wxEVT_BUTTON,  &MainFrame::OnAddPayment,     this);
    m_button36->Bind(wxEVT_BUTTON,  &MainFrame::OnEditPayment,    this);
    m_button33->Bind(wxEVT_BUTTON,  &MainFrame::OnPaymentHistory, this);
    m_button35->Bind(wxEVT_BUTTON,  &MainFrame::OnAllPayments,    this);
    m_button34->Bind(wxEVT_BUTTON,  &MainFrame::OnRefundPayment,  this);

    // ─── Menu events ─────────────────────────────────────────────
    Bind(wxEVT_MENU, &MainFrame::OnLoadData,              this, idLoadData);
    Bind(wxEVT_MENU, &MainFrame::OnSaveData,              this, idSaveData);
    Bind(wxEVT_MENU, &MainFrame::OnBackup,                this, idBackup);
    Bind(wxEVT_MENU, &MainFrame::OnGarageOccupancyReport, this, idOccupancy);
    Bind(wxEVT_MENU, &MainFrame::OnGarageFinanceReport,   this, idFinance);
    Bind(wxEVT_MENU, &MainFrame::OnGarageRatingReport,    this, idRating);
    Bind(wxEVT_MENU, &MainFrame::OnDebtorsReport,         this, idDebtors);
    Bind(wxEVT_MENU, &MainFrame::OnReturnRateReport,      this, idReturn);
    Bind(wxEVT_MENU, &MainFrame::OnLogView,               this, idLog);
    Bind(wxEVT_MENU, &MainFrame::OnHelp,                  this, idHelp);
    Bind(wxEVT_MENU, &MainFrame::OnAbout,                 this, idAbout);
}

// ========== Clients ==========
void MainFrame::OnAddTenant(wxCommandEvent& event) {
    TenantEditFrame* frame = new TenantEditFrame(this, m_db, -1);
    frame->Show();
}

void MainFrame::OnEditTenant(wxCommandEvent& event) {
    wxArrayString choices;
    sqlite3* db = m_db->GetDB();
    if (db) {
        sqlite3_stmt* stmt;
        const char* sql = "SELECT id, surname, name FROM Tenant ORDER BY surname";
        if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
            while (sqlite3_step(stmt) == SQLITE_ROW) {
                int id = sqlite3_column_int(stmt, 0);
                wxString name = wxString::Format("%s %s",
                    wxString::FromUTF8((const char*)sqlite3_column_text(stmt, 1)),
                    wxString::FromUTF8((const char*)sqlite3_column_text(stmt, 2)));
                choices.Add(wxString::Format("%d - %s", id, name));
            }
            sqlite3_finalize(stmt);
        }
    }
    if (choices.IsEmpty()) { wxMessageBox(wxT("Нет арендаторов"), wxT("Информация"), wxOK | wxICON_INFORMATION); return; }
    wxSingleChoiceDialog dlg(this, wxT("Выберите арендатора:"), wxT("Редактирование"), choices);
    if (dlg.ShowModal() == wxID_OK) {
        int tenantId = wxAtoi(choices[dlg.GetSelection()].BeforeFirst(' '));
        TenantEditFrame* frame = new TenantEditFrame(this, m_db, tenantId);
        frame->Show();
    }
}

void MainFrame::OnTenantInfo(wxCommandEvent& event) {
    TenantInfoFrame* frame = new TenantInfoFrame(this, m_db);
    frame->Show();
}

void MainFrame::OnAllTenants(wxCommandEvent& event) {
    AllTenantsFrame* frame = new AllTenantsFrame(this, m_db);
    frame->Show();
}

// ========== Agreements ==========
void MainFrame::OnNewAgreement(wxCommandEvent& event) {
    NewAgreementFrame* frame = new NewAgreementFrame(this, m_db);
    frame->Show();
}

void MainFrame::OnExtendAgreement(wxCommandEvent& event) {
    wxMessageBox(wxT("Для продления откройте список договоров и выберите нужный."),
                 wxT("Продление договора"), wxOK | wxICON_INFORMATION);
    AllAgreementsFrame* frame = new AllAgreementsFrame(this, m_db);
    frame->Show();
}

void MainFrame::OnEditAgreement(wxCommandEvent& event) {
    AllAgreementsFrame* frame = new AllAgreementsFrame(this, m_db);
    frame->Show();
}

void MainFrame::OnAllAgreements(wxCommandEvent& event) {
    AllAgreementsFrame* frame = new AllAgreementsFrame(this, m_db);
    frame->Show();
}

void MainFrame::OnAgreementInfo(wxCommandEvent& event) {
    AllAgreementsFrame* frame = new AllAgreementsFrame(this, m_db);
    frame->Show();
}

void MainFrame::OnCloseRental(wxCommandEvent& event) {
    CloseAgreementFrame* frame = new CloseAgreementFrame(this, m_db);
    frame->Show();
}

// ========== Garages ==========
void MainFrame::OnAddGarage(wxCommandEvent& event) {
    GarageEditFrame* frame = new GarageEditFrame(this, m_db, -1);
    frame->Show();
}

void MainFrame::OnDeleteGarage(wxCommandEvent& event) {
    wxArrayString choices;
    sqlite3* db = m_db->GetDB();
    if (db) {
        sqlite3_stmt* stmt;
        const char* sql = "SELECT id, personal_numbers, location FROM Garage";
        if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
            while (sqlite3_step(stmt) == SQLITE_ROW) {
                int id = sqlite3_column_int(stmt, 0);
                wxString num = wxString::FromUTF8((const char*)sqlite3_column_text(stmt, 1));
                wxString loc = wxString::FromUTF8((const char*)sqlite3_column_text(stmt, 2));
                choices.Add(wxString::Format("%d - %s (%s)", id, num, loc));
            }
            sqlite3_finalize(stmt);
        }
    }
    if (choices.IsEmpty()) { wxMessageBox(wxT("Нет гаражей"), wxT("Информация"), wxOK | wxICON_INFORMATION); return; }
    wxSingleChoiceDialog dlg(this, wxT("Выберите гараж для удаления:"), wxT("Удаление"), choices);
    if (dlg.ShowModal() == wxID_OK) {
        int garageId = wxAtoi(choices[dlg.GetSelection()].BeforeFirst(' '));
        if (wxMessageBox(wxT("Удалить гараж?"), wxT("Подтверждение"), wxYES_NO | wxICON_QUESTION) == wxYES) {
            if (m_db->DeleteGarage(garageId))
                wxMessageBox(wxT("Гараж удалён"), wxT("Успех"), wxOK | wxICON_INFORMATION);
            else
                wxMessageBox(wxT("Ошибка при удалении"), wxT("Ошибка"), wxOK | wxICON_ERROR);
        }
    }
}

void MainFrame::OnEditGarage(wxCommandEvent& event) {
    wxArrayString choices;
    sqlite3* db = m_db->GetDB();
    if (db) {
        sqlite3_stmt* stmt;
        const char* sql = "SELECT id, personal_numbers, location FROM Garage";
        if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
            while (sqlite3_step(stmt) == SQLITE_ROW) {
                int id = sqlite3_column_int(stmt, 0);
                wxString num = wxString::FromUTF8((const char*)sqlite3_column_text(stmt, 1));
                wxString loc = wxString::FromUTF8((const char*)sqlite3_column_text(stmt, 2));
                choices.Add(wxString::Format("%d - %s (%s)", id, num, loc));
            }
            sqlite3_finalize(stmt);
        }
    }
    if (choices.IsEmpty()) { wxMessageBox(wxT("Нет гаражей"), wxT("Информация"), wxOK | wxICON_INFORMATION); return; }
    wxSingleChoiceDialog dlg(this, wxT("Выберите гараж:"), wxT("Редактирование"), choices);
    if (dlg.ShowModal() == wxID_OK) {
        int garageId = wxAtoi(choices[dlg.GetSelection()].BeforeFirst(' '));
        GarageEditFrame* frame = new GarageEditFrame(this, m_db, garageId);
        frame->Show();
    }
}

void MainFrame::OnAllGarages(wxCommandEvent& event) {
    AllGaragesFrame* frame = new AllGaragesFrame(this, m_db);
    frame->Show();
}

void MainFrame::OnGarageInfo(wxCommandEvent& event) {
    GarageInfoFrame* frame = new GarageInfoFrame(this, m_db);
    frame->Show();
}

// ========== Payments ==========
void MainFrame::OnAddPayment(wxCommandEvent& event) {
    PaymentFrame* frame = new PaymentFrame(this, m_db);
    frame->Show();
}

void MainFrame::OnEditPayment(wxCommandEvent& event) {
    AllPaymentsFrame* frame = new AllPaymentsFrame(this, m_db);
    frame->Show();
}

void MainFrame::OnPaymentHistory(wxCommandEvent& event) {
    TenantInfoFrame* frame = new TenantInfoFrame(this, m_db);
    frame->Show();
}

void MainFrame::OnAllPayments(wxCommandEvent& event) {
    AllPaymentsFrame* frame = new AllPaymentsFrame(this, m_db);
    frame->Show();
}

void MainFrame::OnRefundPayment(wxCommandEvent& event) {
    wxMessageBox(wxT("Функция возврата средств в разработке."), wxT("Возврат"), wxOK | wxICON_INFORMATION);
}

// ========== Menu ==========
void MainFrame::OnLoadData(wxCommandEvent& event) {
    wxMessageBox(wxT("Загрузка данных выполняется автоматически при старте."), wxT("База данных"), wxOK | wxICON_INFORMATION);
}

void MainFrame::OnSaveData(wxCommandEvent& event) {
    wxMessageBox(wxT("Данные сохраняются автоматически."), wxT("База данных"), wxOK | wxICON_INFORMATION);
}

void MainFrame::OnBackup(wxCommandEvent& event) {
    wxMessageBox(wxT("Резервная копия: скопируйте файл garage_rental.db."), wxT("Резервная копия"), wxOK | wxICON_INFORMATION);
}

void MainFrame::OnGarageOccupancyReport(wxCommandEvent& event) {
    GarageOccupancyFrame* frame = new GarageOccupancyFrame(this, m_db);
    frame->Show();
}

void MainFrame::OnGarageFinanceReport(wxCommandEvent& event) {
    GarageFinanceFrame* frame = new GarageFinanceFrame(this, m_db);
    frame->Show();
}

void MainFrame::OnGarageRatingReport(wxCommandEvent& event) {
    GarageRatingFrame* frame = new GarageRatingFrame(this, m_db);
    frame->Show();
}

void MainFrame::OnDebtorsReport(wxCommandEvent& event) {
    DebtorsFrame* frame = new DebtorsFrame(this, m_db);
    frame->Show();
}

void MainFrame::OnReturnRateReport(wxCommandEvent& event) {
    ReturnRateFrame* frame = new ReturnRateFrame(this, m_db);
    frame->Show();
}

void MainFrame::OnLogView(wxCommandEvent& event) {
    wxMessageBox(wxT("Журнал событий в разработке."), wxT("Журнал"), wxOK | wxICON_INFORMATION);
}

void MainFrame::OnHelp(wxCommandEvent& event) {
    wxMessageBox(
        wxT("Руководство пользователя:\n\n")
        "1. Арендаторы — добавление и управление клиентами\n"
        "2. Договоры — создание и контроль договоров аренды\n"
        "3. Гаражи — управление гаражным фондом\n"
        "4. Оплаты — приём и учёт платежей\n"
        "5. Отчёты доступны через меню «Отчёты»",
        wxT("Справка"), wxOK | wxICON_INFORMATION);
}

void MainFrame::OnAbout(wxCommandEvent& event) {
    wxMessageBox(
        wxT("Система управления арендой гаражей\n")
        wxT("Версия 1.0\n\n")
        wxT("Разработано с использованием wxWidgets и SQLite"),
        wxT("О программе"), wxOK | wxICON_INFORMATION);
}

MainFrame::~MainFrame() {}
