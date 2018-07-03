#ifndef BST_H
#define BST_H

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * BSTNode class.
 * @tparam T The type of the element
 */
template<typename T>
class BSTNode {
private:
    T element;
    BSTNode<T>* left;
    BSTNode<T>* right;
public:
    BSTNode();
    BSTNode(T);
    template<typename> friend class BST;
};

/**
 * Creates a BSTNode.
 * @tparam T The type of the element
 */
template<typename T>
BSTNode<T>::BSTNode() {
    this->left = nullptr;
    this->right = nullptr;
}

/**
 * Creates a BSTNode.
 * @tparam T The type of the element
 * @param element The element to store
 */
template<typename T>
BSTNode<T>::BSTNode(T element) {
    this->element = element;
    this->left = nullptr;
    this->right = nullptr;
}





/**
 * BST class
 * @tparam T The type of the element
 */
template <typename T>
class BST {
private:
    BSTNode<T>* bst;
    void insertList(vector<T>&);
    void insertList_aux(vector<T>&, int, int);
    int getHeight_aux(const BSTNode<T>*) const;
    void deleteByMerging(BSTNode<T>*&);
    void bstToVector_aux(const BSTNode<T>*, vector<T>*) const;
    void printInOrder_aux(const BSTNode<T>*) const;
public:
    BST(vector<T>& list);
    void insert(const T&);
    void remove(const T&);
    int getHeight() const;
    void printInOrder() const;
    vector<T> bstToVector() const;
};

/**
 * Creates a binary search tree.
 *
 * @tparam T The type of the element
 * @param list The list to consume from
 */
template<typename T>
BST<T>::BST(vector<T>& list) {

    // Initializes the bst and size
    bst = nullptr;

    // Sorts the list in ascending order
    sort(list.begin(), list.end(), less<int>());

    // Inserts the elements from the list into the bst
    insertList(list);
}

/**
 * Insert an element in the binary search tree.
 * Code extracted from the CPSC-2150 slides.
 *
 * @tparam T The type of the element
 * @param element The element to insert
 */
template<typename T>
void BST<T>::insert(const T& element) {

    BSTNode<T>* p = bst;
    BSTNode<T>* previous = nullptr;

    while(p != nullptr) {
        previous = p;
        if(element < p->element)
            p = p->left;
        else
            p = p->right;
    }

    // If the tree is empty, inserts a node in the root
    if(bst == nullptr)
        bst = new BSTNode<T>(element);
    // If the element to insert is smaller than the root,
    // is inserted in the left child
    else if (element < previous->element)
        previous->left = new BSTNode<T>(element);
    // If the element to insert is greater than the root,
    // is inserted in the right child
    else
        previous->right = new BSTNode<T>(element);
}

/**
 * Inserts a vector list and converts into a balanced binary search tree.
 * Complexity: O(n)
 *
 * @tparam T The type of the element
 * @param list The list to insert
 */
template<typename T>
void BST<T>::insertList(vector<T>& list) {
    insertList_aux(list, list.size()-1, 0);
}

/**
 * Inserts a vector list and converts into a balanced binary search tree.
 * Complexity: O(n)
 *
 * @tparam T The type of the element
 * @param list The list to insert
 * @param max The maximum index of the list
 * @param min The minimum index of the list
 */
template<typename T>
void BST<T>::insertList_aux(vector<T>& list, int max, int min) {

    int mid = ((max-min)/2)+min;
    //cout << "______ min: " << min << " max:" << max << " mid:" << mid << " = " << list[mid];

    if(max-min < 0) {
        return;
    }
    // List of two elements left
    if(max-min == 1) {
        //cout << " (2 left) INSERT: " << list[min] << ", " << list[max] << endl;
        insert(list[min]);
        insert(list[max]);
        return;
    }
    // List of one element left
    if (max-min == 0) {
        //cout << " (1 left) INSERT: " << list[max] << endl;
        insert(list[max]);
        return;
    }

    //cout << " INSERT: " << list[mid] << endl;
    insert(list[mid]);
    insertList_aux(list, mid-1, min);
    insertList_aux(list, max, mid+1);
}

/**
 * Deletes the element from the binary search tree.
 * Code extracted from the CPSC-2150 slides.
 * Complexity: TODO
 *
 * @tparam T The type of the element
 * @param node
 */
template<typename T>
void BST<T>::deleteByMerging(BSTNode<T>*& node) {

    BSTNode<T> *tmp = node;

    if (node != 0) {
        // node has no right child: it's left
        if (!node->right)
            // child (if any) is attached to its parent;
            node = node->left;
        // node has no left child: its right
        else if (node->left == 0)
            // child is attached to its parent;
            node = node->right;
        // be ready for merging subtrees;
        else {
            // 1. move left
            tmp = node->left;
            // 2. and then right as far as possible;
            while (tmp->right != 0)
                tmp = tmp->right;
            // 3. establish the link between the rightmost node of the left subtree and the right subtree;
            tmp->right = node->right;
            tmp = node;
            node = node->left;
        }

        delete tmp;
    }
}

/**
 * Deletes the element from the binary search tree.
 * Code extracted from the CPSC-2150 slides.
 * Complexity: TODO
 *
 * @tparam T The type of the element
 * @param element The element to delete
 */
template<typename T>
void BST<T>::remove(const T& element) {

    BSTNode<T> *node = bst, *prev = nullptr;

    while (node != nullptr) {
        if (node->element == element)
            break;
        prev = node;
        if (element < node->element)
            node = node->left;
        else
            node = node->right;
    }

    if (node != nullptr && node->element == element)
        if (node == bst)
            deleteByMerging(bst);
        else if (prev->left == node)
            deleteByMerging(prev->left);
        else deleteByMerging(prev->right);
}

/**
 * Calculates and returns the height of a balanced binary search tree.
 * Complexity: O(logn)
 *
 * @tparam T The type of the element
 * @return The height of a balanced binary search tree
 */
template<typename T>
int BST<T>::getHeight() const {
    return getHeight_aux(bst);
}

/**
 * Calculates and returns the height of a balanced binary search tree.
 * Complexity: O(logn)
 *
 * @tparam T The type of the element
 * @param root The root node of the tree
 * @return The height of a balanced binary search tree
 */
template<typename T>
int BST<T>::getHeight_aux(const BSTNode<T>* root) const {

    if(root == nullptr)
        return 0;

    // Traverses to the deepest node of each side and return the deepest one.
    int leftHeight = getHeight_aux(root->left);
    int rightHeight = getHeight_aux(root->right);
    return max(leftHeight, rightHeight) + 1;
}

/**
 * Prints the binary search tree in-order traversal.
 * Complexity: O(n)
 *
 * @tparam T The type of the element
 */
template<typename T>
void BST<T>::printInOrder() const {

    cout << "[";
    printInOrder_aux(bst);
    cout << "]" << endl;
}

/**
 * Prints the binary search tree in-order traversal.
 * Complexity: O(n)
 *
 * @tparam T The type of the element
 * @param root The root node of the tree
 */
template<typename T>
void BST<T>::printInOrder_aux(const BSTNode<T>* root) const {

    if(root == nullptr)
        return;

    printInOrder_aux(root->left);
    cout << root->element << ",";
    printInOrder_aux(root->right);
}

/**
 * Converts a binary search tree into a vector list.
 *
 * @tparam T The type of the element
 * @return A vector list
 */
template<typename T>
vector<T> BST<T>::bstToVector() const {

    vector<int> list;
    bstToVector_aux(bst, &list);
    return list;
}

/**
 * Converts a binary search tree into a vector list.
 *
 * @tparam T The type of the element
 * @param root The root node of the tree
 * @param list The list to store the elements
 */
template<typename T>
void BST<T>::bstToVector_aux(const BSTNode<T>* root, vector<T>* list) const {

    if(root == nullptr)
        return;

    bstToVector_aux(root->left, list);
    list->push_back(root->element);
    bstToVector_aux(root->right, list);
}


#endif
