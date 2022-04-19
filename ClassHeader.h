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

class CourseOfClass
{
    public:
        Course *_Course = nullptr;
        CourseOfClass *Next = nullptr;
};


class Class
{
    public:
        string ClassName;
        StudentInClass *Students = nullptr;
        CourseOfClass *Courses = nullptr;
        Class *Next = nullptr;

        void SaveAClassData(string path);
        void SaveClassData(string path, string allClassInfoPath);
        Student *FindStudentByID(string ID);
        void AddAStudentIntoAClass(Student *&_Student);
        void AddACourseIntoAClass(Course *&_Course);
        void RemoveACourse(Course* delCourse);
        void ShowAllStudentInfo();
        void ShowAllCourseInfo();
};

void LoadLastClassData(Class *&Head, string path, Student *&StudentHead, Course *&CourseHead);
void AddaClass(Class* &classHead, Class* newClass);
void DeleteAClass(Class *&Head);
void DeleteAllClass(Class *&Head);
void ImportStudentInClassFromCSVFile(Student* &StudentHead, string Path, Class* curClass);
Class* findClassByID(Class* AllClass, string ClassName);
