#pragma once
#include "clsScreen.h"
#include "clsCurrency.h"
#include <iomanip>
class clsCurrenciesListScreen : protected clsScreen {
    static void _PrintCurrency(clsCurrency Currency) {
        cout << "\t| " << setw(28) << left << Currency.Country();
        cout << "| " << setw(5) << left << Currency.CurrencyCode();
        cout << "| " << setw(42) << left << Currency.CurrencyName();
        cout << "| " << setw(24) << left << Currency.Rate();
    };
public:
    static void ShowCurrenciesListScreen() {
        vector <clsCurrency> vCurrencies = clsCurrency::GetCurrenciesList();
        string Title = "\t  Currencies List Screen";
        string SubTitle = "\t    (" + to_string(vCurrencies.size()) + ") Currency(s).";
        _DrawScreenHeader(Title, SubTitle);
        cout << endl << setw(8) << left << "\t_______________________________________________________";
        cout << "_________________________________________\n\n";
        cout << "\t| " << setw(28) << left << "Country";
        cout << "| " << setw(5) << left << "Code";
        cout << "| " << setw(42) << left << "Name";
        cout << "| " << setw(24) << left << "Rate/(1$)";
        cout << endl << setw(8) << left << "\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;
        if (vCurrencies.size() == 0)
            cout << clsUtil::Tabs(4) << "No Currencies is available in the system!\n";
        else
            for (clsCurrency Currency : vCurrencies) {
                _PrintCurrency(Currency);
                cout << endl;
            };
        cout << setw(8) << left << "\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;
    };
};