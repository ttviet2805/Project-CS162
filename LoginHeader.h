#ifndef _LOGIN_H_
#define _LOGIN_H_
#include<iostream>
#include<fstream>
#include<string>
#include"Utils.h"
#include"Const.h"
#include"ViewInfo.h"
using namespace std;

using namespace std;

class Account {
public:
    char username[50];
    char password[50];

    Account* Next;

    Account() {
        Next = nullptr;
    }
};

// File txt of Login: username -> password -> username -> password -> ...
class Login {
private:
	char username[50];
	char* password;
	static const char defaultPass = '1';

    // return 0 if can not find the Account File
    // return 1 if find the account
    // return 2 if can not find the account
	int foundUsername(char filename[]);
	bool match(char inputted[], char sN[]); // to check if 2 string equal together

	int changePasswordInit(char filename[]);

public:
    Login() {
	    delete password;
        memset(username, 0, sizeof(username));
        password = new char[50];
        stt = -1;
        type = 1;
	}

	int stt;//so thu tu cua hoc sinh trong file
	int type;//student/lecturer/staff
	void login(char fileName[]); // login system
	void logout(char fileName[]);
	void changePassword(char filename[]);
};
#endif
