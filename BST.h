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
    void insertList_aux(vector<T>&, int, int);
    void deleteByCopying(BSTNode<T>*);
    void bstToVector_aux(const BSTNode<T>*, vector<T>*) const;
public:
    BST(vector<T>& list);
    BSTNode<T>* getTree() const;
    BSTNode<T>* search(const T&);
    void insertList(vector<T>&);
    void insertElement(const T&);
    void deleteElement(T&);
    int getHeight(const BSTNode<T>*) const;
    void printInOrder(const BSTNode<T>*) const;
    BST<T>* merge(const BST<T>*) const;
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
 * Returns the binary search tree.
 *
 * @tparam T The type of the element
 * @return The binary search tree
 */
template<typename T>
BSTNode<T>* BST<T>::getTree() const {
    return bst;
}

/**
 * Search for an element in the binary search tree and returns its node.
 * Code extracted from the CPSC-2150 slides.
 *
 * @tparam T The type of the element
 * @param element The element to search for
 * @return The node of the element to search for
 */
template<typename T>
BSTNode<T>* BST<T>::search(const T& element) {

    BSTNode<T>* node = bst;

    while (node != nullptr) {
        // Base case. The element has been found.
        if (element == node->element)
            return node;
        // If the element to look for is smaller than the node's element,
        // sub-branch left
        else if (element < node->element)
            node = node->left;
        // If the element to look for is greater than the node's element,
        // sub-branch right
        else
            node = node->right;
    }

    return nullptr;
};

/**
 * Insert an element in the binary search tree.
 * Code extracted from the CPSC-2150 slides.
 *
 * @tparam T The type of the element
 * @param element The element to insert
 */
template<typename T>
void BST<T>::insertElement(const T& element) {

    BSTNode<T>* p = bst;
    BSTNode<T>* prev = nullptr;

    while(p != nullptr) {
        prev = p;
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
    else if (element < prev->element)
        prev->left = new BSTNode<T>(element);
    // If the element to insert is greater than the root,
    // is inserted in the right child
    else
        prev->right = new BSTNode<T>(element);
}

/**
 * Inserts a vector list and converts into a binary search tree.
 *
 * @tparam T The type of the element
 * @param list The list to insert
 */
template<typename T>
void BST<T>::insertList(vector<T>& list) {
    insertList_aux(list, list.size()-1, 0);
}

/**
 * Inserts a vector list and converts into a binary search tree.
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
        insertElement(list[min]);
        insertElement(list[max]);
        return;
    }
    // List of one element left
    if (max-min == 0) {
        //cout << " (1 left) INSERT: " << list[max] << endl;
        insertElement(list[max]);
        return;
    }

    //cout << " INSERT: " << list[mid] << endl;
    insertElement(list[mid]);
    insertList_aux(list, mid-1, min);
    insertList_aux(list, max, mid+1);
}

/**
 * Deletes an element from the tree.
 *
 * @tparam T The type of the element
 * @param element The element to delete
 */
template<typename T>
void BST<T>::deleteElement(T& element) {

    BSTNode<T>* node = search(element);

    if(node != nullptr)
        deleteByCopying(node);
}

/**
 * Deletes the node from the tree.
 * Code extracted from the CPSC-2150 slides.
 *
 * @tparam T The type of the element
 * @param node The node of the tree
 */
template<typename T>
void BST<T>::deleteByCopying(BSTNode<T>* node) {

    if(node == nullptr)
        return;

    BSTNode<T>* tmp = node;
    BSTNode<T>* prev;

    // Node to be deleted has only one child:
    // Copy the child to the node and delete the child
    if (node->right == nullptr)
        node = node->left;
    else if (node->left == nullptr)
        node = node->right;

    // Node to be deleted has two children:
    // Find inorder successor of the node. Copy contents of the inorder
    // successor to the node and delete the inorder successor.
    else { //TODO: Something is wrong here

        prev = node;
        // Finds the "right most node" int the left-subtree
        tmp = node->left;
        while (tmp->right != nullptr) {
            prev = tmp;
            tmp = tmp->right;
        }
        // Copy the value of the "right most node" to the node that is going to
        // be deleted
        node->element = tmp->element;

        if(prev == node)
            prev->left = tmp->left;
        else
            prev->right = tmp->left;
    }

    delete tmp;
}

/**
 * Calculates and returns the height of a balanced binary search tree.
 *
 * @tparam T The type of the element
 * @param root The root node of the tree
 * @return The height of a balanced binary search tree
 */
template<typename T>
int BST<T>::getHeight(const BSTNode<T>* root) const {

    if(root == nullptr)
        return 0;

    // Traverses to the deepest node of each side and return the deepest one.
    int leftHeight = getHeight(root->left);
    int rightHeight = getHeight(root->right);
    return max(leftHeight, rightHeight) + 1;
}

/**
 * Prints the binary search tree in-order traversal.
 *
 * @tparam T The type of the element
 * @param root The root node of the tree
 */
template<typename T>
void BST<T>::printInOrder(const BSTNode<T>* root) const {

    if(root == nullptr)
        return;

    printInOrder(root->left);
    cout << root->element << ",";
    printInOrder(root->right);
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
