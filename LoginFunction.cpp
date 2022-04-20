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
    Login* AllUser = nullptr;
    loadUserAccount(AllUser, FileName);

    Login* cur = AllUser;

    while(cur) {
        if(match(cur->userAccount.username, userAccount.username) && match(cur->userAccount.password, userAccount.password))
            return 1;

        cur = cur->Next;
    }

    string noExistAccount = "User non-existed, please check your typing";
    gotoxy(midScreen - noExistAccount.size() / 2 + 1, 11);
    cout << noExistAccount;
    Sleep(3000);
    clrscr();

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
	Login* AllUser = nullptr;
    loadUserAccount(AllUser, filename);

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

    Login* curUser = findUserByAccount(AllUser, userAccount.username);

    if(!curUser) {
        cout << "Do not find the user";
        Sleep(3000);
    }

    curUser->userAccount.password = newP;

    saveUserAccount(AllUser, filename);

	return 1;
}

Login* findUserByAccount(Login* AllUser, string username) {
    Login* cur = AllUser;

    while(cur) {
        if(cur->userAccount.username == username) return cur;
        cur = cur->Next;
    }

    return nullptr;
}

void loadUserAccount(Login* &userHead, string filename) {
    ifstream fin;
    fin.open(filename);

    Login* Dummy = new Login;
    Login* cur = Dummy;

    string userName;
    while(!fin.eof() && getline(fin, userName)) {
        cur->Next = new Login;
        cur->Next->userAccount.username = userName;
        getline(fin, cur->Next->userAccount.password);
        cur = cur->Next;
    }

    userHead = Dummy->Next;
    cur = Dummy;
    Dummy = Dummy->Next;
    delete cur;

    fin.close();
}

void saveUserAccount(Login* userHead, string filename) {
    ofstream fout(filename);
    Login* cur = userHead;

    while(cur) {
        fout << cur->userAccount.username << '\n' << cur->userAccount.password << '\n';
        cur = cur->Next;
    }

    fout.close();
}

void addANewUser(Login* &AllUser, Login* newUser) {
    Login* cur = AllUser;

    if(!cur) {
        AllUser = newUser;
    }
    else {
        while(cur->Next) cur = cur->Next;
        cur->Next = newUser;
    }
}
