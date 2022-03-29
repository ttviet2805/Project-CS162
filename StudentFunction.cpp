#include <iostream>
#include <fstream>
#include <string>

#include "StudentHeader.h"
#include "DateHeader.h"

using namespace std;

void Student::ShowStudentInfo() {
    cout << "StudentID: " << Info->ID << '\n';
    cout << "Name: " << Info->FirstName << ' ' << Info->LastName << '\n';
    cout << "Gender: " << Info->Gender << '\n';
    cout << "Date of Birth: ";
    Info->Dob.OutputDate();

    cout << '\n';
}

void Student::EnrollACourse(Course* AddCourse) {
    Course* NewCourse = new Course;
    (*NewCourse) = (*AddCourse);
    NewCourse->Next = nullptr;

    (*NewCourse).ShowCourseInfo();

    Course* cur = CourseHead;

    while(cur && cur->Next) cur = cur->Next;

    if(CourseHead) {
        cout << CourseHead->Info->CourseID << ' ' << CourseHead->Info->CourseName << '\n';
    }

    cout << "Do you want to enroll this course\n";
    cout << "If you want, please write YES, else write NO: ";

    string Option; cin >> Option;
    if(Option == "YES") {
        if(cur) cur->Next = NewCourse;
        else {
            CourseHead = NewCourse;
        }
        if(CourseHead) {
        cout << CourseHead->Info->CourseID << ' ' << CourseHead->Info->CourseName << '\n';
    }
        cout << "Enrollment Success\n";
    }
    else {
        cout << "You have not enroll this Course\n";
    }
}

void Student::ViewAListOfEnrollCourse() {
    cout << "Here is List of Enroll Courses\n";
    Course* cur = CourseHead;

    while(cur) {
        (*cur).ShowCourseInfo();
        cur = cur->Next;
        cout << '\n';
    }

    cout << '\n';
}

void Student::RemoveACourse(Course* DelCourse) {
    Delete(CourseHead);
}

void DeleteAStudent(Student *&pD)
{
    delete(pD->Info);
    delete(pD);
}

void DeleteAllStudent(Student *&Head)
{
    while (Head)
    {
        Student *pD = Head;
        Head = Head->Next;
        DeleteAStudent(pD);
    }
}

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
        getline(fi, cur->Info->ID);
        getline(fi, cur->Info->FirstName);
        getline(fi, cur->Info->LastName);
        getline(fi, cur->Info->Gender);
        fi >> cur->Info->Dob.Day >> cur->Info->Dob.Month >> cur->Info->Dob.Year;
        fi.ignore();
        getline(fi, cur->Info->SocialID);
        getline(fi, cur->Info->StudentClass);
        
    }
    Student *pD = Head;
    Head = Head->Next;
    delete (pD);
    fi.close();
}




