#include "SemesterHeader.h"

Semester* loadSemester() {
    ifstream fin("Savefile/SchoolYear/SchoolYearInfo.txt");

    if(!fin) return nullptr;

    SchoolYear* res = new SchoolYear;
    getline(fin, res->schoolYearName);
    if(res->schoolYearName == "") {
        fin.close();
        return nullptr;
    }

    fin >> res->startDate.Day >> res->startDate.Month >> res->startDate.Year;
    fin >> res->endDate.Day >> res->endDate.Month >> res->endDate.Year;

    fin.close();

    fin.open("Savefile/SchoolYear/" + res->schoolYearName + "/Semester/SemesterInfo.txt");

    Semester* resSemester = new Semester;

    getline(fin, resSemester->semesterName);
    if(resSemester->semesterName == "") {
        fin.close();
        return nullptr;
    }

    fin >> resSemester->startDate.Day >> resSemester->startDate.Month >> resSemester->startDate.Year;
    fin >> resSemester->endDate.Day >> resSemester->endDate.Month >> resSemester->endDate.Year;

    fin.close();

    return resSemester;
}

void Semester::ShowSemesterInfo() {
    clrscr();
    Button profileButton = Button(19, 5, 80, 3, "Semester Information");
    profileButton.drawRectangleWithText();

    const int startRow = 10;
    const int startCol = 40;

    SchoolYear* curSchoolYear = loadSchoolYear();
    if(!curSchoolYear) {
        gotoxy(startCol, startRow + 2);
        cout << "Do not have school year data!!!";
        gotoxy(startCol, startRow + 4);
        system("pause");
        return;
    }

    if(this == nullptr) {
        gotoxy(45, 10);
        cout << "You have not create a semester yet!!!";
        gotoxy(45, 12);
        system("pause");
        return;
    }

    gotoxy(45, 10);
    cout << semesterName << endl;

    gotoxy(45, 11);
    cout << "Start Date: " << startDate.Day << '/' << startDate.Month << '/' << startDate.Year << '\n';
    gotoxy(45, 12);
    cout << "End Date: " << endDate.Day << '/' << endDate.Month << '/' << endDate.Year << '\n';

    gotoxy(45, 14);
    system("pause");
}

void createANewSemester() {
    clrscr();
    ShowCur(1);
    changeTextColor(11);
    Button profileButton = Button(19, 5, 80, 3, "Create A New Semester");
    profileButton.drawRectangleWithText();

    Semester* newSemester = new Semester;

    const int startCol = 9;
    gotoxy(40, startCol);
    cout << "Semester name: ";
    getline(cin, newSemester->semesterName);

    gotoxy(40, startCol + 1);
    cout << "Enter the start date Information\n";
    gotoxy(40, startCol + 2);
    cout << "Day: ";
    cin >> newSemester->startDate.Day;
    gotoxy(40, startCol + 3);
    cout << "Month: ";
    cin >> newSemester->startDate.Month;
    gotoxy(40, startCol + 4);
    cout << "Year: ";
    cin >> newSemester->startDate.Year;

    gotoxy(40, startCol + 5);
    cout << "Enter the end date Information\n";
    gotoxy(40, startCol + 6);
    cout << "Day: ";
    cin >> newSemester->endDate.Day;
    gotoxy(40, startCol + 7);
    cout << "Month: ";
    cin >> newSemester->endDate.Month;
    gotoxy(40, startCol + 8);
    cout << "Year: ";
    cin >> newSemester->endDate.Year;

    cin.get();

    SchoolYear* curSchoolYear = loadSchoolYear();

    if(!curSchoolYear) {
        cout << "You have not create a school year yet!!!";
        return;
    }

    gotoxy(40, startCol + 10);
    cout << "Create A New Semester Successfully";

    ofstream fout("Savefile/SchoolYear/" + curSchoolYear->schoolYearName + "/Semester/SemesterInfo.txt");
    fout << newSemester->semesterName << '\n';
    fout << newSemester->startDate.Day << ' ' << newSemester->startDate.Month << ' ' << newSemester->startDate.Year << '\n';
    fout << newSemester->endDate.Day << ' ' << newSemester->endDate.Month << ' ' << newSemester->endDate.Year;
    fout.close();

    gotoxy(40, startCol + 12);
    system("pause");

//    string fileName = "Savefile/SchoolYear/" + curSchoolYear->schoolYearName + "/Semester/";
//
//    if(mkdir(fileName.c_str()) == -1) {
//        gotoxy(40, startCol + 10);
//        cout << "Semester " + newSemester->semesterName + " has already existed";
//        gotoxy(40, startCol + 11);
//        cout << "Enter Again to try again or Back to back: ";
//        string Option; getline(cin, Option);
//
//        if(Option == "Again") {
//            Sleep(3000);
//            createANewSemester();
//            ShowCur(0);
//            return;
//        }
//
//        if(Option == "Back") {
//            ShowCur(0);
//            return;
//        }
//
//        gotoxy(40, startCol + 13);
//        cout << "We can not find Back or Again, try again\n";
//        Sleep(3000);
//        createANewSchoolYear();
//        ShowCur(0);
//        return;
//    }
//    else {
//        gotoxy(40, startCol + 10);
//        cout << "Create A New Semester Successfully";
//
//        ofstream fout("Savefile/SchoolYear/" + curSchoolYear->schoolYearName + "/Semester/SemesterInfo.txt");
//        fout << newSemester->semesterName << '\n';
//        fout << newSemester->startDate.Day << ' ' << newSemester->startDate.Month << ' ' << newSemester->startDate.Year << '\n';
//        fout << newSemester->endDate.Day << ' ' << newSemester->endDate.Month << ' ' << newSemester->endDate.Year;
//
//        string classFolder = fileName + "/Class";
//        mkdir(classFolder.c_str());
//        string semesterFolder = fileName + "/CourseScoreBoard";
//        mkdir(semesterFolder.c_str());
//
//        gotoxy(40, startCol + 12);
//        system("pause");
//        fout.close();
//
//        fout.open(fileName + "/Course.txt");
//        fout.close();
//
//        Student* AllStudent = nullptr;
//        LoadLastStudentData(AllStudent, "Savefile/Student/", "AllStudentInfo.txt");
//        Course* AllCourse = nullptr;
//        LoadLastCoursesData(AllCourse, "Savefile/Course/", "AllCourseInfo.txt", AllStudent);
//
//        string schoolYearPath;
//        ifstream fin;
//        fin.open("Savefile/Path/SchoolYearPath.txt");
//        getline(fin, schoolYearPath);
//        fin.close();
//
//        Class* AllClass = nullptr;
//        LoadLastClassData(AllClass, schoolYearPath, AllStudent, AllCourse);
//
//        fout.open(fileName + "/Class/AllClassInfo.txt");
//
//        while(AllClass) {
//            string newClassFolder = fileName + "/Class/" + AllClass->ClassName;
//            mkdir(newClassFolder.c_str());
//            fout << AllClass->ClassName << '\n';
//            AllClass = AllClass->Next;
//        }
//
//        fout.close();
//
//        return;
//    }
}

void Semester::setDate(int d1, int m1, int y1, int d2, int m2, int y2) {
    startDate.changeDate(d1, m1, y1);
    endDate.changeDate(d2, m2, y2);
}
