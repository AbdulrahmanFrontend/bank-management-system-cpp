#pragma once
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"
class clsFindUserScreen : protected clsScreen {
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
public:
    static void ShowFindUserScreen() {
        _DrawScreenHeader("\t  Add New User Screen");
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
        if (User1.IsEmpty())
            cout << endl << "User is not found :-)\n";
        else
            cout << endl << "User is found :-)\n";
        _PrintUser(User1);
    };
};