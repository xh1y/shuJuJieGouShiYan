#include <iostream>
#include <string>
#include <cctype>
#include <vector>
using namespace std;

template<class T>
class Stack {
private:
    T *data;
    int top_;
    int bottom;

public:
    Stack() : data(new T[100]), top_(0), bottom(0){};

    ~Stack();

    explicit Stack(int size);

    void push(T data);

    T pop();

    T getTop();

    bool empty() const;

    int length() const;

    int top() const;
};

template<typename T>
Stack<T>::Stack(int size) {
    data = new T[size];
    top_ = -1;
    bottom = -1;
}

template<typename T>
T Stack<T>::getTop() {
    return data[top_];
}

template<typename T>
void Stack<T>::push(T data) {
    this->data[++top_] = data;
}

template<typename T>
T Stack<T>::pop() {
    T data = this->data[top_];
    top_--;
    return data;
}

template<typename T>
bool Stack<T>::empty() const {
    return top_ == -1;
}

template<typename T>
int Stack<T>::length() const {
    return top_ - bottom;
}

template<typename T>
Stack<T>::~Stack() = default;

template<typename T>
int Stack<T>::top() const {
    return top_;
}


typedef enum { smaller = -1, same, bigger } compare;

compare compareSign(char op1, char op2);

bool isLegalOperator(char c);

int getValue(char op, int a, int b);

void discardIllegalCharacter(string &s);

int getValueFromStack(Stack<int> s);

int main() {
    vector<string> Strings;
    string expression;
    char op;
    int a, b, x, top;
    while (getline(cin, expression) && expression != "=") {
        discardIllegalCharacter(expression);
        Strings.push_back(expression);
    }

    for (auto &String: Strings) {
        int charNum = 0;
        Stack<int> numbers;
        Stack<char> operators;
        operators.push('=');
        while (charNum < String.size()) {
            char ch = String[charNum];
            if (isdigit(String[charNum])) {
                Stack<int> eachDigit;
                while (isdigit(String[charNum])) {
                    eachDigit.push(String[charNum]);
                    charNum++;
                }
                numbers.push(getValueFromStack(eachDigit));
                // charNum--;
            } else {
                switch (compareSign(operators.getTop(), String[charNum])) {
                    case smaller:
                        operators.push(String[charNum]);
                        charNum++;
                        break;
                    case bigger:
                        if (operators.empty() || numbers.length() < 2) {
                            cout << "illegal expression!";
                            break;
                        }
                        op = operators.getTop();
                        operators.pop();
                        b = numbers.getTop();
                        numbers.pop();
                        a = numbers.getTop();
                        numbers.pop();
                        numbers.push(getValue(op, a, b));
                        break;
                    case same:
                        operators.pop();
                        charNum++;
                        break;
                }
            }
        }
        cout << String << '=' << numbers.getTop() << endl;
    }

    return 0;
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

int getValue(char op, int a, int b) {
    switch (op) {
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
                throw ("Divisor can't be 0!");
            }
            return a / b;
            break;
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

int getValueFromStack(Stack<int> s) {
    int num = 0;
    int mul = 1;
    while (!s.empty()) {
        num += (s.getTop() - 48) * mul;
        s.pop();
        mul *= 10;
    }
    return num;
}
