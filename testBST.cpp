#include <iostream>
#include <vector>
#include <ctime>
#include <cmath>
#include "BST.h"
#include "Stack.h"

using namespace std;

//Exercise 2: Binary Search Tree
const int MIN = 3;
const int MAX = 3;

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
const char ADDITION_SYMBOL = '+';
const char SUBTRACTION_SYMBOL = '-';
const char MULTIPLICATION_SYMBOL = '*';
const char DIVISION_SYMBOL = '/';
const char PARENTHESES_SYMBOL_OPEN = '(';
const char PARENTHESES_SYMBOL_CLOSE = ')';
const char SQUARE_BRACKETS_SYMBOL_OPEN = '[';
const char SQUARE_BRACKETS_SYMBOL_CLOSE = ']';
const char CURLY_BRACKETS_SYMBOL_OPEN = '{';
const char CURLY_BRACKETS_SYMBOL_CLOSE = '}';

string getExpression();
string infix_PostfixExpr(string);
bool isOperand(char);
bool isOperator(char);
int getPrecedence(char);
char getOppositeParentheses(char);
bool isUnexpectedParentheses(char, char);
BST<int>* infix_ExprTree(string);


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
    vector<int> list1 = genData(n1);
    cout << "The List1(" << n1 << "): ";
    printList(list1);

    int n2 = getInput();
    vector<int> list2 = genData(n2);
    cout << "The List2(" << n2 << "): ";
    printList(list2);

    BST<int>* bst1 = makeBST(list1);
    cout << "In-order traversal of bst1 is: ";
    printBT(bst1);

    BST<int>* bst2 = makeBST(list2);
    cout << "In-order traversal of bst2 is: ";
    printBT(bst2);

    remove(list1[n1/2], bst1);
    cout << "In-order traversal of bst1 after deleting " << list1[n1/2] <<" is : ";
    printBT(bst1);

    BST<int>* bst3 = mergeBST(bst1, bst2);
    cout << "In_order traversal of bst3 is: ";
    printBT(bst3);

    cout << "The height of bst1 is " << height(bst1) << endl;
    cout << "The height of bst2 is " << height(bst2) << endl;
    cout << "The height of merged tree is " << height(bst3) << endl;

    //Exercise 3: Expression Trees
    string infix = getExpression();
    cout << "The Post-fix expression is " << infix_PostfixExpr(infix) <<endl;

    BST<int>* bt4 = infix_ExprTree(infix);
    cout << "In-order traversal of bt4 is: ";
    printBT(bt4);

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
        //list.push_back(generateRandomNumber(-n, nTotal));
        list.push_back(i);

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
 * Complexity: O(n)
 *
 * @param bst The binary search tree
 */
void printBT(const BST<int>* bst) {
    bst->printInOrder();
}

/**
 * Calculates and returns the height of the binary tree.
 * Complexity: O(logn)
 *
 * @param bst The binary search tree
 * @return The height of the binary tree
 */
int height(const BST<int>* bst) {
    return bst->getHeight();
}

/**
 * Removes the element from the binary tree.
 * Complexity: TODO
 *
 * @param element The element to remove
 * @param bst The binary search tree to remove from
 */
void remove(int element, BST<int>* bst) {
    bst->remove(element);
};


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
BST<int>* mergeBST(const BST<int>* bstA, const BST<int>* bstB) {

    vector<int> temp;
    vector<int> bstAVector = bstA->bstToVector();
    vector<int> bstBVector = bstB->bstToVector();

    int i = 0, j = 0;

    // Traverse both vectors inserting in ascending order
    while (i < bstAVector.size() && j < bstBVector.size()) {
        if (bstAVector[i] < bstBVector[j])
            temp.push_back(bstAVector[i++]);
        else
            temp.push_back(bstBVector[j++]);
    }

    // Store remaining elements
    while (i < bstAVector.size())
        temp.push_back(bstAVector[i++]);
    while (j < bstBVector.size())
        temp.push_back(bstBVector[j++]);

    return new BST<int>(temp);
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
        cout << list[i] << ((i == list.size()-1)? "": ",");
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
 *
 * @return The infix expression
 */
string getExpression() {

    string infix;
    cout << "Please enter the expression: ";
    cin >> infix;

    return infix;
}

/**
 * Generates and returns a postfix expression from the infix expression given.
 * Complexity: TODO
 *
 * @param infix The infix expression
 * @return The postfix expression
 */
string infix_PostfixExpr(string infix) {

    if(isOperator(infix[0]))
        throw runtime_error("The expression is not infix");
    else if(infix.size() < 3)
        throw runtime_error("Expression too short");

    // This solves the issue of removing the opening parentheses
    infix = PARENTHESES_SYMBOL_OPEN + infix + PARENTHESES_SYMBOL_CLOSE;
    Stack<char> stack;
    string output;

    for (int i = 0; i < infix.size(); i++) {

        // 1. If the character is '(' or '{', push it to the stack
        if (infix[i] == PARENTHESES_SYMBOL_OPEN ||
            infix[i] == SQUARE_BRACKETS_SYMBOL_OPEN ||
            infix[i] == CURLY_BRACKETS_SYMBOL_OPEN)
            stack.push(infix[i]);

            // 2. If the character is ')', pop from the stack until its open tag '('
            // is found. Is going to add all the operators inside the parentheses,
            // and then, delete them.
        else if (infix[i] == PARENTHESES_SYMBOL_CLOSE ||
                 infix[i] == SQUARE_BRACKETS_SYMBOL_CLOSE ||
                 infix[i] == CURLY_BRACKETS_SYMBOL_CLOSE)
        {
            char openingSymbol = getOppositeParentheses(infix[i]);
            while (stack.getSize() > 0 && stack.top() != openingSymbol) {
                if(isUnexpectedParentheses(stack.top(), openingSymbol))
                    throw runtime_error("Error position " + to_string(i) + ": unexpected '" + infix[i] + "'");
                output += stack.pop();
            }
            // Removes the opening parentheses
            stack.pop();
        }

            // 3. If the character is an operator, pop from the stack until the same
            // operator is found.
        else if(isOperator(infix[i])) {
            while (stack.getSize() > 0 && getPrecedence(infix[i]) <= getPrecedence(stack.top()))
                output += stack.pop();
            // Push the operator to the stack (In the last iteration it's going
            // to push an item that is going to be added in the point 6
            stack.push(infix[i]);
        }

            // 4. If the character is an operand, add it to output
        else if (isOperand(infix[i]))
            output += infix[i];
        // 5. Everything else is discarded
    }

    return output;
}

/**
 * Checks and returns whether the character is an operand or not.
 * E.G.: 1, A
 *
 * @param c The character to check
 * @return Whether the character is an operand or not
 */
bool isOperand(char c) {
    return (isalpha(c) || isdigit(c));
}

/**
 * Checks and returns whether the character is a operator or not.
 * E.G.: +, -, *, /
 *
 * @param c The character to checked
 * @return Whether the character is a valid operator or not
 */
bool isOperator(char c) {
    return (c==ADDITION_SYMBOL ||
            c==SUBTRACTION_SYMBOL ||
            c==MULTIPLICATION_SYMBOL ||
            c==DIVISION_SYMBOL);
}

/**
 * Check and returns the precedence of the operator.
 * 1. Multiplications and divisions
 * 2. Additions and subtractions
 * Non-defined operators won't have any precedence
 *
 * @param o The operator to check
 * @return The precedence of the operator
 */
int getPrecedence(char o) {

    switch(o) {
        case MULTIPLICATION_SYMBOL:
        case DIVISION_SYMBOL:
            return 2;
        case ADDITION_SYMBOL:
        case SUBTRACTION_SYMBOL:
            return 1;
        default:
            return 0;
    }
}

/**
 * Exchange the parentheses for its opposite symbol.
 * @param s The text to change
 */
void exchangeParentheses(string& s) {

    if(s.empty())
        throw runtime_error("The string is empty");

    for (int i = 0; i < s.size(); i++)
        s[i] = getOppositeParentheses(s[i]);
}

/**
 * Returns the opposite of the defined parentheses symbols.
 * '(' returns ')'
 * @param c The character to find for
 * @return The opposite parentheses symbol
 */
char getOppositeParentheses(char c) {

    switch (c) {
        case PARENTHESES_SYMBOL_OPEN:
            return PARENTHESES_SYMBOL_CLOSE;
        case PARENTHESES_SYMBOL_CLOSE:
            return PARENTHESES_SYMBOL_OPEN;
        case SQUARE_BRACKETS_SYMBOL_OPEN:
            return SQUARE_BRACKETS_SYMBOL_CLOSE;
        case SQUARE_BRACKETS_SYMBOL_CLOSE:
            return SQUARE_BRACKETS_SYMBOL_OPEN;
        case CURLY_BRACKETS_SYMBOL_OPEN:
            return CURLY_BRACKETS_SYMBOL_CLOSE;
        case CURLY_BRACKETS_SYMBOL_CLOSE:
            return CURLY_BRACKETS_SYMBOL_OPEN;
        default:
            return c;
    }
}

bool isUnexpectedParentheses(char xxx, char s) {

    switch (s) {
        case PARENTHESES_SYMBOL_OPEN:
            return (xxx == SQUARE_BRACKETS_SYMBOL_OPEN || xxx == CURLY_BRACKETS_SYMBOL_OPEN);
        case SQUARE_BRACKETS_SYMBOL_OPEN:
            return (xxx == PARENTHESES_SYMBOL_OPEN || xxx == CURLY_BRACKETS_SYMBOL_OPEN);
        case CURLY_BRACKETS_SYMBOL_OPEN:
            return (xxx == PARENTHESES_SYMBOL_OPEN || xxx == SQUARE_BRACKETS_SYMBOL_OPEN);
        default:
            return true;
    }
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

    vector<int> list;
    return new BST<int>(list);
};
