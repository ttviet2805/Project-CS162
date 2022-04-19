#include <iostream>
#include <fstream>
#include <string>

#include "StudentAndCourseHeader.h"
#include "DateHeader.h"

using namespace std;

void Student::ShowStudentInfo() {
    cout << "StudentID: " << Info->ID << '\n';
    cout << "Name: " << Info->FirstName << ' ' << Info->LastName << '\n';
    cout << "Gender: " << Info->Gender << '\n';
    cout << "Date of Birth: ";
    Info->Dob.OutputDate();
    cout << "Social ID: " << Info->SocialID << '\n';
    cout << "Class: " << Info->StudentClass << '\n';
}

bool Student::FindACourseAlreadyRegisted(CourseInfo *Info)
{
    StudentScoreBoard *cur = ScoreBoard;
    while (cur)
    {
        if (cur->Info->CourseID == Info->CourseID) return 1;
        cur = cur->Next;
    }
    return 0;
}

int Student::CountNumberOfCoursesRegisted()
{
    StudentScoreBoard *cur = ScoreBoard;
    int res = 0;
    while (cur) res++, cur = cur->Next;
    return res;
}

void Student::EnrollACourse(Course *&CourseHead) {
    Course *cur = CourseHead;
    system("cls");
    while(cur)
    {
        if (CountNumberOfCoursesRegisted() > 5)
        {
            cout << "Maximum number of registed courses!";
            system("pause");
            return;
        }

        if (FindACourseAlreadyRegisted(cur->Info))
        {
            cur = cur->Next;
            continue;
        }
        cout << cur->Info->CourseID << ' ' << cur->Info->CourseName << '\n';

        cout << "Do you want to enroll this course\n";
        cout << "If you want, please write YES, else write NO: ";

        string Option; cin >> Option;
        if(Option == "YES")
        {
            StudentScoreBoard *New = new StudentScoreBoard;
            New->Info = cur->Info;
            New->Score = new CourseScore;
            cur->AddANewStudent(Info, New->Score);
            AddAStudentScoreBoard(New->Info, New->Score);
            cout << "Enrollment Success\n";
        }
        else cout << "You have not enroll this Course\n";

        cur = cur->Next;
    }
}

void Student::ViewAListOfEnrollCourse()
{
    system("cls");
    cout << "Here is List of Enroll Courses\n";
    StudentScoreBoard* cur = ScoreBoard;

    while(cur) {
        cur->Info->ShowCourseInfo();
        cur = cur->Next;
    }

    system("pause");
}

void Student::RemoveACourse(Course *&CourseHead) //CourseHead la list tat ca cac mon hoc
{
    if (CountNumberOfCoursesRegisted() == 0)
    {
        cout << "Not registed any courses!";
        system("pause");
        return;
    }

    StudentScoreBoard *cur = ScoreBoard;
    system("cls");
    while(cur)
    {
        cout << cur->Info->CourseID << ' ' << cur->Info->CourseName << '\n';

        cout << "Do you want to remove this course\n";
        cout << "If you want, please write YES, else write NO: ";

        string Option; cin >> Option;
        if(Option == "YES")
        {
            if (cur == ScoreBoard)
            {
                RemoveAStudentFromACourse(CourseHead, cur->Info, Info);
                cur = cur->Next;
                ScoreBoard = ScoreBoard->Next;
            }
            else
            {
                StudentScoreBoard *p = ScoreBoard;
                while (p->Next != cur) p = p->Next;
                RemoveAStudentFromACourse(CourseHead, cur->Info, Info);
                cur = cur->Next;
                p->Next = cur;
            }
            cout << "Remove Success\n";
        }
        else
        {
            cout << "You have not remove this Course\n";
            cur = cur->Next;
        }
    }
}

Student *Student::FindStudentByID(string ID)
{
    Student *cur = this;
    while (cur)
    {
        if (cur->Info->ID == ID) return cur;
        cur = cur->Next;
    }
    return nullptr;
}

void Student::AddAStudentScoreBoard(CourseInfo *Info, CourseScore *Score)
{
    StudentScoreBoard *curSSB = ScoreBoard;
    if (curSSB == nullptr)
    {
        ScoreBoard = new StudentScoreBoard({Info, Score, nullptr});
        return;
    }
    while (curSSB->Next) curSSB = curSSB->Next;
    curSSB->Next = new StudentScoreBoard({Info, Score, nullptr});
}

void Student::SaveStudentsData(string path, string Filename)
{
    ofstream fo;
    fo.open(path + Filename);
    Student *cur = this;
    while (cur)
    {
        fo << cur->Info->ID << '\n';
        fo << cur->Info->FirstName << '\n';
        fo << cur->Info->LastName << '\n';
        fo << cur->Info->Gender << '\n';
        fo << cur->Info->Dob.Day << " " << cur->Info->Dob.Month << " " << cur->Info->Dob.Year << '\n';
        fo << cur->Info->SocialID << '\n';
        fo << cur->Info->StudentClass << '\n';
        cur = cur->Next;
    }
    fo.close();
}
/////////////////////////////////////

//Outer Functions of student
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

void LoadLastStudentData(Student *&Head, string path, string Filename)
{
    ifstream fi;
    fi.open(path + Filename);
    if (!fi.is_open()) return;

    Head = new Student;
    Student *cur = Head;

    string tmpID;
    while (!fi.eof() && getline(fi, tmpID))
    {
        cur->Next = new Student, cur = cur->Next;
        cur->Info->ID = tmpID;
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

void Student::deleteCurrentCourse(CourseInfo* curCourseInfo) {
    StudentScoreBoard* cur = ScoreBoard;

    if(cur && cur->Info->CourseID == curCourseInfo->CourseID) {
        StudentScoreBoard* Del = cur;
        ScoreBoard = ScoreBoard->Next;
        delete Del;
        return;
    }

    while(cur && cur->Next && cur->Next->Info->CourseID != curCourseInfo->CourseID) cur = cur->Next;

    if(cur == nullptr || cur->Next == nullptr) return;

    StudentScoreBoard* Del = cur->Next;
    cur->Next = Del->Next;

    delete Del;
}

void addANewStudentIntoStudentList(Student* &AllStudent, Student* newStudent) {
    Student* cur = AllStudent;

    if(cur) {
        while(cur->Next) cur = cur->Next;

        cur->Next = newStudent;
    }
    else {
        AllStudent = newStudent;
    }
}
