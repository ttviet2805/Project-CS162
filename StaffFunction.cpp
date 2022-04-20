#include "StaffHeader.h"

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define ENTER 13

void CreateAFolder(string FileName) {
    if(mkdir(FileName.c_str()) == -1)
        cerr << " Error : " << strerror(errno) << endl;

    else
        cout << "File Created";
}

void LoadAllStaffData(Staff* &staffHead, string Path, string FileName) {
    ifstream fin;
    fin.open(Path + FileName);

    if(!fin.is_open()) return;

    Staff* Dummy = new Staff;
    Staff* cur = Dummy;

    string firstName;
    while(!fin.eof() && getline(fin, firstName)) {
        cur->Next = new Staff;
        cur->Next->Info->FirstName = firstName;
        getline(fin, cur->Next->Info->LastName);
        getline(fin, cur->Next->Info->Gender);
        getline(fin, cur->Next->Info->ID);
        fin >> cur->Next->Info->Dob.Day >> cur->Next->Info->Dob.Month >> cur->Next->Info->Dob.Year;

        cur = cur->Next;
    }

    staffHead = Dummy->Next;

    fin.close();
}

SchoolYear* loadSchoolYear() {
    ifstream fin("Savefile/SchoolYear/SchoolYearInfo.txt");
    if(fin.eof()) {
        fin.close();
        return nullptr;
    }

    SchoolYear* res = new SchoolYear;
    getline(fin, res->schoolYearName);
    if(res->schoolYearName == "") {
        fin.close();
        return nullptr;
    }

    fin >> res->startDate.Day >> res->startDate.Month >> res->startDate.Year;
    fin >> res->endDate.Day >> res->endDate.Month >> res->endDate.Year;

    fin.close();
    return res;
}

void ShowSchoolYearInfo() {
    clrscr();
    ShowCur(0);
    Button profileButton = Button(19, 5, 80, 3, "School Year Information");
    profileButton.drawRectangleWithText();

    SchoolYear* curSchoolYear = loadSchoolYear();
    if(!curSchoolYear) {
        gotoxy(45, 10);
        cout << "You have not create a school year yet!!!";
        gotoxy(45, 12);
        system("pause");
        return;
    }

    gotoxy(45, 10);
    cout << "School Year " << curSchoolYear->schoolYearName << endl;

    gotoxy(45, 11);
    cout << "Start Date: " << curSchoolYear->startDate.Day << '/' << curSchoolYear->startDate.Month << '/' << curSchoolYear->startDate.Year << '\n';
    gotoxy(45, 12);
    cout << "End Date: " << curSchoolYear->endDate.Day << '/' << curSchoolYear->endDate.Month << '/' << curSchoolYear->endDate.Year << '\n';

    gotoxy(45, 14);
    system("pause");
}

void SchoolYear::setDate(int d1, int m1, int y1, int d2, int m2, int y2) {
    startDate.changeDate(d1, m1, y1);
    endDate.changeDate(d2, m2, y2);
}

void Staff::ShowStaffInfo() {
    cout << "First name: " << Info->FirstName << endl;
    cout << "Last name: " << Info->LastName << endl;
    cout << "Gender: " << Info->Gender << endl;
    cout << "Staff ID: " << Info->ID << endl;
    cout << "Date of Birth: ";
    Info->Dob.OutputDate();
    cout << endl;
}

void CreateAClass() {
    const int startRow = 10, startCol = 40;
    clrscr();
    ShowCur(1);
    changeTextColor(11);
    Button profileButton = Button(19, 5, 80, 3, "Create A New Class");
    profileButton.drawRectangleWithText();

    Student* AllStudent = nullptr;
    LoadLastStudentData(AllStudent, "Savefile/Student/", "AllStudentInfo.txt");
    Course* AllCourse = nullptr;
    LoadLastCoursesData(AllCourse, "Savefile/Course/", "AllCourseInfo.txt", AllStudent);

    string schoolYearPath;
    ifstream fin("Savefile/Path/SchoolYearPath.txt");
    getline(fin, schoolYearPath);
    fin.close();

    Class* AllClass = nullptr;
    LoadLastClassData(AllClass, schoolYearPath, AllStudent, AllCourse);

    Class* resClass = new Class;

    gotoxy(startCol, startRow);
    cout << "Input class name: ";
    getline(cin, resClass->ClassName);

    SchoolYear* curSchoolYear = loadSchoolYear();
    if(!curSchoolYear) {
        gotoxy(startCol, startRow + 2);
        cout << "Do not have school year data!!!";
        gotoxy(startCol, startRow + 4);
        system("pause");
        return;
    }


    string fileName = "Savefile/SchoolYear/" + curSchoolYear->schoolYearName + "/Class/" + resClass->ClassName;

    if(mkdir(fileName.c_str()) == -1) {
        gotoxy(startCol, startRow + 3);
        cout << "Class " + resClass->ClassName + " has already existed";
        gotoxy(startCol, startRow + 4);
        cout << "Enter Again to try again or Back to back: ";
        string Option; getline(cin, Option);

        if(Option == "Again") {
            Sleep(3000);
            CreateAClass();
            ShowCur(0);
            return;
        }

        if(Option == "Back") {
            ShowCur(0);
            return;
        }

        gotoxy(startCol, startRow + 6);
        cout << "We can not find Back or Again, try again\n";
        Sleep(3000);
        CreateAClass();
        ShowCur(0);
        return;
    }
    else {
        gotoxy(startCol, startRow + 3);
        cout << "Create A New Class Successfully";
        gotoxy(startCol, startRow + 5);

        AddaClass(AllClass, resClass);

        ofstream fout;
        fout.open("Savefile/SchoolYear/" + curSchoolYear->schoolYearName + "/Class/" + resClass->ClassName + "/Course.txt");
        fout.close();

        AllClass->SaveClassData(schoolYearPath + "Class/",schoolYearPath + "Class/" + "AllClassInfo.txt");
        system("pause");
        return;
    }
}

void AddANewClass(Class* &classHead, Class* newClass) {
    if(!classHead) {
        classHead = newClass;
        return;
    }

    Class* cur = classHead;
    while(cur && cur->Next) cur = cur->Next;

    cur->Next = newClass;
}

void createANewSchoolYear() {
    clrscr();
    ShowCur(1);
    changeTextColor(11);
    Button profileButton = Button(19, 5, 80, 3, "Create A New School Year");
    profileButton.drawRectangleWithText();

    SchoolYear* newSchoolYear = new SchoolYear;

    const int startCol = 9;
    gotoxy(40, startCol);
    cout << "Input new school year's name: ";
    getline(cin, newSchoolYear->schoolYearName);

    gotoxy(40, startCol + 1);
    cout << "Enter the start date Information\n";
    gotoxy(40, startCol + 2);
    cout << "Day: ";
    cin >> newSchoolYear->startDate.Day;
    gotoxy(40, startCol + 3);
    cout << "Month: ";
    cin >> newSchoolYear->startDate.Month;
    gotoxy(40, startCol + 4);
    cout << "Year: ";
    cin >> newSchoolYear->startDate.Year;

    gotoxy(40, startCol + 5);
    cout << "Enter the end date Information\n";
    gotoxy(40, startCol + 6);
    cout << "Day: ";
    cin >> newSchoolYear->endDate.Day;
    gotoxy(40, startCol + 7);
    cout << "Month: ";
    cin >> newSchoolYear->endDate.Month;
    gotoxy(40, startCol + 8);
    cout << "Year: ";
    cin >> newSchoolYear->endDate.Year;

    cin.get();

    string fileName = "Savefile/SchoolYear/" + newSchoolYear->schoolYearName;

    if(mkdir(fileName.c_str()) == -1) {
        gotoxy(40, startCol + 10);
        cout << "School year " + newSchoolYear->schoolYearName + " has already existed";
        gotoxy(40, startCol + 11);
        cout << "Enter Again to try again or Back to back: ";
        string Option; getline(cin, Option);

        if(Option == "Again") {
            Sleep(3000);
            createANewSchoolYear();
            ShowCur(0);
            return;
        }

        if(Option == "Back") {
            ShowCur(0);
            return;
        }

        gotoxy(40, startCol + 13);
        cout << "We can not find Back or Again, try again\n";
        Sleep(3000);
        createANewSchoolYear();
        ShowCur(0);
        return;
    }
    else {
        gotoxy(40, startCol + 10);
        cout << "Create A New School Year Successfully";

        ofstream fout("Savefile/SchoolYear/SchoolYearInfo.txt");
        fout << newSchoolYear->schoolYearName << '\n';
        fout << newSchoolYear->startDate.Day << ' ' << newSchoolYear->startDate.Month << ' ' << newSchoolYear->startDate.Year << '\n';
        fout << newSchoolYear->endDate.Day << ' ' << newSchoolYear->endDate.Month << ' ' << newSchoolYear->endDate.Year;

        fout.close();

        gotoxy(40, startCol + 12);

        string classFolder = "Savefile/SchoolYear/" + newSchoolYear->schoolYearName + "/Class";
        mkdir(classFolder.c_str());
        string semesterFolder = "Savefile/SchoolYear/" + newSchoolYear->schoolYearName + "/Semester";
        mkdir(semesterFolder.c_str());

        fout.open(classFolder + "/AllClassInfo.txt");
        fout.close();

        fout.open(semesterFolder + "/SemesterInfo.txt");
        fout.close();

        fout.open("Savefile/Path/SchoolYearPath.txt");
        string tmpPath = "Savefile/SchoolYear/" + newSchoolYear->schoolYearName + '/';
        fout << tmpPath;
        fout.close();

        fout.open(tmpPath + "AllCourseInfo.txt");
        fout.close();

        string scoreFolder = "Savefile/SchoolYear/" + newSchoolYear->schoolYearName + "/CourseScoreBoard";
        mkdir(scoreFolder.c_str());

        string courseFolder = "Savefile/SchoolYear/" + newSchoolYear->schoolYearName + "/Course";
        mkdir(courseFolder.c_str());

        system("pause");
        return;
    }
}

void addStudentIntoClassByStaff() {
    clrscr();
    ShowCur(1);
    changeTextColor(11);
    Button profileButton = Button(19, 5, 80, 3, "Add Student Into Class");
    profileButton.drawRectangleWithText();

    string curClassName = "";

    const int startRow = 9;
    const int startCol = 40;

    gotoxy(startCol, startRow);
    cout << "Enter Class: ";
    getline(cin, curClassName);

    SchoolYear* curSchoolYear = loadSchoolYear();
    if(!curSchoolYear) {
        gotoxy(startCol, startRow + 2);
        cout << "Do not have school year data!!!";
        gotoxy(startCol, startRow + 4);
        system("pause");
        return;
    }

    string classFileName = "Savefile/SchoolYear/" + curSchoolYear->schoolYearName + "/Class/";
    ifstream fin;
    fin.open(classFileName + "AllClassInfo.txt");
    bool isExist = false;

    while(!fin.eof()) {
        string tmp;
        getline(fin, tmp);

        if(tmp == curClassName) isExist = true;
    }

    fin.close();

    if(!isExist) {
        gotoxy(startCol, startRow + 2);
        cout << "This class do not exist, try again";
        gotoxy(startCol, startRow + 4);
        system("pause");
        addStudentIntoClassByStaff();
        return;
    }

    gotoxy(startCol, startRow + 1);
    cout << "Enter the number of students you want to add: ";
    int numStu; cin >> numStu;

    cin.get();

    Student* AllStudent = nullptr;
    LoadLastStudentData(AllStudent, "Savefile/Student/", "AllStudentInfo.txt");
    Course* AllCourse = nullptr;
    LoadLastCoursesData(AllCourse, "Savefile/Course/", "AllCourseInfo.txt", AllStudent);

    string schoolYearPath;
    fin.open("Savefile/Path/SchoolYearPath.txt");
    getline(fin, schoolYearPath);
    fin.close();

    Class* AllClass = nullptr;
    LoadLastClassData(AllClass, schoolYearPath, AllStudent, AllCourse);

    Class* curClass = findClassByID(AllClass, curClassName);

    Login* AllUser = nullptr;
    loadUserAccount(AllUser, "Savefile/User/StudentUser.txt");

    for(int i = 1; i <= numStu; i++) {
        Student* newStudent = new Student;

        int curRow = startRow + 3 + (i - 1) * 8;
        gotoxy(startCol - 10, curRow);
        cout << "Student " << i << '\n';
        gotoxy(startCol - 10, curRow + 1);
        cout << "ID: ";
        getline(cin, newStudent->Info->ID);
        gotoxy(0, 0);
        gotoxy(startCol - 10, curRow + 2);
        cout << "First name: ";
        getline(cin, newStudent->Info->FirstName);
        gotoxy(startCol - 10, curRow + 3);
        cout << "Last name: ";
        getline(cin, newStudent->Info->LastName);
        gotoxy(startCol - 10, curRow + 4);
        cout << "Gender: ";
        getline(cin, newStudent->Info->Gender);
        gotoxy(startCol - 10, curRow + 5);
        cout << "Date of Birth: (dd/mm/yyyy) ";
        string Dob; getline(cin, Dob);

        int day = 0, month = 0, year = 0;
        int low = 0;
        while(low < (int) Dob.size() && Dob[low] != '/') day = day * 10 + Dob[low] - '0', low++;
        low++;
        while(low < (int) Dob.size() && Dob[low] != '/') month = month * 10 + Dob[low] - '0', low++;
        low++;
        while(low < (int) Dob.size()) year = year * 10 + Dob[low] - '0', low++;
        newStudent->Info->Dob.changeDate(day, month, year);

        gotoxy(startCol - 10, curRow + 6);
        cout << "Social ID: ";
        getline(cin, newStudent->Info->SocialID);
        gotoxy(startCol - 10, curRow + 7);

        newStudent->Info->StudentClass = curClassName;
        curClass->AddAStudentIntoAClass(newStudent);
        addANewStudentIntoStudentList(AllStudent, newStudent);
        Login* newUser = new Login;
        newUser->userAccount.username = newStudent->Info->ID;
        newUser->userAccount.password = "123456";

        gotoxy(0, 0);
        addANewUser(AllUser, newUser);
    }

    saveUserAccount(AllUser, "Savefile/User/StudentUser.txt");

    AllStudent->SaveStudentsData("Savefile/Student/", "AllStudentInfo.txt");
    AllClass->SaveClassData(schoolYearPath + "Class/",schoolYearPath + "Class/" + "AllClassInfo.txt");

    gotoxy(startCol - 10, startRow + 4 + numStu * 8);
    cout << "Add new students successfully";
    gotoxy(startCol - 10, startRow + 6 + numStu * 8);
    system("pause");
}

void staffAddCourse() {
    clrscr();
    ShowCur(1);
    changeTextColor(11);
    Button profileButton = Button(19, 5, 80, 3, "Add Course");
    profileButton.drawRectangleWithText();

    string schoolYearPath = "";
    ifstream fin;
    fin.open("Savefile/Path/SchoolYearPath.txt");
    getline(fin, schoolYearPath);
    fin.close();

    Student* AllStudent = nullptr;
    LoadLastStudentData(AllStudent, "Savefile/Student/", "AllStudentInfo.txt");
    Course* AllCourse = nullptr;
    LoadLastCoursesData(AllCourse, schoolYearPath, "AllCourseInfo.txt", AllStudent);

    Class* AllClass = nullptr;
    LoadLastClassData(AllClass, schoolYearPath, AllStudent, AllCourse);

    const int startRow = 10;
    const int startCol = 40;

    Course *New = new Course;
    char Name[] = "Name: ", ID[] = "ID: ", Lecturer[] = "Lecturer: ", Credit[] = "Number of Credits: ", Start[] = "Start day: ", End[] = "End day: ",
                    Ses1[] = "Session 1: ", Ses2[] = "Session 2: ";

    string curClassName = "";
    gotoxy(startCol, startRow - 1);
    cout << "Course of Class: ";
    getline(cin, curClassName);

    Class* curClass = findClassByID(AllClass, curClassName);
    if(!curClass) {
        gotoxy(startCol, startRow + 2);
        cout << "Our system can not find this class, try again!!!";
        Sleep(3000);
        staffAddCourse();
        return;
    }

    gotoxy(startCol, startRow);
    cout << Name; getline(cin, New->Info->CourseName);
    gotoxy(startCol, startRow + 1);
    cout << ID; getline(cin, New->Info->CourseID);
    gotoxy(startCol, startRow + 2);
    cout << Lecturer; getline(cin, New->Info->LecturerName);
    gotoxy(startCol, startRow + 3);
    cout << Credit; cin >> New->Info->NumOfCredits;
    gotoxy(startCol, startRow + 4);
    cout << Start; New->Info->StartDate.InputDate();
    gotoxy(startCol, startRow + 5);
    cout << End; New->Info->EndDate.InputDate();
    gotoxy(startCol, startRow + 6);
    cout << Ses1 << " (MON S1) ", New->Info->FirstS.Cin();
    gotoxy(startCol, startRow + 7);
    cout << Ses2 << " (MON S1) ", New->Info->SecondS.Cin();
    cin.get();

    AddANewCourse(AllCourse, New);

    AllCourse->SaveCoursesData(schoolYearPath, "/AllCourseInfo.txt");

    curClass->AddACourseIntoAClass(New);

    curClass->SaveAClassData(schoolYearPath + "Class/");
}

void staffModifyCourse(Course* &curCourse) {
    clrscr();
    ShowCur(1);
    changeTextColor(11);
    Button profileButton = Button(19, 5, 80, 3, "Modify Course");
    profileButton.drawRectangleWithText();

    string schoolYearPath = "";
    ifstream fin;
    fin.open("Savefile/Path/SchoolYearPath.txt");
    getline(fin, schoolYearPath);
    fin.close();

    Student* AllStudent = nullptr;
    LoadLastStudentData(AllStudent, "Savefile/Student/", "AllStudentInfo.txt");

    const int startRow = 10;
    const int startCol = 40;

    Course *New = new Course;
    char Name[] = "Name: ", ID[] = "ID: ", Lecturer[] = "Lecturer: ", Credit[] = "Number of Credits: ", Start[] = "Start day: ", End[] = "End day: ",
                    Ses1[] = "Session 1: ", Ses2[] = "Session 2: ";

    gotoxy(startCol, startRow);
    cout << Name; getline(cin, curCourse->Info->CourseName);
    gotoxy(startCol, startRow + 1);
    cout << ID; getline(cin, curCourse->Info->CourseID);
    gotoxy(startCol, startRow + 2);
    cout << Lecturer; getline(cin, curCourse->Info->LecturerName);
    gotoxy(startCol, startRow + 3);
    cout << Credit; cin >> curCourse->Info->NumOfCredits;
    gotoxy(startCol, startRow + 4);
    cout << Start; curCourse->Info->StartDate.InputDate();
    gotoxy(startCol, startRow + 5);
    cout << End; curCourse->Info->EndDate.InputDate();
    gotoxy(startCol, startRow + 6);
    cout << Ses1 << " (MON S1) ", curCourse->Info->FirstS.Cin();
    gotoxy(startCol, startRow + 7);
    cout << Ses2 << " (MON S1) ", curCourse->Info->SecondS.Cin();
    cin.get();

    gotoxy(startCol, startRow + 9);
    cout << "Modify Course Successful";
    gotoxy(startCol, startRow + 11);
    system("pause");

    curCourse->SaveCoursesData(schoolYearPath, "/AllCourseInfo.txt");
}

void staffDeleteCourse(Course* &curCourse) {
    clrscr();
    string schoolYearPath = "";
    ifstream fin;
    fin.open("Savefile/Path/SchoolYearPath.txt");
    getline(fin, schoolYearPath);
    fin.close();

    Student* AllStudent = nullptr;
    LoadLastStudentData(AllStudent, "Savefile/Student/", "AllStudentInfo.txt");
    Course* AllCourse = nullptr;
    LoadLastCoursesData(AllCourse, schoolYearPath, "AllCourseInfo.txt", AllStudent);

    Class* AllClass = nullptr;
    LoadLastClassData(AllClass, schoolYearPath, AllStudent, AllCourse);

    clrscr();

    ShowCur(1);
    gotoxy(45, 10);
    cout << "Are you sure to delete this course?";
    gotoxy(45, 11);
    cout << "Enter YES to delete, else enter any key: ";
    string Option; getline(cin, Option);
    ShowCur(0);

    if(Option == "YES") {
        gotoxy(45, 13);
        cout << "You have delete this course!!!";
        Course* tmp = AllCourse;

        if(tmp) {
            if(tmp->Info->CourseID == curCourse->Info->CourseID) {
                Course* Del = tmp;
                AllCourse = AllCourse->Next;
                delete Del;
            }
            else {
                while(tmp && tmp->Next && tmp->Next->Info->CourseID != curCourse->Info->CourseID) {
                    tmp = tmp->Next;
                }

                if(tmp && tmp->Next) {
                    Course* Del = tmp->Next;
                    tmp->Next = Del->Next;
                    delete Del;
                }
            }
        }

        Class* tmpClass = AllClass;
        while(tmpClass) {
            tmpClass->RemoveACourse(curCourse);
            tmpClass = tmpClass->Next;
        }

        ofstream fout(schoolYearPath + "CourseScoreBoard/" + curCourse->Info->CourseName + ".txt");
        fout.close();

        AllClass->SaveClassData(schoolYearPath + "Class/",schoolYearPath + "Class/" + "AllClassInfo.txt");
        AllCourse->SaveCoursesData(schoolYearPath, "/AllCourseInfo.txt");
        AllStudent->SaveStudentsData(schoolYearPath + "Student/", "AllStudentInfo.txt");

        gotoxy(45, 15);
        system("pause");
        return;
    }

    gotoxy(45, 13);
    cout << "You have not delete this course";
    gotoxy(45, 15);
    system("pause");
}

void staffviewlistOfStudentInCourse(Course* curCourse) {
    ShowCur(0);
    clrscr();
    changeTextColor(11);
    Button listOfStudentButton = Button(19, 5, 80, 3, "List of Students");
    listOfStudentButton.drawRectangleWithText();

    Student* AllStudent = nullptr;
    LoadLastStudentData(AllStudent, "Savefile/Student/", "AllStudentInfo.txt");


    const int startCol = 5, startRow = 10;

    Student* Dummy = new Student;
    Student* curStudent = Dummy;
    CourseScoreBoard* curCourseScoreBoard = curCourse->Scoreboard;

    while(curCourseScoreBoard) {
        Student* curStu = AllStudent->FindStudentByID(curCourseScoreBoard->Student->ID);
        curStudent->Next = new Student;
        *curStudent->Next = *curStu;
        curStudent->Next->Next = nullptr;
        curStudent = curStudent->Next;
        curCourseScoreBoard = curCourseScoreBoard->Next;
    }

    gotoxy(startCol, startRow);
    cout << "ID";
    gotoxy(startCol + 15, startRow);
    cout << "First name";
    gotoxy(startCol + 40, startRow);
    cout << "Last name";
    gotoxy(startCol + 60, startRow);
    cout << "Gender";
    gotoxy(startCol + 70, startRow);
    cout << "Date of Birth";
    gotoxy(startCol + 85, startRow);
    cout << "Class";
    gotoxy(startCol + 95, startRow);
    cout << "Social ID";


    Student* cur = Dummy->Next;
    int tmpcnt = 1;

    while(cur) {
        ++tmpcnt;
        gotoxy(startCol, startRow + tmpcnt);
        cout << cur->Info->ID;
        gotoxy(startCol + 15, startRow + tmpcnt);
        cout << cur->Info->FirstName;
        gotoxy(startCol + 40, startRow + tmpcnt);
        cout << cur->Info->LastName;
        gotoxy(startCol + 60, startRow + tmpcnt);
        cout << cur->Info->Gender;
        gotoxy(startCol + 70, startRow + tmpcnt);
        cout << cur->Info->Dob.Day << '/' << cur->Info->Dob.Month << '/' << cur->Info->Dob.Year;
        gotoxy(startCol + 85, startRow + tmpcnt);
        cout << cur->Info->StudentClass;
        gotoxy(startCol + 95, startRow + tmpcnt);
        cout << cur->Info->SocialID;
        ++tmpcnt;

        cur = cur->Next;
    }

    gotoxy(45, startRow + tmpcnt + 2);
    system("pause");
}

void staffExportStudentToCSVFile(Course* curCourse) {
    ShowCur(0);
    clrscr();
    changeTextColor(11);
    Button listOfStudentButton = Button(19, 5, 80, 3, "Export to CSV File");
    listOfStudentButton.drawRectangleWithText();

    Student* AllStudent = nullptr;
    LoadLastStudentData(AllStudent, "Savefile/Student/", "AllStudentInfo.txt");

    string schoolYearPath = "";
    ifstream fin;
    fin.open("Savefile/Path/SchoolYearPath.txt");
    getline(fin, schoolYearPath);
    fin.close();

    const int startCol = 5, startRow = 10;

    Student* Dummy = new Student;
    Student* curStudent = Dummy;
    CourseScoreBoard* curCourseScoreBoard = curCourse->Scoreboard;

    while(curCourseScoreBoard) {
        Student* curStu = AllStudent->FindStudentByID(curCourseScoreBoard->Student->ID);
        curStudent->Next = new Student;
        *curStudent->Next = *curStu;
        curStudent->Next->Next = nullptr;
        curStudent = curStudent->Next;
        curCourseScoreBoard = curCourseScoreBoard->Next;
    }

    Student* lstStudent = Dummy->Next;

    loadingFunction(45, 24);

    string CSVFilename; getline(cin, CSVFilename);

    ofstream fout;
    fout.open(schoolYearPath + "Course/" + curCourse->Info->CourseName + ".csv");

    while(lstStudent) {
        fout << lstStudent->Info->ID << ',' << lstStudent->Info->FirstName << ',' << lstStudent->Info->LastName;
        fout << ',' << lstStudent->Info->Gender << ',';
        Date tmpDate = lstStudent->Info->Dob;
        fout << tmpDate.Day << '/' << tmpDate.Month << '/' << tmpDate.Year << ',';
        fout << lstStudent->Info->SocialID << ',' << lstStudent->Info->StudentClass << '\n';
        lstStudent = lstStudent->Next;
    }

    fout.close();
}

void staffViewScoreBoard(Course* curCourse) {
    clrscr();
    changeTextColor(11);
    Button listOfStudentButton = Button(19, 5, 80, 3, "View Course's Scoreboard");
    listOfStudentButton.drawRectangleWithText();

    const int startCol = 5, startRow = 10;

    gotoxy(startCol, startRow);
    cout << "ID";
    gotoxy(startCol + 15, startRow);
    cout << "First name";
    gotoxy(startCol + 40, startRow);
    cout << "Last name";
    gotoxy(startCol + 55, startRow);
    cout << "Total Mark";
    gotoxy(startCol + 70, startRow);
    cout << "Final Mark";
    gotoxy(startCol + 85, startRow);
    cout << "Midterm Mark";
    gotoxy(startCol + 100, startRow);
    cout << "Other Mark";


    CourseScoreBoard* curScore = curCourse->Scoreboard;
    int tmpcnt = 1;

    while(curScore) {
        ++tmpcnt;
        curScore->Score->CalScore();
        gotoxy(startCol, startRow + tmpcnt);
        cout << curScore->Student->ID;
        gotoxy(startCol + 15, startRow + tmpcnt);
        cout << curScore->Student->FirstName;
        gotoxy(startCol + 40, startRow + tmpcnt);
        cout << curScore->Student->LastName;
        gotoxy(startCol + 55, startRow + tmpcnt);
        cout << curScore->Score->Total;
        gotoxy(startCol + 70, startRow + tmpcnt);
        cout << curScore->Score->Final;
        gotoxy(startCol + 85, startRow + tmpcnt);
        cout << curScore->Score->MidTerm;
        gotoxy(startCol + 100, startRow + tmpcnt);
        cout << curScore->Score->Other;
        curScore = curScore->Next;
        ++tmpcnt;
    }

    gotoxy(45, startRow + tmpcnt + 2);
    system("pause");
}

void staffImportScoreBoardByManual(Course* &curCourse) {
    ShowCur(1);
    clrscr();
    changeTextColor(11);
    Button createClassButton = Button(19, 5, 80, 3, "Import Course Scoreboard By Manual");
    createClassButton.drawRectangleWithText();

    string schoolYearPath = "";
    ifstream fin;
    fin.open("Savefile/Path/SchoolYearPath.txt");
    getline(fin, schoolYearPath);
    fin.close();

    Student* AllStudent = nullptr;
    LoadLastStudentData(AllStudent, "Savefile/Student/", "AllStudentInfo.txt");

    const int startRow = 11;
    const int startCol = 48;
    // de sua lan dau xuong dong ne
    // thu xem
    gotoxy(0, 11);

    int numStu;
    cout << "Enter number students: "; cin >> numStu;
    cin.get();

    CourseScoreBoard* curScore = curCourse->Scoreboard;

    for(int i = 1; i <= numStu; i++) {
        cout << "Student " << i << '\n';
        cout << "ID: ";
        string tmpID; getline(cin, tmpID);

        Student* curStudent = AllStudent->FindStudentByID(tmpID);
        if(!curStudent) {
            cout << "Our system does not have this student's data" << '\n';
            cout << "Try Again";
            Sleep(3000);
            staffImportScoreBoardByManual(curCourse);
            return;
        }

        CourseScore* curStudentScore = new CourseScore;
        cout << "Final Score: "; cin >> curStudentScore->Final;
        cout << "Midterm Score: "; cin >> curStudentScore->MidTerm;
        cout << "Other Score: "; cin >> curStudentScore->Other;
        cin.get();

        CourseScoreBoard* tmpScore = curScore;
        if(tmpScore->Student->ID == tmpID) {
            tmpScore->UpdateScore(curStudentScore);
        }
        else {
            while(tmpScore && tmpScore->Next && tmpScore->Next->Student->ID != tmpID) {
                tmpScore = tmpScore->Next;
            }

            if(!tmpScore->Next) {
                CourseScoreBoard* New = new CourseScoreBoard;
                New->Student = curStudent->Info;
                New->Score = curStudentScore;
                New->Next = tmpScore->Next;
                tmpScore->Next = New;
            }
            else {
                tmpScore->Next->UpdateScore(curStudentScore);
            }
        }

        cout << '\n';
    }

//    CourseScoreBoard* tmpScore = curScore;
//    while(tmpScore) {
//        cout << tmpScore->Score->Final << ' ' << tmpScore->Student->ID << endl;
//        tmpScore = tmpScore->Next;
//    }

    curCourse->SaveCourseScoreBoard(schoolYearPath, "CourseScoreBoard/" + curCourse->Info->CourseName + ".txt");
    cout << "Import Student's Score successful" << endl;
    cout << endl;
    system("pause");
}

void solveWithACourse(Course* &curCourse) {
    const int startRow = 15;
    const int startCol = 48;
    const int startX = 10;
    const int numButton = 7;
    string Modify = "Modify";
    string Delete = "Delete";
    string listOfStudent = "List Of Students";
    string exportStudent = "Export Students In Course";
    string importScoreBoard = "Import Course's Scoreboard";
    string viewScoreBoard = "View Scoreboard";
    string BackButton = "Back";

    while(1) {
        ShowCur(0);
        clrscr();
        changeTextColor(11);
        Button createClassButton = Button(19, 5, 80, 3, "Current Course");
        createClassButton.drawRectangleWithText();

        gotoxy(startCol, startRow + 2);
        cout << Modify;
        gotoxy(startCol, startRow + 3);
        cout << Delete;
        gotoxy(startCol, startRow + 4);
        cout << listOfStudent;
        gotoxy(startCol, startRow + 5);
        cout << exportStudent;
        gotoxy(startCol, startRow + 6);
        cout << importScoreBoard;
        gotoxy(startCol, startRow + 7);
        cout << viewScoreBoard;
        gotoxy(startCol, startRow + 8);
        cout << BackButton;

        gotoxy(10, 9);
        cout << "ID";
        gotoxy(15, 9);
        cout << "Course ID";
        gotoxy(30, 9);
        cout << "Course Name";
        gotoxy(69, 9);
        cout << "Number Of";
        gotoxy(69, 10);
        cout << "Credits";
        gotoxy(81, 9);
        cout << "Course Time";
        gotoxy(96, 9);
        cout << "Lecture Name";

        gotoxy(startX, startRow - 3);
        cout << 1;

        gotoxy(startX + 5, startRow - 3);
        cout << curCourse->Info->CourseID;

        gotoxy(startX + 20, startRow - 3);
        cout << curCourse->Info->CourseName;

        gotoxy(startX + 63, startRow - 3);
        cout << curCourse->Info->NumOfCredits;

        Session S1 = curCourse->Info->FirstS;
        Session S2 = curCourse->Info->SecondS;
        gotoxy(startX + 71, startRow - 3);
        cout << "S1" << ": " << S1.Day << ' ' << S1.Hour << ": " << S1.Mins;
        gotoxy(startX + 71, startRow - 2);
        cout << "S2" << ": " << S2.Day << ' ' << S2.Hour << ": " << S2.Mins;

        gotoxy(startX + 86, startRow - 3);
        cout << curCourse->Info->LecturerName;

        int curCol = 1;
        bool isEnter = false;

        while(1)
        {
            gotoxy(startCol - 3, curCol + startRow + 1);
            cout << ">>";

            int c = getch();
            int prevCol = curCol;

            if(c == ENTER) {
                switch(curCol) {
                case 1:
                    staffModifyCourse(curCourse);
                    isEnter = true;
                    break;

                case 2:
                    staffDeleteCourse(curCourse);
                    return;
                    isEnter = true;
                    break;

                case 3:
                    staffviewlistOfStudentInCourse(curCourse);
                    isEnter = true;
                    break;

                case 4:
                    staffExportStudentToCSVFile(curCourse);
                    isEnter = true;
                    break;

                case 5:
                    staffImportScoreBoardByManual(curCourse);
                    isEnter = true;
                    break;

                case 6:
                    staffViewScoreBoard(curCourse);
                    isEnter = true;
                    break;

                case 7:
                    return;
                }

            }
            else {
                if(c == KEY_UP) {
                    curCol--;
                    if(curCol < 1) curCol = numButton;
                }
                else {
                    if(c == KEY_DOWN) {
                        curCol++;
                        if(curCol > numButton) curCol = 1;
                    }
                }
            }

//            AllCourse->SaveCoursesData(schoolYearPath, "/AllCourseInfo.txt");

            if(isEnter) break;

            gotoxy(startCol - 3, prevCol + startRow + 1);
            cout << "  ";
        }
    }
}
