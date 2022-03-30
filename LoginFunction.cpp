#include <conio.h>

#include"LoginHeader.h"
#include "ConsoleSolve.h"

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
        string errorService = "Sorry, our service encountered an error, please retry!";
        gotoxy(midScreen - errorService.size() / 2 + 1, 11);
        cout << errorService;
        Sleep(2000);
        clrscr();
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

    string noExistAccount = "User non-existed, please check your typing";
    gotoxy(midScreen - noExistAccount.size() / 2 + 1, 11);
    cout << noExistAccount;
    Sleep(3000);
    clrscr();

    fin.close();
    return 2;
}

void setLogInPosition() {
    gotoxy(45, 3);
    for(int i = 0; i < 30; i++) cout << char(219);
    gotoxy(45, 5);
    for(int i = 0; i < 30; i++) cout << char(219);

    gotoxy(57, 4);
    cout << "LOGIN";
    gotoxy(74, 4);
    cout << char(219);

    for(int i = 3; i <= 9; i++) {
        gotoxy(45, i);
        cout << char(219);
        gotoxy(74, i);
        cout << char(219);
    }

    gotoxy(45, 9);
    for(int i = 0; i < 30; i++) cout << char(219);
}

void Login::login(char FileName[]) {

    while(1) {
        setLogInPosition();
        // Login View
        gotoxy(47, 6);
        cout << "Username: ";
        gotoxy(47, 7);
        cout << "Password: ";

        gotoxy(57, 6);
        cin >> username;

        gotoxy(57, 7);
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
            string successLogin = "You have login successful\n";
            gotoxy(midScreen - successLogin.size() / 2 + 1, 11);
            cout << successLogin;
            Sleep(2000);
            clrscr();
            break;
        }
    }
//    changePassword(FileName);
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
	Account* Dummy = new Account;
	Dummy->Next = nullptr;
	Account* curDummy = Dummy;

    while(!in.eof()) {
        char tmpUsername[50];
        char tmpPassword[50];
        in >> tmpUsername;
        in >> tmpPassword;

        curDummy->Next = new Account;
        strcpy(curDummy->Next->username, tmpUsername);
        strcpy(curDummy->Next->password, tmpPassword);
        curDummy = curDummy->Next;
    }

    curDummy->Next = nullptr;

    accountHead = Dummy->Next;

    in.close();

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
    fout.open(filename, ios::out | ios::trunc);
    int cnt = 0;

    Account* accountCur = accountHead;

    if(accountCur) {
        ++cnt;

        if(cnt != stt) {
            fout << accountCur->username << '\n';
            fout << accountCur->password;
        }
        else {
            fout << accountCur->username << '\n';
            fout << newP;
        }

        accountCur = accountCur->Next;
    }

    while(accountCur) {
        ++cnt;

        fout << '\n';
        if(cnt != stt) {
            fout << accountCur->username << '\n';
            fout << accountCur->password;
        }
        else {
            fout << accountCur->username << '\n';
            fout << newP;
        }

        accountCur = accountCur->Next;
    }


    accountCur = accountHead;

    while(accountCur) {
        Account* Del = accountCur;
        accountCur = accountCur->Next;

        delete Del;
    }

    fout.close();

	return 1;
}
