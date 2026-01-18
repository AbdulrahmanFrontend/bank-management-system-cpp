#pragma once
#include "clsAddNewClientScreen.h"
#include "clsClientsListScreen.h"
#include "clsDeleteClientScreen.h"
#include "clsFindClientScreen.h"
#include "clsUpdateClientScreen.h"
#include "clsTransactionsScreen.h"
#include "clsManageUsersScreen.h"
#include "Global.h"
#include "clsLoginRegisterScreen.h"
#include "clsCurrencyExchangeMainScreen.h"
class clsMainScreen : protected clsScreen {
    enum enMainMenuOptions {
        eListClients = 1, eAddNewClient, eDeleteClient,
        eUpdateClient, eFindClient, eShowTransactionsMenu,
        eManageUsers, eLoginRegister, eCurrencyExchange, eExit
    };
    static short _ReadMainMenuOption() {
        cout << setw(37) << left << "" << "Choose what do you want to do [1 to 10]: ";
        short Choice = clsInputValidate<short>::ReadNumberBetween(1, 10, "Enter Number between 1 to 10: ");
        return Choice;
    };
    static  void _GoBackToMainMenu() {
        cout << "\n\nPress any key to go back to Main Menu...";
        system("pause>0");
        ShowMainMenu();
    };
    static void _ShowAllClientsScreen() {
        //  cout << "\nClient List Screen Will be here...\n";
        clsClientsListScreen::ShowClientsList();
    };
    static void _ShowAddNewClientsScreen() {
        // cout << "\nAdd New Client Screen Will be here...\n";
        clsAddNewClientScreen::ShowAddNewClientScreen();
    };
    static void _ShowDeleteClientScreen() {
        //cout << "\nDelete Client Screen Will be here...\n";
        clsDeleteClientScreen::ShowDeleteClientScreen();
    };
    static void _ShowUpdateClientScreen() {
        //cout << "\nUpdate Client Screen Will be here...\n";
        clsUpdateClientScreen::ShowUpdateClientScreen();
    };
    static void _ShowFindClientScreen() {
        // cout << "\nFind Client Screen Will be here...\n";
        clsFindClientScreen::ShowFindClientScreen();
    };
    static void _ShowTransactionsMenu() {
        // cout << "\nTransactions Menue Will be here...\n";
        clsTransactionsScreen::ShowTransactionsMenu();
    };
    static void _ShowManageUsersMenu() {
        //cout << "\nUsers Menue Will be here...\n";
        clsManageUsersScreen::ShowManageUsersMenu();
    };
    static void _ShowLoginRegisterScreen() {
        //cout << "\nUsers Menue Will be here...\n";
        clsLoginRegisterScreen::ShowLoginRegisterScreen();
    };
    static void _ShowCurrencyExchangeMainScreen() {
        //cout << "\nUsers Menue Will be here...\n";
        clsCurrencyExchangeMainScreen::ShowCurrenciesMenu();
    };
    /*static void _ShowEndScreen() {
        cout << "\nEnd Screen Will be here...\n";
    };*/
    static void _Logout() {
        CurrentUser = clsUser::Find("", "");
    };
    static void _PerformMainMenuOption(enMainMenuOptions MainMenuOption) {
        system("cls");
        switch (MainMenuOption) {
        case enMainMenuOptions::eListClients:
            _ShowAllClientsScreen();
            _GoBackToMainMenu();
            break;
        case enMainMenuOptions::eAddNewClient:
            _ShowAddNewClientsScreen();
            _GoBackToMainMenu();
            break;
        case enMainMenuOptions::eDeleteClient:
            _ShowDeleteClientScreen();
            _GoBackToMainMenu();
            break;
        case enMainMenuOptions::eUpdateClient:
            _ShowUpdateClientScreen();
            _GoBackToMainMenu();
            break;
        case enMainMenuOptions::eFindClient:
            _ShowFindClientScreen();
            _GoBackToMainMenu();
            break;
        case enMainMenuOptions::eShowTransactionsMenu:
            _ShowTransactionsMenu();
            _GoBackToMainMenu();
            break;
        case enMainMenuOptions::eManageUsers:
            _ShowManageUsersMenu();
            _GoBackToMainMenu();
            break;
        case enMainMenuOptions::eLoginRegister:
            _ShowLoginRegisterScreen();
            _GoBackToMainMenu();
            break;
        case enMainMenuOptions::eCurrencyExchange:
            _ShowCurrencyExchangeMainScreen();
            _GoBackToMainMenu();
            break;
        case enMainMenuOptions::eExit:
            _Logout();
        };
    };
public:
    static void ShowMainMenu() {
        system("cls");
        _DrawScreenHeader(clsUtil::Tabs(2) + "Main Screen");
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << clsUtil::Tabs(3) << "Main Menu\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] Show Client List.\n";
        cout << setw(37) << left << "" << "\t[2] Add New Client.\n";
        cout << setw(37) << left << "" << "\t[3] Delete Client.\n";
        cout << setw(37) << left << "" << "\t[4] Update Client Info.\n";
        cout << setw(37) << left << "" << "\t[5] Find Client.\n";
        cout << setw(37) << left << "" << "\t[6] Transactions.\n";
        cout << setw(37) << left << "" << "\t[7] Manage Users.\n";
        cout << setw(37) << left << "" << "\t[8] Login Register.\n";
        cout << setw(37) << left << "" << "\t[9] Currency Exchange.\n";
        cout << setw(37) << left << "" << "\t[10] Logout.\n";
        cout << setw(37) << left << "" << "===========================================\n";
        _PerformMainMenuOption((enMainMenuOptions)_ReadMainMenuOption());
    };
};