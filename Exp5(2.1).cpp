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