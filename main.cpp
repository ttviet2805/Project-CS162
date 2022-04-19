#include <iostream>
#include <fstream>

using namespace std;

#include "StudentAndCourseHeader.h"
#include "SystemProcessHeader.h"

//Student *AllStudent;
//Course *AllCourse;

//void Test()
//{
//    string AllStudentInfoPath = "Savefile/Student/";
//    string AllStudentInfoFilename = "AllStudentInfo.txt";
//    string AllCourseInfoPath = "Savefile/Course/";
//    string AllCourseInfoFilename = "AllCourseInfo.txt";
//
//
//    LoadLastStudentData(AllStudent, AllStudentInfoPath, AllStudentInfoFilename);
//    LoadLastCoursesData(AllCourse, AllCourseInfoPath, AllCourseInfoFilename, AllStudent);
//
//    AllStudent->ShowStudentInfo();
//
//    Student *User = AllStudent->FindStudentByID("21125007");
//
//    User->EnrollACourse(AllCourse);
//    User->ViewAListOfEnrollCourse();
//
//    AllStudent->SaveStudentsData(AllStudentInfoPath, AllStudentInfoFilename);
//    AllCourse->SaveCoursesData(AllCourseInfoPath, AllCourseInfoFilename);
//
//    DeleteAllCourse(AllCourse);
//    DeleteAllStudent(AllStudent);
//}

int main()
{
//    Test();
    SystemProcess();

    return 0;
}
