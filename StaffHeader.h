#pragma once

#include <fstream>
#include <iostream>

using namespace std;

#include "DateHeader.h"

class StaffInfo {
public:
    string FirstName, LastName;
    string Gender;
    string ID;
    Date Dob;
};

class Staff {
    public:
        StaffInfo* Info = new StaffInfo;

        Staff* Next = nullptr;

        void ShowStaffInfo();
};

void LoadAllStaffData(Staff* &staffHead, string Path, string FileName);
