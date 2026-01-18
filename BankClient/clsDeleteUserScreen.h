#pragma once
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"
class clsDeleteUserScreen : protected clsScreen {
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
    static void ShowDeleteUserScreen() {
        _DrawScreenHeader("\t  Delete User Screen");
        string UserName = "";
        bool IsUserNotFound = false;
        cout << endl << "Please, enter User Name: ";
        do {
            do {
                UserName = clsInputValidate<int>::ReadString();
                if (UserName == "Admin")
                    cout << "\nThe User 'Admin' cannot deleted, enter another one: ";
            } while (UserName == "Admin");
            IsUserNotFound = !clsUser::IsUserExist(UserName);
            if (IsUserNotFound)
                cout << "User Name is not found, enter another one: ";
        } while (IsUserNotFound);
        clsUser User1 = clsUser::Find(UserName);
        _PrintUser(User1);
        cout << endl << "Are you sure you want to delete this User (y/n)? ";
        char Answer = 'n';
        cin >> Answer;
        if (tolower(Answer) == 'y') {
            if (User1.Delete()) {
                cout << endl << "User has been deleted successfully.\n";
                _PrintUser(User1);
            }
            else
                cout << endl << "Error, user isn't deleted.\n";
        };
    };
};