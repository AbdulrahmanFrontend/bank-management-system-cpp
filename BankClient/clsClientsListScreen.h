#pragma once
#include <iomanip>
#include "clsScreen.h"
#include "clsBankClient.h"
class clsClientsListScreen : protected clsScreen {
    static void _PrintClientRecordLine(clsBankClient Client) {
        cout << "\t| " << setw(15) << left << Client.AccountNumber();
        cout << "| " << setw(20) << left << Client.FullName();
        cout << "| " << setw(12) << left << Client.Phone;
        cout << "| " << setw(20) << left << Client.Email;
        cout << "| " << setw(10) << left << Client.PinCode;
        cout << "| " << setw(12) << left << Client.AccountBalance;
    };
public:
    static void ShowClientsList() {
        if (!CheckAccessRights(clsUser::enPermissions::pListClients))
            return;
        vector <clsBankClient> vClients = clsBankClient::GetClientsList();
        string Title = "\t  Client List Screen";
        string SubTitle = "\t    (" + to_string(vClients.size()) + ") Client(s).";
        _DrawScreenHeader(Title, SubTitle);
        cout << endl << setw(8) << left << "\t_______________________________________________________";
        cout << "_________________________________________\n\n";
        cout << "\t| " << setw(15) << left << "Account Number";
        cout << "| " << setw(20) << left << "Client Name";
        cout << "| " << setw(12) << left << "Phone";
        cout << "| " << setw(20) << left << "Email";
        cout << "| " << setw(10) << left << "Pin Code";
        cout << "| " << setw(12) << left << "Balance";
        cout << endl << setw(8) << left << "\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;
        if (vClients.size() == 0)
            cout << clsUtil::Tabs(3) << "No Clients Available In the System!\n";
        else
            for (clsBankClient Client : vClients) {
                _PrintClientRecordLine(Client);
                cout << endl;
            };
        cout << setw(8) << left << "\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;
    };
};