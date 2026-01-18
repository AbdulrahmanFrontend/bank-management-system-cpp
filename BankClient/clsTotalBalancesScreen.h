#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"
#include <iomanip>
#include "clsUtil.h"
class clsTotalBalancesScreen : protected clsScreen {
	static void _PrintClientRecordBalanceLine(clsBankClient Client) {
        cout << "\t| " << setw(15) << left << Client.AccountNumber();
        cout << "| " << setw(40) << left << Client.FullName();
        cout << "| " << setw(12) << left << Client.AccountBalance;
    };
public:
    static void ShowTotalBalances() {
        vector <clsBankClient> vClients = clsBankClient::GetClientsList();
        string Title = "\t  Balances List Screen";
        string SubTitle = "\t    (" + to_string(vClients.size()) + ") Client(s).";
        _DrawScreenHeader(Title, SubTitle);
        cout << endl << setw(8) << left << "\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;
        cout << "\t| " << left << setw(15) << "Accout Number";
        cout << "| " << left << setw(40) << "Client Name";
        cout << "| " << left << setw(12) << "Balance";
        cout << endl << setw(8) << left << "\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;
        double TotalBalances = clsBankClient::GetTotalBalances();
        if (vClients.size() == 0)
            cout << clsUtil::Tabs(4) << "No Clients Available In the System!\n";
        else {
            for (clsBankClient Client : vClients) {
                _PrintClientRecordBalanceLine(Client);
                cout << endl;
            };
            cout << setw(8) << left << "\t_______________________________________________________";
            cout << "_________________________________________\n" << endl;
            cout << clsUtil::Tabs(5) << "   Total Balances = " << TotalBalances << endl;
            cout << clsUtil::Tabs(4) << "( " << clsUtil::NumberToText(TotalBalances) << ")";
        }
    };
};