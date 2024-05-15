#include <iostream>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <string>

using namespace std;

typedef struct {
    // char no[20];
    // char name[50];
    string no;
    string name;
    float price;
} Book;

typedef struct LNode {
    Book data;
    struct LNode *next;
} LNode, *LinkList;

void inputBook(LinkList &a);
void initList(LinkList &a);
void printDetail(LinkList &a);
void part1_add(LinkList &L);
void part2_modify(LinkList &L);
void modify(LinkList &L);
int countNum(LinkList p);
float getAverage(LinkList &L);
void part3_findMax(LinkList L);
void part4_insert(LinkList L);
void insertBook(LinkList &L);
void deleteBook(LinkList &L, int deletePlace);
void part5_deleteBook(LinkList &L);
void part6_findSameBook(LinkList &L);
void findSameBook(LinkList &L);

int main() {
    LinkList L;
    initList(L);
    const string choices[] = {
        "新建图书信息表", "修改信息表，将所有低于平均价格的图书价格提高 20 %，所有高于或等于平均价格的图书价格提高10 %",
        "查找最贵的图书", "入库新图书", "旧图书的出库", "图书去重"
    };
    while (true) {
        int s;
        cout << "请输入选择的编号：" << endl;
        for (int i = 0; i < 6; i++) {
            cout << i + 1 << ": " << choices[i] << endl;
        }
        cout << "0: 退出" << endl;
        cin >> s;
        system("cls");
        switch (s) {
        case 0:
            goto Last;
            break;
        case 1:
            part1_add(L);
            break;
        case 2:
            part2_modify(L);
            break;
        case 3:
            part3_findMax(L);
            break;
        case 4:
            part4_insert(L);
            break;
        case 5:
            part5_deleteBook(L);
            break;
        case 6:
            part6_findSameBook(L);
            break;
        default:
            break;
        }
        system("pause");
        system("cls");
    }
Last:
    return 0;
}

void inputBook(LinkList &a) {
    LinkList p = a;
    while (p->next != nullptr) {
        p = p->next;
    }
    Book s;
    while ((cin >> s.no >> s.name >> s.price) && !(s.name.compare("0") == 0 && s.no.compare("0") == 0 && s.price == 0)) {
        p->next = new LNode;
        p = p->next;
        p->data = s;
        p->next = nullptr;
    }
}

void initList(LinkList &a) {
    a = new LNode;
    a->next = nullptr;
}

int countNum(LinkList p) {
    int count = 0;
    while (p->next != nullptr) {
        p = p->next;
        count++;
    }
    return count;
}

void printDetail(LinkList &a) {
    if (!a && !a->next) {
        cerr << "空表" << endl;
        return;
    }
    LinkList p = a->next;
    cout.setf(ios_base::fixed, ios_base::floatfield);
    cout << setw(15) << setfill(' ') << left << "书号" << ' ' << setw(15) << setfill(' ') << "  书名" << "     " << setw(5) << "价格" << endl;
    while (p != nullptr) {
        cout << setw(15) << setfill(' ') << left << p->data.no << ' ' << setw(15) << setfill(' ') << p->data.name << " " << setw(5) << setprecision(2) << p->data.price << endl;
        p = p->next;
    }
}

void part1_add(LinkList &L) {
    cout << "请输入图书的书号、书名和价格，输入0 0 0结束输入" << endl;
    inputBook(L);
    system("cls");
    int count = countNum(L);
    cout << "图书总数：" << countNum(L) << endl;
    printDetail(L);
}

void part2_modify(LinkList &L) {
    cout.setf(ios_base::fixed, ios_base::floatfield);
    cout << "平均价格：" << setprecision(2) << getAverage(L) << endl;
    cout << "图书总数：" << countNum(L) << endl;
    modify(L);
    printDetail(L);
}

void modify(LinkList &L) {
    float average = getAverage(L);
    LinkList p = L->next;
    while (p != nullptr) {
        if (p->data.price < average) {
            p->data.price *= 1.2;
        } else {
            p->data.price *= 1.1;
        }
        p = p->next;
    }
}

float getAverage(LinkList &L) {
    float sum = 0;
    int count = countNum(L);
    LinkList p = L->next;
    while (p != nullptr) {
        sum += p->data.price;
        p = p->next;
    }
    return sum / count;
}

void part3_findMax(LinkList L) {
    LinkList p = L->next;
    int count = 0;
    float maxNum = p->data.price;
    while (p != nullptr) {
        if (maxNum < p->data.price) {
            maxNum = p->data.price;
            count = 1;
        } else if (maxNum == p->data.price) {
            count++;
        }
        p = p->next;
    }
    cout << "最贵图书共" << count << "本" << endl;
    cout << setw(15) << setfill(' ') << left << "书号" << ' ' << setw(15) << setfill(' ') << "  书名" << "     " << setw(5) << "价格" << endl;

    p = L->next;
    while (p != nullptr) {
        if (maxNum == p->data.price) {
            cout << setw(15) << setfill(' ') << left << p->data.no << ' ' << setw(15) << setfill(' ') << p->data.name << " " << setw(5) << setprecision(2) << p->data.price << endl;
        }
        p = p->next;
    }
}

void part4_insert(LinkList L) {
    insertBook(L);
    cout << "图书总数：" << countNum(L) << endl;
    printDetail(L);
}

void insertBook(LinkList &L) {
    int insertPlace;
    cout << "请输入插入图书的位置：" << endl;
    cin >> insertPlace;
    Book newBook;
    cout << "请输入插入图书的书号、书名和价格" << endl;
    cin >> newBook.no >> newBook.name >> newBook.price;
    LinkList p = L;
    int i = 1;
    while (p != nullptr && i < insertPlace) {
        p = p->next;
        i++;
    }
    if (p == nullptr || insertPlace <= 0) {
        cout << "抱歉，入库位置非法!" << endl;
        exit(EXIT_FAILURE);
    } else {
        LinkList newElem = new LNode;
        newElem->data = newBook;
        newElem->next = p->next;
        p->next = newElem;
    }
}

void part5_deleteBook(LinkList &L) {
    int deletePlace;
    cout << "请输入删除图书的位置：" << endl;
    cin >> deletePlace;
    deleteBook(L, deletePlace);
    cout << "图书总数：" << countNum(L) << endl;
    printDetail(L);
}

void part6_findSameBook(LinkList &L) {
    findSameBook(L);
    cout << "图书总数：" << countNum(L) << endl;
    printDetail(L);
}

void findSameBook(LinkList &L) {
    LinkList p = L;
    while (p != nullptr && p->next) {
        auto q = p;
        while (q->next != nullptr) {
            if (q->next->data.no.compare(p->data.no) == 0) {
                LinkList t = q->next;
                q->next = t->next;
                delete t;
            } else {
                q = q->next;
            }
        }
        p = p->next;
    }
}

void deleteBook(LinkList &L, int position) {
    if (L == nullptr || position < 1) {
        cout << "抱歉，删除位置非法!" << endl;
        exit(EXIT_FAILURE);
    }

    if (position == 1) {
        LinkList t = L;
        L = L->next;
        delete t;
        return;
    }

    LinkList p = L->next;
    for (int i = 2; p->next != nullptr && i < position; i++) {
        p = p->next;
    }

    if (p->next == nullptr) {
        cout << "抱歉，删除位置非法!" << endl;
        exit(EXIT_FAILURE);
    }

    LinkList t = p->next;
    p->next = t->next;
    delete t;
}