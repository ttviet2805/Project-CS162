#pragma once

#include <iostream>
#include <string.h>

#include "DateHeader.h"
#include "CourseHeader.h"

using namespace std;

class StudentInfo
{
    public:
        string ID, FirstName, LastName;
        string Gender;
        Date Dob;
        string SocialID;
        string StudentClass;
        int numCredit = 0;
        bool isFree[6][5]; // first dimension is the day of week, second dimension is session

        StudentInfo() {

        for(int i = 0; i < 6; i++)
            for(int j = 0; j < 5; j++)
                isFree[i][j] = false;
        }
};

class Student {
    public:

        StudentInfo *Info = new StudentInfo;
        Course* CourseHead = nullptr;
        Student *Next = nullptr;

        void ShowStudentInfo();

        void EnrollACourse(Course* NewCourse);

        void ViewAListOfEnrollCourse();

        void RemoveACourse(Course* DelCourse);
};

void DeleteAStudent(Student *&pD);
void DeleteAllStudent(Student *&pD);
void LoadLastStudentData(Student *&Head, string Filename);
