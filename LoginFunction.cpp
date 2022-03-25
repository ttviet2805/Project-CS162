#include"LoginHeader.h"
#include <conio.h>

bool Login::match(char inputted[], char sN[]) {
	if (strlen(inputted) != strlen(sN))return false;
	for (int i = 0; i < strlen(inputted); ++i) {
		if (inputted[i] != sN[i])return false;
	}
	return true;
}

void Login::logout(char filename[]) {
    cout << "Log out success\n";
	Login();

	login(filename);
}

int Login::foundUsername(char FileName[]) {
    ifstream fin;
    fin.open(FileName);

    if(!fin.is_open()) {
        cout << "Sorry, our service encountered an error, please retry!" << endl;
        return 0;
    }

    char curUserName[50], curPassword[50];

    int numAccount = 0;

    while(!fin.eof()) {
        ++numAccount;
        fin >> curUserName;
        fin >> curPassword;

        if(match(curUserName, username) && match(curPassword, password)) {
            stt = numAccount;
            fin.close();
            return 1;
        }
    }

    cout << "User non-existed, please check your typing" << '\n';
    cout << '\n';

    fin.close();
    return 2;
}


void Login::login(char FileName[]) {
    cout << "**********LOGIN**********\n";

    while(1) {
        // Login View
        cout << "Username: ";
        cin >> username;
        cout << "Password: ";

        memset(password, 0, sizeof(password));

        // login with print * in password
        string pass = "";
        char ch;

        ch = _getch();

        while(ch != 13) {
            pass += ch;
            cout << '*';

            ch = _getch();
        }

        password = (&pass[0]);

        cout << '\n';

        int loginState = foundUsername(FileName);

        if(loginState == 1) {
            cout << "You have login successful\n";
            break;
        }
    }
    changePassword(FileName);
}

void Login::changePassword(char filename[]) {
	cout << "******Change password******" << endl;

	cout << "Please, retype your password again: ";
	char oldP[200];
	while(1) {
		cin >> oldP;
		if (match(password, oldP)) break;
		else cout << "Wrong password, please retype: ";
	}


	changePasswordInit(filename);
}

int Login::changePasswordInit(char filename[]) {
	ifstream in;
	in.open(filename);
	if (!in.is_open()) {
		cout << "Sorry, our service encountered an error, please retry!" << endl;
		return 0;
	}

    // to get the data from Account File
	Account* accountHead = nullptr;
	Account* accountRear = nullptr;

    while(!in.eof()) {
        char tmpUsername[50];
        char tmpPassword[50];
        in >> tmpUsername >> tmpPassword;

        if(!accountHead) {
            accountHead = new Account;
            strcpy(accountHead->username, tmpUsername);
            strcpy(accountHead->password, tmpPassword);
            accountRear = accountHead;
        }
        else {
            Account* tmp = new Account;
            strcpy(tmp->username, tmpUsername);
            strcpy(tmp->password, tmpPassword);

            accountRear->Next = tmp;
            accountRear = tmp;
        }
    }

	cout << "Type in your new password, password must be at least 6 characters" << endl;
	cout << "New password: ";
	char newP[200];
	while(1) {
		cin >> newP;
		if (strlen(newP) < 6) {
			cout << "Password must be at least 6 characters!" << endl << "Retype: ";
		}
		else if (match(password, newP)) {
			cout << "New password must differ from your old password" << endl << "Retype: ";
		}
		else break;
	};

	cout << "Password changed successfully!" << endl;
	//append new password to position at stt

    fstream fout;
    fout.open(filename);
    int cnt = 0;

    Account* accountCur = accountHead;

    while(accountCur) {
        ++cnt;

        if(cnt != stt) {
            fout << accountCur->username << '\n';
            fout << accountCur->password << '\n';
        }
        else {
            fout << accountCur->username << '\n';
            fout << newP << '\n';
        }

        accountCur = accountCur->Next;
    }

    fout.close();

	return 1;
}
