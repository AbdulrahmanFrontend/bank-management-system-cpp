#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
class clsAddNewClientScreen : protected clsScreen {
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
    static void ShowAddNewClientScreen() {
        if (!CheckAccessRights(clsUser::enPermissions::pAddNewClient))
            return;
        _DrawScreenHeader("\t  Add New Client Screen");
        string AccountNumber = "";
        bool IsClientFound = false;
        cout << endl << "Please, enter account number: ";
        do {
            AccountNumber = clsInputValidate<int>::ReadString();
            IsClientFound = clsBankClient::IsClientExist(AccountNumber);
            if (IsClientFound)
                cout << endl << "Account Number is found, enter another one: ";
        } while (IsClientFound);
        clsBankClient NewClient = clsBankClient::GetAddNewClientObject(AccountNumber);
        _ReadClientInfo(NewClient);
        clsBankClient::enSaveResults SaveResult;
        SaveResult = NewClient.Save();
        switch (SaveResult) {
        case clsBankClient::enSaveResults::svSecceeded:
            cout << endl << "Account has been updated successfully :-)\n";
            _PrintClient(NewClient);
            break;
        case clsBankClient::enSaveResults::svFailedEmptyObject:
            cout << endl << "Error, account wasn't saved because it's empty.\n";
            break;
        case clsBankClient::enSaveResults::svFailedAccountNumberExists:
            cout << endl << "Error, account wasn't saved because account number is used!\n";
        };
    };
};