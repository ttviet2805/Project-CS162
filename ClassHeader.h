#pragma once

#include <string>
#include "StudentHeader.h"

class Class
{
    public:
        string ClassName;
        Student *Students;
        Class *Next = nullptr;


};

void LoadLastClassData(Class *&Head, char Filename[]);