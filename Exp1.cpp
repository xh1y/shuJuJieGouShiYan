#include <iostream>
#include <cstdlib>
#include <cstring>
#include <iomanip>
using namespace std;

typedef struct {
    char no[20];
    char name[50];
    float price;
} Book;

typedef struct LNode {
    Book data;
    struct LNode* next;
} LNode, * LinkList;

void inputBook(LinkList& a);
void initList(LinkList& a);
void printDetail(LinkList& a);
void part1_add(LinkList& L);
void part2_modify(LinkList& L);
void modify(LinkList& L);
int countNum(LinkList p);
float getAverage(LinkList& L);
void mostExpensive(LinkList L);
void part3_findMax(LinkList L);
void part4_insert(LinkList L);
void insertBook(LinkList& L);
void deleteBook(LinkList& L, int deletePlace);
void part5_deleteBook(LinkList& L);
void part6_findSameBook(LinkList& L);
void findSameBook(LinkList& L);

int main() {
    LinkList L;
    initList(L);
    part1_add(L);
    part2_modify(L);
    part3_findMax(L);
    part4_insert(L);
    part5_deleteBook(L);
    part6_findSameBook(L);
    return 0;
}

void inputBook(LinkList& a) {
    LinkList p = a;
    while (p->next != nullptr) {
        p = p->next;
    }
    Book s;
    while (scanf("%s%s%f", s.no, s.name, &s.price) == 3 && !(strcmp(s.name, "0") == 0 && strcmp(s.no, "0") == 0 && s.price == 0)) {
        p->next = new LNode;
        p = p->next;
        p->data = s;
        p->next = nullptr;
    }
}

void initList(LinkList& a) {
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

void printDetail(LinkList& a) {
    LinkList p = a->next;
    cout.setf(ios_base::fixed, ios_base::floatfield);
    while (p != nullptr) {
        cout << p->data.no << ' ' << p->data.name << " " << setprecision(2) << p->data.price << endl;
        p = p->next;
    }
}

void part1_add(LinkList& L) {
    inputBook(L);
    int count = countNum(L);
    cout << count << endl;
    printDetail(L);
}

void part2_modify(LinkList& L) {
    cout.setf(ios_base::fixed, ios_base::floatfield);
    cout << setprecision(2) << getAverage(L) << endl;
    cout << countNum(L) << endl;
    modify(L);
    printDetail(L);
}

void modify(LinkList& L) {
    float average = getAverage(L);
    LinkList p = L->next;
    while (p != nullptr) {
        if (p->data.price < average) {
            p->data.price *= 1.2;
        }
        else {
            p->data.price *= 1.1;
        }
        p = p->next;
    }
}

float getAverage(LinkList& L) {
    float sum = 0;
    int count = countNum(L);
    LinkList p = L->next;
    while (p != nullptr) {
        sum += p->data.price;
        p = p->next;
    }
    return sum / count;
}

void mostExpensive(LinkList L) {
    LinkList p = L->next;
    int count = 0;
    float maxNum = p->data.price;
    while (p != nullptr) {
        if (maxNum < p->data.price) {
            maxNum = p->data.price;
            count = 1; // Reset count when finding a new maximum price
        }
        else if (maxNum == p->data.price) {
            count++; // Increment count for each occurrence of the maximum price
        }
        p = p->next;
    }
    cout << count << endl;
    p = L->next;
    while (p != nullptr) {
        if (maxNum == p->data.price) {
            cout << p->data.no << ' ' << p->data.name << " " << setprecision(2) << p->data.price << endl;
        }
        p = p->next;
    }
}

void part3_findMax(LinkList L) {
    mostExpensive(L);
}

void part4_insert(LinkList L) {
    insertBook(L);
    cout << countNum(L) << endl;
    printDetail(L);
}

void insertBook(LinkList& L) {
    int insertPlace;
    cin >> insertPlace;
    Book newBook;
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
    }
    else {
        LinkList newElem = new LNode;
        newElem->data = newBook;
        newElem->next = p->next;
        p->next = newElem;
    }
}

// void deleteBook(LinkList& L, int deletePlace) {
//     LinkList p = L;
//     int i = 1;
//     while (p != nullptr && i < deletePlace) {
//         p = p->next;
//         i++;
//     }
//     if (p == nullptr || deletePlace <= 0) {
//         cout << "抱歉，删除位置非法!" << endl;
//         exit(EXIT_FAILURE);
//     }
//     else {
//         LinkList q = p->next;
//         p->next = q->next;
//         delete q;
//     }
// }

void part5_deleteBook(LinkList& L) {
    int deletePlace;
    cin >> deletePlace;
    deleteBook(L, deletePlace);
    printDetail(L);
}

void part6_findSameBook(LinkList& L) {
    findSameBook(L);
    printDetail(L);
}

void findSameBook(LinkList& L) {
    LinkList p = L;
    while (p != nullptr) {
        LinkList q = p->next;
        int Qplace = 2; // 记录 q 在链表中的位置，起始位置为 2
        while (q != nullptr) {
            if (!strcmp(q->data.no, p->data.no)) {
                LinkList temp = q;
                q = q->next; // 移动 q 到下一个节点之前删除 temp
                deleteBook(p, Qplace); // 删除重复的节点
            }
            else {
                q = q->next;
                Qplace++; // 更新 q 的位置
            }
        }
        p = p->next;
    }
}

void deleteBook(LinkList& L, int position) {
    if (L == nullptr || position < 1) {
        cout << "抱歉，删除位置非法!" << endl;
        exit(EXIT_FAILURE);
    }
    // return;

    if (position == 1) { // 删除头节点
        LinkList temp = L;
        L = L->next;
        delete temp;
        return;
    }

    LinkList prev = L;
    for (int i = 2; prev->next != nullptr && i < position; i++) {
        prev = prev->next;
    }

    if (prev->next == nullptr) {
        cout << "抱歉，删除位置非法!" << endl;
        exit(EXIT_FAILURE);
    }
    // return;

    LinkList temp = prev->next;
    prev->next = temp->next;
    delete temp;
}
