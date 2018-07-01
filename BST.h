#ifndef BST_H
#define BST_H

#include <vector>
#include <queue>
#include <iostream>
using namespace std;

/**
 * Exercise 1: BST class
 * Provide an appropriate data structure and necessary methods to build a binary
 * search tree which enables you to complete the rest of this assignment. Define
 * your class with generic types.
 */
template<typename T>
class Node{
    public:
        Node(){
            left = right = nullptr;
        }
        Node(const T& e, Node<T> *l = nullptr, Node<T> *r = nullptr){
            element = e;
            left = l;
            right = r;
        }
        T element;
        Node<T> *left, *right;
};
template <typename T>
class BST
{
  private:
    Node<T> *bst;

  public:
    BST(){
        bst = nullptr;
    }
    Node<T>* newNode(T);
    T* search(Node<T>* p, const T& ellm) const;
    BST(vector<T> &);
    // vector<T> getList() const;
    // void breadthFirst();
    // void preorder(Node<T>*);
    void inorder(Node<T>*);
    // void postorder(Node<T>*);
    void insert(Node<T>*, int);
    // void insert(const T&); //from the lecture
    Node<T>* getNode(int);
    int getHeight(Node<T>*);
    
    
};

/**
 * Creates a binary Search tree
 * @tparam T
 * @param list
 */
template <typename T>
BST<T>::BST(vector<T> &list) {
   
    Node<T>* some = new Node<T>(2);
}

// template <typename T>
// vector<T> BST<T>::getList() const {
//     return bst;

// }
template <typename T>
Node<T>* BST<T>::newNode(T element){
    Node<T>* temp = new Node<T>(element);
    temp->element = element;
    temp->left = temp->right = nullptr;
    return temp;

}
template <typename T>
T* BST<T>::search(Node<T>* p, const T& elm) const{
    while(p != nullptr){
        if(elm == p->elm)
            return &p->elm;
        else if(elm < p->elm)
            p = p->left;
        else
            p = p->right;
    }
    return nullptr;
}
template <typename T>
int BST<T>::getHeight(Node<T>* root){
    if(root == nullptr)
        return 0;
    else {
        int lb = getHeight(root->left);
        int rb = getHeight(root->right);
        return max(lb, rb) + 1;
    }
}
// template <typename T>
// void BST<T>::breadthFirst(){
//     Queue<Node<T>*> queue;
//     Node<T> *p = root;
//     if(p != nullptr){
//         queue.enqueu(p);
//         while(!queue.empty()){
//             p = queue.dequeue();
//             visit(p); //prints the node
//             if(p->left != nullptr)
//                 queue.enqueue(p->left);
//             if(p->right != nullptr)
//                 queue.enqueue(p->right);
//         }
//     }
// }
// template<typename T>
// void BST<T>::preorder(Node<T> *p){
//     if(p != nullptr){
//         visit(p);
//         preorder(p->left);
//         preorder(p->right);
//     }
// }

template <typename T>
void BST<T>::inorder(Node<T> *p){
    if(p != nullptr){
        inorder(p->left);
        visit(p);
        inorder(p->right);
    }
}
// template <typename T>
// void BST<T>::postorder(Node<T> *p){
//     if (p != nullptr)
//     {
//         postorder(p->left);
//         postorder(p->right);
//         visit(p);
//     }
// }
// void BST<T>::insert(T element, int child, int parent) {

//     int right = 2 * child + 2;
//     int left =  2 * child + 1;

//     if(bst.empty()) {
//         bst[child] = element;
//         return;
//     }

//     if(bst[parent] > element)
//         insert(element, right, parent);
//     else
//         insert(element, left, parent);
// }

//from the lecture
// template <typename T>
// void BST<T>::insert(const T& element)
// {
//     Node<T> *p = bst, *prev = nullptr;
//     while(p != nullptr){
//         prev = p;
//         if(element < p->element){
//             p = p->left;
//         }
//         else {
//             p = p->right;
//         }
//         if(bst == nullptr)
//             bst = new Node<T>(element);
//         else if (element < prev->element){
//             prev->left = new Node<T>(element);
//         }
//         else
//             prev->right = new Node<T>(element);

//     }
// }
template <typename T>
Node<T>* BST<T>:: getNode(int data){
    Node<T>* newNode = new Node<T>();
    newNode->left = nullptr;
    newNode->right = nullptr;
    return newNode;
}
template <typename T>
void BST<T>::insert(Node<T> *list, int data)
{
    if(list == nullptr)
        return getNode(data);
    if(data < list->data)
        list->left = insert(list->left, data);
    else if(data > list->data)
        list->right = insert(list->right, data);
    return list;
}

#endif
