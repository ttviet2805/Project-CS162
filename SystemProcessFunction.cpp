#include "SystemProcessHeader.h"

const int middleScreenX = 60;
const int middleScreenY = 15;

string AllStudentInfoPath = "Savefile/Student/";
string AllStudentInfoFilename = "AllStudentInfo.txt";
string AllCourseInfoPath = "Savefile/Course/";
string AllCourseInfoFilename = "AllCourseInfo.txt";
string AllStudentUserPath = "Savefile/User/";
string AllStudentUserFilename = "StudentUser.txt";

void SystemProcess() {
    Login loginSystem;

    while(1) {
        Student *AllStudent = nullptr;
        Course *AllCourse = nullptr;

        LoadLastStudentData(AllStudent, AllStudentInfoPath, AllStudentInfoFilename);
        LoadLastCoursesData(AllCourse, AllCourseInfoPath, AllCourseInfoFilename, AllStudent);

        loginSystem.login(AllStudentUserPath + AllStudentUserFilename);

        clrscr();

        Student* curStudentUser = AllStudent->FindStudentByID(loginSystem.userAccount.username);

        curStudentUser->ShowStudentInfo();
    }
}
