#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct // 图书编号，名字，价格
{
    char num[20];
    char name[50];
    float price;
} Book;
struct Node {
    Book books;
    struct Node* next;
};
struct Node* createNode(Book x) {
    struct Node* t;
    t = (struct Node*)malloc(sizeof(struct Node));
    t->next = NULL;
    strcpy(t->books.num, x.num);
    strcpy(t->books.name, x.name);
    t->books.price = x.price;
    return t;
}
void init(struct Node** phead) {
    *phead = NULL;
}
void printlist(struct Node* head) {
    int i = 0;
    while (head) {
        printf("%s %s %.2f\n", head->books.num, head->books.name, head->books.price);
        head = head->next;
        i++;
    }
}
int insert(struct Node** phead, int k, Book x) {
    struct Node* p = *phead;
    struct Node* t;
    t = createNode(x);
    if (k < 1)
        return 0;
    else if (k == 1) {
        *phead = t;
        return 1;
    }
    else {
        int count = 1;
        while (p && count < k - 1) {
            p = p->next;
            count++;
        }
    }

    if (p) {
        t->next = p->next;
        p->next = t;
        return 1;
    }
    else
        return 0;
}
int getlength(struct Node* head) {
    int len = 0;
    while (head) {
        len++;
        head = head->next;
    }
    return len;
}
int removeNode(struct Node** phead, int k) {
    if (k < 1) {
        return 0;
    }
    else if (k == 1) {
        if (*phead) {
            *phead = (*phead)->next;
            return 1;
        }
        else
            return 0;
    }
    else {
        struct Node* t;
        struct Node* p;
        p = *phead;
        int count = 1;
        while (p && count < k - 1) {
            p = p->next;
            count++;
        }
        if (p == NULL || p->next == NULL)
            return 0;
        t = p->next;
        p->next = t->next;
        free(t);
        return 1;
    }
}
int main() {
    struct Node* head;
    init(&head);
    Book x;
    int k = 1, a, b;
    while (1) {
        scanf("%s %s %f", x.num, x.name, &x.price);
        if (strcmp(x.name, "0") == 0 && strcmp(x.num, "0") == 0 && x.price == 0)
            break;
        insert(&head, k, x);
        k++;
    }
    scanf("%d", &a);
    if (removeNode(&head, a)) {
        printf("%d\n", getlength(head));
        printlist(head);
    }
    else
        printf("抱歉，出库位置非法!");
    return 0;
}
