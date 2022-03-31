#pragma once

#include <iostream>
#include <windows.h>
#include <conio.h>

using namespace std;

const int midScreen = 60;

void SetBGColor(WORD color);

void clrscr(void);

void gotoxy(short x,short y);

void SetColor(WORD color);

void printAtXY(short x, short y, string Text);

void SetColor(int backgound_color, int text_color);

void drawRectangle(int X, int Y, int sizeX, int sizeY);

void drawRectangleWithText(int X, int Y, int sizeX, int sizeY, string S);

void ShowCur(bool CursorVisibility); // show cursor or not

