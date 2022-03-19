#include <iostream>
#include <fstream>
#include <string>

#include "ClassHeader.h"
#include "StudentHeader.h"

using namespace std;

void LoadLastClassData(Class *&Head, string Filename)
{
    ifstream fi;
    fi.open(Filename);
    if (!fi.is_open()) return;
    Head = new Class;
    Class *cur = Head;
    while (!fi.eof())
    {
        cur->Next = new Class, cur = cur->Next;
        getline(fi, cur->ClassName);
        string path = ".txt";
        LoadLastStudentData(cur->Students, cur->ClassName + path);
    }

    Class *pD = Head;
    Head = Head->Next;
    delete Head->Students;
    delete pD;
    fi.close();
}

