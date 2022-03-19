#ifndef _VIEWINFO_H_
#define _VIEWINFO_H_
#include<iostream>
#include<fstream>
#include<string.h>
#include"Utils.h"
using namespace std;
class ViewInfo {
private:
	int headerCount;
public:
	~ViewInfo();
	void viewInfo(char filename[], int stt);
	void deViewInfo();

	char ** header, **info;
};
#endif