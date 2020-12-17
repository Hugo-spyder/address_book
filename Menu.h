//
// Created by 13513 on 2020/12/16.
//

#ifndef ADDRESS_BOOK_MENU_H
#define ADDRESS_BOOK_MENU_H

#include <windows.h>
#include <conio.h>

#define red 12
#define white 7

using namespace std;

class Menu {
public:
    Menu() = default;
    Menu(const char** opt, const int* color,int num);
    ~Menu() = default;
    void color(int color);
    void gotoxy(int x,int y);
    void show();
    int select();
    void setColor(int coun,int color);
    int getCont() { return counter;}

private:
    enum {Opt=10,x=10,y=5};
    const char* options[Opt]{};
    int colSet[Opt]{};
    int counter;
    int opt_num;
};

#endif //ADDRESS_BOOK_MENU_H
