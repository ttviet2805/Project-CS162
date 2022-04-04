#include <iostream>
#include <fstream>

using namespace std;

#include "StudentAndCourseHeader.h"
#include "ClassHeader.h"

Student *AllStudent;
Course *AllCourse;
Class *AllClass;

void Test()
{
    string AllStudentInfoPath = "Savefile/Student/";
    string AllStudentInfoFilename = "AllStudentInfo.txt";
    string AllCourseInfoPath = "Savefile/Course/";
    string AllCourseInfoFilename = "AllCourseInfo.txt";
    string AllClassInfoPath = "Savefile/Class/";
    string AllClassInfoFilename = "AllClassInfo.txt";

    //Note:
    //Luon uu tien load all students truoc
    //Courses va Classes uu tien nhu nhau
    //Do ben Student qua nhieu thong tin nen se giam bot ben Class, muon ben AllStudents qua Class
    LoadLastStudentData(AllStudent, AllStudentInfoPath, AllStudentInfoFilename);
    LoadLastCoursesData(AllCourse, AllCourseInfoPath, AllCourseInfoFilename, AllStudent);
    LoadLastClassData(AllClass, AllClassInfoPath, AllClassInfoFilename, AllStudent);

    AllStudent->ShowStudentInfo();

    Student *User = AllStudent->FindStudentByID("21125007");

    User->EnrollACourse(AllCourse);
    User->ViewAListOfEnrollCourse();

    AllStudent->SaveStudentsData(AllStudentInfoPath, AllStudentInfoFilename);
    AllCourse->SaveCoursesData(AllCourseInfoPath, AllCourseInfoFilename);
    AllClass->SaveClassData(AllClassInfoPath, AllClassInfoFilename);

    DeleteAllCourse(AllCourse);
    DeleteAllStudent(AllStudent);
    DeleteAllClass(AllClass);
}

int main()
{
    Test();
    return 0;
}


// Doc du lieu (File: nhi phan, text)
// Du lieu nam hoc: 2019-2020, 2020-2021, 2021-2022
// Du lieu lop hoc: 2019CTT1, 2019CTT2, 2020CTT1, 2020CTT2
	// Danh sach sinh vien cua moi lop (msvv, ho ten, ngay sinh, que quan, ...)

// HK2 nam 2021-2022
	// Cac mon hoc: Calculus, CS, ...
		// Danh sach sinh vien (mssv, lop hoc, diem giua ky, diem cuoi ky, diem bai tap)
		// Thong tin lop hoc: nam hoc, hoc ky, thoi khoa bieu

// Mang danh sach nam hoc (danh sach lop => dsach sinh vien)
// Mang danh sach lop hoc
// Mang danh sach nam (Dsach hoc ky -> dsach lop -> dsach sinh vien -> thong tin lop)

// ham main
// Menu chuong trinh chinh
// Ma dang nhap
	// Sinh vien
		// Xem diem
		// Xem thoi khoa bieu
		// Xem thong tin
	// Giao vu
		// Tao/Cap nhat/Xoa hoc ky
		// Tao/Cap nhat/Xoa lop
		// Them sinh vien vao lop
	// Giao vien
		// Xem thoi khoa bieu
		// Diem danh
		// Cap nhat diem cua lop
			// chon lop
		// Cap nhat diem sinh vien
			// chon lop -> chon sinh vien

// Ghi du lieu
