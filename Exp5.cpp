#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <cmath>
#include <stack>

using namespace std;

typedef enum { smaller = -1, same, bigger } compare;

typedef long long ElemType;

typedef struct BinaryTreeNode {
    ElemType data;
    BinaryTreeNode *left_child, *right_child;
} BinaryTreeNode, *BinaryTree;
compare compareSign(char op1, char op2);
ElemType initExpTree(const string& expression);
bool isLegalOperator(char c);
void createExpTree(BinaryTree &binaryTree, BinaryTree left_child, BinaryTree right_child, ElemType root_data);
ElemType evaluateExpTree(BinaryTree binaryTree);
void discardIllegalCharacter(string &s);
ElemType getValue(char op, ElemType a, ElemType b);
ElemType getValueFromStack(stack<ElemType> s);
int main() {
    string s;
    vector<string> Strings;
    cout << "请输入要计算的表达式(以=结束,退出输入请在最后一行输入一个=): " << endl;
    while(getline(cin, s) && s != "=") {
        discardIllegalCharacter(s);
        Strings.push_back(s);
    }
    for(const auto & String : Strings) {
        ElemType val = 0;
        bool err = false;
        try {
           val = initExpTree(String);
        } catch (char const *error) {
            cout << "Error: " << error << endl;
            err = true;
        }
        if (err) {
            cout << String << " is an invalid expression." << endl;
        } else {
            cout << String << val << endl;
        }

    }
    
    return 0;
}

ElemType initExpTree(const string& expression) {
    stack<BinaryTree> expt;
    stack<char> optr;
    optr.push('=');
    char operatorsInput;
    ElemType numbersInput;
    BinaryTree binaryTree;
    bool findEqual = false;
    for (ElemType i = 0; i < expression.length(); i++) {
        if (isdigit(expression[i])) {
            stack<ElemType> numbers;
            while(isdigit(expression[i])) {
                numbers.push(expression[i]);
                i++;
            }
            createExpTree(binaryTree, nullptr, nullptr, getValueFromStack(numbers));
            expt.push(binaryTree);
            i--;
        } else if (!isLegalOperator(expression[i])) {
            throw "Illegal expression!";
        } else {
            char operatorPop;
            BinaryTree treePop1, treePop2;
            switch (compareSign(optr.top(), expression[i])) {
            case smaller:
                optr.push(expression[i]);
                break;
            case bigger:
                if (expt.size() < 2 || optr.empty()) {
                    throw "Illegal expression!";
                    return 0;
                }
                operatorPop = optr.top();
                treePop2 = expt.top();
                optr.pop();
                expt.pop();
                treePop1 = expt.top();
                expt.pop();
                createExpTree(binaryTree, treePop1, treePop2, operatorPop);
                expt.push(binaryTree);
                i--;
                break;
            case same:
                optr.pop();
                break;
            default:
                break;
            }
        }
    }
Judge:
    if(expt.size() == 0) {
        throw "Empty expression";
    }
    binaryTree = expt.top();
    expt.pop();
    if (!expt.empty() or !optr.empty()) {
        throw "Illegal expression!";
    } else {
        return evaluateExpTree(binaryTree);
    }
}

compare compareSign(const char op1, const char op2) {
    if ((op1 == '(' && op2 == ')') || (op1 == '=' && op2 == '=')) {
        return same;
    } else if (op1 == '(' || op1 == '=' || op2 == '(' || (op1
        == '+' || op1 == '-') && (op2 == '*' || op2 == '/')) {
        return smaller;
    } else
        return bigger;
}

bool isLegalOperator(char c) {
    return c == '+' or c == '-' or c == '*' or c == '/' or c == '=' or c == '(' or c == ')';
}

void createExpTree(BinaryTree &binaryTree, BinaryTree left_child, BinaryTree right_child, ElemType root_data) {
    binaryTree = new BinaryTreeNode;
    binaryTree->data = root_data;
    binaryTree->left_child = left_child;
    binaryTree->right_child = right_child;
}

ElemType evaluateExpTree(BinaryTree binaryTree) {
    if (binaryTree->left_child == nullptr && binaryTree->right_child == nullptr)
        return binaryTree->data;
    ElemType rightValue = 0;
    ElemType leftValue = 0;
    leftValue = evaluateExpTree(binaryTree->left_child);
    rightValue = evaluateExpTree(binaryTree->right_child);
    ElemType val = 0;
    val = getValue(binaryTree->data, leftValue, rightValue);
    return val;
}

ElemType getValue(char op, ElemType a, ElemType b) {
    switch (op) {
    case '+':
        return a + b;
    case '-':
        return a - b;
    case '*':
        return a * b;
    case '/':
        if (b == 0) {
            throw "Divisor can't be 0!";
        }
        return static_cast<ElemType>(round(static_cast<double>(a) / static_cast<double>(b)));
    default:
        return 0;
    }
}

void discardIllegalCharacter(string &s) {
    string t;
    for (const char i: s) {
        if (!isspace(i) and (isLegalOperator(i) or isdigit(i))) {
            t.push_back(i);
        }
    }
    s = t;
}

ElemType getValueFromStack(stack<ElemType> s) {
    ElemType num = 0;
    ElemType mul = 1;
    stack<ElemType> sl = s;
    while (!s.empty()) {
        num += (s.top() - 48) * mul;
        s.pop();
        mul *= 10;
    }
    
    return num;
}