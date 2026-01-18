#pragma once
#include "clsCurrenciesListScreen.h"
#include "clsFindCurrencyScreen.h"
#include "clsUpdateCurrencyRateScreen.h"
#include "clsCurrencyCalculatorScreen.h"
class clsCurrencyExchangeMainScreen : protected clsScreen {
	enum enCurrenciesMainMenuOptions {
        eListCurrencies = 1, eFindCurrency, eUpdateCurrencyRate, 
        eCurrencyCalculator, eMainMenu
    };
    static short _ReadCurrenciesMainMenuOptions() {
        cout << setw(37) << left << "" << "Choose what do you want to do [1 to 5]: ";
        short Choice = clsInputValidate<short>::ReadNumberBetween(1, 5, "Enter Number between 1 to 5: ");
        return Choice;
    };
    static  void _GoBackToCurrenciesMenu() {
        cout << "\n\nPress any key to go back to Currencies Menu...";
        system("pause>0");
        ShowCurrenciesMenu();
    };
    static void _ShowCurrenciesListScreen() {
          //cout << "\nCurrency List Screen Will be here...\n";
        clsCurrenciesListScreen::ShowCurrenciesListScreen();
    };
    static void _ShowFindCurrencyScreen() {
         //cout << "\nFind Currency Screen Will be here...\n";
        clsFindCurrencyScreen::ShowFindCurrencyScreen();
    };
    static void _ShowUpdateCurrencyRateScreen() {
        //cout << "\nUpdate Currency Rate Screen Will be here...\n";
        clsUpdateCurrencyRateScreen::ShowUpdateCurrencyRateScreen();
    };
    static void _ShowCurrencyCalculatorScreen() {
         //cout << "\nCurrency Calculator Will be here...\n";
        clsCurrencyCalculatorScreen::ShowCurrencyCalculatorScreen();
    };
    static void _PerformCurrenciesMainMenuOptions(enCurrenciesMainMenuOptions CurrenciesMainMenuOptions) {
        system("cls");
        switch (CurrenciesMainMenuOptions) {
        case enCurrenciesMainMenuOptions::eListCurrencies:
            _ShowCurrenciesListScreen();
            _GoBackToCurrenciesMenu();
            break;
        case enCurrenciesMainMenuOptions::eFindCurrency:
            _ShowFindCurrencyScreen();
            _GoBackToCurrenciesMenu();
            break;
        case enCurrenciesMainMenuOptions::eUpdateCurrencyRate:
            _ShowUpdateCurrencyRateScreen();
            _GoBackToCurrenciesMenu();
            break;
        case enCurrenciesMainMenuOptions::eCurrencyCalculator:
            _ShowCurrencyCalculatorScreen();
            _GoBackToCurrenciesMenu();
            break;
        case enCurrenciesMainMenuOptions::eMainMenu:
            break;
        };
    };
public:
    static void ShowCurrenciesMenu() {
        if (!CheckAccessRights(clsUser::enPermissions::pCurrencyExchange))
            return;
        system("cls");
        _DrawScreenHeader("\tCurrency Exchange Main Screen");
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << clsUtil::Tabs(2) << "Currency Exchange Menu\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] Show Currency List.\n";
        cout << setw(37) << left << "" << "\t[2] Find Currency.\n";
        cout << setw(37) << left << "" << "\t[3] Update Rate.\n";
        cout << setw(37) << left << "" << "\t[4] Currency Calculator.\n";
        cout << setw(37) << left << "" << "\t[5] Main Menu.\n";
        cout << setw(37) << left << "" << "===========================================\n";
        _PerformCurrenciesMainMenuOptions((enCurrenciesMainMenuOptions)_ReadCurrenciesMainMenuOptions());
    };
};