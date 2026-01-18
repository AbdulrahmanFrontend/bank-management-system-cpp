#pragma once
#include "clsUtil.h"
#include "Global.h"
class clsScreen {
protected:
    static void _DrawScreenHeader(string Title, string SubTitle = "") {
        cout << clsUtil::Tabs(5) << "______________________________________";
        cout << "\n\n" << clsUtil::Tabs(5) << "  " << Title;
        if (SubTitle != "")
            cout << endl << clsUtil::Tabs(5) << "  " << SubTitle;
        cout << endl << clsUtil::Tabs(5) << "______________________________________\n\n";
        cout << endl << clsUtil::Tabs(5) << "User: " << CurrentUser.UserName << ".\n";
        cout << clsUtil::Tabs(5) << "Date: " << clsDate::DateToString(clsDate()) << ".\n\n";
    };
    static bool CheckAccessRights(clsUser::enPermissions Permissions) {
        if (!CurrentUser.CheckAccessPermissions(Permissions)) {
            cout << clsUtil::Tabs(5) << "______________________________________";
            cout << "\n\n" << clsUtil::Tabs(5) << "  Access Denied! Contact your Admin.";
            cout << endl << clsUtil::Tabs(5) << "______________________________________\n\n";
            return false;
        };
        return true;
    };
};