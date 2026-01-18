#pragma once
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsBankClient.h"
#include <iomanip>
class clsTransferLogScreen : protected clsScreen {
    static void _PrintTransferLogRecord(clsBankClient::stTransferLogRecord TransferLogRecord) {
        cout << setw(8) << left << "" << "| " << setw(23) << left << TransferLogRecord.DateTime;
        cout << "| " << setw(8) << left << TransferLogRecord.SourceAccountNumber;
        cout << "| " << setw(8) << left << TransferLogRecord.DestinationAccountNumber;
        cout << "| " << setw(8) << left << TransferLogRecord.Amount;
        cout << "| " << setw(10) << left << TransferLogRecord.srcBalanceAfter;
        cout << "| " << setw(10) << left << TransferLogRecord.destBalanceAfter;
        cout << "| " << setw(8) << left << TransferLogRecord.UserName;
    };
public:
    static void ShowTransferLogScreen() {
        vector <clsBankClient::stTransferLogRecord> vTransferLogRecord = clsBankClient::GetTransferLogList();
        string Title = "\tTransfer Log List Screen";
        string SubTitle = "\t    (" + to_string(vTransferLogRecord.size()) + ") User(s).";
        _DrawScreenHeader(Title, SubTitle);
        cout << endl << setw(8) << left << "\t_______________________________________________________";
        cout << "_____________________________________________\n\n";
        cout << "\t| " << setw(23) << left << "Date/Time";
        cout << "| " << left << setw(8) << "s.Acct";
        cout << "| " << left << setw(8) << "d.Acct";
        cout << "| " << left << setw(8) << "Amount";
        cout << "| " << left << setw(10) << "s.Balance";
        cout << "| " << left << setw(10) << "d.Balance";
        cout << "| " << left << setw(8) << "User";
        cout << endl << setw(8) << left << "\t_______________________________________________________";
        cout << "_____________________________________________\n" << endl;
        if (vTransferLogRecord.size() == 0)
            cout << clsUtil::Tabs(4) << "No Transfers Available In the System!\n";
        else
            for (clsBankClient::stTransferLogRecord TransferLogRecord : vTransferLogRecord) {
                _PrintTransferLogRecord(TransferLogRecord);
                cout << endl;
            };
            cout << setw(8) << left << "\t_______________________________________________________";
            cout << "_____________________________________________\n" << endl;
    };
};