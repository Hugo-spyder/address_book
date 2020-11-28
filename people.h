//
// Created by 13513 on 2020/11/16.
//

#ifndef ADDRESS_BOOK_PEOPLE_H
#define ADDRESS_BOOK_PEOPLE_H

#include <string>
using std::string;
class People
{
private:
   string name;
   long long telephone;
   string address;
   string mail;
   string unit;
   string comment;
public:
    People(); // default constructor
    People(string & na, long long & num,string & addr , string & mal , string &ut, string &com);
    ~People() = default;
    // methods
    string myname();
    void showpeople() const;
};
// ---------------------
class PeopleBook
{
private:
    // Node
    struct Node{People people; struct Node *next;};
    // private class members
    Node * head;
    Node * tail;
    int peoples; // 总人数
public:
    PeopleBook();
    ~PeopleBook();
    bool isempty() const;
    int peopleCount() const;
    // 查找联系人
    bool haspeople(const string & na);

    void findpeople(const string & na);
    // 增加 删除
    bool addpeople(const People & pl); // add people
    bool delpeople(const string & na);
};
#endif //ADDRESS_BOOK_PEOPLE_H
