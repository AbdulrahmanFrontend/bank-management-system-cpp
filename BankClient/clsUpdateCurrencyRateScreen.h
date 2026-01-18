#pragma once
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"
class clsUpdateCurrencyRateScreen : protected clsScreen {
    static float _ReadRate() {
        cout << "\nPlease, enter new rate: ";
        float NewRate = clsInputValidate<float>::ReadNumber();
        return NewRate;
    };
    static void _PrintCurrency(clsCurrency Currency) {
        cout << "\nCurrency Card:\n";
        cout << "_____________________________\n";
        cout << "Country    : " << Currency.Country() << ".\n";
        cout << "Code       : " << Currency.CurrencyCode() << ".\n";
        cout << "Name       : " << Currency.CurrencyName() << ".\n";
        cout << "Rate(1$) = : " << Currency.Rate() << ".\n";
        cout << "_____________________________\n";
    };
public:
    static void ShowUpdateCurrencyRateScreen() {
        _DrawScreenHeader("\tUpdate Currency Screen");
        cout << "\nPlease, enter Currency Code: ";
        string CurrencyCode = clsInputValidate<int>::ReadString();
        while (!clsCurrency::IsCurrencyExist(CurrencyCode)) {
            cout << "\nCurrency is not found, choose another one: ";
            CurrencyCode = clsInputValidate<int>::ReadString();
        };
        clsCurrency Currency = clsCurrency::FindByCurrencyCode(CurrencyCode);
        _PrintCurrency(Currency);
        cout << "\nAre you sure you want to update the rate of this Currency y/n? ";
        char Answer = 'n';
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y') {
            cout << "\n\nUpdate Currency Rate:";
            cout << "\n____________________\n";
            Currency.UpdateRate(_ReadRate());
            cout << "\nCurrency Rate has been updated successfully :-)\n";
            _PrintCurrency(Currency);
        };
    };
};