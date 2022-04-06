#pragma once

#include <iostream>

using namespace std;

#include "ConsoleSolve.h"

class Button {
public:
    int X, Y, sizeX, sizeY;
    string Text;
    int color;

    Button* Next = nullptr;

    Button(int _X, int _Y, int _sizeX, int _sizeY, string _Text) {
        X = _X, Y = _Y, sizeX = _sizeX, sizeY = _sizeY;
        Text = _Text;
        color = 15;
    }

    void drawRectangleWithText();

    bool isInButton(int curX, int curY);

    void fillRectangle();

    void fillRectangleWithText(int backgroundColor, int textColor);
};

void addButtonEnd(Button* &buttonHead, Button* addButton);
