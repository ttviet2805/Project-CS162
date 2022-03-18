#include <iostream>
#include <fstream>
#include <unistd.h>

#include "DateHeader.h"
#include "CourseHeader.h"

using namespace std;


void Course::CourseInfo()
{
    char Name[] = "Name: ", ID[] = "ID: ", Lecturer[] = "Lecturer: ", Start[] = "Start day: ", End[] = "End day: ",
                    Ses1[] = "Session 1: ", Ses2[] = "Session 2: ";
    cout << Name << CourseName << '\n';
    cout << ID << CourseID << '\n';
    cout << Lecturer << LecturerName << '\n';
    cout << Start; StartDate.OutputDate();
    cout << End; EndDate.OutputDate();
    cout << Ses1 << ": " << FirstS << '\n';
    cout << Ses2 << ": " << SecondS << '\n';
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
    cout << "6. " << Ses1 << ": " << FirstS << '\n';
    cout << "7. " << Ses2 << ": " << SecondS << '\n';
}

void Course::SaveCoursesData(char Filename[])
{
    ofstream fo(Filename);
    Course *Cur = this;
    while (Cur)
    {
        fo << Cur->CourseName << '\n';
        fo << Cur->CourseID << '\n';
        fo << Cur->LecturerName << '\n';
        fo << Cur->StartDate.Day << " " << Cur->StartDate.Month << Cur->StartDate.Year << '\n';
        fo << Cur->EndDate.Day << " " << Cur->EndDate.Month << Cur->EndDate.Year << '\n';
        fo << Cur->FirstS << '\n' << Cur->SecondS << '\n';
    }

    fo.close();
}

void Course::Update(char Filename[])
{
    while (1)
    {
        system("cls");
        cout << "Choose course: \n";
        int i = 1;
        for (Course *cur = this; cur; cur = cur->Next, i++)
            cout << i << ". " << cur->CourseName << '\n';
        int num;
        cout << "Return and save = 0\n";
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
            cout << "Return and save = 0\n";
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
                    cin.getline(Cur->CourseName, 50);
                    break;
                }
                case 2:
                {
                    cin.ignore();
                    cin.getline(Cur->CourseID, 50);
                    break;
                }
                case 3:
                {
                    cin.ignore();
                    cin.getline(Cur->LecturerName, 50);
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
                    cin.getline(Cur->FirstS, 50);
                    break;
                }
                default:
                {
                    cin.ignore();
                    cin.getline(Cur->SecondS, 50);
                }
            }
        }
    }

    SaveCoursesData(Filename);
}

void LoadLastCoursesData(Course *&Head, char Filename[])
{
    ifstream fi(Filename);
    Head = new Course;
    Course *Dummy = Head;
    while (!fi.eof())
    {
        Dummy->Next = new Course, Dummy = Dummy->Next;
        fi.getline(Dummy->CourseName, 50);
        fi.getline(Dummy->CourseID, 50);
        fi.getline(Dummy->LecturerName, 50);
        int d, m, y;
        fi >> d >> m >> y;
        Dummy->StartDate = Date({d, m, y});
        fi >> d >> m >> y;
        Dummy->EndDate = Date({d, m, y});
        fi.ignore();
        fi.getline(Dummy->FirstS, 50);
        fi.getline(Dummy->SecondS, 50);
    }
    Course *pD = Head;
    Head = Head->Next;
    delete(pD);
    fi.close();
}

void Delete(Course *&Head, char Filename[])
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
        cout << "Return and save = 0\n";
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

    Head->SaveCoursesData(Filename);
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

void DeleteCourse(Course *&Head)
{
    while (Head)
    {
        Course *pD = Head;
        Head = Head->Next;
        delete(pD);
    }
}
