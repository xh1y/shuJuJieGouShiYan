#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char no[20];
    char name[50];
    float price;
} Book;

typedef struct LNode {
    Book data;
    struct LNode *next;
} LNode, *LinkList;

void inputBook(LinkList *a);
void initList(LinkList* a);

int main(void) {
    LinkList L = (LinkList)malloc(sizeof(LinkList));
    initList(&L);
}

void inputBook(LinkList *a) {
    LinkList p = (LinkList)malloc(sizeof(LinkList));
    LinkList s = (*a)->next;
    while(scanf("%s%s%f", p->data.no, p->data.name, p->data.price) == 3 && !(strcmp(p->data.name, "0") && strcmp(p->data.no, "0") && p->data.price == 0)) {
        
    }
}

void initList(LinkList *a) {
    LinkList p = *a;
    p->next = NULL;
}
