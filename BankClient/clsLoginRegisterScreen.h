#pragma once
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"
#include <iomanip>
class clsLoginRegisterScreen : protected clsScreen {
    static void _PrintLoginRegisterRecordLine(clsUser::stLoginRegisterRecord LoginRegisterRecord) {
        cout << setw(8) << left << "" << "| " << setw(35) << left << LoginRegisterRecord.DateTime;
        cout << "| " << setw(20) << left << LoginRegisterRecord.UserName;
        cout << "| " << setw(20) << left << LoginRegisterRecord.Password;
        cout << "| " << setw(10) << left << LoginRegisterRecord.Permissions;
    };
public:
    static void ShowLoginRegisterScreen() {
        if (!CheckAccessRights(clsUser::enPermissions::pShowLoginRegister))
            return;
        vector <clsUser::stLoginRegisterRecord> vLoginRegisterRecord = clsUser::GetLoginRegisterList();
        string Title = "\tLogin Register List Screen";
        string SubTitle = "\t    (" + to_string(vLoginRegisterRecord.size()) + ") User(s).";
        _DrawScreenHeader(Title, SubTitle);
        cout << endl << setw(8) << left << "\t_______________________________________________________";
        cout << "_____________________________________________\n\n";
        cout << "\t| " << setw(35) << left << "Date/Time";
        cout << "| " << setw(20) << left << "UserName";
        cout << "| " << setw(20) << left << "Password";
        cout << "| " << setw(10) << left << "Permissions";
        cout << endl << setw(8) << left << "\t_______________________________________________________";
        cout << "_____________________________________________\n" << endl;
        if (vLoginRegisterRecord.size() == 0)
            cout << clsUtil::Tabs(4) << "No Logins Available In the System!\n";
        else
            for (clsUser::stLoginRegisterRecord LoginRegisterRecord : vLoginRegisterRecord) {
                _PrintLoginRegisterRecordLine(LoginRegisterRecord);
                cout << endl;
            };
        cout << setw(8) << left << "\t_______________________________________________________";
        cout << "_____________________________________________\n" << endl;
    };
};