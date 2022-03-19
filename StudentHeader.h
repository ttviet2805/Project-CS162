#pragma once

#include <iostream>
#include <string.h>

#include "DateHeader.h"

using namespace std;

class Student
{
    public:
        string ID, FirstName, LastName;
        string Gender;
        Date Dob;
        string SocialID;
        Student *Next = nullptr;
};

void LoadLastStudentData(Student *&Head, string Filename);
