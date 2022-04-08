#pragma once

#include <iostream>
#include <windows.h>
#include <conio.h>

using namespace std;

const int midScreen = 60;

void SetBGColor(WORD color);

void clrscr(void);

void gotoxy(short x,short y);

void changeTextColor(WORD color);

void printAtXY(short x, short y, string Text);

void printATXYWithBackGround(short x, short y, int backgroundColor, int textColor, string Text);

void SetColor(int backgound_color, int text_color);

void ShowCur(bool CursorVisibility); // show cursor or not

void loadingFunction(int X, int Y);

/*

0 = Black
1 = Blue
2 = Green
3 = Aqua
4 = Red
5 = Purple
6 = Yellow
7 = White
8 = Gray
9 = Light Blue
10 = Light Green
11 = Light Aqua
12 = Light Red
13 = Light Purple
14 = Light Yellow
15 = Bright White
*/
