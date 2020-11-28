#include <iostream>
#include "User.h"
void showMenu(int);
int signUp();
int signIn();

int main()
{
    // 首先用户登录
    int Select;

    while (true)
    {
        showMenu(1);
        cout << "Select: ";
        cin >> Select;
        if (Select == 1)
        {
            if (signUp())
                break;      // 注册成功，跳出循环
            else
                continue;   // 注册失败，跳出此次循环，继续登录或注册
        }
        else
        {
            if (signIn() == 1)
                break;
            else
                continue;
        }
    }

    return 0;
}

void showMenu(int choose){
    switch (choose)
    {
        case 1:
            cout << "\t\t^**********************^\n";
            cout << "\t\t|     1. Sign up       |\n";
            cout << "\t\t|     2. Sign in       |\n";
            cout << "\t\t^**********************^\n";
            break;
        case 2:
            cout << "\t\t^***********************^\n";
            cout << "\t\t|    1. Query contact   |\n";
            cout << "\t\t|    2. Add contact     |\n";
            cout << "\t\t|    3. Modify contact  |\n";
            cout << "\t\t|    4. Delete contact  |\n";
            cout << "\t\t^***********************^\n";
        default:
            break;
    }
}

int signUp(){
    int state;
    string username;
    string password;
    cout << "Please enter user name:\n";
    cin >> username;
    cout << "Please enter " << username << " password:\n";
    cin >> password;
    User user(username,password);
    return state = user.signUp();
}

int signIn(){
    int state;
    string username;
    string password;
    cout << "Please enter user name:\n";
    cin >> username;
    cout << "Please enter " << username << " password:\n";
    cin >> password;
    User user(username,password);
    return state = user.signIn();
}