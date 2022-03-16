#include"Login_Password.h"

void Login::logout() {
	deLogin();

	Login();
}

void Login::changePassword(char filename[]) {
	cout << "Change password" << endl;
	cout << "Please, retype your current password: ";
	char oldP[200];
	do {
		cin.get(oldP, 200, '\n');
		cin.ignore(200, '\n');
		if (match(password, oldP)) break;
		else cout << "Wrong password, please retype: ";
	} while (1);
	changePasswordInit(filename);
}
