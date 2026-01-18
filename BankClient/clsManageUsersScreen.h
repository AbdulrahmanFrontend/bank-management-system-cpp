#pragma once
#include "clsUsersListScreen.h"
#include "clsAddNewUserScreen.h"
#include "clsDeleteUserScreen.h"
#include "clsUpdateUserScreen.h"
#include "clsFindUserScreen.h"
class clsManageUsersScreen : protected clsScreen {
    enum enManageUsersMenuOptions {
        eListUsers = 1, eAddNewUser, eDeleteUser,
        eUpdateUpdate, eFindUser, eMainMenu
    };
    static short _ReadManageUsersMenuOption() {
        cout << setw(37) << left << "" << "Choose what do you want to do [1 to 6]: ";
        short Choice = clsInputValidate<short>::ReadNumberBetween(1, 6, "Enter Number between 1 to 6: ");
        return Choice;
    };
    static  void _GoBackToManageUsersMenu() {
        cout << "\n\nPress any key to go back to Manage Users Menu...";
        system("pause>0");
        ShowManageUsersMenu();
    };
    static void _ShowAllUsersScreen() {
          //cout << "\nUsers List Screen Will be here...\n";
        clsUsersListScreen::ShowUsersList();
    };
    static void _ShowAddNewUserScreen() {
         //cout << "\nAdd New User Screen Will be here...\n";
        clsAddNewUserScreen::ShowAddNewUserScreen();
    };
    static void _ShowDeleteUserScreen() {
        //cout << "\nDelete User Screen Will be here...\n";
        clsDeleteUserScreen::ShowDeleteUserScreen();
    };
    static void _ShowUpdateUserScreen() {
        //cout << "\nUpdate User Screen Will be here...\n";
        clsUpdateUserScreen::ShowUpdateUserScreen();
    };
    static void _ShowFindUserScreen() {
         //cout << "\nFind User Screen Will be here...\n";
        clsFindUserScreen::ShowFindUserScreen();
    };
    static void _PerfromManageUsersMenuOption(enManageUsersMenuOptions ManagerUsersMenuOption) {
        system("cls");
        switch (ManagerUsersMenuOption) {
        case enManageUsersMenuOptions::eListUsers:
            _ShowAllUsersScreen();
            _GoBackToManageUsersMenu();
            break;
        case enManageUsersMenuOptions::eAddNewUser:
            _ShowAddNewUserScreen();
            _GoBackToManageUsersMenu();
            break;
        case enManageUsersMenuOptions::eDeleteUser:
            _ShowDeleteUserScreen();
            _GoBackToManageUsersMenu();
            break;
        case enManageUsersMenuOptions::eUpdateUpdate:
            _ShowUpdateUserScreen();
            _GoBackToManageUsersMenu();
            break;
        case enManageUsersMenuOptions::eFindUser:
            _ShowFindUserScreen();
            _GoBackToManageUsersMenu();
            break;
        case enManageUsersMenuOptions::eMainMenu:
            break;
        };
    };
public:
    static void ShowManageUsersMenu() {
        if (!CheckAccessRights(clsUser::enPermissions::pManageUsers))
            return;
        system("cls");
        _DrawScreenHeader("\t  Manage Users Screen");
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << clsUtil::Tabs(3) << "Manage Users Menu\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] Show Users List.\n";
        cout << setw(37) << left << "" << "\t[2] Add New User.\n";
        cout << setw(37) << left << "" << "\t[3] Delete User.\n";
        cout << setw(37) << left << "" << "\t[4] Update User Info.\n";
        cout << setw(37) << left << "" << "\t[5] Find User.\n";
        cout << setw(37) << left << "" << "\t[6] Main Menu.\n";
        cout << setw(37) << left << "" << "===========================================\n";
        _PerfromManageUsersMenuOption((enManageUsersMenuOptions)_ReadManageUsersMenuOption());
    };
};