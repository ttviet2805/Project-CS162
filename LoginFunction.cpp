#include <bits/stdc++.h>
#include <unistd.h>
#include "LoginHeader.h"

using namespace std;

void Login()
{
    system("cls");
    char c;
    cout << "Are you an academic staff ? Y/N: ";
    cin >> c;
    bool staff = (c == 'Y');
    string Filename;
    if (staff) Filename = "Staff.txt";
        else Filename = "Student.txt";
    while (1)
    {
        system("cls");
        string Username, Password, User, Pass;
        cout << "Username: ";
        cin >> Username;
        cout << "Password: ";
        cin >> Password;
        bool Log = 0;
        ifstream fi(Filename);
        while (!fi.eof())
        {
            fi >> User;
            fi >> Pass;
            if (User == Username && Pass == Password) {Log = 1; break;}
        }
        fi.close();
        if (Log)
        {
            if (staff)
                /*while (1) StaffFunction();
                else while (1) StudentFunction();*/
            return;
        }
        else
        {
            cout << "Incorrect username or password!";
            sleep(3);
        }
    }
}

