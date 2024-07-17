/*
 * stack.h
 *
 * Implements a simple stack class using dynamic arrays.
 * This may be implemented in 3 stages:
 *   Stage 1: non-template stack class storing strings,
 *            unsafe copies/assignments
 *   Stage 2: template stack class, unsafe copies/assignments
 *   Stage 3: template stack class, safe copies/assignments
 *
 * Note: no underflow detection is performed.  Performing pop() or top()
 * on an empty stack results in undefined behavior (possibly crashing your
 * program)!
 *
 * Author: Your Name
 */

#ifndef _STACK_H
#define _STACK_H
#include "dynamicArray.h"

template <typename T>
class stack {
    private:
    int capacity;
    int stackSize;
    Array<T> stackContainer;

    public:
    stack();
    stack(const stack&);
    ~stack();
    stack& operator=(const stack&);
    void push(const T&);
    T pop();
    T top() const;
    int size() const;
    bool is_empty() const;

};

// To start stage 2, you probably want to copy all of your code from
// stack-stage1.h and stack-stage1.cpp in place of this comment.

template <typename T>
stack<T>::stack() {
    Array<T> newArray(50);
    stackContainer = newArray;
    stackSize = 0;
    capacity = 50;

}

template <typename T>
stack<T>::stack(const stack& OTHER) {
    stackSize = OTHER.stackSize;
    capacity = OTHER.capacity;
    stackContainer = OTHER.stackContainer;
}

template <typename T>
stack<T>::~stack() {
    
}

template <typename T>
stack<T>& stack<T>::operator=(const stack& OTHER) {
    if(this == &OTHER) {
        return *this;
    }
    capacity = OTHER.capacity;
    stackSize = OTHER.stackSize;
    stackContainer = OTHER.stackContainer;
    return *this;
}

template <typename T>
void stack<T>::push(const T& VALUE) {
    if(stackSize == capacity) {
        stackContainer.doubleSize();
        capacity = capacity * 2;
    }
    stackContainer.set(stackSize, VALUE);
    stackSize++;
}

template <typename T>
int stack<T>::size() const{
    return stackSize;
}

template <typename T>
bool stack<T>::is_empty() const{
    if(stackSize == 0) {
        return true;
    } else  {
        return false;
    }
}

template <typename T>
T stack<T>::pop() {
    if(stackSize < 1) {
        return T();
    }
    T value = stackContainer.get(stackSize - 1);
    stackSize--;
    return value;
}

template <typename T>
T stack<T>::top() const{
    return stackContainer.get(stackSize - 1);
}

#endif