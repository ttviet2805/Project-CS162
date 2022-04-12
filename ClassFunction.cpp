#include <iostream>
#include <fstream>
#include <string>

#include "ClassHeader.h"
#include "StudentAndCourseHeader.h"

using namespace std;

//class Functions
//Class

void Class::SaveAClassData(string path)
{
    ofstream fo;
    fo.open(path + ClassName + "/Course.txt");

    CourseOfClass *curCourse = Courses;
    while (curCourse)
    {
        fo << curCourse->_Course->Info->CourseID << '\n';
        curCourse = curCourse->Next;
    }

    fo.close();
}

void Class::SaveClassData(string path)
{
    Class *cur = this;
    while (cur)
    {
        cur->SaveAClassData(path);
        cur = cur->Next;
    }
}

Student* Class::FindStudentByID(string ID)
{
    Class *curClass = this;
    while (curClass)
    {
        StudentInClass *curStudent = curClass->Students;
        while (curStudent)
        {
            if (curStudent->_Student->Info->ID == ID) return curStudent->_Student;
            curStudent = curStudent->Next;
        }
        curClass = curClass->Next;
    }
    return nullptr;
};

void Class::AddAStudentIntoAClass(Student *&_Student)
{
    StudentInClass *New = new StudentInClass({_Student, nullptr});
    if (Students == nullptr) {
        Students = New;
        return;
    }
    StudentInClass *cur = Students;
    while (cur->Next) cur = cur->Next;
    cur->Next = New;
}

void Class::AddACourseIntoAClass(Course *&_Course)
{
    CourseOfClass *New = new CourseOfClass({_Course, nullptr});
    if (Courses == nullptr) {
        Courses = New;
        return;
    }
    CourseOfClass *cur = Courses;
    while (cur->Next) cur = cur->Next;
    cur->Next = New;
}

void Class::ShowAllStudentInfo()
{
    StudentInClass *curStudent = Students;
    while (curStudent)
    {
        curStudent->_Student->ShowStudentInfo();
        curStudent = curStudent->Next;
    }
}

void Class::ShowAllCourseInfo()
{
    CourseOfClass *curCourse = Courses;
    while (curCourse)
    {
        curCourse->_Course->ShowCourseInfo();
        curCourse = curCourse->Next;
    }
}

//Outer Functions
void LoadLastClassData(Class *&Head, string path, Student *&StudentHead, Course *&CourseHead) // path bao gom ca ten semester Savefile/2021-2022/HKI/
{
    ifstream fi;
    fi.open("SaveFile/Class/AllClassInfo.txt");

    Head = new Class;
    Class *cur = Head;

    string ClassName;
    while (!fi.eof() && getline(fi, ClassName))
    {
        cur->Next = new Class, cur = cur->Next;
        cur->ClassName = ClassName;

        Student *curstudent = StudentHead;
        while (curstudent) {
            if (curstudent->Info->StudentClass == ClassName) cur->AddAStudentIntoAClass(curstudent);
            curstudent = curstudent->Next;
        }

        ifstream ficourse;
        ficourse.open(path + ClassName + "/Course.txt");

        string CourseID;
        while (!ficourse.eof() && getline(ficourse, CourseID)) {
            Course *Temp = CourseHead->FindACourseByID(CourseID);
            cur->AddACourseIntoAClass(Temp);
        }

        ficourse.close();
    }

    Class *pD = Head;
    Head = Head->Next;
    DeleteAClass(pD);
    fi.close();
}

void DeleteAClass(Class *&Head)
{
    StudentInClass *cur = Head->Students;
    while (cur)
    {
        StudentInClass *pD = cur;
        cur = cur->Next;
        delete(pD);
    }
    delete(Head);
}

void DeleteAllClass(Class *&Head)
{
    while (Head)
    {
        Class *pD = Head;
        Head = Head->Next;
        DeleteAClass(pD);
    }
}

//ClassName khong bao gom duoi .csv
void ImportStudentInClassFromCSVFile(Student* &StudentHead, Class* &ClassHead, string Path, string ClassName) {
    ifstream fin;
    fin.open(Path + ClassName + ".csv");

    if(!fin.is_open()) {
        cout << "Can not find the CSV File\n";
        return;
    }

    Class *NewClass = new Class;
    NewClass->ClassName = ClassName;
    NewClass->Students = new StudentInClass;
    StudentInClass *CurStudentInClass = NewClass->Students;
    Student *NewStudentList = new Student;
    Student *cur = NewStudentList;

    string TempID;
    while(!fin.eof() && getline(fin, TempID, ',')) {
        cur->Next = new Student;
        cur->Next->Info->ID = TempID;
        getline(fin, cur->Next->Info->SocialID, ',');
        getline(fin, cur->Next->Info->FirstName, ',');
        getline(fin, cur->Next->Info->LastName, ',');
        getline(fin, cur->Next->Info->StudentClass, ',');
        getline(fin, cur->Next->Info->Gender, ',');

        string Dob; getline(fin, Dob, '\n');
        int day = 0, month = 0, year = 0;
        int low = 0;
        while(low < (int) Dob.size() && Dob[low] != '/') day = day * 10 + Dob[low] - '0', low++;
        low++;
        while(low < (int) Dob.size() && Dob[low] != '/') month = month * 10 + Dob[low] - '0', low++;
        while(low < (int) Dob.size()) year = year * 10 + Dob[low] - '0', low++;

        cur->Next->Info->Dob.changeDate(day, month, year);

        CurStudentInClass->Next = new StudentInClass({cur, nullptr});
        CurStudentInClass = CurStudentInClass->Next;

        cur = cur->Next;
    }

    StudentInClass *SICpD = NewClass->Students;
    NewClass->Students = NewClass->Students->Next;
    DeleteAStudent(SICpD->_Student);
    delete(SICpD);

    //Them class moi vao danh sach cac class
    Class *CurClass = ClassHead;
    if (CurClass == nullptr) ClassHead = NewClass;
    else
    {
        while (CurClass->Next) CurClass = CurClass->Next;
        CurClass->Next = NewClass;
    }

    //Them hoc sinh cua class moi vao danh sach tat ca hoc sinh cua truong
    Student *SpD = NewStudentList;
    NewStudentList = NewStudentList->Next;
    DeleteAStudent(SpD);

    Student *curInAllStudent = StudentHead;
    if (curInAllStudent == nullptr) StudentHead = NewStudentList;
    else
    {
        while (curInAllStudent->Next) curInAllStudent = curInAllStudent->Next;
        curInAllStudent->Next = NewStudentList;
    }
    fin.close();

    //Xoa trang file CSV
    ofstream fo(Path + ClassName + ".csv");
    fo.close();
}
