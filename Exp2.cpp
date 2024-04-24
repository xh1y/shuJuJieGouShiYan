#include <iostream>
using namespace std;

const char oper[7] = { '+', '-', '*', '/', '(', ')', '=' };
typedef char SElemType;

typedef struct StackNode {
    SElemType data;
    struct StackNode* next;
} StackNode, * LinkStack;
typedef enum compare {smaller = -1, same, bigger} compare;
void InitStack(LinkStack& S);
bool StackEmpty(LinkStack S);
void Push(LinkStack& S, SElemType e);
void Pop(LinkStack& S, SElemType& e);
SElemType GetTop(LinkStack& S);
bool In(char ch);
compare Precede(char op1, char op2);
char Operate(char first, char op, char second);
char EvaluateExpression();

int main() {
    cout << "请输入要计算的表达式（操作数和结果都在0-9的范围内，以=结束）：" << endl;
    char res = EvaluateExpression();
    cout << "计算结果为" << res - 48 << endl << endl;
    return 0;
}

void InitStack(LinkStack& S) {
    S = NULL;
    
}

bool StackEmpty(LinkStack S) {
    return !S;
}

void Push(LinkStack& S, SElemType e) {
    StackNode* p = new StackNode;
    if (!p) {
        exit(0);
    }
    p->data = e;
    p->next = S;
    S = p;
    
}

void Pop(LinkStack& S, SElemType& e) {
    StackNode* p;
    if (!S)
        return ;
    e = S->data;
    p = S;
    S = S->next;
    delete p;
    
}
SElemType GetTop(LinkStack& S) {
    if (!S)
        return ;

    return S->data;
}
bool In(char ch) {
    for (int i = 0; i < 7; i++) {
        if (ch == oper[i]) {
            return true;
        }
    }
    return false;
}
compare Precede(char op1, char op2) {
    if ((op1 == '(' && op2 == ')') || (op1 == '=' && op2 == '=')) {
        return same;
    }
    else if (op1 == '(' || op1 == '=' || op2 == '(' || (op1
        == '+' || op1 == '-') && (op2 == '*' || op2 == '/')) {
        return smaller;
    }
    else
        return bigger;
}
char Operate(char first, char op, char second) {
    switch (op) {
    case '+':
        return (first - '0') + (second - '0') + 48;
    case '-':
        return (first - '0') - (second - '0') + 48;
    case '*':
        return (first - '0') * (second - '0') + 48;
    case '/':
        return (first - '0') / (second - '0') + 48;
    }
    return 0;
}


char EvaluateExpression() {
    LinkStack optr, numbers;
    char ch, op, a, b, x, top;
    InitStack(numbers); 
    InitStack(optr); 
    Push(optr, '='); 
    cin >> ch;
    while (ch != '=' || (GetTop(optr) != '=')) 
    {
        if (!In(ch)) {
            Push(numbers, ch);
            cin >> ch;
        } 
        else
            switch (Precede(GetTop(optr), ch)) 
            {
            case smaller:
                Push(optr, ch);
                cin >> ch; 
                break;
            case bigger:
                Pop(optr, op); 
                Pop(numbers, b);
                Pop(numbers, a); 
                Push(numbers, Operate(a, op, b)); 
                break;
            case same: 
                Pop(optr, x);
                cin >> ch; 
                break;
            } 
    } 
    return GetTop(numbers); 
}
