#include "SystemProcessHeader.h"

const string StudentFile = "TxtFolder/StudentData.txt";
const string CourseFile = "TxtFolder/CourseData.txt";
char LoginFile[] = "TxtFolder/LoginData.txt";

void systemProcess() {
    Login LoginSystem;

    while(1) {
        LoginSystem.login(LoginFile);

        clrscr();

        int studentIndex = LoginSystem.stt;

        Student* studentHead = nullptr;
        LoadLastStudentData(studentHead, StudentFile);

        int cnt = 0;
        Student* studentCur = studentHead;

        while(studentCur) {
            ++cnt;

            if(cnt == studentIndex) break;
            studentCur = studentCur->Next;
        }

        string studentFirstName = studentCur->Info->FirstName;
        string studentLastName = studentCur->Info->LastName;

        gotoxy(119 - studentFirstName.size() - studentLastName.size() - 1, 0);
        cout << studentFirstName << ' ' << studentLastName;

        string menuStr = "MENU";
        gotoxy(midScreen - menuStr.size() / 2 + 1, 1);
        cout << menuStr;

        drawRectangleWithText(9, 5, 28, 7, "My Profile");
        drawRectangleWithText(46, 5, 28, 7, "Enroll Course");
        drawRectangleWithText(83, 5, 28, 7, "Course Result");
        drawRectangleWithText(9, 5 + 9, 28, 7, "Change Password");
        drawRectangleWithText(46, 5 + 9, 28, 7, "Log Out");
//        drawRectangleWithText(0, 0, 8, 3, "BACK");

        while(1) {
            // Mouse click in Student Profile
            if(checkMouseInButton(9, 5, 28, 7)) {
                clrscr();
                studentCur->ShowStudentInfo();
                Sleep(10000);
                clrscr();
                break;
            }

            // Mouse click in Log Out
            if(checkMouseInButton(46, 5 + 3, 28, 7)) {
                clrscr();
                LoginSystem.logout(LoginFile);
                clrscr();
                Sleep(2000);
                break;
            }

            // Mouse click in Change Password;
            if(checkMouseInButton(9, 5 + 9, 28, 7)) {
                clrscr();
                LoginSystem.changePassword(LoginFile);
                break;
            }
        }
    }

}
