#pragma once

#include <string>
#include "StudentAndCourseHeader.h"

class Class
{
    public:
        string ClassName;
        Student *Students;
        Class *Next = nullptr;
        Class *Head = nullptr;
        Class *Tail = nullptr;
};

void AddaClass(Class *&Head, Class *&Fr);

void LoadLastClassData(Class *&Head, char Filename[]);

void DeleteAllClass(Class *&Head);