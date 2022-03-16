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

bool Login::match(char inputted[], char sN[]) {
	if (strlen(inputted) != strlen(sN))return false;
	for (int i = 0; i < strlen(inputted); ++i) {
		if (inputted[i] != sN[i])return false;
	}
	return true;
}

int Login::passWord(char filename[]) {
	ifstream in;
	in.open(filename);
	if (!in.is_open()) {
		cout << "Sorry, our service encountered an error, please retry!" << endl;
		return 0;
	}

	char* pW = new char[50];
	for (int i = 0; i < stt; ++i) {
		//ignore stt-1 rows of record
		//in.get(c, 50, '\n');
		in.ignore(50, '\n');
	}
	in.get(pW, 50, '\n');
	//pW[strlen(pW)] = '\0';
	if (match(password, pW)) {
		in.close();
		return 1;
	}
	delete[]pW;
	cout << "Wrong password, please check your typing" << endl;
	type = 1;
	stt = -1;
	in.close();
	return 2;
}

int Login::foundUsername(char filename[]) {
	ifstream in;
	in.open(filename);
	if (!in.is_open()) {
		cout << "Sorry, our service encountered an error, please retry!" << endl;
		return 0;
	}
	char* sN = new char[50];
	int id = -1;
	while (!in.eof()) {
		in.get(sN, 50, '\n');
		in.ignore(1, '\n');
		if (sN[0] == '-')++type;
		//sN[strlen(sN)] = '\0';
		++stt;
		//sN loaded, now check if this sN matches the inputted one:
		if (match(username, sN)) {
			in.close();
			return 1;
		}
		delete[]sN;
		sN = new char[50];
		id = -1;
	}
	cout << "User non-existed, please check your typing" << endl;

	type = 1;
	stt = -1;

	in.close();
	return 2;
}

void Login::login() {
	char filenameUsername[50], filenamePassword[50];
	do {
		cout << "Username: ";
		cin.get(username, 50, '\n');
		if (username[0] >= '1' && username[0] <= '9') {
			strcpy_s(filenameUsername, Const::usernameStudent);
			strcpy_s(filenamePassword, Const::passwordStudent);
			type = 0;
		}
		else {
			strcpy_s(filenameUsername, Const::usernameSL);
			strcpy_s(filenamePassword, Const::passwordSL);
			type = 1;//redundant?
		}
		cout << "Password: ";
		cin.ignore(50, '\n');
		cin.get(password, 50, '\n');
		cin.ignore(50, '\n');

		if (username[0] != ' ' && password[0] != ' ' && foundUsername(filenameUsername) == 1 && passWord(filenamePassword) == 1)break;
	} while (1);
	cout << "Login successfully!" << endl;
	if (strlen(password) == 1 && password[0] == defaultPass) {
		cout << "Please change your password" << endl;
		changePasswordInit(filenamePassword);
	}

}

void Login::deLogin() {

	delete[]password;
	stt = -1;
	type = 1;
}
Login::Login() {
	password = new char[50];
	stt = -1;
	type = 1;
}
Login::~Login() {
	deLogin();
}
