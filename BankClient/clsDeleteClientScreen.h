#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
class clsDeleteClientScreen : protected clsScreen {
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
	static void ShowDeleteClientScreen() {
        if (!CheckAccessRights(clsUser::enPermissions::pDeleteClient))
            return;
        _DrawScreenHeader("\t  Delete Client Screen");
        string AccountNumber = "";
        bool IsClientNotFound = false;
        cout << endl << "Please, enter account number: ";
        do {
            AccountNumber = clsInputValidate<int>::ReadString();
            IsClientNotFound = !clsBankClient::IsClientExist(AccountNumber);
            if (IsClientNotFound)
                cout << "Account Number is not found, enter another one: ";
        } while (IsClientNotFound);
        clsBankClient Client1 = clsBankClient::Find(AccountNumber);
        _PrintClient(Client1);
        cout << endl << "Are you sure you want to delete this client (y/n)? ";
        char Answer = 'n';
        cin >> Answer;
        if (tolower(Answer) == 'y') {
            if (Client1.Delete()) {
                cout << endl << "Client has been deleted successfully.\n";
                _PrintClient(Client1);
            }
            else
                cout << endl << "Error, client isn't deleted.\n";
        };
    };
};