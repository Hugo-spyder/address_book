#include "User.h"
#include "people.h"
#include "Menu.h"
#define red 12
#define white 7

int main() {
    // 首先用户登录
    User user;        // 创建用户对象

    const char * Option1[10] = {"1. Login ","2. Register ","3. Exit "};
    int Color1[10] = {12,7,7};
    Menu menu1(Option1,Color1,3);  // 创建菜单
    system("cls"); // 清空屏幕
    menu1.show();

    while (true)
    {
        menu1.setColor(menu1.getCont(),white); // 未选择之前
        int key = menu1.select();
        menu1.setColor(menu1.getCont(),red);   // 选择之后
        menu1.show();
        if(key == '\r')
        {
            system("cls");
            if(menu1.getCont() == 1)
            {
                cin >> user;
                if(user.signIn() == 1)
                    break;
                else
                    continue;
            }
            if(menu1.getCont() == 2)
            {
                cin >> user;
                if (user.signUp())
                    break;      // 注册成功，跳出循环
                else
                    continue;   // 注册失败，跳出此次循环，继续登录或注册
            }
            if(menu1.getCont() == 3)
            {
                menu1.color(white);
                return 0;
            }
        }
    }
    menu1.color(white);
    system("pause");

    // 联系人维护功能
    PeopleBook peopleBook;
    peopleBook.loadData(user.getDataFile());      // 加载数据
    const char * Option2[10] = {"1. Query contact ","2. Add contact ","3. Modify contact ",
                                "4. Delete contact ","5. Display contacts ","6. Sort ","7. Fuzzy Query ","8. Exit "};
    int color2[8] = {red,white,white,white,white,white,white,white};
    Menu menu2(Option2,color2,8); // 创建菜单
    system("cls");           // 清空屏幕
    while (true)
    {
        menu2.show();
        menu2.color(white);
        cout << endl << peopleBook.peopleCount() << " totally people have.";
        menu2.setColor(menu2.getCont(),white); // 未选择之前
        int key = menu2.select();
        menu2.setColor(menu2.getCont(),red);   // 选择之后
        menu2.show();
        menu2.color(white);
        cout << endl << peopleBook.peopleCount() << " totally people have.";

        if(key == '\r')
        {
            system("cls");
            switch (menu2.getCont()) {
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
            if(menu2.getCont() == 8)
            {
                system("cls");
                break;
            }
            system("pause");
            system("cls");
        }
    }
    peopleBook.outData(user.getDataFile());  // 将数据输入文件
    menu2.color(white);
    system("cls");
    return 0;
}
