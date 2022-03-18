#ifndef COURSEHEADER_H_INCLUDED
#define COURSEHEADER_H_INCLUDED

#include "DateHeader.h"

class Course {
	public:
        char CourseName[50], CourseID[50], LecturerName[50];
        Date StartDate, EndDate;
        char FirstS[50], SecondS[50]; //(S1 (07:30), S2 (09:30), S3(13:30) and S4 (15:30))
            // 2 sessions in a week
            // (nhiều nhất 5 course, không thể enroll course trùng lịch với các courses đã đăng kí)
        //ScoreBoard Scoreboard;
        Course *Next = nullptr;

        void CourseInfo();
        void CourseInfoWithNumber();
        void Update(char Filename[]);
        void SaveCoursesData(char Filename[]);
        void AllCoursesInfo();
};

void LoadLastCoursesData(Course *&Head, char Filename[]);
void DeleteAllCourse(Course *Head);
void Delete(Course *&Head, char Filename[]);
void DeleteCourse(Course *&Head);

#endif // COURSEHEADER_H_INCLUDED
