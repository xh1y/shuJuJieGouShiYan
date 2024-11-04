#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Stack {
    char data;
    struct Stack* next;
} Stack, *LinkStack;

void initStack(LinkStack* a) {
    LinkStack p = (LinkStack)malloc(sizeof(Stack));
    p->next = NULL;
    a = &p;
}

void push(LinkStack a, char x) {
    LinkStack t = (LinkStack)malloc(sizeof(struct Stack));
    t->data = x;
    t->next = a->next;
    a->next = t;
}

void pop(LinkStack a) {
    LinkStack p = a->next;
    a->next = p->next;
    free(p);
}

char getTop(LinkStack a) {
    return a->next->data;
}

int getIndex(char t) {
    int index = 0;
    switch (t) {
    case '+':
        index = 0;
        break;
    case '-':
        index = 1;
        break;
    case '*': index = 2;
        break;
    case '/':
        index = 3;
        break;
    case '(':
        index = 4;
        break;
    case ')':
        index = 5;
        break;
    case '#':
    case '=':
        index = 6;
        break;
    default: break;
    }
    return index;
}

char compare(LinkStack a, char n) {
    char p = getTop(a);
    const char priority[][7] = {
        {'>', '>', '<', '<', '<', '>', '>'},
        {'>', '>', '<', '<', '<', '>', '>'},
        {'>', '>', '>', '>', '<', '>', '>'},
        {'>', '>', '>', '>', '<', '>', '>'},
        {'<', '<', '<', '<', '<', '=', '0'},
        {'>', '>', '>', '>', '0', '>', '>'},
        {'<', '<', '<', '<', '<', '0', '='}
    };
    int index1 = getIndex(getTop(a));
    int index2 = getIndex(n);
    return priority[index1][index2];
}

char calculate(char a, char b, char op) {
    switch (op) {
    case '+':
        return a + b - 48;
    case '-':
        return a - b + 48;
    case '*':
        return (a - 48) * (b - 48) + 48;
    case '/':
        return (a - 48) / (b - 48) + 48;
    }
    return 0;
}

void getOneStringResult(char s[]) {
    LinkStack opnd = (LinkStack)malloc(sizeof(struct Stack));
    LinkStack optr = (LinkStack)malloc(sizeof(struct Stack));
    initStack(&opnd);
    initStack(&optr);
    push(optr, '#');
    int i = 0;
    char n;
    while (i < strlen(s)) {
        char n = s[i];
        if (n >= '0' && n <= '9') {
            push(opnd, n);
            i++;
        } else if (n == '+' || n == '-' || n == '*' || n == '/' || n == '#' || n == '(' || n == ')' || n == '=') {
            char m = compare(optr, n);
            if (m == '<') {
                push(optr, n);
                i++;
            } else if (m == '>') {
                char p = getTop(opnd);
                pop(opnd);
                char q = getTop(opnd);
                pop(opnd);
                char m = getTop(optr);
                pop(optr);
                char b = calculate(q, p, m);
                push(opnd, b);
            } else {
                pop(optr);
                i++;
            }
        }
    }
    printf("%d\n", getTop(opnd) - 48);
}


int main() {
    char s[100][100];
    for (int i = 0; i < 100; i++) {
        scanf("%s", s[i]);
        if (strcmp(s[i], "=") == 0) {
            break;
        } else {
            getOneStringResult(s[i]);
        }
    }
    return 0;
}
