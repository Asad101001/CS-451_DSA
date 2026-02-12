#include <iostream>
#include <stdlib.h>
using namespace std;

struct Node {
    int data;
    Node* next;
};
Node* frontPtr = nullptr;
Node* rearPtr  = nullptr;   

void enqueue(int val) {
    Node* temp = new Node;
    temp->data = val;
    temp->next = nullptr;

    if (frontPtr == nullptr)         
        frontPtr = rearPtr = temp;
    else {
        rearPtr->next = temp;     
        rearPtr = temp;           
    }
}

bool dequeue(int &val) {
    if (frontPtr == nullptr) {       
        cout << "Queue is empty!" << endl;
        return false;
    }
    Node* temp = frontPtr;
    val = temp->data;             
    frontPtr = frontPtr->next;    
    if (frontPtr == nullptr)         
        rearPtr = nullptr;
    delete(temp);                   
    return true;
}

void display() {
    if (frontPtr == nullptr) {
        cout << "Queue is empty" << endl;
        return;
    }
    Node* cur = frontPtr;
    while (cur != nullptr) {
        cout << cur->data << " -> ";
        cur = cur->next;
    }
    cout << "NULL" << endl;
}

int main() {
    int val;
    enqueue(10);
    enqueue(23);
    enqueue(44);
    display();
    if (dequeue(val))
        cout << "Dequeued: " << val << endl;
    display();
    return 0;
}

