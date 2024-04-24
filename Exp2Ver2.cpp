#include <iostream>  
#include <cstdlib> // For malloc and free  

const int MAX_STACK_SIZE = 100; // Define the maximum size of the stack  

class Stack {
private:
    int* topPtr; // Pointer to the top of the stack  
    int* basePtr; // Pointer to the base of the stack  
    int stackSize; // Current size of the stack  
    typedef struct {
        int* topPtr; 
        int* basePtr;
    }StackNode, *LinkStack;
public:
    // Constructor  
    Stack() {
        // basePtr = (int*)malloc(MAX_STACK_SIZE * sizeof(int));
        // basePtr = new 
        if (!basePtr) {
            std::cerr << "Memory allocation failed!" << std::endl;
            exit(EXIT_FAILURE);
        }
        topPtr = basePtr - 1; // Initially, the top pointer points to one element below the base  
        stackSize = 0;
    }

    // Destructor  
    ~Stack() {
        free(basePtr);
    }

    // Check if the stack is empty  
    bool isEmpty() const {
        return stackSize == 0;
    }

    // Push an element onto the stack  
    void push(int value) {
        if (stackSize >= MAX_STACK_SIZE) {
            std::cerr << "Stack is full!" << std::endl;
            return;
        }
        *(++topPtr) = value; // Increment the top pointer and store the value  
        ++stackSize; // Increment the stack size  
    }

    // Pop an element from the stack  
    bool pop(int& value) {
        if (isEmpty()) {
            std::cerr << "Stack is empty!" << std::endl;
            return false;
        }
        value = *topPtr--; // Decrement the top pointer and retrieve the value  
        --stackSize; // Decrement the stack size  
        return true;
    }

    // Get the top element of the stack  
    bool top(int& value) const {
        if (isEmpty()) {
            std::cerr << "Stack is empty!" << std::endl;
            return false;
        }
        value = *topPtr; // Retrieve the value at the top pointer  
        return true;
    }

    // Get the size of the stack  
    int size() const {
        return stackSize;
    }
};

int main() {
    
  
}