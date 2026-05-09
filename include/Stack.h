#ifndef STACK_H
#define STACK_H

#include <stdexcept>

template<typename T>
class Stack {
private:
    T* data;
    int capacity;
    int topIndex;
    
    void resize() {
        int newCapacity = capacity * 2;
        T* newData = new T[newCapacity];
        for (int i = 0; i <= topIndex; i++) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        capacity = newCapacity;
    }
    
public:
    Stack(int initialCapacity = 10) : capacity(initialCapacity), topIndex(-1) {
        data = new T[capacity];
    }
    
    ~Stack() {
        delete[] data;
    }
    
    void push(const T& item) {
        if (topIndex >= capacity - 1) resize();
        data[++topIndex] = item;
    }
    
    T pop() {
        if (isEmpty()) throw std::runtime_error("Stack underflow");
        return data[topIndex--];
    }
    
    T peek() const {
        if (isEmpty()) throw std::runtime_error("Stack is empty");
        return data[topIndex];
    }
    
    bool isEmpty() const { return topIndex == -1; }
    int size() const { return topIndex + 1; }
};

#endif