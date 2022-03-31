#include "MouseConsoleFunction.h"
#include <bits/stdc++.h>

HANDLE hStdin;
DWORD fdwSaveOldMode;

int checkMouseInButton(int X, int Y, int sizeX, int sizeY)
{
    DWORD cNumRead, fdwMode, i;
    INPUT_RECORD irInBuf[128];
    int counter = 0;

    // Get the standard input handle.

    hStdin = GetStdHandle(STD_INPUT_HANDLE);
    if (hStdin == INVALID_HANDLE_VALUE);

    // Save the current input mode, to be restored on exit.

    if (!GetConsoleMode(hStdin, &fdwSaveOldMode));

    // Enable the window and mouse input events.

    fdwMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT | ENABLE_INSERT_MODE | ENABLE_EXTENDED_FLAGS;
    if (!SetConsoleMode(hStdin, fdwMode));

    // Loop to read and handle the next 500 input events.

    while (1) {
        // Wait for the events.

        if (!ReadConsoleInput(
            hStdin,      // input buffer handle
            irInBuf,     // buffer to read into
            128,         // size of read buffer
            &cNumRead)); // number of records read

        // Dispatch the events to the appropriate handler.

        for (i = 0; i < cNumRead; i++)
        {
            switch (irInBuf[i].EventType)
            {
            case MOUSE_EVENT: // mouse input
                if(MouseEventProc(irInBuf[i].Event.MouseEvent)) {
                    COORD curMouse = irInBuf[i].Event.MouseEvent.dwMousePosition;
                    if(X<= curMouse.X && curMouse.X <= X + sizeX - 1)
                        if(Y <= curMouse.Y && curMouse.Y <= Y + sizeY - 1)
                            return true;
                }
                break;

            default:
                break;
            }
        }
    }

    // Restore input mode on exit.

    SetConsoleMode(hStdin, fdwSaveOldMode);
}

bool MouseEventProc(MOUSE_EVENT_RECORD mer)
{
#ifndef MOUSE_HWHEELED
#define MOUSE_HWHEELED 0x0008
#endif
    if(mer.dwEventFlags == 0) {
        if (mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
            return true;
        }
    }

    return false;
}

