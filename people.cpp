//
// Created by 13513 on 2020/11/16.
//
#include "people.h"
#include <iostream>
// people methods
// constructor
People::People() {
    name = "none";
    telephone = 0;
    address = "none";
    mail = "none";
    unit = "none";
    comment = "none";
}
People::People(string &na, long long &num, string &addr, string &mal, string &ut, string &com) {
    name = na;
    telephone = num;
    address = addr;
    mail = mal;
    unit = ut;
    comment = com;
}
string People::myname() {
    return name;
}

void People::showpeople() const {
    std::cout << "name:" << name << std::endl;
    std::cout << "telephone:" << telephone << std::endl;
    std::cout << "address:" << address << std::endl;
    std::cout << "mail:" << mail << std::endl;
    std::cout << "unit:" << unit << std::endl;
    std::cout << "comment:" << comment << std::endl;
}
 // -------------------------------------------------------------------------------------

 // peopleBook methods
 PeopleBook::PeopleBook() {
    head = tail = nullptr;
    peoples = 0;
}
PeopleBook::~PeopleBook() {
    Node * temp;
    while(head != nullptr)
    {
        temp = head;
        head = head->next;
        delete temp;
    }
}
bool PeopleBook::isempty() const {
    return peoples == 0;
}
int PeopleBook::peopleCount() const {
    return peoples;
}
// add people to people book
bool PeopleBook::addpeople(const People &pl) {
    Node * add = new Node;
    add->people = pl; // 用到了people 类的默认赋值运算符
    add->next = nullptr;
    peoples++;
    if (head == nullptr)
        head = add;
    else
        tail->next = add;
    tail = add;
    return true;
}
// 查找联系人
bool PeopleBook::haspeople(const string &na) {
    if (head == nullptr)
        return false;
    Node * temp = head;
    bool status = false;
    while ((temp->people.myname() != na) && (temp->next != nullptr))
    {
        temp = temp->next;
    }
   if (temp->people.myname() == na)
       status = true;
    return status;
}
void PeopleBook::findpeople(const string &na) {
   if (head == nullptr)
       std::cout << "address book is empty, please add people.\n";
   else
   {
       Node * temp = head;
       while ((temp->people.myname() != na) && (temp->next != nullptr))
           temp = temp->next;
       if (temp->people.myname() == na)
           temp->people.showpeople();
       else
           std::cout << "This address book don't contain a people who called " << na << std::endl;
   }
}
// 依据人名进行删除
bool PeopleBook::delpeople(const string & na) {
    if (head == nullptr)
        return false;
    else
    {
        Node * temp1 = head;
        Node * temp2 = head;
        while((temp1->people.myname() != na) && (temp1->next != nullptr))
        {
            temp2 = temp1;
            temp1 = temp1->next;
        }
        if (temp1->people.myname() == na)
        {
            temp2->next = temp1->next;
            delete temp1;
            return true;
        }
        else
            return false;
    }
}

