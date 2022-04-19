#pragma once

#include <bits/stdc++.h>
using namespace std;

#include "ConsoleSolve.h"
#include "StaffHeader.h"
#include "StudentAndCourseHeader.h"
#include "ClassHeader.h"

class Semester {
public:
    string semesterName;

    Date startDate, endDate;

    void ShowSemesterInfo();
    void setDate(int d1, int m1, int y1, int d2, int m2, int y2);
};

void createANewSemester();

Semester* loadSemester();
