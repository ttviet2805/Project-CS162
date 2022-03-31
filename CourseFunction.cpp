#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>

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

<<<<<<< Updated upstream
void Course::CourseInfo()
=======
//CourseInfo
void CourseInfo::ShowCourseInfo()
>>>>>>> Stashed changes
{
    char Name[] = "Name: ", ID[] = "ID: ", Lecturer[] = "Lecturer: ", Start[] = "Start day: ", End[] = "End day: ",
                    Ses1[] = "Session 1: ", Ses2[] = "Session 2: ";
    cout << Name << CourseName << '\n';
    cout << ID << CourseID << '\n';
    cout << Lecturer << LecturerName << '\n';
    cout << Start; StartDate.OutputDate();
    cout << End; EndDate.OutputDate();
    cout << Ses1; FirstS.Cout();
    cout << Ses2; SecondS.Cout();
<<<<<<< Updated upstream
=======
}
///////////////////////////////////////////////////////////////////////////

//CourseScore
void CourseScore::CalScore()
{
    //tinh diem
    Final = Other * 0.2 + MidTerm * 0.3 + Final * 0.5;
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

void LoadLastCourseScoreBoardData(CourseScoreBoard *ScoreBoard, CourseInfo *_CourseInfo, string path, string Filename, Student *StudentHead)
{
    ifstream fi(path + Filename);
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
    delete(pD->Score);
    delete(pD);
    fi.close();
}
///////////////////////////////////////////////////////////////////////////

//Course
void Course::ShowCourseInfo()
{
    Info->ShowCourseInfo();
>>>>>>> Stashed changes
}

void Course::CourseInfoWithNumber()
{
    system("cls");
    char Name[] = "Name: ", ID[] = "ID: ", Lecturer[] = "Lecturer: ", Start[] = "Start day: ", End[] = "End day: ",
                    Ses1[] = "Session 1: ", Ses2[] = "Session 2: ";
    cout << "1. " << Name << CourseName << '\n';
    cout << "2. " << ID << CourseID << '\n';
    cout << "3. " << Lecturer << LecturerName << '\n';
    cout << "4. " << Start; StartDate.OutputDate();
    cout << "5. " << End; EndDate.OutputDate();
    cout << "6. " << Ses1; FirstS.Cout();
    cout << "7. " << Ses2; SecondS.Cout();
}

void Course::AllCoursesInfo()
{
    system("cls");
    Course *Cur = this;
    while (Cur)
    {
        Cur->CourseInfo();
        Cur = Cur->Next;
    }
}

<<<<<<< Updated upstream
void Course::Update(string Filename)
=======
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
>>>>>>> Stashed changes
{
    while (1)
    {
        system("cls");
        cout << "Choose course: \n";
        int i = 1;
        for (Course *cur = this; cur; cur = cur->Next, i++)
            cout << i << ". " << cur->CourseName << '\n';
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
            cout << Cur->CourseName << '\n';
            cout << "Choose element: \n";
            Cur->CourseInfoWithNumber();
            int part;
            cout << "Return = 0\n";
            cout << "Please input a number: ";
            cin >> part;
            if (part == 0) break;
            if (part > 7)
            {
                cout << "Please input again!";
                sleep(2);
                continue;
            }
            system("cls");
            cout << "Input new data: ";
            switch (part)
            {
                case 1:
                {
                    cin.ignore();
                    getline(cin, Cur->CourseName);
                    break;
                }
                case 2:
                {
                    cin.ignore();
                    getline(cin, Cur->CourseID);
                    break;
                }
                case 3:
                {
                    cin.ignore();
                    getline(cin, Cur->LecturerName);
                    break;
                }
                case 4:
                {
                    Cur->StartDate.InputDate();
                    break;
                }
                case 5:
                {
                    Cur->EndDate.InputDate();
                    break;
                }
                case 6:
                {
                    cin.ignore();
                    Cur->FirstS.Cin();
                    break;
                }
                default:
                {
                    cin.ignore();
                    Cur->SecondS.Cin();
                }
            }
        }
    }
}

void Course::SaveCourseScoreBoard(string path, string Filename)
{
    ofstream fo;
    fo.open(path + Filename);

    CourseScoreBoard *cur = Scoreboard;
    while (cur)
    {
        fo << cur->Student->ID << '\n';
        fo << cur->Score->MidTerm << " " << cur->Score->Final << " " << cur->Score->Other << '\n';
        cur = cur->Next;
    }

    fo.close();
}

void Course::SaveCoursesData(string path, string Filename)
{
    ofstream fo(path + Filename);
    Course *Cur = this;
    while (Cur)
    {
<<<<<<< Updated upstream
        fo << Cur->CourseName << '\n';
        fo << Cur->CourseID << '\n';
        fo << Cur->LecturerName << '\n';
        fo << Cur->StartDate.Day << " " << Cur->StartDate.Month << " " << Cur->StartDate.Year << '\n';
        fo << Cur->EndDate.Day << " " << Cur->EndDate.Month << " " << Cur->EndDate.Year << '\n';
        fo << Cur->FirstS.Day << " " << Cur->FirstS.Ses << '\n';
        fo << Cur->SecondS.Day << " " << Cur->SecondS.Ses << '\n';
=======
        fo << Cur->Info->CourseName << '\n';
        fo << Cur->Info->CourseID << '\n';
        fo << Cur->Info->LecturerName << '\n';
        fo << Cur->Info->StartDate.Day << " " << Cur->Info->StartDate.Month << " " << Cur->Info->StartDate.Year << '\n';
        fo << Cur->Info->EndDate.Day << " " << Cur->Info->EndDate.Month << " " << Cur->Info->EndDate.Year << '\n';
        fo << Cur->Info->FirstS.Day << " " << Cur->Info->FirstS.Ses << '\n';
        fo << Cur->Info->SecondS.Day << " " << Cur->Info->SecondS.Ses << '\n';
        Cur->SaveCourseScoreBoard(path + "CourseScoreBoard/", Cur->Info->CourseName + ".txt");
>>>>>>> Stashed changes
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
    if (Tail == nullptr) Tail = NewBoard;
        else Tail->Next = NewBoard;
}

///////////////////////////////////////////////////////////////////////////


//Outer Functions
void LoadLastCoursesData(Course *&Head, string path, string Filename, Student *StudentHead)
{
    ifstream fi(path + Filename);
    Head = new Course;
    Course *Dummy = Head;
    string CourseName;
    while (!fi.eof() && getline(fi, CourseName))
    {
        Dummy->Next = new Course, Dummy = Dummy->Next;
        Dummy->CourseName = CourseName;
        getline(fi, Dummy->CourseID);
        getline(fi, Dummy->LecturerName);
        int d, m, y;
        fi >> d >> m >> y;
        Dummy->StartDate = Date({d, m, y});
        fi >> d >> m >> y;
<<<<<<< Updated upstream
        Dummy->EndDate = Date({d, m, y});
        fi >> Dummy->FirstS.Day >> Dummy->FirstS.Ses;
        fi >> Dummy->SecondS.Day >> Dummy->SecondS.Ses;
        Dummy->FirstS.Init();
        Dummy->SecondS.Init();
=======
        Dummy->Info->EndDate = Date({d, m, y});
        fi >> Dummy->Info->FirstS.Day >> Dummy->Info->FirstS.Ses;
        fi >> Dummy->Info->SecondS.Day >> Dummy->Info->SecondS.Ses;
        Dummy->Info->FirstS.Init();
        Dummy->Info->SecondS.Init();
        LoadLastCourseScoreBoardData(Dummy->Scoreboard, Dummy->Info, path + "CourseScoreBoard/", CourseName + ".txt", StudentHead);
>>>>>>> Stashed changes
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
    char Name[] = "Name: ", ID[] = "ID: ", Lecturer[] = "Lecturer: ", Start[] = "Start day: ", End[] = "End day: ",
                    Ses1[] = "Session 1: ", Ses2[] = "Session 2: ";
    cout << Name; cin.ignore(); getline(cin, New->CourseName);
    cout << ID; getline(cin, New->CourseID);
    cout << Lecturer; getline(cin, New->LecturerName);
    cout << Start; New->StartDate.InputDate();
    cout << End; New->EndDate.InputDate();
    cout << Ses1; New->FirstS.Cin();
    cout << Ses2; New->SecondS.Cin();
    if (Head == nullptr) Head = New;
        else
        {
            Course *cur = Head;
            while (cur->Next)
                cur = cur->Next;
            cur->Next = New;
        }
}

void Delete(Course *&Head, string Filename)
{
    while (1)
    {
        system("cls");
        if (Head == nullptr)
        {
            cout << "No more course!";
            sleep(2);
            break;
        }
        cout << "Choose course: \n";
        int i = 1;
        for (Course *cur = Head; cur; cur = cur->Next, i++)
            cout << i << ". " << cur->CourseName << '\n';
        int num;
        cout << "Return = 0\n";
        cout << "Please input a number: ";
        cin >> num;
        if (num == 0) break;
        if (num >= i)
        {
            cout << "Please input again!";
            sleep(2);
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
            delete(pD);
        }
        else
        {
            Course *pD = Cur->Next;
            Cur->Next = pD->Next;
            delete(pD);
        }
    }
}

void DeleteCourse(Course *&Head)
{
    while (Head)
    {
        Course *pD = Head;
        Head = Head->Next;
        delete(pD);
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
                Head->Update(Filename);
                break;
            }
        case 'D':
            {
                Delete(Head, Filename);
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
