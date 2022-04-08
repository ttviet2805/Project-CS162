#include "StudentSystemHeader.h"

const int middleScreenX = 60;
const int middleScreenY = 15;

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define ENTER 13

string AllStudentInfoPath = "Savefile/Student/";
string AllStudentInfoFilename = "AllStudentInfo.txt";
string AllCourseInfoPath = "Savefile/Course/";
string AllCourseInfoFilename = "AllCourseInfo.txt";
string AllStudentUserPath = "Savefile/User/";
string AllStudentUserFilename = "StudentUser.txt";

void myProfileFunction(Student* curStudent) {
    string studentID = "Student ID";
    string firstName = "First Name";
    string lastName = "Last Name";
    string gender = "Gender";
    string Dob = "Date of Birth";
    string socialID = "Social ID";
    string Class = "Class";
    const int rectSize = 31;

    changeTextColor(11);
    Button profileButton = Button(19, 5, 80, 3, "MY PROFILE");
    profileButton.drawRectangleWithText();

    Button profileBackground = Button(19, 9, 80, 15, "");
    profileBackground.color = 11;
    profileBackground.fillRectangle();

    string studentIDString = curStudent->Info->ID;
    while(studentIDString.size() < rectSize) studentIDString += ' ';
    printATXYWithBackGround(25, 10, 11, 0, studentID);
    printATXYWithBackGround(25, 11, 15, 0, studentIDString);

    string firstNameString = curStudent->Info->FirstName;
    while(firstNameString.size() < rectSize) firstNameString += ' ';
    printATXYWithBackGround(25, 13, 11, 0, firstName);
    printATXYWithBackGround(25, 14, 15, 0, firstNameString);

    string lastNameString = curStudent->Info->LastName;
    while(lastNameString.size() < rectSize) lastNameString += ' ';
    printATXYWithBackGround(25, 16, 11, 0, lastName);
    printATXYWithBackGround(25, 17, 15, 0, lastNameString);

    string genderString = curStudent->Info->Gender;
    while(genderString.size() < rectSize) genderString += ' ';
    printATXYWithBackGround(25, 19, 11, 0, gender);
    printATXYWithBackGround(25, 20, 15, 0, genderString);

    Date dateOfBirth = curStudent->Info->Dob;
    string dobString = to_string(dateOfBirth.Day) + '/' + to_string(dateOfBirth.Month) + '/' + to_string(dateOfBirth.Year);
    while(dobString.size() < rectSize) dobString += ' ';
    printATXYWithBackGround(62, 10, 11, 0, Dob);
    printATXYWithBackGround(62, 11, 15, 0, dobString);

    string SocialIDString = curStudent->Info->SocialID;
    while(SocialIDString.size() < rectSize) SocialIDString += ' ';
    printATXYWithBackGround(62, 13, 11, 0, socialID);
    printATXYWithBackGround(62, 14, 15, 0, SocialIDString);
//
    string classString = curStudent->Info->StudentClass;
    while(classString.size() < rectSize) classString += ' ';
    printATXYWithBackGround(62, 16, 11, 0, Class);
    printATXYWithBackGround(62, 17, 15, 0, classString);
}

void enrollCourseFunction(Student* &curStudent, Course* AllCourse) {
    clrscr();
    changeTextColor(11);
    Button enrollCourseButton = Button(19, 5, 80, 3, "Enroll Courses");
    enrollCourseButton.drawRectangleWithText();

    changeTextColor(4);
    string warningString = "You are allow to enroll at most 5 courses";
    gotoxy(middleScreenX - warningString.size() / 2, 9);
    cout << warningString;

    changeTextColor(11);

    const int typeRow = 12;
    const int startX = 5, startY = 14;

    gotoxy(startX, typeRow);
    cout << "ID";
    gotoxy(startX + 5, typeRow);
    cout << "Course ID";
    gotoxy(startX + 20, typeRow);
    cout << "Course Name";
    gotoxy(startX + 59, typeRow);
    cout << "Number Of";
    gotoxy(startX + 59, typeRow + 1);
    cout << "Credits";
    gotoxy(startX + 71, typeRow);
    cout << "Course Time";
    gotoxy(startX + 86, typeRow);
    cout << "Lecture Name";
    gotoxy(startX + 103, typeRow);
    cout << "Option";


    int cnt = 0;
    Course* cur = AllCourse;

    COORD curPos = {0, 0};

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

    int numCourseEnrolled = 0;

    string optionState = " ";
    for(int i = 1; i <= cnt + 5; i++)
        optionState += '0';

    for(int i = 1; i <= cnt; i++) {
        Course* tmpHead = AllCourse;
        int tmpCnt = 1;

        while(tmpCnt < i) {
            tmpHead = tmpHead->Next;
            ++tmpCnt;
        }

        if(curStudent->FindACourseAlreadyRegisted(tmpHead->Info)) {
            optionState[i] = '1';
            numCourseEnrolled++;

            changeTextColor(4);
            gotoxy(startX + 103, startY + (i - 1) * 5);
            cout << char(254);
        }
    }

    ShowCur(1);
    int num = 1;
    cur = AllCourse;
    gotoxy(startX + 103, startY);
    curPos = {startX + 103, startY};
    changeTextColor(4);

    string Text = "Enter Save to save: ";
    gotoxy(middleScreenX - Text.size() / 2, startY + (cnt) * 5);
    cout << Text;

    while(1) {
        gotoxy(curPos.X, curPos.Y);

        if(num == cnt + 1) {
            gotoxy(middleScreenX - Text.size() / 2 + Text.size(), startY + (cnt) * 5);
            string Option;
            getline(cin, Option);

            if(Option == "Save") {
                if(numCourseEnrolled > 5) {
                    gotoxy(middleScreenX - Text.size() / 2, startY + (cnt) * 5 + 2);
                    cout << "You have enroll exceed the maximum number of registed courses!";
                    Sleep(2000);
                    enrollCourseFunction(curStudent, AllCourse);
                    return;
                }

                bool isDuplicated = false;

                Course* tmpCourse1 = AllCourse;
                int numOverlap = 0;

                for(int i = 1; i <= cnt; i++) {
                    Course* tmpCourse2 = tmpCourse1->Next;

                    for(int j = i + 1; j <= cnt; j++) {
                        if(optionState[i] != '1' || optionState[j] != '1') {
                            tmpCourse2 = tmpCourse2->Next;
                            continue;
                        }
                        Session courseSes1 = tmpCourse1->Info->FirstS;
                        Session courseSes2 = tmpCourse1->Info->SecondS;
                        string DayCourse1S1 = courseSes1.Day;
                        string DayCourse1S2 = courseSes2.Day;
                        string SesCourse1S1 = courseSes1.Ses;
                        string SesCourse1S2 = courseSes2.Ses;

                        courseSes1 = tmpCourse2->Info->FirstS;
                        courseSes2 = tmpCourse2->Info->SecondS;
                        string DayCourse2S1 = courseSes1.Day;
                        string DayCourse2S2 = courseSes2.Day;
                        string SesCourse2S1 = courseSes1.Ses;
                        string SesCourse2S2 = courseSes2.Ses;

                        if((DayCourse1S1 == DayCourse2S1 && SesCourse1S1 == SesCourse2S1)) {
                            numOverlap++;
                            isDuplicated = true;
                            string warningOverlap = tmpCourse1->Info->CourseName + " and " + tmpCourse2->Info->CourseName + " are overlap";
                            gotoxy(middleScreenX - warningOverlap.size() / 2, startY + (cnt) * 5 + 2 + numOverlap);
                            cout << warningOverlap;
                            tmpCourse2 = tmpCourse2->Next;
                            continue;
                        }

                        if(DayCourse1S1 == DayCourse2S2 && SesCourse1S1 == SesCourse2S2) {
                            numOverlap++;
                            isDuplicated = true;
                            string warningOverlap = tmpCourse1->Info->CourseName + " and " + tmpCourse2->Info->CourseName + " are overlap";
                            gotoxy(middleScreenX - warningOverlap.size() / 2, startY + (cnt) * 5 + 2 + numOverlap);
                            cout << warningOverlap;
                            tmpCourse2 = tmpCourse2->Next;
                            continue;
                        }

                        if(DayCourse1S2 == DayCourse2S1 && SesCourse1S2 == SesCourse2S1) {
                            numOverlap++;
                            isDuplicated = true;
                            string warningOverlap = tmpCourse1->Info->CourseName + " and " + tmpCourse2->Info->CourseName + " are overlap";
                            gotoxy(middleScreenX - warningOverlap.size() / 2, startY + (cnt) * 5 + 2 + numOverlap);
                            cout << warningOverlap;
                            tmpCourse2 = tmpCourse2->Next;
                            continue;
                        }

                        if(DayCourse1S2 == DayCourse2S2 && SesCourse1S2 == DayCourse2S2) {
                            numOverlap++;
                            isDuplicated = true;
                            string warningOverlap = tmpCourse1->Info->CourseName + " and " + tmpCourse2->Info->CourseName + " are overlap";
                            gotoxy(middleScreenX - warningOverlap.size() / 2, startY + (cnt) * 5 + 2 + numOverlap);
                            cout << warningOverlap;
                            tmpCourse2 = tmpCourse2->Next;
                            continue;
                        }

                        tmpCourse2 = tmpCourse2->Next;
                    }

                    tmpCourse1 = tmpCourse1->Next;
                }

                if(isDuplicated) {
                    string overlapWarning = "That is the list courses which are overlap together, please check and try again";
                    gotoxy(middleScreenX - overlapWarning.size() / 2, startY + (cnt) * 5 + 2 + numOverlap +  2);
                    cout << overlapWarning << '\n';
                    gotoxy(middleScreenX - Text.size() / 2, startY + (cnt) * 5 + numOverlap + 6);
                    system("pause");
                    Sleep(2000);
                    enrollCourseFunction(curStudent, AllCourse);
                    return;
                }

                gotoxy(middleScreenX - Text.size() / 2, startY + (cnt) * 5 + 2);
                cout << "You have save the data successfully";
                break;
            }
            else {
                gotoxy(middleScreenX - Text.size() / 2, startY + (cnt) * 5 + 2);
                cout << "You do not save your data, please check your typing!";
                Sleep(2000);
                enrollCourseFunction(curStudent, AllCourse);
                return;
            }
        }

        int curChar = getch();

        if(curChar == ENTER) {
            if(optionState[num] == '0') {
                if(numCourseEnrolled < 5) {
                    numCourseEnrolled++;
                    optionState[num] = '1';
                }
            }
            else {
                optionState[num] = '0';
                numCourseEnrolled--;
            }

            if(optionState[num] == '1') cout << char(254);
            else cout << " ";
            gotoxy(curPos.X, curPos.Y);
        }
        else {
            if(curChar == KEY_UP) {
                if(num > 1) {
                    num--;
                    curPos.Y = startY + (num - 1) * 5;
                    Sleep(100);
                }
            }
            else {
                if(curChar == KEY_DOWN) {
                    if(num <= cnt) {
                        num++;
                        curPos.Y = startY + (num - 1) * 5;
                        Sleep(100);
                    }
                }
            }
        }
    }

    Sleep(2000);
    ShowCur(0);

    Course* curCourse = AllCourse;
    for(int i = 1; i <= cnt; i++) {
        if(optionState[i] == '0') {
            curCourse->deleteStudent(curStudent->Info);
            curStudent->deleteCurrentCourse(curCourse->Info);
        }

        if(optionState[i] == '1') {
            CourseScoreBoard* tmpCourseBoard = curCourse->Scoreboard;

            while(tmpCourseBoard && tmpCourseBoard->Student != curStudent->Info) {
                tmpCourseBoard = tmpCourseBoard->Next;
            }

            if(tmpCourseBoard);
            else {
                StudentScoreBoard *New = new StudentScoreBoard;
                New->Info = curCourse->Info;
                New->Score = new CourseScore;
                curCourse->AddANewStudent(curStudent->Info, New->Score);
                curStudent->AddAStudentScoreBoard(New->Info, New->Score);
            }
        }

        curCourse = curCourse->Next;
    }

    AllCourse->SaveCoursesData(AllCourseInfoPath, AllCourseInfoFilename);
}

void viewAListOfEnrolledCourseFunction(Student* curStudent) {
    changeTextColor(11);
    Button profileButton = Button(19, 4, 80, 3, "View A List Of Enrolled Courses");
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

    const int startX = 10, startY = 12;

    int cnt = 0;
    StudentScoreBoard* cur = curStudent->ScoreBoard;

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
}

void changePasswordFunction(Login &loginSystem) {
    loginSystem.changePassword(AllStudentUserPath + AllStudentUserFilename);
}

void logOutFunction(Login &loginSystem) {
    loginSystem.logout();
}

void studentSystemProcess() {
    changeTextColor(8);

    Login loginSystem;

    while(1) {
        clrscr();

        COORD mousePos;
        Student *AllStudent = nullptr;
        Course *AllCourse = nullptr;

        LoadLastStudentData(AllStudent, AllStudentInfoPath, AllStudentInfoFilename);
        LoadLastCoursesData(AllCourse, AllCourseInfoPath, AllCourseInfoFilename, AllStudent);

        // Login
        changeTextColor(12);
        loginSystem.login(AllStudentUserPath + AllStudentUserFilename);

        changeTextColor(11);
        ShowCur(0);
        loadingFunction(45, 20);

        clrscr();

        Sleep(1000);

        // Find User
        int Count = 0;
        Student* curStudent = AllStudent->FindStudentByID(loginSystem.userAccount.username);
        Student* tmpStudent = AllStudent;
        while(tmpStudent) {
            ++Count;

            if(tmpStudent->Info->ID == curStudent->Info->ID) {
                loginSystem.numID = Count;
                break;
            }
            tmpStudent = tmpStudent->Next;
        }

        // Menu
        ShowCur(0);

        Button* profileButton = new Button(9, 5, 28, 7, "My Profile");
        Button* enrollCourseButton = new Button(46, 5, 28, 7, "Enroll Course");
        Button* courseResultButton = new Button(83, 5, 28, 7, "Course Result");
        Button* viewScoreButton = new Button(9, 5 + 9, 28, 7, "View Score");
        Button* changePasswordButton = new Button(46, 5 + 9, 28, 7, "Change Password");
        Button* logOutButton = new Button(83, 5 + 9, 28, 7, "Log Out");

        Button* buttonHead = nullptr;
        addButtonEnd(buttonHead, profileButton);
        addButtonEnd(buttonHead, enrollCourseButton);
        addButtonEnd(buttonHead, courseResultButton);
        addButtonEnd(buttonHead, viewScoreButton);
        addButtonEnd(buttonHead, changePasswordButton);
        addButtonEnd(buttonHead, logOutButton);


        while(1) {
            clrscr();

            // draw User's Name
            changeTextColor(4);
            string studentName = "Welcome " + curStudent->Info->FirstName + ' ' + curStudent->Info->LastName;
            printAtXY(120 - studentName.size() - 1, 0, studentName);

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
                        myProfileFunction(curStudent);
                        break;
                    }

                    if(cnt == 2) {
                        enrollCourseFunction(curStudent, AllCourse);
                        break;
                    }

                    if(cnt == 3) {
                        viewAListOfEnrolledCourseFunction(curStudent);
                        break;
                    }

                    if(cnt == 4) {

                        break;
                    }

                    if(cnt == 5) {
                        changePasswordFunction(loginSystem);
                        break;
                    }

                    if(cnt == 6) {
                        logOutFunction(loginSystem);
                        isLogOut = true;
                        break;
                    }
                }

                curButton = curButton->Next;
            }

            if(isLogOut) {
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
