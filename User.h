//
// Created by 13513 on 2020/11/25.
//

#ifndef ADDRESS_BOOK_USER_H
#define ADDRESS_BOOK_USER_H

#include <string>
#include <iostream>
#include <fstream>

using namespace std;
class User
{
private:
    string name;
    string password;
    static string filename; // 静态数据成员
public:
    // method
    User()= default;
    User(string & na, string & pwd);
    ~User()= default;
    void setName(string & na) {name = na;}
    void setPass(string & pa) {password = pa;}
    // 注册功能
    int signUp();
    // 登录功能
    int signIn();
    // 友元函数
    friend ostream & operator<< (ostream & os, const User & us) {
        os << us.name;
        return os;
    }
    friend istream & operator>> (istream & is, User & us);
};
#endif //ADDRESS_BOOK_USER_H
