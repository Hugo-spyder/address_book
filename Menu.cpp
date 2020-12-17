//
// Created by 13513 on 2020/12/17.
//
#include "Menu.h"
#include <iostream>

void Menu::color(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),color);
}
void Menu::gotoxy(int x, int y)
{
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}

void Menu::show() {
    int h = x;
    int v = y;
    for(int i=0; i < opt_num; i++)
    {
        gotoxy(h,v++);
        color(colSet[i]);
        cout << options[i];
    }
}

Menu::Menu(const char** opt, const int *col,int num) {
    opt_num = num;
    counter = 1;
    for(int i=0;i<num;i++) {
        options[i] = opt[i];
        colSet[i] = col[i];
    }
}

void Menu::setColor(int coun,int color) {
    colSet[(coun - 1)] = color;
}

int Menu::select(){
    char key = _getch();
    if(key == 72)    // 72 up arrow
    {
        if(counter == 1)
            counter = opt_num;
        else
            counter--;
        return key;
    }
    if(key == 80)    // down
    {
        if(counter == opt_num)
            counter = 1;
        else
            counter++;
        return key;
    }
    if(key == '\r')
        return key;
}
