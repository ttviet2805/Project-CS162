#ifndef COURSEHEADER_H_INCLUDED
#define COURSEHEADER_H_INCLUDED

#include <iostream>
#include "DateHeader.h"
#include "StudentHeader.h"

using namespace std;

class Session {
    public:
        string Day;
        string Ses;
        int Hour, Mins;

        void Init();
        void Cout();
        void Cin();
};

class CourseInfo
{
    public:
        string CourseName, CourseID, LecturerName;
        Date StartDate, EndDate;
        Session FirstS, SecondS;

        //(S1 (07:30), S2 (09:30), S3(13:30) and S4 (15:30))
        // 2 sessions in a week
        // (nhiều nhất 5 course, không thể enroll course trùng lịch với các courses đã đăng kí)
        //ScoreBoard Scoreboard;
        //Mỗi môn có tỉ lệ % điểm thành phần khác nhau
};

/*class CourseScoreBoard
{
    StudentInfo *Student;

}*/

class Course {
	public:
        CourseInfo *Info;
        //CourseScoreBoard Scoreboard;
        Course *Next = nullptr;

        void ShowCourseInfo();
        void ShowCourseInfoWithNumber();
        void AllCoursesInfo();
        void Update();
        void SaveCoursesData(string Filename);
};

void LoadLastCoursesData(Course *&Head, string Filename);
void AddCourse(Course *&Head);
void DeleteACourse(Course *&pD);
void Delete(Course *&Head);
void DeleteAllCourse(Course *&Head);
void StaffWorkWithCourse(Course *&Head, string Filename);

#endif // COURSEHEADER_H_INCLUDED
