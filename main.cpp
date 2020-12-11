#include "User.h"
#include "people.h"

void showMenu(int);

void queryContact(PeopleBook &);

void addContact(PeopleBook &);

void modifyContact(PeopleBook &);

void deleteContact(PeopleBook &);

void displayContact(PeopleBook &);

void fuzzyQuery(PeopleBook &);

int main() {
    // 首先用户登录
    int Select;
    User user;        // 创建用户对象

    showMenu(1);
    while (true) {
        cout << "Choose(1, 2 or 3): \n";
        while (!(cin >> Select)) {
            cin.clear();
            while (cin.get() != '\n')
                continue;
            cout << "Please enter a number: ";
        }
        cin.get();
        if (Select == 3)
            return 0;
        cin >> user;       // 输入用户的信息：用户名 密码
        if (Select == 1) {
            if (user.signUp())
                break;      // 注册成功，跳出循环
            else
                continue;   // 注册失败，跳出此次循环，继续登录或注册
        } else if (Select == 2) {
            if (user.signIn() == 1)
                break;
            else
                continue;
        }
    }

    // 联系人维护功能
    PeopleBook peopleBook;
    peopleBook.loadData();      // 加载数据

    while (true) {
        cout << endl << user << "'s address book:\n";
        showMenu(2);
        cout << "People total: " << peopleBook.peopleCount() << endl;
        cout << "Choose(from 1 to 6): \n";
        while (!(cin >> Select)) {
            cin.clear();
            while (cin.get() != '\n')
                continue;
            cout << "Please enter a number: \n";
        }
        cin.get();
        switch (Select) {
            case 1:
                queryContact(peopleBook);
                break;
            case 2:
                addContact(peopleBook);
                break;
            case 3:
                modifyContact(peopleBook);
                break;
            case 4:
                deleteContact(peopleBook);
                break;
            case 5:
                displayContact(peopleBook);
                break;
            case 6:
                peopleBook.sort();
                break;
            case 7:
                fuzzyQuery(peopleBook);
                break;
            default:
                break;
        }
        if (Select == 8)
            break;
    }

    peopleBook.outData();  // 将数据导入文件
    return 0;
}

void showMenu(int choose) {
    switch (choose) {
        case 1:
            cout << "\t\t^**********************^\n";
            cout << "\t\t|     1. Sign up       |\n";
            cout << "\t\t|     2. Sign in       |\n";
            cout << "\t\t|     3. Quit          |\n";
            cout << "\t\t^**********************^\n";
            break;
        case 2:
            cout << "\t\t^*************************^\n";
            cout << "\t\t|    1. Query contact     |\n";
            cout << "\t\t|    2. Add contact       |\n";
            cout << "\t\t|    3. Modify contact    |\n";
            cout << "\t\t|    4. Delete contact    |\n";
            cout << "\t\t|    5. Display contacts  |\n";
            cout << "\t\t|    6. Sort              |\n";
            cout << "\t\t|    7. Fuzzy Query       |\n";
            cout << "\t\t|    8. Quit              |\n";
            cout << "\t\t^*************************^\n";
            break;
        case 3:
            cout << "\t\t^*************************^\n";
            cout << "\t\t|    1. Name              |\n";
            cout << "\t\t|    2. Telephone         |\n";
            cout << "\t\t|    3. Address           |\n";
            cout << "\t\t|    4. Mail              |\n";
            cout << "\t\t|    5. Unit              |\n";
            cout << "\t\t|    6. Comment           |\n";
            cout << "\t\t|    7. Quit              |\n";
            cout << "\t\t^*************************^\n";
        default:
            break;
    }
}

void queryContact(PeopleBook &pB) {
    string name;
    cout << "Please enter the name of people who you are finding :\n";
    getline(cin, name);
    PeopleBook::Node *pN = pB.findpeople(name);
    if (pN != nullptr)
        cout << pN->people.getName() << "'s information:\n" << pN->people << endl;
}

void addContact(PeopleBook &pB) {
    People contact;
    cin >> contact;
    if (pB.findpeople(contact.getName()) != nullptr)
    {
        cout << "There is a people who has a same name in address book.\n";
        return;
    }
    pB.addpeople(contact);
}

void deleteContact(PeopleBook &pB) {
    cout << "Please enter the name of the people who you want to delete :\n";
    string name;
    getline(cin, name);
    pB.delpeople(name);
}

void displayContact(PeopleBook &pB) {
    cout << "How many do you want display?(enter a positive integer less than total people): \n";
    int nums;
    while (!(cin >> nums)) {
        cin.clear();
        while (cin.get() != '\n')
            continue;
        cout << "Please enter a number: ";
    }
    pB.showPeopleBk(nums);
}

void modifyContact(PeopleBook &pB) {
    string name;
    cout << "Please enter the name of people who you want modify: \n";
    getline(cin, name);
    PeopleBook::Node *pN = pB.findpeople(name);
    if (pN == nullptr) {
        cout << "Can't find the people whose name is " << name << endl;
    } else {
        cout << endl << pN->people << endl;
        showMenu(3);
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

void fuzzyQuery(PeopleBook & pB)
{
    cout << "Name:\n";
    string name;
    getline(cin,name);
    pB.fuzzyQuery(name);
}
