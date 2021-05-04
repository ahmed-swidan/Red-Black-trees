#include <iostream>
#include "Node.h"
#include "RBTree.h"
#include "stdio.h"
using namespace std;

int main(int argc, char** argv)
{
    int mode;
    bool isLoaded = false, exit = false;
    RBTree *dict;
    while(!exit)
    {
        do
        {
            cout << "Choose the operation you would like to perform: 1- load dictionary 2- print dictionary size " <<
                 "3- insert a word 4- look-up a word 5- exit: ";
            cin >> mode;

        }
        while(mode < 1 || mode > 6);


        switch(mode)
        {
        case 1:
            dict = new RBTree("dictionary.txt");
            isLoaded = true;
            cout << "Dictionary has been loaded successfully!" << endl;
            break;
        case 2:
            if(isLoaded)
            {
                cout << "Height of the tree = " << dict->height() << endl;
                cout << "Size of the dictionary = " << dict->size() << endl;
            }
            else
                cout << "The dictionary isn't loaded yet!" << endl;
            break;
        case 3:
            if(isLoaded)
            {
                string temp;
                cout << "Type the word you would like to insert: ";
                cin >> temp;
                char newWord[temp.length() + 1];
                strcpy(newWord, temp.c_str());
                try
                {
                    dict->insert(newWord);
                }
                catch(const logic_error& e)
                {
                    cout << "ERROR: Word already in the dictionary!" << endl;
                }
            }
            else
                cout << "The dictionary isn't loaded yet!" << endl;
            break;
        case 4:
            if(isLoaded)
            {
                string temp;
                cout << "Type the word you would like to search: ";
                cin >> temp;
                char target[temp.length() + 1];
                strcpy(target, temp.c_str());
                bool isFound = dict->search(target);
                printf("The word %s.\n", isFound ? "exists" : "doesn't exist");
            }
            else
                cout << "The dictionary isn't loaded yet!" << endl;
            break;
        case 5:
            exit = true;
            break;
        }
    }
    return 0;
}
