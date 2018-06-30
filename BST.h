#ifndef BST_H
#define BST_H

#include <vector>
#include <iostream>
using namespace std;

/**
 * Exercise 1: BST class
 * Provide an appropriate data structure and necessary methods to build a binary
 * search tree which enables you to complete the rest of this assignment. Define
 * your class with generic types.
 */
template <typename T>
class BST
{
  private:
    vector<T> bst;

  public:
    BST(vector<T> &);
    vector<T> getList() const;
    void insert(T, int, int);
};

/**
 * Creates a binary Search tree
 * @tparam T
 * @param list
 */
template <typename T>
BST<T>::BST(vector<T> &list) {

    bst.resize(list.size());

    for (int i = 0; i < list.size(); i++)
        insert(list[i], i, 0);
}

template <typename T>
vector<T> BST<T>::getList() const {
    return bst;
}

template <typename T>
void BST<T>::insert(T element, int child, int parent) {

    int right = 2 * child + 2;
    int left =  2 * child + 1;

    if(bst.empty()) {
        bst[child] = element;
        return;
    }

    if(bst[parent] > element)
        insert(element, right, parent);
    else
        insert(element, left, parent);
}

#endif
