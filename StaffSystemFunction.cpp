#include "StaffSystemHeader.h"

void staffSystemProcess() {
    string Path = "Savefile/Staff/";
    string FileName = "AllStaffInfo.txt";

    Staff* AllStaff = nullptr;
    LoadAllStaffData(AllStaff, Path, FileName);


    while(AllStaff) {
        AllStaff->ShowStaffInfo();
        AllStaff = AllStaff->Next;
    }
}
