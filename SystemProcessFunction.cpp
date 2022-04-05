#include "SystemProcessHeader.h"

const int middleScreenX = 60;
const int middleScreenY = 15;

string AllStudentInfoPath = "Savefile/Student/";
string AllStudentInfoFilename = "AllStudentInfo.txt";
string AllCourseInfoPath = "Savefile/Course/";
string AllCourseInfoFilename = "AllCourseInfo.txt";
string AllStudentUserPath = "Savefile/User/";
string AllStudentUserFilename = "StudentUser.txt";

void myProfileFunction(Student* curStudent) {
    curStudent->ShowStudentInfo();
}

void enrollCourseFunction(Student* &curStudent, Course* AllCourse) {
    curStudent->EnrollACourse(AllCourse);
}

void viewAListOfEnrolledCourseFunction(Student* curStudent) {
    curStudent->ViewAListOfEnrollCourse();
}

void changePasswordFunction(Login &loginSystem) {
    loginSystem.changePassword(AllStudentUserPath + AllStudentUserFilename);
}

void logOutFunction(Login &loginSystem) {
    loginSystem.logout();
}

void SystemProcess() {
    Login loginSystem;

    while(1) {
        clrscr();
        COORD mousePos;
        ShowCur(1);
        Student *AllStudent = nullptr;
        Course *AllCourse = nullptr;

        LoadLastStudentData(AllStudent, AllStudentInfoPath, AllStudentInfoFilename);
        LoadLastCoursesData(AllCourse, AllCourseInfoPath, AllCourseInfoFilename, AllStudent);

        // Login
        changeTextColor(12);
        loginSystem.login(AllStudentUserPath + AllStudentUserFilename);

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
            changeTextColor(9);
            Button* curButton = buttonHead;

            while(curButton) {
                curButton->drawRectangleWithText();
                curButton = curButton->Next;
            }

            while(!getMousePosition(mousePos));
            clrscr();

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

            if(isLogOut) break;

            gotoxy(55, 30);
            cout << "Press 0 to Back: ";
            int n;
            while(cin >> n) {
                if(n == 0) break;
            }
        }
    }
}
