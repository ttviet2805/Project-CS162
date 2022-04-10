#include "StaffHeader.h"

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
