#pragma once

#include <windows.h>
#include <tchar.h>
#include <stdio.h>

bool MouseEventProc(MOUSE_EVENT_RECORD);

int checkMouseInButton(int X, int Y, int sizeX, int sizeY);
