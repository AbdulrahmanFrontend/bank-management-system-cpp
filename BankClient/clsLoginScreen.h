#pragma once
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"
#include "Global.h"
#include "clsMainScreen.h"
class clsLoginScreen : protected clsScreen {
	static bool _Login() {
		bool LoginFailed = false;
		short FailedLoginCount = 0;
		string UserName, Password;
		do {
			if (LoginFailed) {
				FailedLoginCount++;
				cout << "\nInvalid UserName/Password!\n";
				cout << "You have " << 3 - FailedLoginCount << " Trials to login.\n\n";
			};
			if (FailedLoginCount == 3) {
				cout << "You are locked after 3 failed trials.\n\n";
				return false;
			};
			cout << "Please, enter Username: ";
			UserName = clsInputValidate<int>::ReadString();
			cout << "Please, enter Password: ";
			Password = clsInputValidate<int>::ReadString();
			CurrentUser = clsUser::Find(UserName, Password);
			LoginFailed = CurrentUser.IsEmpty();
		} while(LoginFailed);
		CurrentUser.RegisterLogIn();
		clsMainScreen::ShowMainMenu();
		return true;
	};
public:
	static bool ShowLoginScreen() {
		system("cls");
		_DrawScreenHeader("\t  Login Screen");
		return _Login();
	};
};