//
// Created by 13513 on 2020/11/25.
//
#include <iostream>
#include <fstream>
#include <cstdlib>
#include "User.h"

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
        cout << "This user has been used, please sign up again or sign in." << endl;
        return 0;   // 说明用户名被注册过
    }
    else
    {
        writeFile << name << endl;
        writeFile << password << endl;
        writeFile.close();
        cout << "You have sign up successfully!" << endl;
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
            if (password == temp2)
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
            cout << "Password is wrong." << endl;
            return 3; // 3 代表用户名与密码不匹配
        }
        else
        {
            cout << "Sign in successfully." << endl;
            return 1; // 1 登录成功
        }
    }
}
