#include <iostream>
#include <fstream>

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
    cout << Ses1 << 'S' << FirstS << ' ';
    cout << Ses2 << 'S' << SecondS;
}

void Course::CourseInfoWithNumber()
{
    char Name[] = "Name: ", ID[] = "ID: ", Lecturer[] = "Lecturer: ", Start[] = "Start day: ", End[] = "End day: ",
                    Ses1[] = "Session 1: ", Ses2[] = "Session 2: ";
    cout << "1. " << Name << CourseName << '\n';
    cout << "2. " << ID << CourseID << '\n';
    cout << "3. " << Lecturer << LecturerName << '\n';
    cout << "4. " << Start; StartDate.OutputDate();
    cout << "5. " << End; EndDate.OutputDate();
    cout << "6. " << Ses1 << 'S' << FirstS << ' ';
    cout << "7. " << Ses2 << 'S' << SecondS;
}

void Course::LoadLastCoursesData(char Filename[])
{
    ifstream fi(Filename);
    int init = 1;
    Course *Dummy = this;
    while (!fi.eof())
    {
        if (!init) Dummy->Next = new Course;
            else init--;
        fi.getline(Dummy->CourseName, 50);
        fi.getline(Dummy->CourseID, 50);
        fi.getline(Dummy->LecturerName, 50);
        int d, m, y;
        fi >> d >> m >> y;
        Dummy->StartDate = Date({d, m, y});
        fi >> d >> m >> y;
        Dummy->EndDate = Date({d, m, y});
        fi >> Dummy->FirstS >> Dummy->SecondS;
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
        cout << "Return = 0";
        cout << "Please input a number: ";
        cin >> num;
        if (num == 0) return;
        if (num >= i) continue;
        Course *Cur = this;
        for (num--; num > 0; num--) Cur = Cur->Next;

        while (1)
        {
            system("cls");
            cout << Cur->CourseName << '\n';
            cout << "Choose element: \n";
            Cur->CourseInfoWithNumber();
            int num;
            cout << "Return = 0\n";
            cout << "Please input a number: ";
            cin >> num;
            if (num == 0) break;
            if (num > 7) continue;
            system("cls");
            cout << "Input new data: ";
            switch (num)
            {
                case 1:
                {
                    cin.getline(Cur->CourseName, 50);
                    break;
                }
                case 2:
                {
                    cin.getline(Cur->CourseID, 50);
                    break;
                }
                case 3:
                {
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
                    char c;
                    cin >> c;
                    cin >> Cur->FirstS;
                    break;
                }
                default:
                {
                    char c;
                    cin >> c;
                    cin >> Cur->SecondS;
                }
            }
        }
    }
}

void Course::Delete()
{

}
