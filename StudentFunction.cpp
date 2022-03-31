#include <iostream>
#include <fstream>
#include <string>

#include "StudentAndCourseHeader.h"
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

<<<<<<< Updated upstream
void Student::EnrollACourse(Course NewCourse) {
    if(!CourseHead) {
        CourseHead = &NewCourse;
        return;
    }
=======
bool Student::FindACourseAlreadyRegisted(CourseInfo *Info)
{
    StudentScoreBoard *cur = ScoreBoard;
    while (cur)
    {
        if (cur->Info == Info) return 1;
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
>>>>>>> Stashed changes

void Student::EnrollACourse(Course *CourseHead) {
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

<<<<<<< Updated upstream
    while(cur->Next) cur = cur->Next;

    cout << "Do you want to enroll this course\n";
    cout << "If you want, please write YES, else write NO\n";

    string Option; cin >> Option;
    if(Option == "YES") {
        NewCourse.CourseInfo();

        Course* tmp = &NewCourse;
        cur->Next = tmp;
        cout << "Enroll Succesful\n";
=======
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

void Student::RemoveACourse(Course *CourseHead) //CourseHead la list tat ca cac mon hoc
{
    if (CountNumberOfCoursesRegisted() == 0)
    {
        cout << "Not registed any courses!";
        system("pause");
        return;
>>>>>>> Stashed changes
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

<<<<<<< Updated upstream
void Student::ViewAListOfEnrollCourse() {
    cout << "Here is List of Enroll Courses\n";
    Course* cur = CourseHead;

    while(cur) {
        (*cur).CourseInfo();
=======
Student *Student::FindStudentByID(string ID)
{
    Student *cur = this;
    while (cur)
    {
        if (cur->Info->ID == ID) return cur;
>>>>>>> Stashed changes
        cur = cur->Next;
    }
    return nullptr;
}

void Student::AddAStudentScoreBoard(CourseInfo *Info, CourseScore *Score)
{
    StudentScoreBoard *curSSB = ScoreBoard;
    if (curSSB == nullptr)
    {
        curSSB = new StudentScoreBoard({Info, Score, nullptr});
        return;
    }
    while (curSSB->Next) curSSB = curSSB->Next;
    curSSB->Next = new StudentScoreBoard({Info, Score, nullptr});
}

<<<<<<< Updated upstream
void Student::RemoveACourse(Course DelCourse) {
    Course* cur = CourseHead;
    Course* pre = nullptr;
=======
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
>>>>>>> Stashed changes

    while(cur) {
        if(cur->CourseID == DelCourse.CourseID) {
            cout << "You have removed this course\n";

<<<<<<< Updated upstream
            if(pre) pre->Next = cur->Next;
            else {
                CourseHead = cur->Next;
            }
=======
void LoadLastStudentData(Student *&Head, string path, string Filename)
{
    ifstream fi;
    fi.open(path + Filename);
    if (!fi.is_open()) return;
>>>>>>> Stashed changes

            delete cur;
            return;
        }

<<<<<<< Updated upstream
        pre = cur;
        cur = cur->Next;
=======
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
>>>>>>> Stashed changes
    }

    cout << "We have not find this course\n";
}






