#pragma once
#include "clsPerson.h"
#include "clsString.h"
#include <fstream>
class clsUser : public clsPerson {
    enum enMode { EmptyMode, UpdateMode, AddNewMode };
    enMode _Mode;
    string _UserName, _Password;
    short _Permissions;
    bool _MarkedForDelete = false;
    static clsUser _ConvertLinetoUserObject(string Line, string Seperator = "#//#") {
        vector<string> vUserData;
        vUserData = clsString::Split(Line, Seperator);
        return clsUser(enMode::UpdateMode, vUserData[0], vUserData[1], vUserData[2],
            vUserData[3], vUserData[4], clsUtil::DecryptText(vUserData[5]), stoi(vUserData[6]));
    };
    struct stLoginRegisterRecord;
    static stLoginRegisterRecord _ConvertLinetoLoginRegister(string Line, string Seperator = "#//#") {
        vector<string> vLoginRegisterData;
        vLoginRegisterData = clsString::Split(Line, Seperator);
        stLoginRegisterRecord Record;
        Record.DateTime = vLoginRegisterData[0];
        Record.UserName = vLoginRegisterData[1];
        Record.Password = clsUtil::DecryptText(vLoginRegisterData[2]);
        Record.Permissions = stoi(vLoginRegisterData[3]);
        return Record;
    };
    static vector<clsUser>_LoadUsersDataFromFile() {
        vector<clsUser>_vUsers;
        fstream MyFile;
        MyFile.open("Users.txt", ios::in);
        if (MyFile.is_open()) {
            string Line;
            while (getline(MyFile, Line)) {
                clsUser User = _ConvertLinetoUserObject(Line);
                _vUsers.push_back(User);
            };
        };
        MyFile.close();
        return _vUsers;
    };
    static vector<stLoginRegisterRecord>_LoadUsersDataFromLoginRegisterFile() {
        vector<stLoginRegisterRecord>_vLoginRegister;
        fstream MyFile;
        MyFile.open("LoginRegister.txt", ios::in);
        if (MyFile.is_open()) {
            string Line;
            while (getline(MyFile, Line)) {
                stLoginRegisterRecord User = _ConvertLinetoLoginRegister(Line);
                _vLoginRegister.push_back(User);
            };
        };
        MyFile.close();
        return _vLoginRegister;
    };
    static string _ConvertUserObjectToLine(clsUser User, string Seperator = "#//#") {
        string stUserRecord = "";
        stUserRecord += User.FirstName + Seperator;
        stUserRecord += User.LastName + Seperator;
        stUserRecord += User.Email + Seperator;
        stUserRecord += User.Phone + Seperator;
        stUserRecord += User.UserName + Seperator;
        stUserRecord += clsUtil::EncryptText(User.Password) + Seperator;
        stUserRecord += to_string(User.Permissions);
        return stUserRecord;
    };
    static void _SaveUsersDataToFile(vector<clsUser>vUsers) {
        fstream MyFile;
        MyFile.open("Users.txt", ios::out);
        string DataLine;
        if (MyFile.is_open())
            for (clsUser& U : vUsers)
                if (!U._MarkedForDelete) {
                    DataLine = _ConvertUserObjectToLine(U);
                    MyFile << DataLine << endl;
                };
        MyFile.close();
    };
    void _Update() {
        vector<clsUser>_vUsers;
        _vUsers = _LoadUsersDataFromFile();
        for (clsUser& U : _vUsers)
            if (U.GetUserName() == _UserName) {
                U = *this;
                break;
            };
        _SaveUsersDataToFile(_vUsers);
    };
    void _AddDataLineToFile(string stDataLine) {
        fstream MyFile;
        MyFile.open("Users.txt", ios::out | ios::app);
        if (MyFile.is_open())
            MyFile << stDataLine << endl;
        MyFile.close();
    };
    void _AddNew() {
        _AddDataLineToFile(_ConvertUserObjectToLine(*this));
    };
    static clsUser _GetEmptyUserObject() {
        return clsUser(enMode::EmptyMode, "", "", "", "", "", "", 0);
    };
    string _PrepareLogInRecord(string Seperator = "#//#") {
        string LoginRecord = "";
        LoginRecord += clsDate::GetSystemDateTimeString() + Seperator;
        LoginRecord += UserName + Seperator;
        LoginRecord += clsUtil::EncryptText(Password) + Seperator;
        LoginRecord += to_string(Permissions);
        return LoginRecord;
    };
public:
    clsUser(enMode Mode, string FirstName, string LastName,
        string Email, string Phone, string UserName, string Password,
        short Permissions) :
        clsPerson(FirstName, LastName, Email, Phone) {
        _Mode = Mode;
        _UserName = UserName;
        _Password = Password;
        _Permissions = Permissions;
    };
    bool MarkedForDelete() {
        return _MarkedForDelete;
    };
    void SetUserName(string UserName) {
        _UserName = UserName;
    };
    string GetUserName() {
        return _UserName;
    };
    __declspec(property(get = GetUserName, put = SetUserName))string UserName;
    void SetPassword(string Password) {
        _Password = Password;
    };
    string GetPassword() {
        return _Password;
    };
    __declspec(property(get = GetPassword, put = SetPassword)) string Password;
    void SetPermissions(int Permissions) {
        _Permissions = Permissions;
    };
    int GetPermissions() {
        return _Permissions;
    };
    __declspec(property(get = GetPermissions, put = SetPermissions)) int Permissions;
    static clsUser Find(string UserName) {
        fstream MyFile;
        MyFile.open("Users.txt", ios::in);//read Mode
        if (MyFile.is_open()) {
            string Line;
            while (getline(MyFile, Line)) {
                clsUser User = _ConvertLinetoUserObject(Line);
                if (User.UserName == UserName) {
                    MyFile.close();
                    return User;
                };
            };
        };
        MyFile.close();
        return _GetEmptyUserObject();
    };
    static clsUser Find(string UserName, string Password) {
        fstream MyFile;
        MyFile.open("Users.txt", ios::in);//read Mode
        if (MyFile.is_open()) {
            string Line;
            while (getline(MyFile, Line)) {
                clsUser User = _ConvertLinetoUserObject(Line);
                if (User.UserName == UserName && User.Password == Password) {
                    MyFile.close();
                    return User;
                };
            };
        };
        MyFile.close();
        return _GetEmptyUserObject();
    };
    bool IsEmpty() {
        return (_Mode == enMode::EmptyMode);
    };
    static bool IsUserExist(string UserName) {
        clsUser User1 = clsUser::Find(UserName);
        return (!User1.IsEmpty());
    };
    enum enSaveResults { svFailedEmptyObject, svSecceeded, svFailedUserNameExists };
    enSaveResults Save() {
        switch (_Mode) {
        case enMode::EmptyMode:
            return enSaveResults::svFailedEmptyObject;
        case enMode::UpdateMode:
            _Update();
            return enSaveResults::svSecceeded;
        case enMode::AddNewMode:
            if (IsUserExist(_UserName))
                return enSaveResults::svFailedUserNameExists;
            else {
                _AddNew();
                _Mode = enMode::UpdateMode;
                return enSaveResults::svSecceeded;
            };
        };
    };
    static clsUser GetAddNewUserObject(string UserName) {
        return clsUser(enMode::AddNewMode, "", "", "", "", UserName, "", 0);
    };
    bool Delete() {
        vector<clsUser>_vUsers;
        _vUsers = _LoadUsersDataFromFile();
        for (clsUser& U : _vUsers)
            if (U.GetUserName() == _UserName) {
                U._MarkedForDelete = true;
                break;
            };
        _SaveUsersDataToFile(_vUsers);
        *this = _GetEmptyUserObject();
        return true;
    };
    static vector<clsUser>GetUsersList() {
        return _LoadUsersDataFromFile();
    };
    enum enPermissions {
        eAll = -1, pListClients = 1, pAddNewClient = 2, pDeleteClient = 4,
        pUpdateClient = 8, pFindClient = 16, pTransactions = 32,
        pManageUsers = 64, pShowLoginRegister = 128, pCurrencyExchange = 256
    };
    bool CheckAccessPermissions(enPermissions Permissions) {
        return ((_Permissions == enPermissions::eAll) ? 1 : (((Permissions & _Permissions) == Permissions) ? 1 : 0));
    };
    void RegisterLogIn() {
        string stDataLine = _PrepareLogInRecord();
        fstream MyFile;
        MyFile.open("LoginRegister.txt", ios::out | ios::app);
        if (MyFile.is_open())
            MyFile << stDataLine << endl;
        MyFile.close();
    };
    struct stLoginRegisterRecord {
        string DateTime, UserName, Password;
        short Permissions = 0;
    };
    static vector<stLoginRegisterRecord>GetLoginRegisterList() {
        return _LoadUsersDataFromLoginRegisterFile();
    };
};