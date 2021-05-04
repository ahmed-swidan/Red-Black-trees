#include "RBTree.h"
#include <iostream>
#include <string.h>
#include "stdlib.h"
#include "stdio.h"
#include <stdexcept>
RBTree::RBTree(char* filename)
{
    root = NULL;
    numberOfElements = 0;
    char temp[30];
    FILE *f = fopen(filename, "r");

    while(!feof(f))
    {
        fscanf(f, "%s\n", temp);
        char* word = (char*)malloc(sizeof(char)*strlen(temp) + 1);
        strcpy(word, temp);
        try
        {
            insert(word);
        }
        catch(const logic_error& e)
        {

        }
    }
    fclose(f);
}

RBTree::~RBTree()
{
    //dtor
}
