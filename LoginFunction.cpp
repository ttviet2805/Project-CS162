#include <conio.h>

#include"LoginHeader.h"
#include "ConsoleSolve.h"
#include "ButtonHeader.h"

bool Login::match(string a, string b) {
	if (a.size() != b.size()) return false;
	for (int i = 0; i < a.size(); ++i) {
		if (a[i] != b[i])return false;
	}
	return true;
}

void Login::logout() {
    gotoxy(47, 6);
	Login();
}

int Login::foundUsername(string FileName) {
    ifstream fin;
    fin.open(FileName);

    if(!fin.is_open()) {
        string errorService = "Sorry, our service encountered an error, please retry!";
        gotoxy(midScreen - errorService.size() / 2 + 1, 11);
        cout << errorService;
        Sleep(3000);
        clrscr();
        return 0;
    }

    string curUserName, curPassword;

    int numAccount = 0;

    while(!fin.eof()) {
        ++numAccount;
        fin >> curUserName;
        fin >> curPassword;

        if(match(curUserName, userAccount.username) && match(curPassword, userAccount.password)) {
            numID = numAccount;
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

void Login::login(string FileName) {

    while(1) {
        setLogInPosition();
        // Login View
        gotoxy(47, 6);
        ShowCur(1);
        cout << "Username: ";
        gotoxy(47, 7);
        cout << "Password: ";

        gotoxy(57, 6);
        getline(cin, userAccount.username);

        ShowCur(0);

        gotoxy(57, 7);
        ShowCur(1);

        // login with print * in password
        string pass = "";
        char ch;

        ch = _getch();

        while(ch != 13) {
            pass += ch;
            cout << '*';

            ch = _getch();
        }

        ShowCur(0);

        userAccount.password = pass;

        cout << '\n';

        int loginState = foundUsername(FileName);

        if(loginState == 1) {
            string successLogin = "LOGIN SUCCESSFUL\n";
            gotoxy(midScreen - successLogin.size() / 2 + 1, 11);
            cout << successLogin;
            Sleep(2000);
            clrscr();
            break;
        }
    }
//    changePassword(FileName);
}

void Login::changePassword(string filename) {
    const int startX = 19, startY = 9;

    Sleep(200);

    while(1) {
        clrscr();
        gotoxy(startX, startY);
        changeTextColor(11);
        Button changePasswordButton = Button(19, 5, 80, 3, "Change Password");
        changePasswordButton.drawRectangleWithText();


        gotoxy(startX, startY);
        cout << "Please, retype your password again: ";
        ShowCur(1);

        string oldP;
        getline(cin, oldP);
        if (match(userAccount.password, oldP)) {
            if(changePasswordInit(filename)) break;
        }
        else {
            gotoxy(startX, startY + 1);
            cout << "Wrong password, please retype";
            Sleep(3000);
        }
    }

    ShowCur(0);
}

int Login::changePasswordInit(string filename) {
	ifstream in;
	in.open(filename);

	if (!in.is_open()) {
		cout << "Sorry, our service encountered an error, please retry!" << endl;
		return 0;
	}

    // to get the data from Account File
	Account* accountHead = nullptr;
	Account* Dummy = new Account;
	Account* curDummy = Dummy;

    while(!in.eof()) {
        string tmpUsername;
        string tmpPassword;
        getline(in, tmpUsername);
        getline(in, tmpPassword);

        curDummy->Next = new Account;
        curDummy->Next->username = tmpUsername;
        curDummy->Next->password = tmpPassword;
        curDummy = curDummy->Next;
    }

    curDummy->Next = nullptr;

    accountHead = Dummy->Next;

    in.close();

    gotoxy(19, 10);
	cout << "Type in your new password, password must be at least 6 characters" << endl;
	gotoxy(19, 11);
	cout << "New password: ";
	string newP;
    getline(cin, newP);

    gotoxy(19, 12);

    if (newP.size() < 6) {
        cout << "Password must be at least 6 characters!";
        Sleep(3000);
        return 0;
    }
    else if (match(userAccount.password, newP)) {
        cout << "New password must differ from your old password";
        Sleep(3000);
        return 0;
    }

    gotoxy(19, 13);
	cout << "Password changed successfully!" << endl;
	gotoxy(19, 14);
	cout << "Log out to confirm";
	Sleep(3000);
	//append new password to position at numID

    fstream fout;
    fout.open(filename, ios::trunc);
    int cnt = 0;

    Account* accountCur = accountHead;

    while(accountCur) {
        ++cnt;

        if(cnt != numID) {
            fout << accountCur->username << '\n';
            fout << accountCur->password;
        }
        else {
            fout << accountCur->username << '\n';
            fout << newP;
        }

        fout << '\n';
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
