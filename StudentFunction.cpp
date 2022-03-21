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

void Student::StudentInfo() {
    cout << "StudentID: " << ID << '\n';
    cout << "Name: " << FirstName << ' ' << LastName << '\n';
    cout << "Gender: " << Gender << '\n';
    cout << "Date of Birth: ";
    Dob.OutputDate();
}

void Student::EnrollACourse(Course NewCourse) {
    if(!CourseHead) {
        CourseHead = &NewCourse;
        return;
    }

    Course* cur = CourseHead;

    while(cur->Next) cur = cur->Next;

    cout << "Do you want to enroll this course\n";
    cout << "If you want, please write YES, else write NO\n";

    string Option; cin >> Option;
    if(Option == "YES") {
        NewCourse.CourseInfo();

        Course* tmp = &NewCourse;
        cur->Next = tmp;
        cout << "Enroll Succesful\n";
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

void Student::RemoveACourse(Course DelCourse) {
    Course* cur = CourseHead;
    Course* pre = nullptr;

    while(cur) {
        if(cur->CourseID == DelCourse.CourseID) {
            cout << "You have removed this course\n";

            if(pre) pre->Next = cur->Next;
            else {
                CourseHead = cur->Next;
            }

            delete cur;
            return;
        }

        pre = cur;
        cur = cur->Next;
    }

    cout << "We have not find this course\n";
}






