#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
class clsUpdateClientScreen : protected clsScreen {
    static void _ReadClientInfo(clsBankClient& Client) {
        cout << endl << "Enter FirstName: ";
        Client.FirstName = clsInputValidate<int>::ReadString();
        cout << endl << "Enter LastName: ";
        Client.LastName = clsInputValidate<int>::ReadString();
        cout << endl << "Enter Email: ";
        Client.Email = clsInputValidate<int>::ReadString();
        cout << endl << "Enter Phone: ";
        Client.Phone = clsInputValidate<int>::ReadString();
        cout << endl << "Enter Pin Code: ";
        Client.PinCode = clsInputValidate<int>::ReadString();
        cout << endl << "Enter Account Balance: ";
        Client.AccountBalance = clsInputValidate<float>::ReadNumber();
    };
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
    static void ShowUpdateClientScreen() {
        if (!CheckAccessRights(clsUser::enPermissions::pUpdateClient))
            return;
        _DrawScreenHeader("\t  Update Client Screen");
        string AccountNumber = "";
        bool IsClientNotFound = false;
        cout << endl << "Please, enter account number: ";
        do {
            AccountNumber = clsInputValidate<int>::ReadString();
            IsClientNotFound = !clsBankClient::IsClientExist(AccountNumber);
            if (IsClientNotFound)
                cout << endl << "Account Number is found, enter another one: ";
        } while (IsClientNotFound);
        clsBankClient Client1 = clsBankClient::Find(AccountNumber);
        _PrintClient(Client1);
        cout << endl << "Are you sure you want to update this client (y/n)? ";
        char Answer = 'n';
        cin >> Answer;
        if (tolower(Answer) == 'y') {
            cout << endl << endl << "Update Client Info:";
            cout << endl << "______________________\n";
            _ReadClientInfo(Client1);
            clsBankClient::enSaveResults SaveResult;
            SaveResult = Client1.Save();
            switch (SaveResult) {
            case clsBankClient::enSaveResults::svSecceeded:
                cout << endl << "Account has been updated successfully :-)\n";
                _PrintClient(Client1);
                break;
            case clsBankClient::enSaveResults::svFailedEmptyObject:
                cout << endl << "Error Account wasn't saved because it's empty.\n";
            };
        };
    };
};