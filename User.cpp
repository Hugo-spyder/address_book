//
// Created by 13513 on 2020/11/25.
//
#include <iostream>
#include <cstdlib>
#include <conio.h>
#include "User.h"
#include "MD5.h"

string User::filename = "UserInfo.txt";
User::User(string &na, string &pwd)  {
    name = na;
    password = pwd;
}

int User::signUp() {
    ofstream writeFile(filename.c_str(), ios::out | ios::app);
    ifstream readFile(filename.c_str());
    int flag = 0;
    // 检测是否有重复账户
    int lines = 0; // 记录所读取的行数
    string temp;
    while(readFile.good())
    {
        getline(readFile,temp);
        lines++;
        if (lines % 2 == 0) continue; // 密码行跳过
        if (temp == name) flag = 1; // 说明用户名已被注册过
    }
    readFile.close();
    if (flag)
    {
        cout << "This user "<< name << " has been registered, please register again or login." << endl;
        return 0;   // 说明用户名被注册过
    }
    else
    {
        writeFile << name << endl;
        writeFile << MD5(password).toStr() << endl;
        writeFile.close();
        cout << name << " have registered successfully!" << endl;
        return 1;   // 注册成功
    }
}

int User::signIn() {
    ifstream readFile(filename.c_str());
    if (!readFile.is_open())
    {
        cout << "Couldn't open the file UserInfo.txt\n";
        cout << "Program terminating.\n";
        exit(EXIT_FAILURE);
    }
    string temp1;
    string temp2;
    int exitName = 0;
    int match = 0;
    while (readFile.good())
    {
        getline(readFile,temp1);
        getline(readFile,temp2);
        if (name == temp1)
        {
            exitName = 1;
            if (MD5(password).toStr() == temp2)
            {
                match = 1;
                break;
            }
        }
    }
    readFile.close();
    if (!exitName) {
        cout << "Don't have this user name." << endl;
        return 2;// 2 代表没有此用户名
    }
    else{
        if (!match)
        {
            cout << "Password or username is wrong." << endl;
            return 3; // 3 代表用户名与密码不匹配
        }
        else
        {
            cout << endl << name << " login successfully." << endl;
            return 1; // 1 登录成功
        }
    }
}

// friend function
istream & operator>> (istream & is, User & us)
{
    cout << "Please enter user name:\n";
    getline(is,us.name);
    us.dataFile = us.name + "Data.txt";
    cout << "Please enter " << us.name << "'s password:\n";
    char ch;
    int index = 0;
    while (true){
        ch = _getch();
        if (ch == 8)  // 8 退格键
        {
            if(index != 0){
                cout << char(8) << " " << char(8);
                us.password.erase(us.password.begin() + (--index));
            }
        }
        else if (ch == '\r'){
            break;
        }
        else{
            cout << "*" ;
            us.password += ch;
            index++;
        }
    }
    return is;
}
