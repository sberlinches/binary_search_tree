#ifndef DLL_H
#define DLL_H

#include <iostream>

using namespace std;

/**
 * Node class
 * @tparam T The type of the data
 */
template<typename T>
class Node {
private:
    T data;
    Node<T>* next;
    Node<T>* prev;
public:
    Node();
    Node(T, Node<T>*, Node<T>*);
    /*T getData() { return data; };
    Node<T>* getNext() { return next; };
    Node<T>* getPrev() { return prev; };
    void setNext(Node<T>* next) { this->next = next; };
    void setPrev(Node<T>* prev) { this->prev = prev; };*/
    template<typename> friend class DLL;
    template<typename> friend class Iterator;
};

/**
 * Creates an empty node
 */
template<typename T>
Node<T>::Node() {
    next = prev = nullptr;
}

/**
 * Creates an empty node
 * @tparam T The type of the data
 * @param data
 * @param next
 * @param prev
 */
template<typename T>
Node<T>::Node(T data, Node<T> *next, Node<T> *prev) {
    this->data = data;
    this->next = next;
    this->prev = prev;
}

/**
 * Iterator class
 * @tparam T The type of the data
 */
template<typename T>
class Iterator {
private:
    Node<T>* current;
public:
    Iterator(Node<T>*);
    Iterator<T> getNext();
    T getData();
    bool isEqual(const Iterator<T>&);
};

/**
 *
 * @tparam T
 * @param node
 */
template<typename T>
Iterator<T>::Iterator(Node<T> *node) {
    current = node;
}

/**
 *
 * @tparam T
 * @return
 */
template<typename T>
Iterator<T> Iterator<T>::getNext() {
    current = current->next;
    return *this;
}

/**
 *
 * @tparam T
 * @return
 */
template<typename T>
T Iterator<T>::getData() {
    return current->data;
};

/**
 *
 * @tparam T
 * @param itr
 * @return
 */
template<typename T>
bool Iterator<T>::isEqual(const Iterator<T>& itr) {
    return (current == itr.current);
}


/**
 * Doubly Liked List class
 * @tparam T The type of the data
 */
template<typename T>
class DLL {
private:
    int size;
    Node<T>* head;
    Node<T>* tail;
public:
    DLL();
    int getSize() const;
    bool isEmpty() const;
    /*Node<T>* getHead() { return head; };
    Node<T>* getTail() { return tail; };
    void setSize(int size) { this->size = size; };
    void setHead(Node<T>* head) { this->head = head; };
    void setTail(Node<T>* tail) { this->tail = tail; };*/
    void addLast(T);
    T removeLast();
    T getLast() const;
    template<typename> friend class Iterator;
    Iterator<T> begin() const;
    Iterator<T> end() const;
};

/**
 * Creates an empty doubly linked list.
 */
template<typename T>
DLL<T>::DLL() {
    size = 0;
    head = tail = nullptr;
}

/**
 * Returns the size of the list.
 * @return The size of the list
 */
template<typename T>
int DLL<T>::getSize() const {
    return size;
}

/**
 * Returns whether the list is empty or not.
 * @return Whether the list is empty or not
 */
template<typename T>
bool DLL<T>::isEmpty() const {
    return (head == nullptr);
}

/**
 * Add an element to the last position of the list.
 * @tparam T The type of the data
 * @param data The data to be inserted in the node
 */
template<typename T>
void DLL<T>::addLast(T data) {

    Node<T>* temp = new Node<T>(data, nullptr, tail);

    if (head == nullptr)
        head = tail = temp;
    else {
        tail = temp;
        tail->prev->next = temp;
    }
    size++;
}

/**
 * Removes the last element of the list and returns its value.
 * @tparam T The type of the data
 * @return The value of the removed element
 */
template<typename T>
T DLL<T>::removeLast() {

    if (head == nullptr)
        throw runtime_error("DLL.removeLast: The List is empty");

    Node<T>* tmp = head;
    Node<T>* last = tail;
    T data = last->data;

    for (int i = 0; i < size - 2; i++)
        tmp = tmp->next;

    tail = tmp;
    tail->next = nullptr;
    delete last;
    size--;
    return data;
}

/**
 * Returns the last value of the list.
 * @tparam T The type of the data
 * @return The last value of the list
 */
template<typename T>
T DLL<T>::getLast() const {
    if (head == nullptr)
        throw runtime_error("DLL.getLast: The List is empty");
    return tail->data;
}

/**
 * Returns the head of the list.
 *
 * @tparam T The type of the data
 * @return the head of the list
 */
template<typename T>
Iterator<T> DLL<T>::begin()const {
    return Iterator<T>(head);
}

/**
 * Returns the tail of the list.
 *
 * @tparam T The type of the data
 * @return the tail of the list.
 */
template<typename T>
Iterator<T> DLL<T>::end()const {
    return Iterator<T>(tail->next);
}




#endif
