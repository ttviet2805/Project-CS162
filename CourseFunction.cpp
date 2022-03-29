#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>

#include "DateHeader.h"
#include "CourseHeader.h"

using namespace std;

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

void Course::CourseInfo()
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

void Course::Update()
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

void Course::SaveCoursesData(string Filename)
{
    ofstream fo(Filename);
    Course *Cur = this;
    while (Cur)
    {
        fo << Cur->CourseName << '\n';
        fo << Cur->CourseID << '\n';
        fo << Cur->LecturerName << '\n';
        fo << Cur->StartDate.Day << " " << Cur->StartDate.Month << " " << Cur->StartDate.Year << '\n';
        fo << Cur->EndDate.Day << " " << Cur->EndDate.Month << " " << Cur->EndDate.Year << '\n';
        fo << Cur->FirstS.Day << " " << Cur->FirstS.Ses << '\n';
        fo << Cur->SecondS.Day << " " << Cur->SecondS.Ses << '\n';
        Cur = Cur->Next;
    }

    fo.close();
}

void LoadLastCoursesData(Course *&Head, string Filename)
{
    ifstream fi(Filename);
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
        Dummy->EndDate = Date({d, m, y});
        fi >> Dummy->FirstS.Day >> Dummy->FirstS.Ses;
        fi >> Dummy->SecondS.Day >> Dummy->SecondS.Ses;
        Dummy->FirstS.Init();
        Dummy->SecondS.Init();
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

void Delete(Course *&Head)
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
