#include "User.h"
#include "people.h"
#include <windows.h>
#include <conio.h>
#define red 12
#define white 7

void color(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),color);
}
void gotoxy(int x, int y)
{
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}

int main() {
    // 首先用户登录
    User user;        // 创建用户对象

    int Set[3] = {red,white,white};
    int counter = 1;
    char key;

    system("cls");
    for(int i;;)
    {
        gotoxy(10,5);
        color(Set[0]);
        cout << "1. Login ";

        gotoxy(10,6);
        color(Set[1]);
        cout << "2. Register ";

        gotoxy(10,7);
        color(Set[2]);
        cout << "3. Quit ";

        key = _getch();

        if(key == 72 && (counter >= 2 && counter <= 3))    // 72 up arrow
        {
            counter--;
        }

        if(key == 80 && (counter <= 2 && counter >= 1))   // 80 down arrow
        {
            counter++;
        }

        if(key == '\r')
        {
            if(counter == 1)
            {
                gotoxy(0,8);
                cin >> user;
                if(user.signIn() == 1)
                    break;
                else
                    continue;
            }
            if(counter == 2)
            {
                gotoxy(0,8);
                cin >> user;
                if (user.signUp())
                    break;      // 注册成功，跳出循环
                else
                    continue;   // 注册失败，跳出此次循环，继续登录或注册
            }
            if(counter == 3)
            {
                system("cls");
                color(white);
                return 0;
            }
        }
        // default color
        Set[0] = white;
        Set[1] = white;
        Set[2] = white;
        if (counter == 1)
            Set[0] = red;
        if (counter == 2)
            Set[1] = red;
        if (counter == 3)
            Set[2] = red;
    }
    color(white);

    // 联系人维护功能
    PeopleBook peopleBook;
    peopleBook.loadData(user.getDataFile());      // 加载数据
    int opt[8] = {red,white,white,white,white,white,white,white};
    counter = 1;

    system("cls");
    for(int i;;)
    {
        gotoxy(10,5);
        color(opt[0]);
        cout << "1. Query contact ";

        gotoxy(10,6);
        color(opt[1]);
        cout << "2. Add contact ";

        gotoxy(10,7);
        color(opt[2]);
        cout << "3. Modify contact ";

        gotoxy(10,8);
        color(opt[3]);
        cout << "4. Delete contact ";

        gotoxy(10,9);
        color(opt[4]);
        cout << "5. Display contacts ";

        gotoxy(10,10);
        color(opt[5]);
        cout << "6. Sort ";

        gotoxy(10,11);
        color(opt[6]);
        cout << "7. Fuzzy Query ";

        gotoxy(10,12);
        color(opt[7]);
        cout << "8. Quit ";

        color(white);
        cout << endl << peopleBook.peopleCount() << " totally people have.";

        key = _getch();

        if(key == 72 && (counter >= 2 && counter <= 8))    // 72 up arrow
        {
            counter--;
        }

        if(key == 80 && (counter <= 7 && counter >= 1))   // 80 down arrow
        {
            counter++;
        }

        if(key == '\r')
        {
            system("cls");
            switch (counter) {
                case 1:
                    peopleBook.queryContact();
                    break;
                case 2:
                    peopleBook.addContact();
                    break;
                case 3:
                    peopleBook.modifyContact();
                    break;
                case 4:
                    peopleBook.deletContact();
                    break;
                case 5:
                    peopleBook.displayContact();
                    break;
                case 6:
                    peopleBook.sort();
                    break;
                case 7:
                    peopleBook.fuzzyQuery();
                    break;
                default: break;
            }
            if(counter == 8)
            {
                system("cls");
                break;
            }
            system("pause");
            system("cls");
        }
        // default color
        for(int & j : opt)
            j = white;

        switch (counter)
        {
            case 1: opt[0] = red; break;
            case 2: opt[1] = red; break;
            case 3: opt[2] = red; break;
            case 4: opt[3] = red; break;
            case 5: opt[4] = red; break;
            case 6: opt[5] = red; break;
            case 7: opt[6] = red; break;
            case 8: opt[7] = red; break;
            default: break;
        }
    }
    peopleBook.outData(user.getDataFile());
    color(white);
    return 0;
}
