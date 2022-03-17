#ifndef COURSEHEADER_H_INCLUDED
#define COURSEHEADER_H_INCLUDED

class Date
{
public:
    int Day, Month, Year;

    void OutputDate();
    void InputDate();
};

class Course {
	public:
        char CourseName[50], CourseID[50], LecturerName[50];
        Date StartDate, EndDate;
        int FirstS, SecondS; //(S1 (07:30), S2 (09:30), S3(13:30) and S4 (15:30))
            // 2 sessions in a week
            // (nhiều nhất 5 course, không thể enroll course trùng lịch với các courses đã đăng kí)
        //ScoreBoard Scoreboard;
        Course *Next = nullptr;

        void CourseInfo();
        void CourseInfoWithNumber();
        void LoadLastCoursesData(char Filename[]);
        void Update();
        void Delete();
};


#endif // COURSEHEADER_H_INCLUDED
