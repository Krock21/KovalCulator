#include "Node.h"

Node::Node() : name("Noname"), val(-239)
{}

Node::Node(std::string name) : name(name), val(-239)
{}

Node::Node(long double val) : name("Noname"), val(val)
{}