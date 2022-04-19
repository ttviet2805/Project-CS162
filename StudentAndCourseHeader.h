#ifndef STUDENTHEADER_H_INCLUDED
#define STUDENTHEADER_H_INCLUDED

#include <iostream>

using namespace std;

#include "DateHeader.h"

//Session
class Session {
    public:
        string Day;
        string Ses;
        int Hour, Mins;

        void Init();
        void Cout();
        void Cin();
};
////////////////////////////////////////

//Info
class StudentInfo
{
    public:
        string ID, FirstName, LastName;
        string Gender;
        Date Dob;
        string SocialID;
        string StudentClass;
        int numCredit = 0;
        bool isFree[6][5]; // first dimension is the day of week, second dimension is session
};

class CourseInfo
{
    public:
        string CourseName, CourseID, LecturerName;
        Date StartDate, EndDate;
        Session FirstS, SecondS;
        int NumOfCredits = 0;

        void ShowCourseInfo();
};

class CourseScore
{
    public:
        float MidTerm = 0, Final = 0, Other = 0, Total = 0;

        void CalScore();
        void ShowCourseScore();
};
///////////////////////////////////

//ScoreBoard
class StudentScoreBoard
{
    public:
        CourseInfo *Info = nullptr;
        CourseScore *Score = nullptr;
        StudentScoreBoard *Next = nullptr;
};

class CourseScoreBoard
{
    public:
        StudentInfo *Student = nullptr;
        CourseScore *Score = nullptr;
        CourseScoreBoard *Next = nullptr;

        void ShowCourseScoreBoard();
        void UpdateScore(CourseScore* curCourseScore);
};

//////////////////////////////////////////////

//Course
class Course {
	public:
        CourseInfo *Info = new CourseInfo; //thong tin chung cua course
        CourseScoreBoard *Scoreboard = nullptr; //nhieu scoreboard, moi scoreboard gom` thong tin sv va diem cua sv
        Course *Next = nullptr;

        void ShowCourseInfo();
        void ShowCourseInfoWithNumber();
        void AllCoursesInfo();
        void ShowAllCourseScoreBoard();
        void Update();
        void SaveCourseScoreBoard(string path, string Filename);
        void SaveCoursesData(string path, string Filename);
        void AddANewStudent(StudentInfo *SI, CourseScore *CS);
        void deleteStudent(StudentInfo* curStudent);
        Course *FindACourseByID(string ID);
};

void AddCourse(Course *&Head);
void DeleteACourse(Course *&pD);
void Delete(Course *&Head);
void DeleteAllCourse(Course *&Head);
void StaffWorkWithCourse(Course *&Head, string Filename);
void RemoveAStudentFromACourse(Course *&Head, CourseInfo *_Course, StudentInfo *_Student);
void AddANewCourse(Course* &CourseHead, Course* newCourse);
//////////////////

//Student
class Student {
    public:

        StudentInfo *Info = new StudentInfo;
        StudentScoreBoard *ScoreBoard = nullptr;
        Student *Next = nullptr;

        void ShowStudentInfo();
        bool FindACourseAlreadyRegisted(CourseInfo *Info);
        int CountNumberOfCoursesRegisted();
        void EnrollACourse(Course *&CourseHead); //CourseHead la danh sach tat ca cac mon hoc
        void ViewAListOfEnrollCourse();
        void RemoveACourse(Course *&CourseHead);
        Student *FindStudentByID(string ID);
        void AddAStudentScoreBoard(CourseInfo *Info, CourseScore *Score);
        void SaveStudentsData(string path, string Filename); //chi save student info, khong save scoreboard,
                                                             //luc doc bang diem cho course se doc luon bang diem cho student
        void deleteCurrentCourse(CourseInfo* curCourseInfo);
};

void addANewStudentIntoStudentList(Student* &AllStudent, Student* newStudent);
void DeleteAStudent(Student *&pD);
void DeleteAllStudent(Student *&pD);
void LoadLastStudentData(Student *&Head, string path, string Filename);
//////////////////////////////////


void LoadLastCoursesData(Course *&Head, string path, string Filename, Student *&StudentHead);
void LoadLastCourseScoreBoardData(CourseScoreBoard *&ScoreBoard, CourseInfo *_CourseInfo, string path, string Filename, Student *&StudentHead);
#endif // STUDENTHEADER_H_INCLUDED
