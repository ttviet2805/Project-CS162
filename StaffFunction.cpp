#include "StaffHeader.h"

void CreateAFolder(string FileName) {
    if(mkdir(FileName.c_str()) == -1)
        cerr << " Error : " << strerror(errno) << endl;

    else
        cout << "File Created";
}

void SchoolYear::ShowSchoolYearInfo() {
    cout << schoolYearName << endl;

    startDate.OutputDate();
    endDate.OutputDate();
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

void LoadAllStaffData(Staff* &staffHead, string Path, string FileName) {
    ifstream fin;
    fin.open(Path + FileName);

    if(!fin.is_open()) return;

    Staff* Dummy = new Staff;
    Staff* cur = Dummy;

    while(!fin.eof()) {
        cur->Next = new Staff;
        getline(fin, cur->Next->Info->FirstName);
        getline(fin, cur->Next->Info->LastName);
        getline(fin, cur->Next->Info->Gender);
        getline(fin, cur->Next->Info->ID);
        fin >> cur->Next->Info->Dob.Day >> cur->Next->Info->Dob.Month >> cur->Next->Info->Dob.Year;

        cur = cur->Next;
    }

    staffHead = Dummy->Next;

    fin.close();
}

Class* CreateAClass() {
    cout << "Input class name: ";
    string newClass; getline(cin, newClass);

    Class* resClass = new Class;
    resClass->ClassName = newClass;

    return resClass;
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
    changeTextColor(11);
    Button profileButton = Button(19, 5, 80, 3, "Create A New School Year");
    profileButton.drawRectangleWithText();

    SchoolYear* newSchoolYear = new SchoolYear;

    const int startCol = 9;
    gotoxy(40, startCol);
    cout << "Input new school year's name: ";
    string tmpName; getline(cin, newSchoolYear->schoolYearName);

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

    string fileName = "Savefile/SchoolYear/" + newSchoolYear->schoolYearName;
    CreateAFolder(fileName);
}
