#include "StaffHeader.h"

void Staff::ShowStaffInfo() {
    cout << "First name: " << FirstName << endl;
    cout << "Last name: " << LastName << endl;
    cout << "Gender: " << Gender << endl;
    cout << "Staff ID: " << ID << endl;
    cout << "Date of Birth: ";
    Dob.OutputDate();
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
        getline(fin, cur->Next->FirstName);
        getline(fin, cur->Next->LastName);
        getline(fin, cur->Next->Gender);
        getline(fin, cur->Next->ID);
        fin >> cur->Next->Dob.Day >> cur->Next->Dob.Month >> cur->Next->Dob.Year;

        cur = cur->Next;
    }

    staffHead = Dummy->Next;

    fin.close();
}
