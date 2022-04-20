#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <windows.h>

#include "DateHeader.h"
#include "StudentAndCourseHeader.h"

using namespace std;

//Session
void Session::Init()
{
    if (Ses == "S1") Hour = 7;
    else if (Ses == "S2") Hour = 9;
    else if (Ses == "S3") Hour = 13;
    else Hour = 15;
    Mins = 30;
}

void Session::Cout()
{
    cout << Day << " (" + Ses + ") " << Hour << ':' << Mins << '\n';
}

void Session::Cin()
{
    cin >> Day >> Ses;
    Init();
}
///////////////////////////////////////////////////////////////////////////

//CourseInfo
void CourseInfo::ShowCourseInfo()
{
    char Name[] = "Name: ", ID[] = "ID: ", Lecturer[] = "Lecturer: ", Credit[] = "Number of credits: ", Start[] = "Start day: ", End[] = "End day: ",
                    Ses1[] = "Session 1: ", Ses2[] = "Session 2: ";
    cout << Name << CourseName << '\n';
    cout << ID << CourseID << '\n';
    cout << Lecturer << LecturerName << '\n';
    cout << Credit << NumOfCredits << '\n';
    cout << Start; StartDate.OutputDate();
    cout << End; EndDate.OutputDate();
    cout << Ses1; FirstS.Cout();
    cout << Ses2; SecondS.Cout();
}
///////////////////////////////////////////////////////////////////////////

//CourseScore
void CourseScore::CalScore()
{
    //tinh diem
    Total = Other * 0.2 + MidTerm * 0.3 + Final * 0.5;
}

void CourseScore::ShowCourseScore()
{
    CalScore();
    cout << MidTerm << " " << Final << " " << Other << " " << Total << '\n';
}
///////////////////////////////////////////////////////////////////////////

//CourseScoreBoard
void CourseScoreBoard::ShowCourseScoreBoard()
{
    cout << Student->ID << " " << Student->FirstName << " " << Student->LastName << " ";
    Score->ShowCourseScore();
}

void LoadLastCourseScoreBoardData(CourseScoreBoard *&ScoreBoard, CourseInfo *_CourseInfo, string path, string Filename, Student *&StudentHead)
{
    ifstream fi;
    fi.open(path + Filename);
    if (!fi.is_open()) return;
    string ID;
    ScoreBoard = new CourseScoreBoard;
    CourseScoreBoard *cur = ScoreBoard;
    while (!fi.eof() && getline(fi, ID))
    {
        cur->Next = new CourseScoreBoard;
        cur = cur->Next;
        Student *CurStudent = StudentHead->FindStudentByID(ID);
        cur->Student = CurStudent->Info;
        cur->Score = new CourseScore;
        fi >> cur->Score->MidTerm >> cur->Score->Final >> cur->Score->Other;
        CurStudent->AddAStudentScoreBoard(_CourseInfo, cur->Score);
        fi.ignore();
    }
    CourseScoreBoard *pD = ScoreBoard;
    ScoreBoard = ScoreBoard->Next;
    delete(pD);
    fi.close();
}
///////////////////////////////////////////////////////////////////////////

//Course
void Course::ShowCourseInfo()
{
    Info->ShowCourseInfo();
}

void Course::ShowCourseInfoWithNumber()
{
    system("cls");
    char Name[] = "Name: ", ID[] = "ID: ", Lecturer[] = "Lecturer: ", Credit[] = "Number of credits: ", Start[] = "Start day: ", End[] = "End day: ",
                    Ses1[] = "Session 1: ", Ses2[] = "Session 2: ";
    cout << "1. " << Name << Info->CourseName << '\n';
    cout << "2. " << ID << Info->CourseID << '\n';
    cout << "3. " << Lecturer << Info->LecturerName << '\n';
    cout << "4. " << Credit << Info->NumOfCredits << '\n';
    cout << "5. " << Start; Info->StartDate.OutputDate();
    cout << "6. " << End; Info->EndDate.OutputDate();
    cout << "7. " << Ses1; Info->FirstS.Cout();
    cout << "8. " << Ses2; Info->SecondS.Cout();
}

void Course::AllCoursesInfo()
{
    system("cls");
    Course *Cur = this;
    while (Cur)
    {
        Cur->ShowCourseInfo();
        Cur = Cur->Next;
    }
}

void Course::ShowAllCourseScoreBoard()
{
    int i = 0;
    CourseScoreBoard *cur = this->Scoreboard;
    while (cur)
    {
        cout << ++i << " " ;
        cur->ShowCourseScoreBoard();
        cur = cur->Next;
    }
}

void Course::Update()
{
    while (1)
    {
        system("cls");
        cout << "Choose course: \n";
        int i = 1;
        for (Course *cur = this; cur; cur = cur->Next, i++)
            cout << i << ". " << cur->Info->CourseName << '\n';
        int num;
        cout << "Return = 0\n";
        cout << "Please input a number: ";
        cin >> num;
        if (num == 0) break;
        if (num >= i) continue;
        Course *Cur = this;
        for (num--; num > 0; num--) Cur = Cur->Next;

        while (1)
        {
            system("cls");
            cout << Cur->Info->CourseName << '\n';
            cout << "Choose element: \n";
            Cur->ShowCourseInfoWithNumber();
            int part;
            cout << "Return = 0\n";
            cout << "Please input a number: ";
            cin >> part;
            if (part == 0) break;
            if (part > 8)
            {
                cout << "Please input again!";
                Sleep(2000);
                continue;
            }
            system("cls");
            cout << "Input new data: ";
            switch (part)
            {
                case 1:
                {
                    cin.ignore();
                    getline(cin, Cur->Info->CourseName);
                    break;
                }
                case 2:
                {
                    cin.ignore();
                    getline(cin, Cur->Info->CourseID);
                    break;
                }
                case 3:
                {
                    cin.ignore();
                    getline(cin, Cur->Info->LecturerName);
                    break;
                }
                case 4:
                {
                    cin >> Cur->Info->NumOfCredits;
                    break;
                }
                case 5:
                {
                    Cur->Info->StartDate.InputDate();
                    break;
                }
                case 6:
                {
                    Cur->Info->EndDate.InputDate();
                    break;
                }
                case 7:
                {
                    cin.ignore();
                    Cur->Info->FirstS.Cin();
                    break;
                }
                default:
                {
                    cin.ignore();
                    Cur->Info->SecondS.Cin();
                }
            }
        }
    }
}

void Course::SaveCourseScoreBoard(string path, string Filename)
{
    ofstream fo;
    fo.open(path + Filename);

//    if(fo.is_open()) {
//        cout << "YUP";
//    }
//    cout << path + Filename << endl;
    CourseScoreBoard *cur = Scoreboard;
    while (cur)
    {
//        cout << "# " << cur->Student->ID<< ' ' << cur << endl;
        fo << cur->Student->ID << '\n';
        fo << cur->Score->MidTerm << " " << cur->Score->Final << " " << cur->Score->Other << '\n';
        cur = cur->Next;
    }

//    cout << endl;

    fo.close();
}

void Course::SaveCoursesData(string path, string Filename)
{
    ofstream fo(path + Filename);
    Course *Cur = this;
    while (Cur)
    {
        fo << Cur->Info->CourseName << '\n';
        fo << Cur->Info->CourseID << '\n';
        fo << Cur->Info->LecturerName << '\n';
        fo << Cur->Info->NumOfCredits << '\n';
        fo << Cur->Info->StartDate.Day << " " << Cur->Info->StartDate.Month << " " << Cur->Info->StartDate.Year << '\n';
        fo << Cur->Info->EndDate.Day << " " << Cur->Info->EndDate.Month << " " << Cur->Info->EndDate.Year << '\n';
        fo << Cur->Info->FirstS.Day << " " << Cur->Info->FirstS.Ses << '\n';
        fo << Cur->Info->SecondS.Day << " " << Cur->Info->SecondS.Ses << '\n';
        Cur = Cur->Next;
    }

    Cur = this;
    while (Cur)
    {
        Cur->SaveCourseScoreBoard(path + "CourseScoreBoard/", Cur->Info->CourseName + ".txt");
        Cur = Cur->Next;
    }

    fo.close();
}

void Course::AddANewStudent(StudentInfo *SI, CourseScore *CS)
{
    CourseScoreBoard *Tail = Scoreboard;
    while (Tail && Tail->Next) Tail = Tail->Next;
    CourseScoreBoard *NewBoard = new CourseScoreBoard;
    NewBoard->Student = SI;
    NewBoard->Score = CS;
    if (Tail == nullptr) Scoreboard = NewBoard;
        else Tail->Next = NewBoard;
}

///////////////////////////////////////////////////////////////////////////


//Outer Functions
void LoadLastCoursesData(Course *&Head, string path, string Filename, Student *&StudentHead)
{
    ifstream fi(path + Filename);
    Head = new Course;
    Course *Dummy = Head;
    string CourseName;
    while (!fi.eof() && getline(fi, CourseName))
    {
        Dummy->Next = new Course, Dummy = Dummy->Next;
        Dummy->Info->CourseName = CourseName;
        getline(fi, Dummy->Info->CourseID);
        getline(fi, Dummy->Info->LecturerName);
        int d, m, y;
        fi >> Dummy->Info->NumOfCredits;
        fi >> d >> m >> y;
        Dummy->Info->StartDate = Date({d, m, y});
        fi >> d >> m >> y;
        Dummy->Info->EndDate = Date({d, m, y});
        fi >> Dummy->Info->FirstS.Day >> Dummy->Info->FirstS.Ses;
        fi >> Dummy->Info->SecondS.Day >> Dummy->Info->SecondS.Ses;
        Dummy->Info->FirstS.Init();
        Dummy->Info->SecondS.Init();
        LoadLastCourseScoreBoardData(Dummy->Scoreboard, Dummy->Info, path + "CourseScoreBoard/", CourseName + ".txt", StudentHead);
        fi.ignore();
    }
    Course *pD = Head;
    Head = Head->Next;
    delete(pD);
    fi.close();
}

void AddCourse(Course *&Head)
{
    system("cls");
    Course *New = new Course;
    char Name[] = "Name: ", ID[] = "ID: ", Lecturer[] = "Lecturer: ", Credit[] = "Number of Credits: ", Start[] = "Start day: ", End[] = "End day: ",
                    Ses1[] = "Session 1: ", Ses2[] = "Session 2: ";
    cout << Name; cin.ignore(); getline(cin, New->Info->CourseName);
    cout << ID; getline(cin, New->Info->CourseID);
    cout << Lecturer; getline(cin, New->Info->LecturerName);
    cout << Credit; cin >> New->Info->NumOfCredits;
    cout << Start; New->Info->StartDate.InputDate();
    cout << End; New->Info->EndDate.InputDate();
    cout << Ses1; New->Info->FirstS.Cin();
    cout << Ses2; New->Info->SecondS.Cin();
    if (Head == nullptr) Head = New;
        else
        {
            Course *cur = Head;
            while (cur->Next)
                cur = cur->Next;
            cur->Next = New;
        }
}

void DeleteACourse(Course *&pD)
{
    if (pD == nullptr) return;
    delete(pD->Info);
    delete(pD);
}

void Delete(Course *&Head)
{
    while (1)
    {
        system("cls");
        if (Head == nullptr)
        {
            cout << "No more course!";
            Sleep(2000);
            break;
        }
        cout << "Choose course: \n";
        int i = 1;
        for (Course *cur = Head; cur; cur = cur->Next, i++)
            cout << i << ". " << cur->Info->CourseName << '\n';
        int num;
        cout << "Return = 0\n";
        cout << "Please input a number: ";
        cin >> num;
        if (num == 0) break;
        if (num >= i)
        {
            cout << "Please input again!";
            Sleep(2);
            continue;
        }
        bool Recheck = 0;
        cout << "Are you sure? (Y/N): ";
        char c;
        cin >> c;
        Recheck = (c == 'Y');
        if (!Recheck) continue;
        Course *Cur = Head;
        for (num--, num--; num > 0; num--) Cur = Cur->Next;
        if (num == -1)
        {
            Course *pD = Head;
            Head = Head->Next;
            DeleteACourse(pD);
        }
        else
        {
            Course *pD = Cur->Next;
            Cur->Next = pD->Next;
            DeleteACourse(pD);
        }
    }
}

void DeleteAllCourse(Course *&Head)
{
    while (Head)
    {
        Course *pD = Head;
        Head = Head->Next;
        DeleteACourse(pD);
    }
}

void StaffWorkWithCourse(Course *&Head, string Filename)
{
    while (1)
    {
        system("cls");
        if (Head == nullptr)
        {
            cout << "No courses exist!";
            system("pause");
            break;
        }
        cout << "Choose an action:\n";
        cout << "I: Show all courses information\n";
        cout << "A: Add a course\n";
        cout << "U: Update a course\n";
        cout << "D: Delete a course\n";
        cout << "0: Return and save all changes!\n";
        cout << "Input an option: ";
        char c;
        cin >> c;
        switch (c)
        {
        case 'I':
            {
                Head->AllCoursesInfo();
                system("pause");
                break;
            }
        case 'A':
            {
                AddCourse(Head);
                break;
            }
        case 'U':
            {
                Head->Update();
                break;
            }
        case 'D':
            {
                Delete(Head);
                break;
            }
        default:
            {
                return;
            }
        }
    }
}

void RemoveAStudentFromACourse(Course *&CourseHead, CourseInfo *_Course, StudentInfo *_Student)
{
    Course *cur = CourseHead;
    while (cur->Info != _Course) cur = cur->Next;
    CourseScoreBoard *SB = cur->Scoreboard;
    if (SB->Student == _Student)
    {
        CourseScoreBoard *pD = SB;
        SB = SB->Next;
        delete(pD->Score);
        delete(pD);
        return;
    }
    while (SB->Next->Student != _Student) SB = SB->Next;
    CourseScoreBoard *pD = SB->Next;
    SB->Next = SB->Next->Next;
    delete(pD->Score);
    delete(pD);
}

void Course::deleteStudent(StudentInfo* curStudentInfo) {
    CourseScoreBoard* cur = Scoreboard;

    if(cur && cur->Student->ID == curStudentInfo->ID) {
        CourseScoreBoard* Del = cur;
        Scoreboard = Scoreboard->Next;
        delete Del;
        return;
    }

    while(cur && cur->Next && cur->Next->Student != curStudentInfo) cur = cur->Next;

    if(cur == nullptr || cur->Next == nullptr) return;

    CourseScoreBoard* Del = cur->Next;
    cur->Next = Del->Next;
    delete Del;
}

Course *Course::FindACourseByID(string ID)
{
    Course *cur = this;
    while (cur)
    {
        if (cur->Info->CourseID == ID) return cur;
        cur = cur->Next;
    }
    return nullptr;
}

void AddANewCourse(Course* &CourseHead, Course* newCourse) {
    Course* cur = CourseHead;
    if(!cur) {
        CourseHead = newCourse;
        return;
    }

    while(cur->Next) cur = cur->Next;
    cur->Next = newCourse;
}

void CourseScoreBoard::UpdateScore(CourseScore* curCourseScore) {
    Score = curCourseScore;
}

bool CourseScore::isFinish() {
    if(MidTerm != -1 || Final != -1 || Other != -1) return true;
    return false;
}
