#pragma once

#include <iostream>
#include "StudentAndCourseHeader.h"

using namespace std;

class StudentInClass
{
    public:
        Student *_Student = nullptr;
        StudentInClass *Next = nullptr;
};

class Class
{
    public:
        string ClassName;
        StudentInClass *Students = nullptr;
        Class *Next = nullptr;

        void SaveClassData(string path, string Filename);
        Student *FindStudentByID(string ID);
        void AddAStudentIntoAClass(Student *&_Student);
};

void LoadLastClassData(Class *&Head, string path, string Filename, Student *&StudentHead);
//void AddaClass();
void DeleteAClass(Class *&Head);
void DeleteAllClass(Class *&Head);
