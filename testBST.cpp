#include <iostream>
#include <vector>
#include <ctime>
#include <cmath>
#include "BST.h"

using namespace std;

const int MIN = 1;
const int MAX = 10;

//Exercise 2: Binary Search Tree
int getInput();
vector<int> genData(int);
BST<int>* makeBST(vector<int>&);
void printBT(const BST<int>*);
int height(const BST<int>*);
void remove(int, BST<int>*);
BST<int>* mergeBST(const BST<int>*, const BST<int>*);
void printList(const vector<int>&);
int generateRandomNumber(int, int);
//Exercise 3: Expression Trees
string getExpression();
string infix_PostfixExpr(string);
BST<int>* infix_ExprTree(string);
bool isHiger(char, char);
string pop(string);
bool isOperator(char);
int priorty(char);


/**
 * A3 Binary Trees
 * Ayaka Adachi (100225327)
 * Sergio Berlinches (100291288)
 * 06/29/18
 *
 * Learning Outcomes
 *
 * - Design, implement and analyze the tree-based algorithms in terms of time
 *   and space complexity.
 * - Design and implement the operations of binary search tree and expression
 *   trees.
 * - Write recursive solutions to non-trivial problems, such as binary search
 *   tree traversals.
 * - Develop C++ code based on the existing constraints.
 *
 * Description
 *
 * This is a practice on design, implement and analyzing problems using binary
 * search trees. Your final main function (testBST.cpp) should be compatible
 * with the following main function. By compatible it means the number of
 * parameters of each function should match. The type of parameters is
 * determined by your design and implementation. This makes some constraints in
 * your design, which is likely to occur in the real world.
 *
 */
int main() {

    srand(time(NULL));

    //Exercise 2: Binary Search Tree
    int n1 = getInput();
    //generates a list of n1 random numbers [-n1, n1]
    vector<int> list1 = genData(n1);
    cout << "The List1(" << n1 << "): ";
    printList(list1);

    int n2 = getInput();
    //generates a list of n2 random numbers [-n2, n2]
    vector<int> list2 = genData(n2);
    cout << "The List2(" << n2 << "): ";
    printList(list2);

    BST<int>* bst1 = makeBST(list1);
    cout << "In-order traversal of bst1 is: ";
    printBT(bst1);

    //removing the middle element of the corresponding tree
    // remove(list1[n1/2], bst1);

    // cout << "In-order traversal of bst1 after deleting " << list1[n1/2] <<" is : ";
    // printBT(bst1);

    // BST<int>* bst2 = makeBST(list2);
    // cout << "In-order traversal of bst2 is: ";
    // printBT(bst2);

    // BST<int>* bst3 = mergeBST(bst1, bst2);
    // cout << "In_order traversal of bst3 is: ";
    // printBT(bst3);

    // cout << "The height of bst1 is " << height(bst1) << endl;
    // cout << "The height of bst2 is " << height(bst2) << endl;
    // cout << "The height of merged tree is " << height(bst3) << endl;

    // //Exercise 3: Expression Trees
    // string infix = getExpression();
    // cout << "The Post-fix expression is " << infix_PostfixExpr(infix) <<endl;

    // BST<int>* bt4 = infix_ExprTree(infix);
    // cout << "In-order traversal of bt4 is: ";
    // printBT(bt4);

    return 0;
}

/**
 * Returns a random non-negative integer.
 * Complexity: O(1)
 *
 * @return a random non-negative integer
 */
int getInput() {
    return generateRandomNumber(MIN, MAX);
}

/**
 * Generates and returns a list of n random integers in the interval [-n, n].
 * Complexity: O(n)
 *
 * @param n A positive integer
 * @return A list of n random integers in the interval [-n, n]
 */
vector<int> genData(int n) {

    if(n <= 0)
        throw runtime_error("genData: n must be greater than zero.");

    vector<int> list;
    int nTotal = n*2+1;

    for (int i = 0; i < nTotal; ++i)
        list.push_back(generateRandomNumber(-n, nTotal));

    return list;
}

/**
 * Generates and returns a binary search tree.
 * Complexity: TODO
 *
 * @param list
 * @return A binary search tree
 */
BST<int>* makeBST(vector<int>& list) {

    if(list.empty())
        throw runtime_error("makeBST: The list cannot be empty.");

    return new BST<int>(list);
}

/**
 * Prints the binary tree using an in-order traversal.
 * complexity: TODO
 *
 * @param bst
 */
void printBT(const BST<int>* bst) {

    // printList(bst->getList());
}

/**
 * Calculates and returns the height of the binary tree.
 * Complexity: TODO
 *
 * @param bst The binary tree
 * @return The height of the binary tree
 */
int height(const BST<int>* bst) {

    int n = 0;
    return (int)ceil(log2(n)) + 1;
}

/**
 * Removes the key from the binary tree.
 * Complexity: TODO
 *
 * @param key
 * @param bst
 */
void remove(int key, BST<int>* bst) {};

/**
 * Write an efficient function (time and space efficient) named mergeBST()
 * which, given two binary search trees, merges them into one binary search
 * tree. Your algorithm should avoid ending up with an unbalanced BST. The
 * original BSTs must remain unchanged.
 * Complexity: TODO
 *
 * @param bstA
 * @param bstB
 * @return
 */
BST<int>* mergeBST( BST<int>* bstA,  BST<int>* bstB) {
    if (!bstA)
        return bstB;
    if (!bstB)
        return bstA;
    // bstA->elm += bstB->elm;
    // bstA->left = mergeBST(bstA->left, bstB->left);
    // bstA->right = mergeBST(bstA->right, bstB->right);
    // return bstA;
    // vector<int> list;
    // return new BST<int>(list);
};

/**
 * Prints the list on screen.
 * Complexity: O(n)
 *
 * @param list The list to print
 */
void printList(const vector<int>& list) {

    cout << "[";
    for(int i = 0; i < list.size(); i++)
        cout << list[i] << ((i == list.size()-1)? "": ", ");
    cout << "]" << endl;
}

/**
 * Generates and returns a random number in the interval of min and max.
 * Complexity: O(1)
 *
 * @param min The minimum number in the interval
 * @param max The maximum number in the interval
 * @return A random number in the interval of min and max
 */
int generateRandomNumber(int min, int max) {

    if(min > max)
        throw runtime_error("generateRandomNumber: The minimum number must be lower than the maximum number.");

    return rand() % max + min;
}

/**
 * Reads and returns an infix expression from input.
 * Complexity: TODO
 *
 * @return The infix expression
 */
string getExpression() {
    return "1+1";
}

/**
 * Generates and returns a postfix expression from the infix expression given.
 * Complexity: TODO
 *
 * @param infix The infix expression
 * @return The postfix expression
 */
string infix_PostfixExpr(string infix) {

    if(infix.empty())
        throw runtime_error("infix_PostfixExpr: The infix expression cannot be empty.");

    string postfix, stack;
    
    for(int i = 0; i < infix.length(); i++){
        if(isOperator(infix[i])){
            if(stack.empty()){
                stack.push_back(infix[i]);
            }
            else if(!stack.empty()){
                if(infix[i] == '(')
                    stack.push_back(infix[i]);
                else if(infix[i] == ')'){
                    while(*(stack.end()-1) != '('){
                        postfix.push_back(*(stack.end()-1));
                        stack = pop(stack);
                    }
                    stack = pop(stack);
                }
            }
            else {
                while(isHiger(*(stack.end()-1), infix[i])){
                    postfix.push_back(*(stack.end()-1));
                    stack = pop(stack);
                }
                if(!(isHiger(*(stack.end()-1), infix[i])))
                    stack.push_back(infix[i]);
            }

        }
    }
    while(!stack.empty()){
        string::iterator itr = stack.end() - 1;
        postfix.push_back(*itr);
        stack = pop(stack);
    }

    return postfix;
}

bool isOperator(char ch){
    switch(ch){
        case '+':
        case '-':
        case '*':
        case '/':
        case '(':
        case ')':
        case '^':
            return true;
        default:
            return false;
    }
}
 int priorty(char ch){
     switch(ch){
         case '+':
         case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
        default:
            return 0; 
     }
 }

 bool isHiger(char ch1, char ch2){
     if(priorty(ch1) >= priorty(ch2))
        return true;
    else
        return false;
 }

 string pop(string s){
     return s.substr(0, s.size()-1);
 }

/**
 * Generates and returns the expression tree from the infix expression given.
 * Complexity: TODO
 *
 * @param infix The infix expression
 * @return The expression tree from the infix expression given
 */
BST<int>* infix_ExprTree(string infix) {

    if(infix.empty())
        throw runtime_error("infix_ExprTree: The infix expression cannot be empty.");

    // vector<int> list;
    // return new BST<int>(list);
};

