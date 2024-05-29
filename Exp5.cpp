#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <cmath>
#include <stack>

using namespace std;

typedef enum { smaller = -1, same, bigger } compare;

typedef struct BinaryTreeNode {
    int data;
    struct BinaryTreeNode *lchild, *rchild;
} BinaryTreeNode, *BinaryTree;
compare compareSign(char op1, char op2);
int InitExpTree(string expression);
bool isLegalOperator(char c);
void CreateExpTree(BinaryTree &binaryTree, BinaryTree leftChild, BinaryTree rightChild, char rootData);
int EvaluateExpTree(BinaryTree binaryTree);
void discardIllegalCharacter(string &s);
int getValue(char thetha, int a, int b);
int getValueFromStack(stack<int> s);
int main() {
    string s = "";
    vector<string> Strings;
    cout << "请输入要计算的表达式(以=结束,退出输入请在最后一行输入一个=): " << endl;
    while(getline(cin, s) && s != "=") {
        discardIllegalCharacter(s);
        Strings.push_back(s);
    }
    for(int i = 0; i < Strings.size(); i++) {
        int val;
        bool err = false;
        try {
           val = InitExpTree(Strings[i]);
        } catch (char const *error) {
            cout << "Error: " << error << endl;
            err = true;
        }
        if (err) {
            cout << Strings[i] << " is an invalid expression." << endl;
        } else {
            cout << Strings[i] << val << endl;
        }

    }
    
    return 0;
}

int InitExpTree(string expression) {
    stack<BinaryTree> expt;
    stack<char> optr;
    optr.push('=');
    char operatorsInput;
    int numbersInput;
    BinaryTree binaryTree;
    bool findEqual = false;
    for (int i = 0; i < expression.length(); i++) {
        if (isdigit(expression[i])) {
            stack<int> numbers;
            while(isdigit(expression[i])) {
                numbers.push(expression[i]);
                i++;
            }
            CreateExpTree(binaryTree, nullptr, nullptr, getValueFromStack(numbers));
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
                if (expt.size() < 2 || optr.size() == 0) {
                    throw "Illegal expression!";
                    return 0;
                }
                operatorPop = optr.top();
                treePop2 = expt.top();
                optr.pop();
                expt.pop();
                treePop1 = expt.top();
                expt.pop();
                CreateExpTree(binaryTree, treePop1, treePop2, operatorPop);
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
        return EvaluateExpTree(binaryTree);
    }
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

bool isLegalOperator(char c) {
    return c == '+' or c == '-' or c == '*' or c == '/' or c == '=' or c == '(' or c == ')';
}

void CreateExpTree(BinaryTree &binaryTree, BinaryTree leftChild, BinaryTree rightChild, char rootData) {
    binaryTree = new BinaryTreeNode;
    binaryTree->data = rootData;
    binaryTree->lchild = leftChild;
    binaryTree->rchild = rightChild;
}

int EvaluateExpTree(BinaryTree binaryTree) {
    int leftValue = 0, rightValue = 0;
    if (binaryTree->lchild == nullptr && binaryTree->rchild == nullptr)
        return binaryTree->data;
    else {
        leftValue = EvaluateExpTree(binaryTree->lchild);
        rightValue = EvaluateExpTree(binaryTree->rchild);
        int val = 0;
        val = getValue(binaryTree->data, leftValue, rightValue);
        return val;
    }
}

int getValue(char thetha, int a, int b) {
    switch (thetha) {
    case '+':
        return a + b;
        break;
    case '-':
        return a - b;
        break;
    case '*':
        return a * b;
        break;
    case '/':
        if (b == 0) {
            // return 0;
            throw "Divisor can't be 0!";
        }
        return round(static_cast<double>(a) / static_cast<double>(b));
        break;
    default:
        return 0;
    }
}

void discardIllegalCharacter(string &s) {
    string t = "";
    int count = 0;
    for(string::iterator i = s.begin(); i <= s.end(); i++) {
        if(!isspace(*i) and (isLegalOperator(*i) or isdigit(*i))) {
            t.push_back(*i);
            count++;
        }
    }
    if(count != 0)
        s = t;
}

int getValueFromStack(stack<int> s) {
    int num = 0;
    int mul = 1;
    stack<int> sl = s;
    while (!s.empty()) {
        num += (s.top() - 48) * mul;
        s.pop();
        mul *= 10;
    }
    
    return num;
}