#pragma once

#include <iostream>
#include <string.h>

#include "DateHeader.h"
#include "CourseHeader.h"

using namespace std;

class Student
{
    public:
        string ID, FirstName, LastName;
        string Gender;
        Date Dob;
        string SocialID;
        Student *Next = nullptr;

        Course* CourseHead = nullptr;

        void EnrollACourse(Course NewCourse);

        void ViewAListOfEnrollCourse();

        void RemoveACourse(Course DelCourse);

};

void LoadLastStudentData(Student *&Head, string Filename);
