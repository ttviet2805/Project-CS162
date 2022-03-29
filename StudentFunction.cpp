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
        getline(fi, cur->FirstName);
        getline(fi, cur->LastName);
        getline(fi, cur->Gender);
        fi >> cur->Dob.Day >> cur->Dob.Month >> cur->Dob.Year;
        fi.ignore();
        getline(fi, cur->SocialID);
        getline(fi, cur->StudentClass);
        
    }
    Student *pD = Head;
    Head = Head->Next;
    delete (pD);
    fi.close();
}

void Student::StudentInfo() {
    cout << "StudentID: " << ID << '\n';
    cout << "Name: " << FirstName << ' ' << LastName << '\n';
    cout << "Gender: " << Gender << '\n';
    cout << "Date of Birth: ";
    Dob.OutputDate();

    cout << '\n';
}

void Student::EnrollACourse(Course* AddCourse) {
    Course* NewCourse = new Course;
    (*NewCourse) = (*AddCourse);
    NewCourse->Next = nullptr;

    (*NewCourse).CourseInfo();

    Course* cur = CourseHead;

    while(cur && cur->Next) cur = cur->Next;

    if(CourseHead) {
        cout << CourseHead->CourseID << ' ' << CourseHead->CourseName << '\n';
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
        cout << CourseHead->CourseID << ' ' << CourseHead->CourseName << '\n';
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
        (*cur).CourseInfo();
        cur = cur->Next;
        cout << '\n';
    }

    cout << '\n';
}

void Student::RemoveACourse(Course* DelCourse) {
    Delete(CourseHead);
}






