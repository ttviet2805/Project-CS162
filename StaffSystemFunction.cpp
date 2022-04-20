#include "StaffSystemHeader.h"

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define ENTER 13

const string AllStaffUserPath = "Savefile/User/";
const string AllStaffUserFilename = "StaffUser.txt";
const string AllStaffInfoPath = "Savefile/Staff/";
const string AllStaffInfoFilename = "AllStaffInfo.txt";

void myProfileFunction(Staff* curStaff) {
    string staffID = "Staff ID";
    string firstName = "First Name";
    string lastName = "Last Name";
    string gender = "Gender";
    string Dob = "Date of Birth";
    string socialID = "Social ID";
    const int rectSize = 31;

    changeTextColor(11);
    Button profileButton = Button(19, 5, 80, 3, "MY PROFILE");
    profileButton.drawRectangleWithText();

    Button profileBackground = Button(19, 9, 80, 15, "");
    profileBackground.color = 11;
    profileBackground.fillRectangle();

    string staffIDString = curStaff->Info->ID;
    while(staffIDString.size() < rectSize) staffIDString += ' ';
    printATXYWithBackGround(25, 10, 11, 0, staffID);
    printATXYWithBackGround(25, 11, 15, 0, staffIDString);

    string firstNameString = curStaff->Info->FirstName;
    while(firstNameString.size() < rectSize) firstNameString += ' ';
    printATXYWithBackGround(25, 13, 11, 0, firstName);
    printATXYWithBackGround(25, 14, 15, 0, firstNameString);

    string lastNameString = curStaff->Info->LastName;
    while(lastNameString.size() < rectSize) lastNameString += ' ';
    printATXYWithBackGround(25, 16, 11, 0, lastName);
    printATXYWithBackGround(25, 17, 15, 0, lastNameString);

    string genderString = curStaff->Info->Gender;
    while(genderString.size() < rectSize) genderString += ' ';
    printATXYWithBackGround(25, 19, 11, 0, gender);
    printATXYWithBackGround(25, 20, 15, 0, genderString);

    Date dateOfBirth = curStaff->Info->Dob;
    string dobString = to_string(dateOfBirth.Day) + '/' + to_string(dateOfBirth.Month) + '/' + to_string(dateOfBirth.Year);
    while(dobString.size() < rectSize) dobString += ' ';
    printATXYWithBackGround(62, 10, 11, 0, Dob);
    printATXYWithBackGround(62, 11, 15, 0, dobString);
}

void createASchoolYearFunction() {
    createANewSchoolYear();
}

void schoolYearInformationFuntion() {
    ShowSchoolYearInfo();
}

void IntoClass(Class* curClass, string curSchoolYear) {
    ShowCur(0);
    clrscr();
    changeTextColor(11);
    Button listOfStudentButton = Button(19, 5, 80, 3, "List of Students");
    listOfStudentButton.drawRectangleWithText();

    const int startCol = 5, startRow = 10;

    if(!curClass->Students) {
        gotoxy(45, startRow + 3);
        cout << "The class has no member";
        cout << endl << endl;
        system("pause");
        return;
    }

    gotoxy(startCol, startRow);
    cout << "ID";
    gotoxy(startCol + 15, startRow);
    cout << "First name";
    gotoxy(startCol + 40, startRow);
    cout << "Last name";
    gotoxy(startCol + 60, startRow);
    cout << "Gender";
    gotoxy(startCol + 70, startRow);
    cout << "Date of Birth";
    gotoxy(startCol + 85, startRow);
    cout << "Class";
    gotoxy(startCol + 95, startRow);
    cout << "Social ID";


    StudentInClass* curStu = curClass->Students;

    int tmpcnt = 1;

    while(curStu) {
        ++tmpcnt;
        Student* cur = curStu->_Student;
        gotoxy(startCol, startRow + tmpcnt);
        cout << cur->Info->ID;
        gotoxy(startCol + 15, startRow + tmpcnt);
        cout << cur->Info->FirstName;
        gotoxy(startCol + 40, startRow + tmpcnt);
        cout << cur->Info->LastName;
        gotoxy(startCol + 60, startRow + tmpcnt);
        cout << cur->Info->Gender;
        gotoxy(startCol + 70, startRow + tmpcnt);
        cout << cur->Info->Dob.Day << '/' << cur->Info->Dob.Month << '/' << cur->Info->Dob.Year;
        gotoxy(startCol + 85, startRow + tmpcnt);
        cout << cur->Info->StudentClass;
        gotoxy(startCol + 95, startRow + tmpcnt);
        cout << cur->Info->SocialID;
        ++tmpcnt;

        curStu = curStu->Next;
    }

    gotoxy(45, startRow + tmpcnt + 2);
    system("pause");
}

void loadStudentFromCSV() {
    ShowCur(1);
    clrscr();
    changeTextColor(11);
    Button createClassButton = Button(19, 5, 80, 3, "Import Student From CSV File");
    createClassButton.drawRectangleWithText();

    const int startRow = 10, startCol = 53;

    SchoolYear* curSchoolYear = loadSchoolYear();
    if(!curSchoolYear) {
        gotoxy(startCol, startRow + 2);
        cout << "Do not have school year data!!!";
        gotoxy(startCol, startRow + 4);
        system("pause");
        return;
    }

    Student* AllStudent = nullptr;
    LoadLastStudentData(AllStudent, "Savefile/Student/", "AllStudentInfo.txt");
    Course* AllCourse = nullptr;
    LoadLastCoursesData(AllCourse, "Savefile/Course/", "AllCourseInfo.txt", AllStudent);

    string schoolYearPath;
    ifstream fin;
    fin.open("Savefile/Path/SchoolYearPath.txt");
    getline(fin, schoolYearPath);
    fin.close();

    Class* AllClass = nullptr;
    LoadLastClassData(AllClass, schoolYearPath, AllStudent, AllCourse);

    string ClassName = "";
    gotoxy(startCol, startRow);
    cout << "Class: ";
    getline(cin, ClassName);

    Class* curClass = findClassByID(AllClass, ClassName);

    string classFileName = "Savefile/SchoolYear/" + curSchoolYear->schoolYearName + "/Class/";
    fin.open(classFileName + "AllClassInfo.txt");

    bool isExist = false;

    while(!fin.eof()) {
        string tmp;
        getline(fin, tmp);

        if(tmp == curClass->ClassName) isExist = true;
    }

    fin.close();

    if(!isExist) {
        gotoxy(startCol, startRow + 2);
        cout << "This class do not exist, try again";
        gotoxy(startCol, startRow + 4);
        system("pause");
        loadStudentFromCSV();
        return;
    }

    // Savefile/SchoolYear/2021-2022/Class/21CTT1/AllStudentInfo.csv
    ImportStudentInClassFromCSVFile(AllStudent, curClass);

    AllStudent->SaveStudentsData("Savefile/Student/", "AllStudentInfo.txt");

    ShowCur(0);

    loadingFunction(45, startRow + 6);

    //Savefile/SchoolYear/2021-2022/Class/21CTT1/Student.csv

//    gotoxy(startCol, startRow + 3);
//    cout << "Load Student From CSV File Successfully";
//
//    gotoxy(startCol, startRow + 5);
//    system("pause");
}

void viewClassScoreboard(Class* curClass) {
    clrscr();
    changeTextColor(11);
    Button listOfStudentButton = Button(19, 5, 80, 3, "View Scoreboard");
    listOfStudentButton.drawRectangleWithText();

    string schoolYearPath = "";
    ifstream fin;
    fin.open("Savefile/Path/SchoolYearPath.txt");
    getline(fin, schoolYearPath);
    fin.close();

    Student* AllStudent = nullptr;
    LoadLastStudentData(AllStudent, "Savefile/Student/", "AllStudentInfo.txt");

    Course* AllCourse = nullptr;
    LoadLastCoursesData(AllCourse, schoolYearPath, "AllCourseInfo.txt", AllStudent);

    const int startCol = 15, startRow = 10;

    gotoxy(startCol, startRow);
    cout << "ID";
    gotoxy(startCol + 15, startRow);
    cout << "First name";
    gotoxy(startCol + 40, startRow);
    cout << "Last name";
    gotoxy(startCol + 60, startRow);
    cout << "Total Mark";
    gotoxy(startCol + 75, startRow);
    cout << "GPA";

    StudentInClass* curStu = curClass->Students;
    int tmpcnt = 1;

    while(curStu) {
        ++tmpcnt;
        gotoxy(startCol, startRow + tmpcnt);
        cout << curStu->_Student->Info->ID;
        gotoxy(startCol + 15, startRow + tmpcnt);
        cout << curStu->_Student->Info->FirstName;
        gotoxy(startCol + 40, startRow + tmpcnt);
        cout << curStu->_Student->Info->LastName;

        Student* ttt = AllStudent->FindStudentByID(curStu->_Student->Info->ID);
        StudentScoreBoard* curStuScore = ttt->ScoreBoard;

        float totalScore = 0;
        int cnt = 0;
        while(curStuScore) {
            ++cnt;
            curStuScore->Score->CalScore();
            totalScore += curStuScore->Score->Total;
            curStuScore = curStuScore->Next;
        }

        if(cnt != 0)
            totalScore = totalScore * 1.0 / cnt;

        gotoxy(startCol + 60, startRow + tmpcnt);
        cout << totalScore;

        gotoxy(startCol + 75, startRow + tmpcnt);
        float res = totalScore * 1.0 / 10 * 4;
        cout << fixed << setprecision(2) << res;

        ++tmpcnt;
        curStu = curStu->Next;
    }

    gotoxy(45, startRow + tmpcnt + 2);
    system("pause");
}

void listofClassMenu(Class* curClass, string curSchoolYearName) {
    const int startRow = 11;
    const int startCol = 48;
    const int numButton = 3;
    string listOfStudent = "List Of Students";
    string viewScoreboard = "View Scoreboard";
    string BackButton = "Back";

    while(1) {
        ShowCur(0);
        clrscr();
        changeTextColor(11);
        Button createClassButton = Button(19, 5, 80, 3, "Class");
        createClassButton.drawRectangleWithText();

        gotoxy(startCol, startRow);
        cout << listOfStudent;
        gotoxy(startCol, startRow + 1);
        cout << viewScoreboard;
        gotoxy(startCol, startRow + 2);
        cout << BackButton;

        int curCol = 1;
        bool isEnter = false;

        while(1)
        {
            gotoxy(startCol - 3, curCol + startRow - 1);
            cout << ">>";

            int c = getch();
            int prevCol = curCol;

            if(c == ENTER) {
                switch(curCol) {
                case 1:
                    IntoClass(curClass, curSchoolYearName);
                    isEnter = true;
                    break;

                case 2:
                    viewClassScoreboard(curClass);
                    isEnter = true;
                    break;

                case 3:
                    isEnter = true;
                    return;
                    break;
                }
            }
            else {
                if(c == KEY_UP) {
                    curCol--;
                    if(curCol < 1) curCol = numButton;
                }
                else {
                    if(c == KEY_DOWN) {
                        curCol++;
                        if(curCol > numButton) curCol = 1;
                    }
                }
            }

            if(isEnter) break;

            gotoxy(startCol - 3, prevCol + startRow - 1);
            cout << "  ";
        }
    }
}

void listOfClassFunction() {
    const int startRow = 10;
    const int startCol = 50;
    string BackButton = "Back";

    SchoolYear* curSchoolYear = loadSchoolYear();
    if(!curSchoolYear) {
        gotoxy(startCol, startRow + 2);
        cout << "Do not have school year data!!!";
        gotoxy(startCol, startRow + 4);
        system("pause");
        return;
    }

    Student* AllStudent = nullptr;
    LoadLastStudentData(AllStudent, "Savefile/Student/", "AllStudentInfo.txt");
    Course* AllCourse = nullptr;
    LoadLastCoursesData(AllCourse, "Savefile/Course/", "AllCourseInfo.txt", AllStudent);

    string schoolYearPath;
    ifstream fin;
    fin.open("Savefile/Path/SchoolYearPath.txt");
    getline(fin, schoolYearPath);
    fin.close();

    Class* AllClass = nullptr;
    LoadLastClassData(AllClass, schoolYearPath, AllStudent, AllCourse);

    Class* listClass = AllClass;

    fin.close();

    while(1) {
        ShowCur(0);
        clrscr();
        changeTextColor(11);
        Button createClassButton = Button(19, 5, 80, 3, "List of Classes");
        createClassButton.drawRectangleWithText();

        Class* cur = listClass;
        int cnt = 0;

        while(cur) {
            ++cnt;
            gotoxy(startCol, startRow + cnt - 1);
            cout << cur->ClassName;
            cur = cur->Next;
        }

//        cout << cnt << endl;
        gotoxy(startCol, startRow + cnt);
        cout << BackButton;

        const int numButton = cnt + 1;

        if(cnt == 0) {
            gotoxy(startCol, startRow);
            cout << "No class exists";
            cout << endl;
            system("pause");
            break;
        }

        int curCol = 1;
        bool isEnter = false;

        while(1) {
            gotoxy(startCol - 3, curCol + startRow - 1);
            cout << ">>";

            int c = getch();
            int prevCol = curCol;

            if(c == ENTER) {
                if(curCol == cnt + 1) {
                    return;
                }

                isEnter = true;
                Class* tmpClass = listClass;
                Class* curClass = listClass;
                int num = 0;
                while(tmpClass) {
                    ++num;
                    if(num == curCol) {
                        curClass = tmpClass;
                        break;
                    }
                    tmpClass = tmpClass->Next;
                }

                listofClassMenu(tmpClass, curSchoolYear->schoolYearName);
//                IntoClass(tmpClass, curSchoolYear->schoolYearName);

            }
            else {
                if(c == KEY_UP) {
                    curCol--;
                    if(curCol < 1) curCol = numButton;
                }
                else {
                    if(c == KEY_DOWN) {
                        curCol++;
                        if(curCol > numButton) curCol = 1;
                    }
                }
            }

            if(isEnter) break;

            gotoxy(startCol - 3, prevCol + startRow - 1);
            cout << "  ";
        }
    }
}

void createClassFunction() {
    const int startRow = 11;
    const int startCol = 48;
    const int numButton = 4;
    string createClass = "Create A New Class";
    string addStudentIntoClass = "Add Students Into Class";
    string fromCSV = "Add Students Into Class From CSV File";
    string BackButton = "Back";

    while(1) {
        ShowCur(0);
        clrscr();
        changeTextColor(11);
        Button createClassButton = Button(19, 5, 80, 3, "Create Classes");
        createClassButton.drawRectangleWithText();

        gotoxy(startCol, startRow);
        cout << createClass;
        gotoxy(startCol, startRow + 1);
        cout << addStudentIntoClass;
        gotoxy(startCol, startRow + 2);
        cout << fromCSV;
        gotoxy(startCol, startRow + 3);
        cout << BackButton;

        int curCol = 1;
        bool isEnter = false;

        while(1)
        {
            gotoxy(startCol - 3, curCol + startRow - 1);
            cout << ">>";

            int c = getch();
            int prevCol = curCol;

            if(c == ENTER) {
                switch(curCol) {
                case 1:
                    isEnter = true;
                    CreateAClass();
                    break;

                case 2:
                    isEnter = true;
                    addStudentIntoClassByStaff();
                    break;

                case 3:
                    loadStudentFromCSV();
                    isEnter = true;
                    break;

                case 4:
                    isEnter = true;
                    return;
                    break;
                }

            }
            else {
                if(c == KEY_UP) {
                    curCol--;
                    if(curCol < 1) curCol = numButton;
                }
                else {
                    if(c == KEY_DOWN) {
                        curCol++;
                        if(curCol > numButton) curCol = 1;
                    }
                }
            }

            if(isEnter) break;

            gotoxy(startCol - 3, prevCol + startRow - 1);
            cout << "  ";
        }
    }
}

void manageStudentFunction() {
    const int startRow = 11;
    const int startCol = 48;
    const int numButton = 5;
    string CreateSchoolYear = "Create A New School Year";
    string SchoolYearInformation = "School Year Information";
    string CreateClass = "Manage Classes";
    string ListOfClass = "List Of Classes";
    string BackButton = "Back";

    while(1) {
        ShowCur(0);
        clrscr();
        changeTextColor(11);
        Button manageStudentButton = Button(19, 5, 80, 3, "Manage Student");
        manageStudentButton.drawRectangleWithText();

        gotoxy(startCol, startRow);
        cout << CreateSchoolYear;
        gotoxy(startCol, startRow + 1);
        cout << SchoolYearInformation;
        gotoxy(startCol, startRow + 2);
        cout << CreateClass;
        gotoxy(startCol, startRow + 3);
        cout << ListOfClass;
        gotoxy(startCol, startRow + 4);
        cout << BackButton;

        int curCol = 1;
        bool isEnter = false;

        while(1)
        {
            gotoxy(startCol - 3, curCol + startRow - 1);
            cout << ">>";

            int c = getch();
            int prevCol = curCol;

            if(c == ENTER) {
                switch(curCol) {
                case 1:
                    isEnter = true;
                    createASchoolYearFunction();
                    break;

                case 2:
                    isEnter = true;
                    schoolYearInformationFuntion();
                    break;

                case 3:
                    isEnter = true;
                    createClassFunction();
                    break;

                case 4:
                    isEnter = true;
                    listOfClassFunction();
                    break;

                case 5:
                    isEnter = true;
                    return;
                }
            }
            else {
                if(c == KEY_UP) {
                    curCol--;
                    if(curCol < 1) curCol = numButton;
                }
                else {
                    if(c == KEY_DOWN) {
                        curCol++;
                        if(curCol > numButton) curCol = 1;
                    }
                }
            }

            if(isEnter) break;

            gotoxy(startCol - 3, prevCol + startRow - 1);
            cout << "  ";
        }
    }
}

void semesterInformationFunction() {
    Semester* curSemester = loadSemester();

    curSemester->ShowSemesterInfo();
}

void createACourseRegistrationFunction() {
    ShowCur(1);
    clrscr();
    changeTextColor(11);
    Button courseReg = Button(19, 5, 80, 3, "Course Registration");
    courseReg.drawRectangleWithText();

    const int startRow = 11;
    const int startCol = 48;

    gotoxy(startCol, startRow);
    cout << "Start date: (dd/mm/yyyy) ";
    string startDate; getline(cin, startDate);
    gotoxy(startCol, startRow + 1);
    cout << "End date: (dd/mm/yyyy) ";
    string endDate; getline(cin, endDate);

    gotoxy(startCol, startRow + 3);
    cout << "Create A Course Registration Successfully";

    SchoolYear* curSchoolYear = loadSchoolYear();
    Semester* cur = loadSemester();

    ofstream fout("Savefile/SchoolYear/" + curSchoolYear->schoolYearName + "/Semester/CourseRegistration.txt");
    fout << startDate << '\n' << endDate << '\n';
    fout.close();

    gotoxy(startCol, startRow + 5);
    system("pause");
}

void showRegistrationInfoFunction() {
    ifstream fin;
    SchoolYear* curSchoolYear = loadSchoolYear();
    fin.open("Savefile/SchoolYear/" + curSchoolYear->schoolYearName + "/Semester/CourseRegistration.txt");
    string startDate; getline(fin, startDate);
    string endDate; getline(fin, endDate);

    ShowCur(1);
    clrscr();
    changeTextColor(11);
    Button courseReg = Button(19, 5, 80, 3, "Course Registration Information");
    courseReg.drawRectangleWithText();

    const int startCol = 40, startRow = 10;
    gotoxy(startCol, startRow);
    cout << "Start date: " << startDate;
    gotoxy(startCol, startRow + 1);
    cout << "End date: " << endDate;
    gotoxy(startCol, startRow + 3);
    system("pause");
}

void addCourseFunction() {
    const int startRow = 11;
    const int startCol = 48;
    const int numButton = 3;
    string addCourseButton = "Add Courses";
    string addCourseCVS = "Add Courses From CSV File";
    string BackButton = "Back";

    while(1) {
        ShowCur(0);
        clrscr();
        changeTextColor(11);
        Button createClassButton = Button(19, 5, 80, 3, "Add Courses");
        createClassButton.drawRectangleWithText();

        gotoxy(startCol, startRow);
        cout << addCourseButton;
        gotoxy(startCol, startRow + 1);
        cout << addCourseCVS;
        gotoxy(startCol, startRow + 2);
        cout << BackButton;

        int curCol = 1;
        bool isEnter = false;

        while(1)
        {
            gotoxy(startCol - 3, curCol + startRow - 1);
            cout << ">>";

            int c = getch();
            int prevCol = curCol;

            if(c == ENTER) {
                switch(curCol) {
                case 1:
                    staffAddCourse();
                    isEnter = true;
                    break;

                case 2:
                    isEnter = true;
                    break;

                case 3:
                    isEnter = true;
                    return;
                    break;
                }
            }
            else {
                if(c == KEY_UP) {
                    curCol--;
                    if(curCol < 1) curCol = numButton;
                }
                else {
                    if(c == KEY_DOWN) {
                        curCol++;
                        if(curCol > numButton) curCol = 1;
                    }
                }
            }

            if(isEnter) break;

            gotoxy(startCol - 3, prevCol + startRow - 1);
            cout << "  ";
        }
    }
}

void listOfCourseFunction() {
    while(1) {
        clrscr();
        changeTextColor(11);
        Button profileButton = Button(19, 4, 80, 3, "List Of All Courses");
        profileButton.drawRectangleWithText();

        changeTextColor(11);

        gotoxy(10, 9);
        cout << "ID";
        gotoxy(15, 9);
        cout << "Course ID";
        gotoxy(30, 9);
        cout << "Course Name";
        gotoxy(69, 9);
        cout << "Number Of";
        gotoxy(69, 10);
        cout << "Credits";
        gotoxy(81, 9);
        cout << "Course Time";
        gotoxy(96, 9);
        cout << "Lecture Name";

        string schoolYearPath = "";
        ifstream fin;
        fin.open("Savefile/Path/SchoolYearPath.txt");
        getline(fin, schoolYearPath);
        fin.close();

        Student* AllStudent = nullptr;
        LoadLastStudentData(AllStudent, "Savefile/Student/", "AllStudentInfo.txt");
        Course* AllCourse = nullptr;
        LoadLastCoursesData(AllCourse, schoolYearPath, "AllCourseInfo.txt", AllStudent);
        Class* AllClass = nullptr;
        LoadLastClassData(AllClass, schoolYearPath, AllStudent, AllCourse);

        Course* cur = AllCourse;
        int cnt = 0, curCol = 1;
        while(cur) {
            cnt++, cur = cur->Next;
        }

        const int startX = 10, startY = 12;
        const int numButton = cnt + 1;
        cnt = 0, cur = AllCourse;

        while(cur) {
            ++cnt;

            gotoxy(startX, startY + (cnt - 1) * 5);
            cout << cnt;

            gotoxy(startX + 5, startY + (cnt - 1) * 5);
            cout << cur->Info->CourseID;

            gotoxy(startX + 20, startY + (cnt - 1) * 5);
            cout << cur->Info->CourseName;

            gotoxy(startX + 63, startY + (cnt - 1) * 5);
            cout << cur->Info->NumOfCredits;

            Session S1 = cur->Info->FirstS;
            Session S2 = cur->Info->SecondS;
            gotoxy(startX + 71, startY + (cnt - 1) * 5);
            cout << "S1" << ": " << S1.Day << ' ' << S1.Hour << ": " << S1.Mins;
            gotoxy(startX + 71, startY + 1 + (cnt - 1) * 5);
            cout << "S2" << ": " << S2.Day << ' ' << S2.Hour << ": " << S2.Mins;

            gotoxy(startX + 86, startY + (cnt - 1) * 5);
            cout << cur->Info->LecturerName;

            cur = cur->Next;
        }

        bool isEnter = false;
        gotoxy(startX, startY + cnt * 5);
        cout << "Back";

        while(1)
        {
            gotoxy(startX - 5, startY + (curCol - 1) * 5);
            cout << ">>";

            int c = getch();
            int prevCol = curCol;

            if(c == ENTER) {
                isEnter = true;

                if(curCol == cnt + 1) {
                    return;
                }

                isEnter = true;
                Course* curCourse = AllCourse;
                int tmpcnt = 0;
                while(curCourse) {
                    ++tmpcnt;
                    if(tmpcnt == curCol) {
                        solveWithACourse(curCourse);
                        isEnter = true;
                        break;
                    }
                    curCourse = curCourse->Next;
                }
            }
            else {
                if(c == KEY_UP) {
                    curCol--;
                    if(curCol < 1) curCol = numButton;
                }
                else {
                    if(c == KEY_DOWN) {
                        curCol++;
                        if(curCol > numButton) curCol = 1;
                    }
                }
            }

            if(isEnter) break;

            gotoxy(startX - 5, startY + (prevCol - 1) * 5);
            cout << "  ";
        }
    }
}

void manageCourseFunction() {
    const int startRow = 11;
    const int startCol = 48;
    const int numButton = 7;
    string createSemester = "Create A New Semester";
    string semesterInformation = "Semester Information";
    string createACourseRegistration = "Create Registration Session";
    string courseRegInfo = "Course Registration Infomation";
    string AddCourse = "Add Courses";
    string ListOfClass = "List Of Courses";
    string BackButton = "Back";

    while(1) {
        ShowCur(0);
        clrscr();
        changeTextColor(11);
        Button manageStudentButton = Button(19, 5, 80, 3, "Manage Courses");
        manageStudentButton.drawRectangleWithText();

        gotoxy(startCol, startRow);
        cout << createSemester;
        gotoxy(startCol, startRow + 1);
        cout << semesterInformation;
        gotoxy(startCol, startRow + 2);
        cout << createACourseRegistration;
        gotoxy(startCol, startRow + 3);
        cout << courseRegInfo;
        gotoxy(startCol, startRow + 4);
        cout << AddCourse;
        gotoxy(startCol, startRow + 5);
        cout << ListOfClass;
        gotoxy(startCol, startRow + 6);
        cout << BackButton;

        int curCol = 1;
        bool isEnter = false;

        while(1)
        {
            gotoxy(startCol - 3, curCol + startRow - 1);
            cout << ">>";

            int c = getch();
            int prevCol = curCol;

            if(c == ENTER) {
                switch(curCol) {
                case 1:
                    createANewSemester();
                    isEnter = true;
                    break;

                case 2:
                    semesterInformationFunction();
                    isEnter = true;
                    break;

                case 3:
                    createACourseRegistrationFunction();
                    isEnter = true;
                    break;

                case 4:
                    showRegistrationInfoFunction();
                    isEnter = true;
                    break;

                case 5:
                    addCourseFunction();
                    isEnter = true;
                    break;

                case 6:
                    listOfCourseFunction();
                    isEnter = true;
                    break;

                case 7:
                    isEnter = true;
                    return;
                }
            }
            else {
                if(c == KEY_UP) {
                    curCol--;
                    if(curCol < 1) curCol = numButton;
                }
                else {
                    if(c == KEY_DOWN) {
                        curCol++;
                        if(curCol > numButton) curCol = 1;
                    }
                }
            }

            if(isEnter) break;

            gotoxy(startCol - 3, prevCol + startRow - 1);
            cout << "  ";
        }
    }
}

void changeStaffPasswordFunction(Login &loginSystem) {
    loginSystem.changePassword(AllStaffUserPath + AllStaffUserFilename);
}

void logOutStaffFunction(Login &loginSystem) {
    loginSystem.logout();
}

void staffSystemProcess() {
//    manageCourseFunction();
//    exit(0);
    changeTextColor(8);

    Login loginSystem;

    while(1) {
        clrscr();

        COORD mousePos;

        Staff* AllStaff = nullptr;
        LoadAllStaffData(AllStaff, AllStaffInfoPath, AllStaffInfoFilename);

        // Login
        changeTextColor(12);
        loginSystem.login(AllStaffUserPath + AllStaffUserFilename);

        changeTextColor(11);
        ShowCur(0);
        loadingFunction(45, 20);

        clrscr();

        Sleep(1000);

        // Find User
        int Count = 0;
        Staff* curStaff = AllStaff;

        while(curStaff) {
            if(curStaff->Info->ID == loginSystem.userAccount.username) {
                break;
            }

            curStaff = curStaff->Next;
        }

        // Menu
        ShowCur(0);

        Button* profileButton = new Button(9, 5, 28, 7, "My Profile");
        Button* manageStudent = new Button(46, 5, 28, 7, "Manage Student");
        Button* manageCourseButton = new Button(83, 5, 28, 7, "Manage Courses");
        Button* changePasswordButton = new Button(9, 5 + 9, 28, 7, "Change Password");
        Button* logOutButton = new Button(46, 5 + 9, 28, 7, "Log Out");

        Button* buttonHead = nullptr;
        addButtonEnd(buttonHead, profileButton);
        addButtonEnd(buttonHead, manageStudent);
        addButtonEnd(buttonHead, manageCourseButton);
        addButtonEnd(buttonHead, changePasswordButton);
        addButtonEnd(buttonHead, logOutButton);

        while(1) {
            clrscr();

            // draw User's Name
            changeTextColor(4);
            string staffName = "Welcome " + curStaff->Info->FirstName + ' ' + curStaff->Info->LastName;
            printAtXY(120 - staffName.size() - 1, 0, staffName);

            // draw all Button
            changeTextColor(11);
            Button* curButton = buttonHead;

            while(curButton) {
                curButton->drawRectangleWithText();
                curButton = curButton->Next;
            }

            while(1) {
                if(getMousePosition(mousePos)) {
                    curButton = buttonHead;
                    bool isClickInButton = false;

                    while(curButton) {
                        if(curButton->isInButton(mousePos.X, mousePos.Y)) isClickInButton = true;
                        curButton = curButton->Next;
                    }

                    if(isClickInButton) break;
                }
            }

            clrscr();

            gotoxy(0, 5);

            curButton = buttonHead;
            int cnt = 0;
            bool isLogOut = false;

            while(curButton) {
                ++cnt;

                if(curButton->isInButton(mousePos.X, mousePos.Y)) {
                    if(cnt == 1) {
                        myProfileFunction(curStaff);
                        break;
                    }

                    if(cnt == 2) {
                        manageStudentFunction();
                        break;
                    }

                    if(cnt == 3) {
                        manageCourseFunction();
                        break;
                    }

                    if(cnt == 4) {
                        changeStaffPasswordFunction(loginSystem);
                        break;
                    }

                    if(cnt == 5) {
                        isLogOut = true;
                        logOutStaffFunction(loginSystem);
                        break;
                    }
                }

                curButton = curButton->Next;
            }

            if(isLogOut) {
                SystemProcess();
                return;
                gotoxy(46, 0);
                break;
            }

            Button backButton = Button(0, 0, 8, 3, "BACK");
            changeTextColor(4);
            backButton.drawRectangleWithText();

            while(1) {
                if(getMousePosition(mousePos) && backButton.isInButton(mousePos.X, mousePos.Y))
                    break;
            }
        }
    }
}
