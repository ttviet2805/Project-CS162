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
    curStudent->EnrollACourse(AllCourse);
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
        cout << 0;

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

            if(isLogOut) break;

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

void SystemProcess() {
    studentSystemProcess();
}
