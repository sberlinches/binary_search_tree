#ifndef BST_H
#define BST_H

#include <vector>

using namespace std;


/**
 * Exercise 1: BST class
 * Provide an appropriate data structure and necessary methods to build a binary
 * search tree which enables you to complete the rest of this assignment. Define
 * your class with generic types.
 */
template<typename T>
class BST {
private:
    vector<T>* bst;
public:
    BST(vector<T>&);
    bool empty();
};

/**
 * Creates a binary Search tree
 * @tparam T
 * @param list
 */
template<typename T>
BST<T>::BST(vector<T>& list) {
    bst = &list;
}

#endif
