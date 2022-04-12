#pragma once

#include <fstream>
#include <iostream>
#include <direct.h>

using namespace std;

#include "DateHeader.h"
#include "ClassHeader.h"
#include "StudentAndCourseHeader.h"
#include "ConsoleSolve.h"
#include "ButtonHeader.h"

class SchoolYear {
public:
    string schoolYearName;

    Date startDate, endDate;

    void ShowSchoolYearInfo();
    void setDate(int d1, int m1, int y1, int d2, int m2, int y2);
};

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

void CreateAFolder(string FileName);
void LoadAllStaffData(Staff* &staffHead, string Path, string FileName);
void LoadAllStudentDataByCSV(Student* &studentHead, string Path, string FileName);
Class* CreateAClass();
void AddANewClass(Class* &classHead, Class* newClass);

void createANewSchoolYear();
