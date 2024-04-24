#include <iostream>
#include <cstdlib>
#include <cctype>
#include <ctype.h>
using namespace std;
typedef char SElemType;
typedef enum { illegal = -2, smaller = -1, same, bigger } compare;
typedef struct StackNode {
    SElemType data;
    struct StackNode* next;
} StackNode, * Stack;

void InitStack(Stack& S) {
    S = NULL;
}

void Push(Stack& S, SElemType e) {
    Stack p;
    p = new StackNode;
    p->data = e;
    p->next = S;
    S = p;
}

SElemType Pop(Stack &S) {
    Stack p;
    SElemType e;
    if (S == NULL)
        e = '\0';
    e = S->data;
    p = S;
    S = S->next;
    delete p;
    return e;
}

void Pop(Stack& S, SElemType& e) { // 这是书上的写法
    Stack p;
    if (S == NULL)
        e = '\0';
    e = S->data;
    p = S;
    S = S->next;
    delete p;
}

SElemType GetTop(Stack S) {
    if (S != nullptr)
        return S->data;
    else
        return '\0';
}

int getIndex(char op) {
    int index = -1;
    switch (op) {
    case '+':
        index = 0;
        break;
    case '-':
        index = 1;
        break;
    case '*':
        index = 2;
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
        index = 6;
        break;
    default:
        index = -1;
        break;
    }
    return index;
}

compare comparePriority(SElemType a, SElemType b) {
    const compare priority[][7] = {
        {bigger, bigger, smaller, smaller, smaller, bigger, bigger},
        {bigger, bigger, smaller, smaller, smaller, bigger, bigger},
        {bigger, bigger, bigger, bigger, smaller, bigger, bigger},
        {bigger, bigger, bigger, bigger, smaller, bigger, bigger},
        {smaller, smaller, smaller, smaller, smaller, same, illegal},
        {bigger, bigger, bigger, bigger, illegal, bigger, bigger},
        {smaller, smaller, smaller, smaller, smaller, illegal, same}
    };
    return priority[getIndex(a)][getIndex(b)];
}

int main() {
    Stack optr = new StackNode;
    Stack number = new StackNode;
    SElemType element, pop;
    SElemType res = 0;
    Pop(optr);
    Pop(number);
    while (element = cin.get() != '=') {
        if (isdigit(element)) {
            Push(number, element);
        }
        else {
            if(getIndex(element) >= 0) {
                compare cmp = comparePriority(GetTop(optr), element);
                if(cmp == smaller) {
                    Push(optr, element);
                } else if(cmp == same) {
                    Pop(optr, pop);
                } else {
                    SElemType num1;
                    SElemType num2;
                    SElemType op1;
                    Pop(number, num1);
                    Pop(number, num2);
                    if(num2 == '\0') {

                    } else {
                        Pop(optr, op1);
                        SElemType result;
                        switch (op1) {
                        case '+':
                            result = num1 + num2;
                            break;
                        case '-':
                            result = num1 - num2;
                            break;
                        case '*':
                            result = num1 * num2;
                            break;
                        case '/':
                            result = num1 / num2;
                            break;
                        case '#':
                            break;
                        }
                    }
                }
            }
        }
    }
    Pop(number, res);
    cout << (int)res;
    return 0;
}