#ifndef COURSEHEADER_H_INCLUDED
#define COURSEHEADER_H_INCLUDED

#include <iostream>
#include "DateHeader.h"

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

class Course {
	public:

        string CourseName, CourseID, LecturerName;
        Date StartDate, EndDate;
        Session FirstS, SecondS; //(S1 (07:30), S2 (09:30), S3(13:30) and S4 (15:30))
            // 2 sessions in a week
            // (nhiều nhất 5 course, không thể enroll course trùng lịch với các courses đã đăng kí)
        //ScoreBoard Scoreboard;
        //Mỗi môn có tỉ lệ % điểm thành phần khác nhau
        double process_percent; //tỉ lệ điểm quá trình, thực hành, dự án...
        double midterm_percent; //thi giữa kỳ
        double final_percent; //thi cuối kỳ
        Course *Next = nullptr;

        void CourseInfo();
        void CourseInfoWithNumber();
        void AllCoursesInfo();
        void Update(string Filename);
        void SaveCoursesData(string Filename);
};

void LoadLastCoursesData(Course *&Head, string Filename);
void AddCourse(Course *&Head);
void Delete(Course *&Head, string Filename);
void DeleteCourse(Course *&Head);
void StaffWorkWithCourse(Course *&Head, string Filename);

#endif // COURSEHEADER_H_INCLUDED
