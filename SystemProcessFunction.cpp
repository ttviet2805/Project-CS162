#include "SystemProcessHeader.h"

void SystemProcess() {
    staffSystemProcess();
    exit(0);
    ShowCur(0);
    changeTextColor(4);
    Button typeUserButton = Button(30, 5, 60, 5, "Type of User");
    typeUserButton.drawRectangleWithText();

    changeTextColor(11);
    Button studentUser = Button(20, 12, 30, 7, "Student");
    Button staffUser = Button(70, 12, 30, 7, "Staff");

    studentUser.drawRectangleWithText();
    staffUser.drawRectangleWithText();

    COORD mousePos = {0, 0};

    while(1) {
        if(getMousePosition(mousePos)) {
            if(studentUser.isInButton(mousePos.X, mousePos.Y)) {
                loadingFunction(45, 24);
                studentSystemProcess();
            }
            else {
                if(staffUser.isInButton(mousePos.X, mousePos.Y)) {
                   staffSystemProcess();
                }
            }
        }
    }
}
