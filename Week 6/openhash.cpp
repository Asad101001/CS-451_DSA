#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
};

Node HT[10];
int Size = 10;

void insert(int val) {
    int index = val % Size;
    if (HT[index].data == -1)
        HT[index].data = val;
    else {
        Node* temp = new Node;
        temp->data = val;
        temp->next = nullptr;
    }
}

void search(int val){
    int index = val % Size;
    Node* temp = HT[index].next;
    int pos = 1;
        while (temp->data != -1){
            if (temp->data == val){
                cout << "Value " << val << " found at position " << pos << endl;
                return;
            }
            temp = temp->next;
            pos++;
        }
        cout << "Value " << val << " not found at position "<< endl;
    }


int main() {
    for (int i = 0; i < Size; i++) {
        HT[i].data = -1;
        HT[i].next = nullptr;
    }
    insert(3);
    insert(4);
    insert(5);
    insert(6);
    insert(7);
    search(3);
    cout <<"values inserted";
}

