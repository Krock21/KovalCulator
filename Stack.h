#ifndef CALCULATOR_STACK_H
#define CALCULATOR_STACK_H

#include <stack>
#include <iostream>
#include "Node.h"

class Stack
{
public:
    std::stack<Node> st;

    void push(Node val);

    Node top();

    Node pop();

    bool empty();
};


#endif //CALCULATOR_STACK_H
