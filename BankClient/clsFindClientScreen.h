#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
class clsFindClientScreen : protected clsScreen {
    static void _PrintClient(clsBankClient Client) {
        cout << endl << "Client Card:";
        cout << endl << "---------------------\n";
        cout << "FirstName   : " << Client.FirstName << ".\n";
        cout << "LastName    : " << Client.LastName << ".\n";
        cout << "Full Name   : " << Client.FullName() << ".\n";
        cout << "Email       : " << Client.Email << ".\n";
        cout << "Phone       : " << Client.Phone << ".\n";
        cout << "Acc. Number : " << Client.AccountNumber() << ".\n";
        cout << "Password    : " << Client.PinCode << ".\n";
        cout << "Balance     : " << Client.AccountBalance << ".";
        cout << endl << "---------------------\n";
    };
public:
	static void ShowFindClientScreen() {
        if (!CheckAccessRights(clsUser::enPermissions::pFindClient))
            return;
        _DrawScreenHeader("\t  Add New Client Screen");
        string AccountNumber = "";
        bool IsClientNotFound = false;
        cout << endl << "Please, enter account number: ";
        do {
            AccountNumber = clsInputValidate<int>::ReadString();
            IsClientNotFound = !clsBankClient::IsClientExist(AccountNumber);
            if (IsClientNotFound)
                cout << endl << "Account Number is not found, enter another one: ";
        } while (IsClientNotFound);
        clsBankClient Client1 = clsBankClient::Find(AccountNumber);
        if (Client1.IsEmpty())
            cout << endl << "Client is not found :-)\n";
        else
            cout << endl << "Client is found :-)\n";
        _PrintClient(Client1);
    };
};