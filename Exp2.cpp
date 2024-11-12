#include <iostream>
#include <cstdlib>
#include <cctype>

using namespace std;

const char oper[7] = { '+', '-', '*', '/', '(', ')', '=' };
typedef char SElemType;

typedef struct StackNode {
    SElemType data;
    struct StackNode *next;
} StackNode, *LinkStack;
typedef enum compare { smaller = -1, same, bigger } compare;
void InitStack(LinkStack S);
bool StackEmpty(LinkStack S);
void Push(LinkStack &S, SElemType e);
SElemType Pop(LinkStack &S);
SElemType GetTop(LinkStack &S);
bool isSign(char ch);
compare compareSign(char op1, char op2);
char calculate(char first, char op, char second);

int main() {
    cout << "请输入要计算的表达式（以=结束）：" << endl;
    LinkStack optr, numbers;
    char ch, op, a, b, x, top;
    InitStack(numbers);
    InitStack(optr);
    Push(optr, '=');
    cin >> ch;
    while (ch != '=' || (GetTop(optr) != '=')) {
        if (!isSign(ch)) {
            if (isdigit(ch))
                Push(numbers, ch);
            cin >> ch;
        } else {
            switch (compareSign(GetTop(optr), ch)) {
            case smaller:
                Push(optr, ch);
                cin >> ch;
                break;
            case bigger:
                try {
                    op = Pop(optr);
                    b = Pop(numbers);
                    a = Pop(numbers);
                } catch (string e) {
                    cout << e;
                }
                Push(numbers, calculate(a, op, b));
                break;
            case same:
                try {
                    x = Pop(optr);
                } catch (string e) {
                    cout << e;
                }
                cin >> ch;
                break;
            }
        }
    }
    cout << GetTop(numbers) - '0' << endl << endl;
    return 0;
}

void InitStack(LinkStack S) {
    S = nullptr;
}

bool StackEmpty(LinkStack S) {
    return !S;
}

void Push(LinkStack &S, SElemType e) {
    StackNode *p = new StackNode;
    if (!p) {
        exit(0);
    }
    p->data = e;
    p->next = S;
    S = p;

}

SElemType Pop(LinkStack &S) {
    SElemType e;
    StackNode *p;
    if (!S)
        throw static_cast<string>("Stack Empty");
    e = S->data;
    p = S;
    S = S->next;
    delete p;
    return e;
}
SElemType GetTop(LinkStack &S) {
    if (!S)
        return '\0';
    return S->data;
}

bool isSign(char ch) {
    for (int i = 0; i < 7; i++) {
        if (ch == oper[i]) {
            return true;
        }
    }
    return false;
}

compare compareSign(char op1, char op2) {
    if ((op1 == '(' && op2 == ')') || (op1 == '=' && op2 == '=')) {
        return same;
    } else if (op1 == '(' || op1 == '=' || op2 == '(' || (op1
        == '+' || op1 == '-') && (op2 == '*' || op2 == '/')) {
        return smaller;
    } else
        return bigger;
}
char calculate(char first, char op, char second) {
    switch (op) {
    case '+':
        return (first - '0') + (second - '0') + '0';
    case '-':
        return (first - '0') - (second - '0') + '0';
    case '*':
        return (first - '0') * (second - '0') + '0';
    case '/':
        return (first - '0') / (second - '0') + '0';
    }
    return 0;
}