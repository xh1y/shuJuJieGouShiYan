#include <iostream>
#include <cstdlib>
#include <cctype>
#include <vector>
#include <string>
#include <stack>

using namespace std;
typedef enum { smaller = -1, same, bigger } compare;

compare compareSign(char op1, char op2);
bool isLegalOperator(char c);
int getValue(char thetha, int a, int b);
void discardIllegalCharacter(string& s);
int getValueFromStack(stack<int> s);

int main() {
    vector<string> Strings;
    string expression;
    char op;
    int a, b, x, top;
    while (cin >> expression && expression.compare("=") != 0) {
        discardIllegalCharacter(expression);
        Strings.push_back(expression);
    }

    for (int expNum = 0; expNum < Strings.size(); expNum++) {
        int charNum = 0;
        stack<int> numbers;
        stack<char> optr;
        optr.push('=');
        while (charNum < Strings[expNum].size()) {
            char ch = Strings[expNum][charNum];
            if (isdigit(Strings[expNum][charNum])) {
                stack<int> eachDigit;
                while (isdigit(Strings[expNum][charNum])) {
                    eachDigit.push(Strings[expNum][charNum]);
                    charNum++;
                }
                numbers.push(getValueFromStack(eachDigit));
                // charNum--;
            } else {
                switch (compareSign(optr.top(), Strings[expNum][charNum])) {
                case smaller:
                    optr.push(Strings[expNum][charNum]);
                    charNum++;
                    break;
                case bigger:
                    // try {
                        // op = Pop(optr);
                        // b = Pop(numbers);
                        // a = Pop(numbers);
                    if (optr.empty() || numbers.size() < 2) {
                        cout << "illegal expression!";
                        break;
                    }
                    op = optr.top();
                    optr.pop();
                    b = numbers.top();
                    numbers.pop();
                    a = numbers.top();
                    numbers.pop();
                    // }
                    // catch (string e) {
                    //     cout << e;
                    // }
                    // Push(numbers, calculate(a, op, b));
                    numbers.push(getValue(op, a, b));
                    break;
                case same:
                    // x = Pop(optr);
                    x = optr.top();
                    optr.pop();
                    charNum++;
                    break;
                }

            }
        }
        cout << Strings[expNum] << numbers.top() << endl;
    }

    return 0;
}

compare compareSign(char op1, char op2) {
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

bool isLegalOperator(char c) {
    return c == '+' or c == '-' or c == '*' or c == '/' or c == '=' or c == '(' or c == ')';
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
        return int(a / b);
        break;
    default:
        return 0;
    }
}

void discardIllegalCharacter(string& s) {
    string t = "";
    for (string::iterator i = s.begin(); i <= s.end(); i++) {
        if (!isspace(*i) and (isLegalOperator(*i) or isdigit(*i))) {
            t.push_back(*i);
        }
    }
    s = t;
}

int getValueFromStack(stack<int> s) {
    int num = 0;
    int mul = 1;
    while (!s.empty()) {
        num += (s.top() - 48) * mul;
        s.pop();
        mul *= 10;
    }
    return num;
}