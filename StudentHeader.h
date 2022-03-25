#pragma once

#include <iostream>
#include <string.h>

#include "DateHeader.h"
#include "CourseHeader.h"

using namespace std;

class Student {
    public:
        string ID, FirstName, LastName;
        string Gender;
        Date Dob;
        string SocialID;
        string StudentClass;
        Student *Next = nullptr;

        Course* CourseHead = nullptr;

        int numCredit = 0;
        bool isFree[6][5]; // first dimension is the day of week, second dimension is session

        Student() {
            numCredit = 0;

            for(int i = 0; i < 6; i++)
                for(int j = 0; j < 5; j++)
                    isFree[i][j] = false;
        }

        void StudentInfo();

        void EnrollACourse(Course* NewCourse);

        void ViewAListOfEnrollCourse();

        void RemoveACourse(Course* DelCourse);
};

void LoadLastStudentData(Student *&Head, string Filename);
