#ifndef STACK_H
#define STACK_H

#include <iostream>
#include "DLL.h"

using namespace std;

/**
 * Stack class
 * @tparam T The type of the data
 */
template<typename T>
class Stack {
public:
    Stack();
    DLL<T> getList() { return list; };
    int getSize() const;
    bool isEmpty() const;
    T top() const;
    void push(T value);
    T pop();
private:
    DLL<T> list;
};

/**
 * Creates an empty stack
 * @tparam T The type of the data
 */
template<typename T>
Stack<T>::Stack() {}

/**
 * Returns the number of elements in the stack.
 * @tparam T The type of the data
 * @return The number of elements in the stack
 */
template<typename T>
int Stack<T>::getSize() const {
    return list.getSize();
}

/**
 * Checks whether the stack is empty or not.
 * @tparam T The type of the data
 * @return Whether the stack is empty or not
 */
template<typename T>
bool Stack<T>::isEmpty() const {
    return list.isEmpty();
}

/**
 * Returns a reference to the item at the top of the stack.
 * @tparam T
 * @return
 */
template<typename T>
T Stack<T>::top() const {
    return list.getLast();
}

/**
 * Insert the value onto the top of the stack.
 * @tparam T The type of the data
 * @param value The value to insert
 */
template<typename T>
void Stack<T>::push(T value) {
    list.addLast(value);
}

/**
 * Remove and returns the item from the top of the stack.
 * @tparam T The type of the data
 * @return The item from the top of the stack
 */
template<typename T>
T Stack<T>::pop() {
    return list.removeLast();
}


#endif
