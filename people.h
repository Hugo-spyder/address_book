//
// Created by 13513 on 2020/11/16.
//

#ifndef ADDRESS_BOOK_PEOPLE_H
#define ADDRESS_BOOK_PEOPLE_H

#include <string>
#include <iostream>
#include <fstream>
using std::string;
using std::ostream;
using std::istream;
using std::ifstream;
using std::ofstream;
class People
{
private:
   string name;
   string telephone;
   string address;
   string mail;
   string unit;
   string comment;
public:
    People() = default; // default constructor
    ~People() = default;
    // methods
    string getName() const { return name;};
    void setName(string & na) {name = na;}
    void setTele(string & te) {telephone = te;}
    void setAddr(string & ad) {address = ad;}
    void setMail(string & ma) {mail = ma;}
    void setUnit(string & un) {unit = un;}
    void setComm(string & co) {comment = co;}
    // friend function
    friend ostream & operator<<(ostream & os, const People & peo);
    friend ofstream & operator<<(ofstream & of, const People & peo);
    friend istream & operator>>(istream & is, People & peo);
};
// ---------------------
class PeopleBook
{
public:
    // Node
    struct Node{People people; struct Node *next;};
    PeopleBook();
    ~PeopleBook();
    bool isempty() const;
    int peopleCount() const;
    // 查找联系人
    Node * findpeople(const string & na);
    // 增加 删除
    bool addpeople(const People & pl); // add people
    bool delpeople(const string & na);
    // 从文件中读取数据
    void loadData();
    void outData();
    // 显示通讯录
    void showPeopleBk(int nums);
    // 排序
    template <typename T>
    void swap(T & a, T & b);
    Node * partition(Node*pBegin, Node * pEnd);
    void quitSort(Node *pBegin,Node *pEnd);
    bool sort();
private:
    Node * head;
    Node * tail;
    int peoples;
};
#endif //ADDRESS_BOOK_PEOPLE_H
