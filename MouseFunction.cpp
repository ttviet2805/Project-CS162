#include "MouseHeader.h"

HANDLE hStdin;
DWORD fdwSaveOldMode;

void mouseClickButton() {
    DWORD cNumRead, fdwMode, i;
    INPUT_RECORD irInBuf[128];

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

        if (!ReadConsoleInput(hStdin, irInBuf, 128, &cNumRead));

        // Dispatch the events to the appropriate handler.

        for (i = 0; i < cNumRead; i++)
        {
            switch (irInBuf[i].EventType)
            {
                case MOUSE_EVENT: // mouse input
                    COORD mousePosition = irInBuf[i].Event.MouseEvent.dwMousePosition;
//                    MouseEventProc(irInBuf[i].Event.MouseEvent);
                    int X = mousePosition.X, Y = mousePosition.Y;
//                    std::cout << X << ' ' << Y << endl;

                    break;
            }
        }
    }

    // Restore input mode on exit.

    SetConsoleMode(hStdin, fdwSaveOldMode);
}

bool isLeftMouseClick(MOUSE_EVENT_RECORD mer)
{
#ifndef MOUSE_HWHEELED
#define MOUSE_HWHEELED 0x0008
#endif
    if(mer.dwEventFlags == 0) {
        if (mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
        {
            return true;
        }
    }

    return false;
}
