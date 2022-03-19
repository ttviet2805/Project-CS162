#include <iostream>
#include <fstream>
#include <string>

#include "StudentHeader.h"
#include "DateHeader.h"

using namespace std;

void LoadLastStudentData(Student *&Head, string Filename)
{
    ifstream fi;
    fi.open(Filename);
    if (!fi.is_open()) return;
    Head = new Student;
    Student *cur = Head;
    while (!fi.eof())
    {
        cur->Next = new Student, cur = cur->Next;
        getline(fi, cur->ID);
        getline(fi, cur->ID);
        getline(fi, cur->FirstName);
        getline(fi, cur->LastName);
        getline(fi, cur->Gender);
        fi >> cur->Dob.Day >> cur->Dob.Month >> cur->Dob.Year;
        fi.ignore();
        getline(fi, cur->SocialID);
    }
    Student *pD = Head;
    Head = Head->Next;
    delete (pD);
    fi.close();
}
