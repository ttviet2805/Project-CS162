#include "StaffSystemHeader.h"

const string AllStaffUserPath = "Savefile/User/";
const string AllStaffUserFilename = "StaffUser.txt";
const string AllStaffInfoPath = "Savefile/Staff/";
const string AllStaffInfoFilename = "AllStaffInfo.txt";

void manageStudentFunction() {
    changeTextColor(11);
    Button manageStudentButton = Button(19, 5, 80, 3, "Manage Student");
    manageStudentButton.drawRectangleWithText();
}

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

void staffSystemProcess() {
    createANewSchoolYear();

    exit(0);
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
                loginSystem.numID = Count;
                break;
            }

            curStaff = curStaff->Next;
        }

        // Menu
        ShowCur(0);

        Button* profileButton = new Button(9, 5, 28, 7, "My Profile");
        Button* manageStudent = new Button(46, 5, 28, 7, "Manage Student");
//        Button* courseResultButton = new Button(83, 5, 28, 7, "Course Result");
//        Button* viewScoreButton = new Button(9, 5 + 9, 28, 7, "View Score");
//        Button* changePasswordButton = new Button(46, 5 + 9, 28, 7, "Change Password");
//        Button* logOutButton = new Button(83, 5 + 9, 28, 7, "Log Out");

        Button* buttonHead = nullptr;
        addButtonEnd(buttonHead, profileButton);
        addButtonEnd(buttonHead, manageStudent);
//        addButtonEnd(buttonHead, courseResultButton);
//        addButtonEnd(buttonHead, viewScoreButton);
//        addButtonEnd(buttonHead, changePasswordButton);
//        addButtonEnd(buttonHead, logOutButton);


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
                }

                curButton = curButton->Next;
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
