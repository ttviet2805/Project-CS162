#include "SystemProcessHeader.h"

void SystemProcess() {
    ShowCur(0);
    changeTextColor(4);
    Button typeUserButton = Button(30, 3, 60, 5, "Type of User");
    typeUserButton.drawRectangleWithText();

    changeTextColor(11);
    Button studentUser = Button(20, 10, 30, 7, "Student");
    Button staffUser = Button(70, 10, 30, 7, "Staff");
    Button exitButton = Button(52, 19, 16, 5, "Exit");

    studentUser.drawRectangleWithText();
    staffUser.drawRectangleWithText();
    changeTextColor(4);
    exitButton.drawRectangleWithText();

    changeTextColor(11);
    COORD mousePos = {0, 0};

    while(1) {
        if(getMousePosition(mousePos)) {
            if(studentUser.isInButton(mousePos.X, mousePos.Y)) {
                loadingFunction(45, 27);
                studentSystemProcess();
            }
            else {
                if(staffUser.isInButton(mousePos.X, mousePos.Y)) {
                    loadingFunction(45, 27);
                    staffSystemProcess();
                }
                else {
                    if(exitButton.isInButton(mousePos.X, mousePos.Y)) {
                        exit(0);
                    }
                }
            }
        }
    }
}
