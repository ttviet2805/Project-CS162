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

    gotoxy(posX, posY);
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
