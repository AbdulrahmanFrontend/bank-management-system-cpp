#pragma once
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"
class clsUpdateUserScreen : protected clsScreen {
    static void _ReadUserInfo(clsUser& User) {
        cout << endl << "Enter FirstName: ";
        User.FirstName = clsInputValidate<int>::ReadString();
        cout << endl << "Enter LastName: ";
        User.LastName = clsInputValidate<int>::ReadString();
        cout << endl << "Enter Email: ";
        User.Email = clsInputValidate<int>::ReadString();
        cout << endl << "Enter Phone: ";
        User.Phone = clsInputValidate<int>::ReadString();
        cout << endl << "Enter Password: ";
        User.Password = clsInputValidate<int>::ReadString();
        cout << endl << "Enter Permissions: ";
        if (User.UserName == "Admin") {
            cout << "\nThe User 'Admin' cannot changed his permissions.\n";
            return;
        }
        User.Permissions = _ReadPermissionsToSet();
    };
    static void _PrintUser(clsUser User) {
        cout << endl << "User Card:";
        cout << endl << "---------------------\n";
        cout << "FirstName   : " << User.FirstName << ".\n";
        cout << "LastName    : " << User.LastName << ".\n";
        cout << "Full Name   : " << User.FullName() << ".\n";
        cout << "Email       : " << User.Email << ".\n";
        cout << "Phone       : " << User.Phone << ".\n";
        cout << "User Name   : " << User.UserName << ".\n";
        cout << "Password    : " << User.Password << ".\n";
        cout << "Permissions : " << User.Permissions << ".";
        cout << endl << "---------------------\n";
    };
    static short _ReadPermissionsToSet() {
        short Permissions = 0;
        char Answer = 'n';
        cout << "\nDo you want to give full access (y/n)? ";
        cin >> Answer;
        if (tolower(Answer) == 'y')
            return -1;
        cout << "\nDo you want to give access to: \n ";
        cout << "\nShow Client List (y/n)? ";
        cin >> Answer;
        if (tolower(Answer) == 'y')
            Permissions += clsUser::enPermissions::pListClients;
        cout << "\nAdd New Client (y/n)? ";
        cin >> Answer;
        if (tolower(Answer) == 'y')
            Permissions += clsUser::enPermissions::pAddNewClient;
        cout << "\nDelete Client (y/n)? ";
        cin >> Answer;
        if (tolower(Answer) == 'y')
            Permissions += clsUser::enPermissions::pDeleteClient;
        cout << "\nUpdate Client (y/n)? ";
        cin >> Answer;
        if (tolower(Answer) == 'y')
            Permissions += clsUser::enPermissions::pUpdateClient;
        cout << "\nFind Client (y/n)? ";
        cin >> Answer;
        if (tolower(Answer) == 'y')
            Permissions += clsUser::enPermissions::pFindClient;
        cout << "\nTransactions (y/n)? ";
        cin >> Answer;
        if (tolower(Answer) == 'y')
            Permissions += clsUser::enPermissions::pTransactions;
        cout << "\nManage Users (y/n)? ";
        cin >> Answer;
        if (tolower(Answer) == 'y')
            Permissions += clsUser::enPermissions::pManageUsers;
        cout << "\nShow Login Register List (y/n)? ";
        cin >> Answer;
        if (tolower(Answer) == 'y')
            Permissions += clsUser::enPermissions::pShowLoginRegister;
        cout << "\nCurrency Exchange (y/n)? ";
        cin >> Answer;
        if (tolower(Answer) == 'y')
            Permissions += clsUser::enPermissions::pCurrencyExchange;
        if (Permissions == 511)
            Permissions = -1;
        return Permissions;
    };
public:
    static void ShowUpdateUserScreen() {
        _DrawScreenHeader("\t  Update User Screen");
        string UserName = "";
        bool IsUserNotFound = false;
        cout << endl << "Please, enter user name: ";
        do {
            UserName = clsInputValidate<int>::ReadString();
            IsUserNotFound = !clsUser::IsUserExist(UserName);
            if (IsUserNotFound)
                cout << endl << "User Name is not found, enter another one: ";
        } while (IsUserNotFound);
        clsUser User1 = clsUser::Find(UserName);
        _PrintUser(User1);
        cout << endl << "Are you sure you want to update this user (y/n)? ";
        char Answer = 'n';
        cin >> Answer;
        if (tolower(Answer) == 'y') {
            cout << endl << endl << "Update User Info:";
            cout << endl << "______________________\n";
            _ReadUserInfo(User1);
            clsUser::enSaveResults SaveResult;
            SaveResult = User1.Save();
            switch (SaveResult) {
            case clsUser::enSaveResults::svSecceeded:
                cout << endl << "User has been updated successfully :-)\n";
                _PrintUser(User1);
                break;
            case clsUser::enSaveResults::svFailedEmptyObject:
                cout << endl << "Error User wasn't saved because it's empty.\n";
            };
        };
    };
};