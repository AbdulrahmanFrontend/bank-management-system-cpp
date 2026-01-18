#pragma once
#include "clsString.h"
#include <fstream>
#include <string>
using namespace std;
class clsCurrency {
    enum enMode { EmptyMode, UpdateMode };
    enMode _Mode;
    string _Country, _CurrencyCode, _CurrencyName;
    float _Rate;
    static clsCurrency _ConvertLinetoCurrencyObject(string Line, string Seperator = "#//#") {
        vector<string> vCurrencyData;
        vCurrencyData = clsString::Split(Line, Seperator);
        return clsCurrency(enMode::UpdateMode, vCurrencyData[0], vCurrencyData[1], vCurrencyData[2], stof(vCurrencyData[3]));
    };
    static vector<clsCurrency>_LoadCurrenciesDataFromFile() {
        vector<clsCurrency>_vCurrencies;
        fstream MyFile;
        MyFile.open("Currencies.txt", ios::in);
        if (MyFile.is_open()) {
            string Line;
            while (getline(MyFile, Line)) {
                clsCurrency Currency = _ConvertLinetoCurrencyObject(Line);
                _vCurrencies.push_back(Currency);
            };
            MyFile.close();
        };
        return _vCurrencies;
    };
    static string _ConvertCurrencyObjectToLine(clsCurrency Currency, string Seperator = "#//#") {
        string stCurrencyRecord = "";
        stCurrencyRecord += Currency.Country() + Seperator;
        stCurrencyRecord += Currency.CurrencyCode() + Seperator;
        stCurrencyRecord += Currency.CurrencyName() + Seperator;
        stCurrencyRecord += to_string(Currency.Rate());
        return stCurrencyRecord;
    };
    static void _SaveCurrenciesDataToFile(vector<clsCurrency>vCurrencies) {
        fstream MyFile;
        MyFile.open("Currencies.txt", ios::out);
        string DataLine;
        if (MyFile.is_open())
            for (clsCurrency& C : vCurrencies) {
                DataLine = _ConvertCurrencyObjectToLine(C);
                MyFile << DataLine << endl;
            }
        MyFile.close();
    };
    void _Update() {
        vector<clsCurrency>_vCurrencies;
        _vCurrencies = _LoadCurrenciesDataFromFile();
        for (clsCurrency& C : _vCurrencies)
            if (C.CurrencyCode() == _CurrencyCode) {
                C = *this;
                break;
            };
        _SaveCurrenciesDataToFile(_vCurrencies);
    };
    static clsCurrency _GetEmptyCurrencyObject() {
        return clsCurrency(enMode::EmptyMode, "", "", "", 0);
    };
public:
    clsCurrency(enMode Mode, string Country, string CurrencyCode, 
        string CurrencyName, float Rate) {
        _Mode = Mode;
        _Country = Country;
        _CurrencyCode = CurrencyCode;
        _CurrencyName = CurrencyName;
        _Rate = Rate;
    };
    string Country() {
        return _Country;
    };
    string CurrencyCode() {
        return _CurrencyCode;
    };
    string CurrencyName() {
        return _CurrencyName;
    };
    void UpdateRate(float NewRate) {
        _Rate = NewRate;
        _Update();
    };
    float Rate() {
        return _Rate;
    };
    static clsCurrency FindByCurrencyCode(string CurrencyCode) {
        fstream MyFile;
        MyFile.open("Currencies.txt", ios::in);//read Mode
        if (MyFile.is_open()) {
            string Line;
            while (getline(MyFile, Line)) {
                clsCurrency Currency = _ConvertLinetoCurrencyObject(Line);
                if (Currency.CurrencyCode() == clsString::UpperAllString(CurrencyCode)) {
                    MyFile.close();
                    return Currency;
                };
            };
            MyFile.close();
        };
        return _GetEmptyCurrencyObject();
    };
    static clsCurrency FindByCountry(string Country) {
        fstream MyFile;
        MyFile.open("Currencies.txt", ios::in);//read Mode
        if (MyFile.is_open()) {
            string Line;
            while (getline(MyFile, Line)) {
                clsCurrency Currency = _ConvertLinetoCurrencyObject(Line);
                if (clsString::UpperAllString(Currency.Country()) == clsString::UpperAllString(Country)) {
                    MyFile.close();
                    return Currency;
                };
            };
            MyFile.close();
        };
        return _GetEmptyCurrencyObject();
    };
    bool IsEmpty() {
        return (_Mode == enMode::EmptyMode);
    };
    static bool IsCurrencyExist(string CurrencyCode) {
        clsCurrency Currency = clsCurrency::FindByCurrencyCode(CurrencyCode);
        return (!Currency.IsEmpty());
    };
    static vector<clsCurrency>GetCurrenciesList() {
        return _LoadCurrenciesDataFromFile();
    };
    float ConvertToUSD(float Amount) {
        return Amount / Rate();
    };
    float ConvertToOtherCurrency(float Amount, clsCurrency Currency) {
        float AmountInUSD = ConvertToUSD(Amount);
        return Currency.CurrencyCode() == "USD" ? AmountInUSD : Amount * Currency.Rate();
    }
};