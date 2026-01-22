#include <iostream>
#include <stdlib.h>
#include <vector>
using namespace std;

struct Node{
    int data;
    Node *next;
};

Node *list = NULL;

bool search(int value) {
    
    Node* cur = list;  
    int position = 0;  

    while (cur != NULL) {
        if (cur->data == value) {
            cout << "Value " << value << " found at position " << position << endl;
            return true;
        }
        cur = cur->next;
        position++;
    }

    cout << "Value " << value << " not found in list" << endl;
    return false;
}
