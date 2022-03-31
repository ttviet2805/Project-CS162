#include "ConsoleSolve.h"

void SetColor(int backgound_color, int text_color)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

    int color_code = backgound_color * 16 + text_color;
    SetConsoleTextAttribute(hStdout, color_code);
}

void SetBGColor(WORD color)
{
	HANDLE hConsoleOutput;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
	GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);

	WORD wAttributes = screen_buffer_info.wAttributes;
	color &= 0x000f;
	color <<= 4;
	wAttributes &= 0xff0f;
	wAttributes |= color;

	SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}

void clrscr(void)
{
	system("cls");
}

void gotoxy(short x,short y)
{
	HANDLE hConsoleOutput;
	COORD Cursor_an_Pos = { x,y};
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput , Cursor_an_Pos);
}

void printAtXY(short x, short y, string Text) {
    gotoxy(x, y);
    cout << Text << ' ';
}

void SetColor(WORD color)
{
	HANDLE hConsoleOutput;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
	GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);

	WORD wAttributes = screen_buffer_info.wAttributes;
	color &= 0x000f;
	wAttributes &= 0xfff0;
	wAttributes |= color;

	SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}

void drawRectangle(int X, int Y, int sizeX, int sizeY) {
	gotoxy(X, Y);

	for(int i = X; i <= X + sizeX - 1; i++) cout << char(219);

	gotoxy(X, Y + sizeY - 1);

	for(int i = X; i <= X + sizeX - 1; i++) cout << char(219);

	for(int i = Y; i <= Y + sizeY - 1; i++) {
		gotoxy(X, i);
		cout << char(219);
	}

	for(int i = Y; i <= Y + sizeY - 1; i++) {
		gotoxy(X + sizeX - 1, i);
		cout << char(219);
	}
}

void drawRectangleWithText(int X, int Y, int sizeX, int sizeY, string S) {
    drawRectangle(X, Y, sizeX, sizeY);

    int middlePointX = X + sizeX / 2 - 1, middlePointY = Y + sizeY / 2;

    if(sizeX % 2 == 0) {
        if(S.size() % 2 == 0)
            gotoxy(middlePointX - S.size() / 2 + 1, middlePointY);
        else
            gotoxy(middlePointX - S.size() / 2, middlePointY);
    }
    else
        gotoxy(middlePointX - S.size() / 2 + 1, middlePointY);
    cout << S;
}

void ShowCur(bool CursorVisibility)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO ConCurInf;

    ConCurInf.dwSize = 10;
    ConCurInf.bVisible = CursorVisibility;

    SetConsoleCursorInfo(handle, &ConCurInf);
}
