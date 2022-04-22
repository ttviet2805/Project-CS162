#pragma once

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

//    cout << "here";
    CourseOfClass *curCourse = Courses;
    while (curCourse)
    {
        fo << curCourse->_Course->Info->CourseID << '\n';
        curCourse = curCourse->Next;
    }
//    cout << "Here2";

    fo.close();
}

Class* findClassByID(Class* AllClass, string ClassName) {
    while(AllClass) {
        if(AllClass->ClassName == ClassName) return AllClass;
        AllClass = AllClass->Next;
    }

    return nullptr;
}

void SaveIntoAllClassFile(Class* curClass, string Path) {
    ofstream fout(Path);

    while(curClass) {
        fout << curClass->ClassName << '\n';
        curClass = curClass->Next;
    }

    fout.close();
}

void Class::SaveClassData(string path, string allClassInfoPath)
{
    SaveIntoAllClassFile(this, allClassInfoPath);

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
    fi.open(path + "Class/AllClassInfo.txt");

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
        ficourse.open(path + "Class/" + ClassName + "/Course.txt");

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
void ImportStudentInClassFromCSVFile(Student* &StudentHead, Class* curClass) {
    string schoolYearPath = "";
    ifstream fin;
    fin.open("Savefile/Path/SchoolYearPath.txt");
    getline(fin, schoolYearPath);
    fin.close();

    string Path = schoolYearPath + "Class/" + curClass->ClassName + "/Student.csv";
    fin.open(Path);

    if(!fin.is_open()) {
//        cout << "Can not find the CSV File\n";
        fin.close();
        return;
    }

    StudentInClass* Dummy = new StudentInClass;
    StudentInClass *CurStudentInClass = curClass->Students;
    Dummy->Next = CurStudentInClass;
    CurStudentInClass = Dummy;
    while(CurStudentInClass->Next) CurStudentInClass = CurStudentInClass->Next;

    Student *DummyStudent = new Student;
    Student *cur = DummyStudent;

    string TempID;
    while(!fin.eof() && getline(fin, TempID, ',')) {
        cur->Next = new Student;
        cur->Next->Info->ID = TempID;
        getline(fin, cur->Next->Info->FirstName, ',');
        getline(fin, cur->Next->Info->LastName, ',');
        getline(fin, cur->Next->Info->Gender, ',');

        string Dob; getline(fin, Dob, ',');
        int day = 0, month = 0, year = 0;
        int low = 0;
        while(low < (int) Dob.size() && Dob[low] != '/') day = day * 10 + Dob[low] - '0', low++;
        low++;
        while(low < (int) Dob.size() && Dob[low] != '/') month = month * 10 + Dob[low] - '0', low++;
        low++;
        while(low < (int) Dob.size()) year = year * 10 + Dob[low] - '0', low++;

        getline(fin, cur->Next->Info->SocialID, ',');
        getline(fin, cur->Next->Info->StudentClass, '\n');

        cur->Next->Info->Dob.changeDate(day, month, year);

        CurStudentInClass->Next = new StudentInClass({cur, nullptr});
        CurStudentInClass = CurStudentInClass->Next;

        cur = cur->Next;
    }

    CurStudentInClass = Dummy->Next;
    Student* newStudentList = DummyStudent->Next;
    delete Dummy;
    delete DummyStudent;

//    StudentInClass *SICpD = curClass->Students;
//    curClass->Students = curClass->Students->Next;
//    DeleteAStudent(SICpD->_Student);
//    delete(SICpD);

    //Them hoc sinh cua class moi vao danh sach tat ca hoc sinh cua truong
//    Student *SpD = NewStudentList;
//    NewStudentList = NewStudentList->Next;
//    DeleteAStudent(SpD);

    Student *curInAllStudent = StudentHead;
    if (curInAllStudent == nullptr) StudentHead = newStudentList;
    else
    {
        while (curInAllStudent->Next) curInAllStudent = curInAllStudent->Next;
        curInAllStudent->Next = newStudentList;
    }
    fin.close();

    StudentHead->SaveStudentsData(schoolYearPath + "Student/", "AllStudentInfo.txt");
//    Xoa trang file CSV
    ofstream fo(Path);
    fo.close();
}

void AddaClass(Class* &classHead, Class* newClass) {
    Class* cur = classHead;

    if(cur) {
        while(cur->Next) cur = cur->Next;
        cur->Next = newClass;
    }
    else {
        classHead = newClass;
    }
}

void Class::RemoveACourse(Course* delCourse) {
    CourseOfClass* tmp = Courses;

    while(tmp && tmp->Next && tmp->Next->_Course != delCourse) {
        tmp = tmp = tmp->Next;
    }

    if(tmp && tmp->Next) {
        CourseOfClass* Del = tmp->Next;
        tmp->Next = Del->Next;
        delete Del;
    }
}
