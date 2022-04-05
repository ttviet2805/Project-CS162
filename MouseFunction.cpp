#include "MouseHeader.h"

bool isLeftMouseClick(MOUSE_EVENT_RECORD mer)
{
#ifndef MOUSE_HWHEELED
#define MOUSE_HWHEELED 0x0008
#endif
    if(mer.dwEventFlags == 0)
        if (mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) return true;

    return false;
}

bool getMousePosition(COORD& mousePos) {
    HANDLE hStdin;
    DWORD fdwSaveOldMode;

    DWORD cNumRead, fdwMode, i;
    INPUT_RECORD irInBuf[128];

    hStdin = GetStdHandle(STD_INPUT_HANDLE);

    if (!GetConsoleMode(hStdin, &fdwSaveOldMode));

    fdwMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT | ENABLE_INSERT_MODE | ENABLE_EXTENDED_FLAGS;
    if (!SetConsoleMode(hStdin, fdwMode));

    if (!ReadConsoleInput(hStdin, irInBuf, 128, &cNumRead));

    for (i = 0; i < cNumRead; i++)
    {
        if(irInBuf[i].EventType == MOUSE_EVENT) {
            if(isLeftMouseClick(irInBuf[i].Event.MouseEvent)) {
                COORD mousePosition = irInBuf[i].Event.MouseEvent.dwMousePosition;
                int X = mousePosition.X, Y = mousePosition.Y;
                mousePos = {X, Y};
                return true;
            }
        }
    }

    SetConsoleMode(hStdin, fdwSaveOldMode);

    return false;
}
