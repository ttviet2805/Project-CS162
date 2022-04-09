#pragma once

#include <fstream>
#include <iostream>

using namespace std;

#include "DateHeader.h"
#include "AllConst.h"

class Staff {
    public:
        string FirstName, LastName;
        string Gender;
        string ID;
        Date Dob;

        Staff* Next = nullptr;

        void ShowStaffInfo();
};

void LoadAllStaffData(Staff* &staffHead, string Path, string FileName);
