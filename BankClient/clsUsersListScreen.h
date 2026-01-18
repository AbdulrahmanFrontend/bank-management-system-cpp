#pragma once
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsUser.h"
#include <iomanip>
class clsUsersListScreen : protected clsScreen {
    static void _PrintUserRecordLine(clsUser User) {
        cout << "\t| " << setw(15) << left << User.UserName;
        cout << "| " << setw(20) << left << User.FullName();
        cout << "| " << setw(12) << left << User.Phone;
        cout << "| " << setw(20) << left << User.Email;
        cout << "| " << setw(10) << left << User.Password;
        cout << "| " << setw(12) << left << User.Permissions;
    };
public:
    static void ShowUsersList() {
        vector <clsUser> vUsers = clsUser::GetUsersList();
        string Title = "\t  User List Screen";
        string SubTitle = "\t    (" + to_string(vUsers.size()) + ") User(s).";
        _DrawScreenHeader(Title, SubTitle);
        cout << endl << setw(8) << left << "\t_______________________________________________________";
        cout << "_____________________________________________\n\n";
        cout << "\t| " << setw(15) << left << "UserName";
        cout << "| " << setw(20) << left << "User Name";
        cout << "| " << setw(12) << left << "Phone";
        cout << "| " << setw(20) << left << "Email";
        cout << "| " << setw(10) << left << "Password";
        cout << "| " << setw(12) << left << "Permissions";
        cout << endl << setw(8) << left << "\t_______________________________________________________";
        cout << "_____________________________________________\n" << endl;
        if (vUsers.size() == 0)
            cout << clsUtil::Tabs(3) << "No Users Available In the System!\n";
        else
            for (clsUser User : vUsers) {
                _PrintUserRecordLine(User);
                cout << endl;
            };
        cout << setw(8) << left << "\t_______________________________________________________";
        cout << "_____________________________________________\n" << endl;
    };
};