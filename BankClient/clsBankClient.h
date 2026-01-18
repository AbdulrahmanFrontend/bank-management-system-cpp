#pragma once
#include "clsPerson.h"
#include "clsString.h"
#include <fstream>
class clsBankClient : public clsPerson {
    enum enMode { EmptyMode, UpdateMode, AddNewMode };
    enMode _Mode;
    string _AccountNumber, _PinCode;
    float _AccountBalance;
    bool _MarkedForDelete = false;
    static clsBankClient _ConvertLinetoClientObject(string Line, string Seperator = "#//#") {
        vector<string> vClientData;
        vClientData = clsString::Split(Line, Seperator);
        return clsBankClient(enMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2],
            vClientData[3], vClientData[4], vClientData[5], stof(vClientData[6]));
    };
    static vector<clsBankClient>_LoadClientsDataFromFile() {
        vector<clsBankClient>_vClients;
        fstream MyFile;
        MyFile.open("Clients.txt", ios::in);
        if (MyFile.is_open()) {
            string Line;
            while (getline(MyFile, Line)) {
                clsBankClient Client = _ConvertLinetoClientObject(Line);
                _vClients.push_back(Client);
            };
        };
        MyFile.close();
        return _vClients;
    };
    static string _ConvertClientObjectToLine(clsBankClient Client, string Seperator = "#//#") {
        string stClientRecord = "";
        stClientRecord += Client.FirstName + Seperator;
        stClientRecord += Client.LastName + Seperator;
        stClientRecord += Client.Email + Seperator;
        stClientRecord += Client.Phone + Seperator;
        stClientRecord += Client.AccountNumber() + Seperator;
        stClientRecord += Client.PinCode + Seperator;
        stClientRecord += to_string(Client.AccountBalance);
        return stClientRecord;
    };
    static void _SaveClientsDataToFile(vector<clsBankClient>vClients) {
        fstream MyFile;
        MyFile.open("Clients.txt", ios::out);
        string DataLine;
        if (MyFile.is_open())
            for (clsBankClient& C : vClients)
                if (!C._MarkedForDelete) {
                    DataLine = _ConvertClientObjectToLine(C);
                    MyFile << DataLine << endl;
                };
        MyFile.close();
    };
    void _Update() {
        vector<clsBankClient>_vClients;
        _vClients = _LoadClientsDataFromFile();
        for (clsBankClient& C : _vClients)
            if (C.AccountNumber() == _AccountNumber) {
                C = *this;
                break;
            };
        _SaveClientsDataToFile(_vClients);
    };
    void _AddDataLineToFile(string stDataLine) {
        fstream MyFile;
        MyFile.open("Clients.txt", ios::out | ios::app);
        if (MyFile.is_open())
            MyFile << stDataLine << endl;
        MyFile.close();
    };
    void _AddNew() {
        _AddDataLineToFile(_ConvertClientObjectToLine(*this));
    };
    static clsBankClient _GetEmptyClientObject() {
        return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
    };
    string _PrepareTransferLogRecord(double Amount, clsBankClient DestinationClient, string Seperator = "#//#") {
        string TransferLogRecord = "";
        TransferLogRecord += clsDate::GetSystemDateTimeString() + Seperator;
        TransferLogRecord += _AccountNumber + Seperator;
        TransferLogRecord += DestinationClient.AccountNumber() + Seperator;
        TransferLogRecord += to_string(Amount) + Seperator;
        TransferLogRecord += to_string(_AccountBalance) + Seperator;
        TransferLogRecord += to_string(DestinationClient.AccountBalance) + Seperator;
        TransferLogRecord += CurrentUser.UserName;
        return TransferLogRecord;
    };
    void _RegisterTransferLog(double Amount, clsBankClient DestinationClient) {
        string stDataLine = _PrepareTransferLogRecord(Amount, DestinationClient);
        fstream MyFile;
        MyFile.open("TransferLog.txt", ios::out | ios::app);
        if (MyFile.is_open())
            MyFile << stDataLine << endl;
        MyFile.close();
    };
    struct stTransferLogRecord;
    static stTransferLogRecord _ConvertLinetoTransferLog(string Line, string Seperator = "#//#") {
        vector<string> vTransferLogData = clsString::Split(Line, Seperator);
        stTransferLogRecord Record;
        Record.DateTime = vTransferLogData[0];
        Record.SourceAccountNumber = vTransferLogData[1];
        Record.DestinationAccountNumber = vTransferLogData[2];
        Record.Amount = stof(vTransferLogData[3]);
        Record.srcBalanceAfter = stof(vTransferLogData[4]);
        Record.destBalanceAfter = stof(vTransferLogData[5]);
        Record.UserName = vTransferLogData[6];
        return Record;
    };
    static vector<stTransferLogRecord>_LoadClientsDataFromTransferLogFile() {
        vector<stTransferLogRecord>_vTransferLogs;
        fstream MyFile;
        MyFile.open("TransferLog.txt", ios::in);
        if (MyFile.is_open()) {
            string Line;
            while (getline(MyFile, Line)) {
                stTransferLogRecord TransferLogRecord = _ConvertLinetoTransferLog(Line);
                _vTransferLogs.push_back(TransferLogRecord);
            };
        };
        MyFile.close();
        return _vTransferLogs;
    };
public:
    clsBankClient(enMode Mode, string FirstName, string LastName,
        string Email, string Phone, string AccountNumber, string PinCode,
        float AccountBalance) :
        clsPerson(FirstName, LastName, Email, Phone) {
        _Mode = Mode;
        _AccountNumber = AccountNumber;
        _PinCode = PinCode;
        _AccountBalance = AccountBalance;
    };
    bool IsEmpty() {
        return (_Mode == enMode::EmptyMode);
    };
    string AccountNumber() {
        return _AccountNumber;
    };
    bool MarkedForDelete() {
        return _MarkedForDelete;
    };
    void SetPinCode(string PinCode) {
        _PinCode = PinCode;
    };
    string GetPinCode() {
        return _PinCode;
    };
    __declspec(property(get = GetPinCode, put = SetPinCode)) string PinCode;
    void SetAccountBalance(float AccountBalance) {
        _AccountBalance = AccountBalance;
    };
    float GetAccountBalance() {
        return _AccountBalance;
    };
    __declspec(property(get = GetAccountBalance, put = SetAccountBalance)) float AccountBalance;
    static clsBankClient Find(string AccountNumber) {
        fstream MyFile;
        MyFile.open("Clients.txt", ios::in);//read Mode
        if (MyFile.is_open()) {
            string Line;
            while (getline(MyFile, Line)) {
                clsBankClient Client = _ConvertLinetoClientObject(Line);
                if (Client.AccountNumber() == AccountNumber) {
                    MyFile.close();
                    return Client;
                };
            };
        };
        MyFile.close();
        return _GetEmptyClientObject();
    };
    static clsBankClient Find(string AccountNumber, string PinCode) {
        fstream MyFile;
        MyFile.open("Clients.txt", ios::in);//read Mode
        if (MyFile.is_open()) {
            string Line;
            while (getline(MyFile, Line)) {
                clsBankClient Client = _ConvertLinetoClientObject(Line);
                if (Client.AccountNumber() == AccountNumber && Client.PinCode == PinCode) {
                    MyFile.close();
                    return Client;
                };
            };
        };
        MyFile.close();
        return _GetEmptyClientObject();
    };
    static bool IsClientExist(string AccountNumber) {
        clsBankClient Client1 = clsBankClient::Find(AccountNumber);
        return (!Client1.IsEmpty());
    };
    enum enSaveResults { svFailedEmptyObject, svSecceeded, svFailedAccountNumberExists };
    enSaveResults Save() {
        switch (_Mode) {
        case enMode::EmptyMode:
            return enSaveResults::svFailedEmptyObject;
        case enMode::UpdateMode:
            _Update();
            return enSaveResults::svSecceeded;
        case enMode::AddNewMode:
            if (IsClientExist(_AccountNumber))
                return enSaveResults::svFailedAccountNumberExists;
            else {
                _AddNew();
                _Mode = enMode::UpdateMode;
                return enSaveResults::svSecceeded;
            };
        };
    };
    static clsBankClient GetAddNewClientObject(string AccountNumber) {
        return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);
    };
    bool Delete() {
        vector<clsBankClient>_vClients;
        _vClients = _LoadClientsDataFromFile();
        for (clsBankClient& C : _vClients)
            if (C.AccountNumber() == _AccountNumber) {
                C._MarkedForDelete = true;
                break;
            };
        _SaveClientsDataToFile(_vClients);
        *this = _GetEmptyClientObject();
        return true;
    };
    static vector<clsBankClient>GetClientsList() {
        return _LoadClientsDataFromFile();
    };
    static double GetTotalBalances() {
        vector<clsBankClient>vClients = clsBankClient::GetClientsList();
        double TotalBalances = 0;
        for (clsBankClient& C : vClients)
            TotalBalances += C.AccountBalance;
        return TotalBalances;
    };
    void Deposit(float Amount) {
        _AccountBalance += Amount;
        Save();
    };
    bool Withdraw(float Amount) {
        if (Amount > _AccountBalance)
            return false;
        _AccountBalance -= Amount;
        Save();
    };
    bool Transfer(double Amount, clsBankClient& DestinationClient) {
        if (Amount > _AccountBalance)
            return false;
        Withdraw(Amount);
        DestinationClient.Deposit(Amount);
        _RegisterTransferLog(Amount, DestinationClient);
        return true;
    };
    struct stTransferLogRecord {
        string DateTime, SourceAccountNumber, DestinationAccountNumber;
        float Amount = 0, srcBalanceAfter = 0, destBalanceAfter = 0;
        string UserName;
    };
    static vector<stTransferLogRecord>GetTransferLogList() {
        return _LoadClientsDataFromTransferLogFile();
    };
};