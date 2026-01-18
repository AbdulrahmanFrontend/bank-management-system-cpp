#pragma once
#include "clsDepositScreen.h"
#include "clsWithdrawScreen.h"
#include "clsTotalBalancesScreen.h"
#include "clsTransferScreen.h"
#include "clsTransferLogScreen.h"
class clsTransactionsScreen : protected clsScreen {
    enum enTransactionsMenuOptions {
        eDeposit = 1, eWithdraw, eShowTotalBalance,
        eTransfer, eTransferLog, eShowMainMenu
    };
    static short ReadTransactionsMenuOption() {
        cout << setw(37) << left << "" << "Choose what do you want to do [1 to 6]: ";
        short Choice = clsInputValidate<short>::ReadNumberBetween(1, 6, "Enter Number between 1 to 6: ");
        return Choice;
    };
    static void _ShowDepositScreen() {
        //cout << "\n Deposit Screen will be here.\n";
        clsDepositScreen::ShowDepositScreen();
    };
    static void _ShowWithdrawScreen() {
        //cout << "\n Withdraw Screen will be here.\n";
        clsWithdrawScreen::ShowWithdrawScreen();
    };
    static void _ShowTotalBalancesScreen() {
        //cout << "\n Balances Screen will be here.\n";
        clsTotalBalancesScreen::ShowTotalBalances();
    };
    static void _ShowTransferScreen() {
        //cout << "\n Balances Screen will be here.\n";
        clsTransferScreen::ShowTransferScreen();
    };
    static void _ShowTransferLogScreen() {
        //cout << "\n Balances Screen will be here.\n";
        clsTransferLogScreen::ShowTransferLogScreen();
    };
    static void _GoBackToTransactionsMenu() {
        cout << "\n\nPress any key to go back to Transactions Menu...";
        system("pause>0");
        ShowTransactionsMenu();
    };
    static void _PerformTransactionsMenuOption(enTransactionsMenuOptions TransactionsMenuOption) {
        system("cls");
        switch (TransactionsMenuOption) {
        case enTransactionsMenuOptions::eDeposit:
            _ShowDepositScreen();
            _GoBackToTransactionsMenu();
            break;
        case enTransactionsMenuOptions::eWithdraw:
            _ShowWithdrawScreen();
            _GoBackToTransactionsMenu();
            break;
        case enTransactionsMenuOptions::eShowTotalBalance:
            _ShowTotalBalancesScreen();
            _GoBackToTransactionsMenu();
            break;
        case enTransactionsMenuOptions::eTransfer:
            _ShowTransferScreen();
            _GoBackToTransactionsMenu();
            break;
        case enTransactionsMenuOptions::eTransferLog:
            _ShowTransferLogScreen();
            _GoBackToTransactionsMenu();
            break;
        case enTransactionsMenuOptions::eShowMainMenu:
            break;
        };
    };
public:
    static void ShowTransactionsMenu() {
        if (!CheckAccessRights(clsUser::enPermissions::pTransactions))
            return;
        system("cls");
        _DrawScreenHeader("\t  Transactions Screen");
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << clsUtil::Tabs(2) << "  Transactions Menu\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] Deposit.\n";
        cout << setw(37) << left << "" << "\t[2] Withdraw.\n";
        cout << setw(37) << left << "" << "\t[3] Total Balances.\n";
        cout << setw(37) << left << "" << "\t[4] Transfer.\n";
        cout << setw(37) << left << "" << "\t[5] Transfer Log.\n";
        cout << setw(37) << left << "" << "\t[6] Main Menu.\n";
        cout << setw(37) << left << "" << "===========================================\n";
        _PerformTransactionsMenuOption((enTransactionsMenuOptions)ReadTransactionsMenuOption());
    };
};