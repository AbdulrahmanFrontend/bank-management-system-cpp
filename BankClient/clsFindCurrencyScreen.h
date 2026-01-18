#pragma once
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"
#include <iomanip>
class clsFindCurrencyScreen : protected clsScreen {
    static void _PrintCurrency(clsCurrency Currency) {
        cout << endl << "\nCurrency Card:";
        cout << endl << "---------------------\n";
        cout << "Country      : " << Currency.Country() << ".\n";
        cout << "Currency Code: " << Currency.CurrencyCode() << ".\n";
        cout << "Currency Name: " << Currency.CurrencyName() << ".\n";
        cout << "Rate(1$)     : " << Currency.Rate() << ".\n";
        cout << "---------------------\n";
    };
    static void _ShowResults(clsCurrency Currency) {
        if (!Currency.IsEmpty()) {
            cout << "\nCurrency is found: -)\n";
            _PrintCurrency(Currency);
        }
        else
            cout << "\nCurrency is not found: -(\n";
    }
public:
    static void ShowFindCurrencyScreen() {
        _DrawScreenHeader("\t  Find Currency Screen");
        cout << "\nDo you want to search by: [1] code or [2] country? ";
        short Answer = clsInputValidate<short>::ReadNumber();
        if (Answer == 1) {
            cout << "\nPlease, enter currency code: ";
            string CurrencyCode = clsInputValidate<int>::ReadString();
            clsCurrency Currency = clsCurrency::FindByCurrencyCode(CurrencyCode);
            _ShowResults(Currency);
        }
        else {
            cout << "\nPlease, enter country: ";
            string Country = clsInputValidate<int>::ReadString();
            clsCurrency Currency = clsCurrency::FindByCountry(Country);
            _ShowResults(Currency);
        }
    };
};