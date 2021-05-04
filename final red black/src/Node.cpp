#include "Node.h"
#include <iostream>

Node::Node()
{
    isRed = true;
    value = 0;
    leftChild = NULL;
    rightChild = NULL;
    parent = NULL;
}

Node::~Node()
{
    //dtor
}
