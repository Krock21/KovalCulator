#ifndef CALCULATOR_NODE_H
#define CALCULATOR_NODE_H

#include <string>

class Node
{
public:
    std::string name;
    long double val;

    Node();

    Node(std::string name);

    Node(long double val);
};


#endif //CALCULATOR_NODE_H
