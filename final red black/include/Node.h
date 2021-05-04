#ifndef NODE_H
#define NODE_H
#include <iostream>


class Node
{
public:
    Node();
    bool isRed;
    char* value;
    Node *parent;
    Node *leftChild;
    Node *rightChild;


    Node* getUncle()
    {
        Node* g = parent->parent;
        if(g->leftChild == parent)
            return g->rightChild;
        else
            return g->leftChild;
    }


    Node* getGrandParent()
    {
        return parent->parent;
    }
    virtual ~Node();

protected:

private:
};

#endif // NODE_H
