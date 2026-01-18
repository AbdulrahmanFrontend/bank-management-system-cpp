#pragma once
#include "clsScreen.h"
#include "clsBankClient.h";
#include "clsInputValidate.h"
class clsTransferScreen : protected clsScreen {
    static void _PrintClient(clsBankClient Client) {
        cout << endl << "Client Card:";
        cout << endl << "---------------------\n";
        cout << "Full Name   : " << Client.FullName() << ".\n";
        cout << "Acc. Number : " << Client.AccountNumber() << ".\n";
        cout << "Balance     : " << Client.AccountBalance << ".";
        cout << endl << "---------------------\n";
    };
    static string _ReadAccountNumber() {
        string AccountNumber = "";
        bool IsClientNotFound = false;
        do {
            AccountNumber = clsInputValidate<int>::ReadString();
            IsClientNotFound = !clsBankClient::IsClientExist(AccountNumber);
            if (IsClientNotFound)
                cout << endl << "Account Number is not found, enter another one: ";
        } while (IsClientNotFound);
        return AccountNumber;
    };
    static double _ReadAmount(clsBankClient SourceClient) {
        cout << "\nPlease, enter transfer amount: ";
        double Amount = clsInputValidate<double>::ReadNumber();
        while (Amount > SourceClient.AccountBalance) {
            cout << "\nAccount exceeds the available balance, enter another amount: ";
            Amount = clsInputValidate<double>::ReadNumber();
        };
        return Amount;
    };
public:
    static void ShowTransferScreen() {
        _DrawScreenHeader("\t  Transfer Screen");
        cout << "\nPlease, enter account number to transfer from: ";
        clsBankClient SourceClient = clsBankClient::Find(_ReadAccountNumber());
        _PrintClient(SourceClient);
        cout << "\nPlease, enter account number to transfer to: ";
        clsBankClient DestinationClient = clsBankClient::Find(_ReadAccountNumber());
        _PrintClient(DestinationClient);
        double Amount = _ReadAmount(SourceClient);
        cout << endl << "Are you sure you want to perform this operation (y/n)? ";
        char Answer = 'n';
        cin >> Answer;
        if (tolower(Answer) == 'y') {
            if (SourceClient.Transfer(Amount, DestinationClient))
                cout << endl << "Transfer is done successfully :-)\n";
            else
                cout << endl << "Transfer is failed :-(\n";
        };
        _PrintClient(SourceClient);
        _PrintClient(DestinationClient);
    };
};