#pragma once
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"
class clsCurrencyCalculatorScreen : protected clsScreen {
    static clsCurrency _GetCurrency(string Message) {
        cout << Message;
        string CurrencyCode = clsInputValidate<int>::ReadString();
        while (!clsCurrency::IsCurrencyExist(CurrencyCode)) {
            cout << "\nCurrency Code is not found, enter another one: ";
            CurrencyCode = clsInputValidate<int>::ReadString();
        };
        clsCurrency Currency = clsCurrency::FindByCurrencyCode(CurrencyCode);
        return Currency;
    };
    static float _ReadAmount() {
        cout << "\nPlease, enter amount to exchange: ";
        float Amount = clsInputValidate<float>::ReadNumber();
        return Amount;
    };
    static void _PrintCurrencyCard(clsCurrency Currency, string Title = "Currency Card:") {
        cout << endl << Title;
        cout << endl << "---------------------\n";
        cout << "Country      : " << Currency.Country() << ".\n";
        cout << "Currency Code: " << Currency.CurrencyCode() << ".\n";
        cout << "Currency Name: " << Currency.CurrencyName() << ".\n";
        cout << "Rate(1$)     : " << Currency.Rate() << ".\n";
        cout << "---------------------\n";
    };
    static void _PrintCalculationsResults(float Amount, clsCurrency CurrencyFrom, clsCurrency CurrencyTo) {
        _PrintCurrencyCard(CurrencyFrom, "Convert From:");
        float AmountInUSD = CurrencyFrom.ConvertToUSD(Amount);
        cout << Amount << " " << CurrencyFrom.CurrencyCode() << " = "
            << AmountInUSD << " USD.\n";
        if (CurrencyTo.CurrencyCode() != "USD") {
            cout << "\nConverting from USD to:";
            _PrintCurrencyCard(CurrencyTo, "To:");
            float AmountInCurrencyTo = CurrencyFrom.ConvertToOtherCurrency(Amount, CurrencyTo);
            cout << Amount << " " << CurrencyFrom.CurrencyCode() << " = "
                << AmountInCurrencyTo << " " << CurrencyTo.CurrencyCode() << ".\n";
        }
    };
public:
    static void ShowCurrencyCalculatorScreen() {
        char Continue = 'y';
        while (tolower(Continue) == 'y') {
            system("cls");
            _DrawScreenHeader("\tCurrency Calculator Screen");
            clsCurrency CurrencyFrom = _GetCurrency("\nPlease, enter currency code 1: ");
            clsCurrency CurrencyTo = _GetCurrency("\nPlease, enter currency code 2: ");
            float Amount = _ReadAmount();
            _PrintCalculationsResults(Amount, CurrencyFrom, CurrencyTo);
            cout << "\n\nDo you want to perform another calculations (y/n)? ";
            cin >> Continue;
        };
    };
};