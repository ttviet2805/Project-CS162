#include <iostream>
#include <fstream>
#include <string>

#include "ClassHeader.h"
#include "StudentAndCourseHeader.h"

using namespace std;

//class Functions
//Class

void Class::SaveAClassData(string path)
{
    ofstream fo;
    fo.open(path + ClassName + "/Course.txt");

    CourseOfClass *curCourse = Courses;
    while (curCourse)
    {
        fo << curCourse->_Course->Info->CourseID << '\n';
        curCourse = curCourse->Next;
    }

    fo.close();
}

void Class::SaveClassData(string path)
{
    Class *cur = this;
    while (cur)
    {
        cur->SaveAClassData(path);
        cur = cur->Next;
    }
}

Student* Class::FindStudentByID(string ID)
{
    Class *curClass = this;
    while (curClass)
    {
        StudentInClass *curStudent = curClass->Students;
        while (curStudent)
        {
            if (curStudent->_Student->Info->ID == ID) return curStudent->_Student;
            curStudent = curStudent->Next;
        }
        curClass = curClass->Next;
    }
    return nullptr;
};

void Class::AddAStudentIntoAClass(Student *&_Student)
{
    StudentInClass *New = new StudentInClass({_Student, nullptr});
    if (Students == nullptr) {
        Students = New;
        return;
    }
    StudentInClass *cur = Students;
    while (cur->Next) cur = cur->Next;
    cur->Next = New;
}

void Class::AddACourseIntoAClass(Course *&_Course)
{
    CourseOfClass *New = new CourseOfClass({_Course, nullptr});
    if (Courses == nullptr) {
        Courses = New;
        return;
    }
    CourseOfClass *cur = Courses;
    while (cur->Next) cur = cur->Next;
    cur->Next = New;
}

void Class::ShowAllStudentInfo()
{
    StudentInClass *curStudent = Students;
    while (curStudent)
    {
        curStudent->_Student->ShowStudentInfo();
        curStudent = curStudent->Next;
    }
}

void Class::ShowAllCourseInfo()
{
    CourseOfClass *curCourse = Courses;
    while (curCourse)
    {
        curCourse->_Course->ShowCourseInfo();
        curCourse = curCourse->Next;
    }
}

//Outer Functions
void LoadLastClassData(Class *&Head, string path, Student *&StudentHead, Course *&CourseHead) // path bao gom ca ten semester Savefile/2021-2022/HKI/
{
    ifstream fi;
    fi.open("SaveFile/Class/AllClassInfo.txt");

    Head = new Class;
    Class *cur = Head;

    string ClassName;
    while (!fi.eof() && getline(fi, ClassName))
    {
        cur->Next = new Class, cur = cur->Next;
        cur->ClassName = ClassName;

        Student *curstudent = StudentHead;
        while (curstudent) {
            if (curstudent->Info->StudentClass == ClassName) cur->AddAStudentIntoAClass(curstudent);
            curstudent = curstudent->Next;
        }

        ifstream ficourse;
        ficourse.open(path + ClassName + "/Course.txt");

        string CourseID;
        while (!ficourse.eof() && getline(ficourse, CourseID)) {
            Course *Temp = CourseHead->FindACourseByID(CourseID);
            cur->AddACourseIntoAClass(Temp);
        }

        ficourse.close();
    }

    Class *pD = Head;
    Head = Head->Next;
    DeleteAClass(pD);
    fi.close();
}

void DeleteAClass(Class *&Head)
{
    StudentInClass *cur = Head->Students;
    while (cur)
    {
        StudentInClass *pD = cur;
        cur = cur->Next;
        delete(pD);
    }
    delete(Head);
}

void DeleteAllClass(Class *&Head)
{
    while (Head)
    {
        Class *pD = Head;
        Head = Head->Next;
        DeleteAClass(pD);
    }
}

