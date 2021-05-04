#ifndef RBTREE_H
#define RBTREE_H
#include "Node.h"
#include <iostream>
#include <string.h>
#include <stdexcept>
using namespace std;


class RBTree
{
public:
    RBTree();
    RBTree(char* filename);
    virtual ~RBTree();
    void insert(char* val)
    {
        insertNode(root,NULL,val);
    }

    void print()
    {
        printTree(root);
    }

    int height()
    {
        return getHeight(root);
    }

    void blackHeight()
    {
        cout<<"tree's black height = "<<getBlackHeigh(root)<<endl;
    }

    bool search(char *word)
    {
        return getSearch(root,word);

    }

    int size()
    {
        return numberOfElements;
    }
protected:

private:
    Node* root;
    int numberOfElements;
    void  rotateRight(Node *n)
    {
        Node* LCRC = n->leftChild->rightChild;
        Node* LC = n->leftChild;
        n->leftChild->parent = n->parent;
        n->leftChild = LCRC;
        if(LCRC != NULL)
            LCRC->parent = n;
        LC->rightChild = n;
        n->parent = LC;
        if(n == root)
            root = LC;
        else if(strcasecmp(LC->parent->value,LC ->value)>0)
            LC->parent->leftChild = LC;
        else if(strcasecmp(LC->parent->value,LC ->value)<0)
            LC->parent->rightChild = LC;


    }

    void  rotateleft(Node *n)
    {
        Node* RCLC = n->rightChild->leftChild;
        Node* RC = n->rightChild;
        n->rightChild->parent = n->parent;
        n->rightChild = RCLC;
        if(RCLC != NULL)
            RCLC->parent = n;
        RC->leftChild = n;
        n->parent = RC;
        if(n == root)
            root = RC;
        else if(strcasecmp(RC->parent->value,RC ->value)>0)
            RC->parent->leftChild = RC;
        else if(strcasecmp(RC->parent->value,RC ->value)<0)
            RC->parent->rightChild = RC;
    }

    void handleLeftLeftCase(Node *n, Node *gp)
    {
        rotateRight(n->getGrandParent());
        gp->isRed = true;
        gp->parent->isRed = false;
    }

    void handleLeftRightCase(Node *n, Node *gp)
    {
        rotateleft(n->parent);
        handleLeftLeftCase(n->leftChild,gp);
    }

    void handleRightRightCase(Node *n, Node *gp)
    {
        rotateleft(n->getGrandParent());
        gp->isRed = true;
        gp->parent->isRed = false;

    }

    void handleRightLeftCase(Node *n, Node *gp)
    {
        rotateRight(n->parent);
        handleRightRightCase(n->rightChild,gp);
    }

    void handleUncleRedCase(Node *n)
    {
        n->parent->isRed = false;
        n->getUncle()->isRed = false;
        n->getGrandParent()->isRed = true;
        if(n->getGrandParent() == root)
            root->isRed = false;
        else
            fix(n->getGrandParent());


    }

    Node* createNode(char* val, Node *p)
    {
        Node* temp = new Node();
        temp->value = val;
        temp->parent = p;
        if(numberOfElements == 0)
        {
            root = temp;
        }
        else if(strcasecmp(val, p->value)<0)
        {
            p->leftChild = temp;
        }
        else if(strcasecmp(val, p->value)>0)
        {
            p->rightChild = temp;
        }

        numberOfElements++;
        fix(temp);
        return temp;
    }

    void insertNode(Node *n,Node *p,char* val)
    {

        if(n == NULL)
            n = createNode(val,p);
        else if(strcasecmp(val, n->value)>0)
        {
            insertNode(n->rightChild,n,val);
        }
        else if(strcasecmp(val, n->value)<0)
        {
            insertNode(n->leftChild,n,val);
        }
        else if(strcasecmp(val, n->value)==0)
        {
            throw std::logic_error("");

        }


    }

    void fix(Node* n)
    {
        if(numberOfElements == 1)
            n->isRed = false;
        else if(n->parent->isRed == true && n->isRed == true)
        {
            if(n->getUncle() == NULL || n->getUncle()->isRed == false) // uncle is black
            {
                if(strcasecmp(n->value, n->parent->value) < 0 && strcasecmp(n->parent->value, n->getGrandParent()->value) < 0)
                    handleLeftLeftCase(n, n->getGrandParent());
                else if(strcasecmp(n->value, n->parent->value) > 0 && strcasecmp(n->parent->value, n->getGrandParent()->value) > 0)
                    handleRightRightCase(n, n->getGrandParent());
                else if(strcasecmp(n->value, n->parent->value) > 0&& strcasecmp(n->parent->value, n->getGrandParent()->value) < 0)
                    handleLeftRightCase(n, n->getGrandParent());
                else if(strcasecmp(n->value, n->parent->value) < 0 && strcasecmp(n->parent->value, n->getGrandParent()->value)>0)
                    handleRightLeftCase(n, n->getGrandParent());
            }
            else //uncle red
            {
                handleUncleRedCase(n);
            }
        }
    }

    void printTree(Node *node)
    {
        if(node == NULL)
            return;
        printTree(node->leftChild);
        cout << node->value<<"  ";
        if(node->isRed == true)
            cout<<"red"<<endl;
        else
            cout<<"black"<<endl;

        if(node->parent == NULL)
            cout <<" parent is "<<node->parent<<endl;
        else
            cout <<" parent is "<<node->parent->value<<endl;

        if(node->leftChild == NULL)
            cout <<" left child is "<<node->leftChild<<endl;
        else
            cout <<" left child is "<<node->leftChild->value<<endl;

        if(node->rightChild == NULL)
            cout <<" right child is "<<node->rightChild<<endl;
        else
            cout <<" right child is "<<node->rightChild->value<<endl;
        printTree(node->rightChild);
    }

    int getHeight(Node *node)
    {
        if (node == NULL)
            return -1;
        return 1 + max(getHeight(node->leftChild), getHeight(node->rightChild));
    }

    int getBlackHeigh(Node *n)
    {
        if(n == NULL)
            return -1;
        if(n->isRed == true)
            return getBlackHeigh(n->leftChild);
        return 1+ getBlackHeigh(n->leftChild);
    }

    bool getSearch(Node *node, char *target)
    {

        if(node == NULL)
            return false;

        if(strcasecmp(node->value, target) > 0)
            return getSearch(node->leftChild, target);
        if(strcasecmp(node->value, target) < 0)
            return getSearch(node->rightChild, target);

        return true;
    }

};

#endif // RBTREE_H
