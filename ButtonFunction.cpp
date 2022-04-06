#include "ButtonHeader.h"

void Button::drawRectangleWithText() {
    const int rectChar = 219;

    gotoxy(X, Y);

    for(int i = X; i <= X + sizeX - 1; i++)
        cout << char(rectChar);

    gotoxy(X, Y + sizeY - 1);

    for(int i = X; i <= X + sizeX - 1; i++)
        cout << char(rectChar);

    for(int i = Y; i <= Y + sizeY - 1; i++) {
        gotoxy(X, i);
        cout << char(rectChar);
        gotoxy(X + sizeX - 1, i);
        cout << char(rectChar);
    }

    int posY = Y + sizeY / 2;
    int posX = X + sizeX / 2 - Text.size() / 2;

    // 4 2
    if(sizeX % 2 == 0 && Text.size() % 2 == 0) {
        gotoxy(posX, posY);
    }
    // 4 1
    if(sizeX % 2 == 0 && Text.size() % 2 == 1) {
        gotoxy(posX - 1, posY);
    }
    // 3 2
    if(sizeX % 2 == 1 && Text.size() % 2 == 0) {
        gotoxy(posX, posY);
    }
    // 3 1
    if(sizeX % 2 == 1 && Text.size() % 2 == 1) {
        gotoxy(posX, posY);
    }

    cout << Text;
}

void addButtonEnd(Button* &buttonHead, Button* addButton) {
    Button* cur = buttonHead;

    if(!cur) {
        buttonHead = addButton;
        return;
    }

    while(cur && cur->Next) cur = cur->Next;

    cur->Next = addButton;
}

bool Button::isInButton(int curX, int curY) {
    return (X <= curX && curX <= X + sizeX - 1 && Y <= curY && curY <= Y + sizeY - 1);
}

void Button::fillRectangle() {
    const int rectChar = 219;

    changeTextColor(color);

    for(int i = X; i <= X + sizeX - 1; i++) {
        for(int j = Y; j <= Y + sizeY - 1; j++) {
            gotoxy(i, j);
            cout << char(rectChar);
        }
    }
}

void Button::fillRectangleWithText(int backgroundColor, int textColor) {
    const int rectChar = 219;

    changeTextColor(backgroundColor);

    for(int i = X; i <= X + sizeX - 1; i++) {
        for(int j = Y; j <= Y + sizeY - 1; j++) {
            gotoxy(i, j);
            cout << char(rectChar);
        }
    }

    SetBGColor(backgroundColor);
    changeTextColor(textColor);

    int posY = Y + sizeY / 2;
    int posX = X + sizeX / 2 - Text.size() / 2;

    if(sizeY % 2 == 0) posY--;

    // 4 2
    if(sizeX % 2 == 0 && Text.size() % 2 == 0) {
        gotoxy(posX, posY);
    }
    // 4 1
    if(sizeX % 2 == 0 && Text.size() % 2 == 1) {
        gotoxy(posX - 1, posY);
    }
    // 3 2
    if(sizeX % 2 == 1 && Text.size() % 2 == 0) {
        gotoxy(posX, posY);
    }
    // 3 1
    if(sizeX % 2 == 1 && Text.size() % 2 == 1) {
        gotoxy(posX, posY);
    }

    cout << Text;

    SetBGColor(0);
    changeTextColor(15);
}
