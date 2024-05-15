#include <iostream>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <string>

using namespace std;

typedef struct {
    string no;
    string name;
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
    const string choices[] = {
        "�½�ͼ����Ϣ��", "�޸���Ϣ�������е���ƽ���۸��ͼ��۸���� 20 %�����и��ڻ����ƽ���۸��ͼ��۸����10 %",
        "��������ͼ��", "�����ͼ��", "��ͼ��ĳ���", "ͼ��ȥ��"
    };
    while (true) {
        int s;
        cout << "������ѡ��ı�ţ�" << endl;
        for (int i = 0; i < 6; i++) {
            cout << i + 1 << ": " << choices[i] << endl;
        }
        cout << "0: �˳�" << endl;
        cin >> s;
        system("cls");
        try {
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
        } catch (const char* e) {
            cerr << e << endl;
        }
        system("pause");
        system("cls");
    }
Last:
    return 0;
}

void inputBook(LinkList& a) {
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
    if (!a && !a->next) {
        cerr << "�ձ�" << endl;
        return;
    }
    LinkList p = a->next;
    cout.setf(ios_base::fixed, ios_base::floatfield);
    cout << setw(15) << setfill(' ') << left << "���" << ' ' << setw(15) << setfill(' ') << "  ����" << "     " << setw(5) << "�۸�" << endl;
    while (p != nullptr) {
        cout << setw(15) << setfill(' ') << left << p->data.no << ' ' << setw(15) << setfill(' ') << p->data.name << " " << setw(5) << setprecision(2) << p->data.price << endl;
        p = p->next;
    }
}

void part1_add(LinkList& L) {
    cout << "������ͼ�����š������ͼ۸�����0 0 0��������" << endl;
    inputBook(L);
    system("cls");
    int count = countNum(L);
    cout << "ͼ��������" << countNum(L) << endl;
    printDetail(L);
}

void part2_modify(LinkList& L) {
    cout.setf(ios_base::fixed, ios_base::floatfield);
    cout << "ƽ���۸�" << setprecision(2) << getAverage(L) << endl;
    cout << "ͼ��������" << countNum(L) << endl;
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

void part3_findMax(LinkList L) {
    if(!L) {
        cout << "û�����ݣ�" << endl;
        throw "No data";
    }
    LinkList p = L->next;
    int count = 0;
    float maxNum = p->data.price;
    while (p != nullptr) {
        if (maxNum < p->data.price) {
            maxNum = p->data.price;
            count = 1;
        }
        else if (maxNum == p->data.price) {
            count++;
        }
        p = p->next;
    }
    cout << "���ͼ�鹲" << count << "��" << endl;
    cout << setw(15) << setfill(' ') << left << "���" << ' ' << setw(15) << setfill(' ') << "  ����" << "     " << setw(5) << "�۸�" << endl;

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
    cout << "ͼ��������" << countNum(L) << endl;
    printDetail(L);
}

void insertBook(LinkList& L) {
    if (!L) {
        cout << "û�����ݣ�" << endl;
        throw "No data";
    }
    int insertPlace;
    cout << "���������ͼ���λ�ã�" << endl;
    cin >> insertPlace;
    Book newBook;
    cout << "���������ͼ�����š������ͼ۸�" << endl;
    cin >> newBook.no >> newBook.name >> newBook.price;
    LinkList p = L;
    int i = 1;
    while (p != nullptr && i < insertPlace) {
        p = p->next;
        i++;
    }
    if (p == nullptr || insertPlace <= 0) {
        cout << "��Ǹ�����λ�÷Ƿ�!" << endl;
        exit(EXIT_FAILURE);
    }
    else {
        LinkList newElem = new LNode;
        newElem->data = newBook;
        newElem->next = p->next;
        p->next = newElem;
    }
}

void part5_deleteBook(LinkList& L) {
    if (!L) {
        cout << "û�����ݣ�" << endl;
        throw "No data";
    }
    int deletePlace;
    cout << "������ɾ��ͼ���λ�ã�" << endl;
    cin >> deletePlace;
    deleteBook(L, deletePlace);
    cout << "ͼ��������" << countNum(L) << endl;
    printDetail(L);
}

void part6_findSameBook(LinkList& L) {
    findSameBook(L);
    cout << "ͼ��������" << countNum(L) << endl;
    printDetail(L);
}

void findSameBook(LinkList& L) {
    if (!L) {
        cout << "û�����ݣ�" << endl;
        throw "No data";
    }
    LinkList p = L;
    while (p != nullptr && p->next) {
        auto q = p;
        while (q->next != nullptr) {
            if (q->next->data.no.compare(p->data.no) == 0) {
                LinkList t = q->next;
                q->next = t->next;
                delete t;
            }
            else {
                q = q->next;
            }
        }
        p = p->next;
    }
}

void deleteBook(LinkList& L, int position) {
    if (!L) {
        cout << "û�����ݣ�" << endl;
        throw "No data";
    }
    if (L == nullptr || position < 1) {
        cout << "��Ǹ��ɾ��λ�÷Ƿ�!" << endl;
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
        cout << "��Ǹ��ɾ��λ�÷Ƿ�!" << endl;
        exit(EXIT_FAILURE);
    }

    LinkList t = p->next;
    p->next = t->next;
    delete t;
}