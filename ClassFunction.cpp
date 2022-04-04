#include <iostream>
#include <fstream>
#include <string>

#include "ClassHeader.h"
#include "StudentAndCourseHeader.h"

using namespace std;

//class Functions
//Class

void Class::SaveClassData(string path, string Filename)
{
    ofstream fo(path + Filename);

    Class *cur = this;
    while (cur)
    {
        fo << cur->ClassName << '\n';
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
    if (Students == nullptr)
    {
        Students = New;
        return;
    }
    StudentInClass *cur = Students;
    while (cur->Next) cur = cur->Next;
    cur->Next = New;
}

//Outer Functions
void LoadLastClassData(Class *&Head, string path, string Filename, Student *&StudentHead)
{
    ifstream fi;
    fi.open(Filename);
    if (!fi.is_open()) return;
    Head = new Class;
    Class *cur = Head;

    string ClassName;
    while (!fi.eof() && getline(fi, ClassName))
    {
        cur->Next = new Class, cur = cur->Next;
        cur->ClassName = ClassName;
        Student *curstudent = StudentHead;
        while (curstudent)
        {
            if (curstudent->Info->StudentClass == ClassName) cur->AddAStudentIntoAClass(curstudent);
            curstudent = curstudent->Next;
        }
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

