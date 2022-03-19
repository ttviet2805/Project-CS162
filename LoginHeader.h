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
class Login {
private:
	Login();
	char username[50];
	char *password;
	static const char defaultPass = '1';
	int foundUsername(char filename[]);
	int passWord(char filename[]);
	bool match(char inputted[], char sN[]);
	
	int changePasswordInit(char filename[]);
	void deLogin();
	
public:
	int stt;//so thu tu cua hoc sinh trong file
	int type;//student/lecturer/staff
	Login();
	~Login();
	void login();
	void logout();
	void changePassword(char filename[]);
};
#endif
