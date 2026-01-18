#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
class clsWithdrawScreen : protected clsScreen {
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
    static void ShowWithdrawScreen() {
        _DrawScreenHeader("\t  Withdraw Screen");
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
        _PrintClient(Client1);
        cout << "\nPlease, enter withdraw amount: ";
        double Amount = clsInputValidate<double>::ReadNumber();
        cout << endl << "Are you sure you want to perform this transaction (y/n)? ";
        char Answer = 'n';
        cin >> Answer;
        if (tolower(Answer) == 'y') {
            if (Client1.Withdraw(Amount)) {
                cout << endl << "Account has been withdrawed successfully :-)\n";
                cout << "\nNew Balance is: " << Client1.AccountBalance << ".\n";
            }
            else {
                cout << "\nWe cannot withdraw, insuffecient balance!\n";
                cout << "Amount to withdraw is: " << Amount << ".\n";
                cout << "Your balace is: " << Client1.AccountBalance << ".\n";
            };
        };
    };
};