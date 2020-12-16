//
// Created by 13513 on 2020/11/16.
//
#include "people.h"
#include <iostream>

using std::cin;
using std::cout;
using std::ifstream;
using std::ofstream;

void showMenu() {
    cout << "\t\t^*************************^\n";
    cout << "\t\t|    1. Name              |\n";
    cout << "\t\t|    2. Telephone         |\n";
    cout << "\t\t|    3. Address           |\n";
    cout << "\t\t|    4. Mail              |\n";
    cout << "\t\t|    5. Unit              |\n";
    cout << "\t\t|    6. Comment           |\n";
    cout << "\t\t|    7. Quit              |\n";
    cout << "\t\t^*************************^\n";
}

// friend people
ostream &operator<<(ostream &os, const People &peo) {
    os << "Name: " << peo.name << std::endl;
    os << "Telephone: " << peo.telephone << std::endl;
    os << "Address: " << peo.address << std::endl;
    os << "Mail: " << peo.mail << std::endl;
    os << "Unit: " << peo.unit << std::endl;
    os << "Comment: " << peo.comment << std::endl;
    return os;
}

ofstream &operator<<(ofstream &of, const People &peo) {
    of << peo.name << std::endl;
    of << peo.telephone << std::endl;
    of << peo.address << std::endl;
    of << peo.mail << std::endl;
    of << peo.unit << std::endl;
    of << peo.comment << std::endl;
    return of;
}

istream &operator>>(istream &is, People &peo) {
    cout << "Name:";
    getline(is, peo.name);
    cout << "Telephone:";
    getline(is, peo.telephone);
    cout << "Address:";
    getline(is, peo.address);
    cout << "Mail:";
    getline(is, peo.mail);
    cout << "Unit:";
    getline(is, peo.unit);
    cout << "Comment:";
    getline(is, peo.comment);
    return is;
}
// -------------------------------------------------------------------------------------

// peopleBook methods
PeopleBook::PeopleBook() {
    head = tail = nullptr;
    peoples = 0;
}

PeopleBook::~PeopleBook() {
    Node *temp;
    while (head != nullptr) {
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
    Node *add = new Node;
    add->people = pl; // 用到了people 类的默认赋值运算符 people类没用new 分配内存
    add->next = nullptr;
    peoples++;
    if (head == nullptr)
        head = add;
    else
        tail->next = add;
    tail = add;        // have tail point to new point
    return true;
}

// 查找联系人
PeopleBook::Node *PeopleBook::findpeople(const string &na)
{
    if (isempty())
        std::cout << "address book is empty, please add people.\n";
    else {
        Node *temp = head;
        while ((temp->people.getName() != na) && (temp->next != nullptr))
            temp = temp->next;
        if (temp->people.getName() == na) {
            std::cout << "The people named " << na << " have been find.\n";
            return temp;
        } else
            std::cout << "This address book don't contain a people who called " << na << std::endl;
    }
    return nullptr;
}

// 依据人名进行删除
bool PeopleBook::delpeople(const string &na) {
    if (isempty()) {
        std::cout << "\nAddress book is empty.\n";
        return false;
    } else {
        Node *temp1 = head;
        Node *temp2 = head;
        while ((temp1->people.getName() != na) && (temp1->next != nullptr)) {
            temp2 = temp1;
            temp1 = temp1->next;
        }
        if (temp1->people.getName() == na) {
            temp2->next = temp1->next;
            std::cout << "Delete " << temp1->people.getName() << " successfully.\n";
            delete temp1;
            peoples--;
            return true;
        } else
            std::cout << "Don't have a contact named " << na << std::endl;
        return false;
    }
}

//  从文件读取数据
void PeopleBook::loadData(string file_name) {
    ifstream readFile(file_name);
    if (!readFile.is_open()) {
        ofstream writeFile(file_name);
        return;
    }
    People people;
    int lines = 0;           // 记录所读取的行数
    string temp;
    while (readFile.good()) {
        getline(readFile, temp);
        lines++;
        switch (lines % 6) {
            case 1:
                people.setName(temp);
                break;
            case 2:
                people.setTele(temp);
                break;
            case 3:
                people.setAddr(temp);
                break;
            case 4:
                people.setMail(temp);
                break;
            case 5:
                people.setUnit(temp);
                break;
            case 0:
                people.setComm(temp);
                addpeople(people);
                break;
        }
    }
    readFile.close();
}

void PeopleBook::outData(string file_name) {
    ofstream writeFile(file_name);
    Node *temp = head;
    while (temp != nullptr) {
        writeFile << temp->people;
        temp = temp->next;
    }
    writeFile.close();
}

void PeopleBook::showPeopleBk(int nums) {
    Node *temp = head;
    int order = nums;
    while (nums > 0 && nums < peoples + 1) {
        cout << "# " << order - nums + 1 << std::endl;
        cout << "---------------------------------\n";
        cout << temp->people;
        cout << "---------------------------------\n";
        nums--;
        temp = temp->next;
    }
    if (order < 1)
        cout << "Please enter a integer at least one.\n";
    if (order > peoples)
        cout << "Please enter a integer less than the people total: " << peoples << std::endl;
}

template<typename T>
void PeopleBook::swap(T &a, T &b) {
    T temp = a;
    a = b;
    b = temp;
}

PeopleBook::Node * PeopleBook::partition(PeopleBook::Node *pBegin, PeopleBook::Node *pEnd) {
    auto pivot = pBegin->people.getName();
    Node * p = pBegin;
    Node * q = p->next;
    while (q != pEnd->next)
    {
        if (q->people.getName() < pivot)
        {
            p = p->next;
            swap(p->people,q->people);
        }
        q = q->next;
    }
    swap(p->people,pBegin->people);
    return p;
}

void PeopleBook::quitSort(PeopleBook::Node *pBegin, PeopleBook::Node *pEnd) {
    if (pBegin != pEnd)
    {
        Node * pivot_position = partition(pBegin,pEnd);
        quitSort(pBegin,pivot_position);
        quitSort(pivot_position->next,pEnd);
    }
}

bool PeopleBook::sort() {
    if (peoples < 2)
    {
        cout << "Can't sort because people less than two.\n";
        return false;
    }
    else
    {
        quitSort(head,tail);
        cout << "Sort successfully.";
        return true;
    }
}

void PeopleBook::computeLPSArray(string &pat, int *lps) {
    // length of the previous longest prefix suffix
    int len = 0;

    lps[0] = 0; // lps[0] is always 0
    int M = pat.size();

    // the loop calculates lps[i] for i = 1 to M - 1
    int i = 1;
    while (i < M)
    {
        if (pat[i] == pat[len])
            lps[i++] = ++len;
        else // (pat[i] != pat[len])
        {
            // This is tricky. Consider the example.
            // AAACAAAA and i = 7. The idea is similar
            // to search step.
            if (len != 0)
                len = lps[len - 1];
                // Also, note that we do not increment
                // i here
            else // if (len == 0)
                lps[i++] = 0;
        }

    }
}

int PeopleBook::KMPSearch(string &pat, string &txt) {
    int M = pat.size();
    int N = txt.size();

    // create lps[] that will hold the longest prefix suffix
    // values for pattern
    int lps[M];

    // Preprocess the pattern (calculate lps[] array)
    computeLPSArray(pat,lps);

    int i = 0; // index for txt[]
    int j = 0;  // index for pat[]
    while (i < N)
    {
        if (pat[j] == txt[i]){
            j++;
            i++;
        }

        if (j == M){
            return 1;
            // j = lps[j - 1];
        }

        // mismatch after j matches
        else if (i < N && pat[j] != txt[i]){
            // Do not match lps[0..lps[j-1]] characters,
            // they will match anyway
            if (j != 0)
                j = lps[j - 1];
            else
                i++;
        }
    }
    return 0;
}

void PeopleBook::fuzzyQuery() {
    cout << "Name:\n";
    string pat;
    getline(cin,pat);
    Node * temp = head;
    while (temp != nullptr){
        if (KMPSearch(pat,temp->people.getName()))
            cout << temp->people.getName() << std::endl;
        temp = temp->next;
    }
}

void PeopleBook::addContact() {
        People contact;
        cin >> contact;
        if (findpeople(contact.getName()) != nullptr)
        {
            cout << "There is a people who has a same name in address book.\n";
            return;
        }
        addpeople(contact);
}

void PeopleBook::queryContact() {
        string name;
        cout << "Please enter the name of people who you are finding :\n";
        getline(cin, name);
        PeopleBook::Node *pN = findpeople(name);
        if (pN != nullptr)
            cout << pN->people.getName() << "'s information:\n" << pN->people << endl;

}

void PeopleBook::displayContact() {
        cout << "How many do you want display?(enter a positive integer less than total people): \n";
        int nums;
        while (!(cin >> nums)) {
            cin.clear();
            while (cin.get() != '\n')
                continue;
            cout << "Please enter a number: ";
        }
        showPeopleBk(nums);
}

void PeopleBook::deletContact() {
        cout << "Please enter the name of the people who you want to delete :\n";
        string name;
        getline(cin, name);
        delpeople(name);
}

void PeopleBook::modifyContact() {
        string name;
        cout << "Please enter the name of people who you want modify: \n";
        getline(cin, name);
        PeopleBook::Node *pN = findpeople(name);
        if (pN == nullptr) {
            cout << "Can't find the people whose name is " << name << endl;
        } else {
            cout << endl << pN->people << endl;
            showMenu();
            cout << "What information do you want modify?\n";
            cout << "Choose(from 1 to 7): \n";
            int Choice;
            while (!(cin >> Choice)) {
                cin.clear();
                while (cin.get() != '\n')
                    continue;
                cout << "Please enter a number: \n";
            }
            cin.get();
            if (Choice == 7)
                return;
            string modifyInfo;
            cout << "Please enter your modify:\n";
            getline(cin, modifyInfo);
            switch (Choice) {
                case 1:
                    pN->people.setName(modifyInfo);
                    break;
                case 2:
                    pN->people.setTele(modifyInfo);
                    break;
                case 3:
                    pN->people.setAddr(modifyInfo);
                    break;
                case 4:
                    pN->people.setMail(modifyInfo);
                    break;
                case 5:
                    pN->people.setUnit(modifyInfo);
                    break;
                case 6:
                    pN->people.setComm(modifyInfo);
                    break;
                default:
                    break;
            }
        }
}
