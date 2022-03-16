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

int Login::changePasswordInit(char filename[]) {
	ifstream in;
	in.open(filename);
	if (!in.is_open()) {
		cout << "Sorry, our service encountered an error, please retry!" << endl;
		return 0;
	}

	char* c = new char[50], * pW = new char[100000];
	int id = -1;
	for (int i = 0; i < stt; ++i) {
		in.get(c, 50, '\n');
		for (int i = 0; i < strlen(c); ++i) {
			pW[++id] = c[i];
		}
		pW[++id] = '\n';
		in.ignore(5, '\n');
	}
	cout << "Type in your new password, password must be at least 6 characters" << endl;
	cout << "New password: ";
	char newP[200];
	do {
		cin.get(newP, 200, '\n');
		cin.ignore(200, '\n');
		if (strlen(newP) < 6) {
			cout << "Password must be at least 6 characters!" << endl << "Retype: ";
		}
		else if (match(password, newP)) {
			cout << "New password must differ from your old password" << endl << "Retype: ";
		}
		else break;
	} while (1);

	cout << "Password changed successfully!" << endl;
	//append new password to position at stt
	delete[]password;
	password = new char[50];
	for (int i = 0; i < strlen(newP); ++i) {
		pW[++id] = newP[i];
		password[i] = newP[i];
	}

	in.ignore(50, '\n');
	pW[++id] = '\n';
	password[strlen(newP)] = '\0';

	delete[]c;
	c = new char[500000];
	in.get(c, 500000, '\0');


	cout << strlen(c) << endl;
	for (int i = 0; i < strlen(c); ++i) {
		pW[++id] = c[i];
	}
	pW[++id] = '\0';

	in.clear();
	in.close();


	fstream out;
	out.open(filename, ios::out);
	if (!out.is_open()) {
		cout << "Sorry, our service encountered an error, please retry!" << endl;
		return 0;
	}
	out << pW;
	out.close();
	delete[]pW;
	delete[]c;
	return 1;
}


