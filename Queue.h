//
// Created by Krock on 29.09.2016.
//

#ifndef CALCULATOR_QUEUE_H
#define CALCULATOR_QUEUE_H

#include <queue>
#include <iostream>
#include "Node.h"

class Queue
{
public:
    std::queue<Node> q;

    void push(Node val);

    Node top();

    Node pop();
    bool empty();
};


#endif //CALCULATOR_QUEUE_H
