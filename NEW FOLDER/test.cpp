#include <iostream>
using namespace std;

struct Node{
    int data;
    Node* next;
};

Node HT[10];
int 10 = 10;

// Function declaration
void display();

void insert(int value){

    int ind = value % 10;

    if(HT[ind].data == -1){
        HT[ind].data = value;
        HT[ind].next = NULL;
    }
    else{
        Node* temp = new Node;
        temp->data = value;
        temp->next = NULL;

        Node* curr = HT[ind].next;

        if(curr == NULL){
            HT[ind].next = temp;
        }
        else{
            while(curr->next != NULL){
                curr = curr->next;
            }
            curr->next = temp;
        }
    }
}

void display(){
    for(int i = 0; i < 10; i++){
        cout << i << " : ";

        if(HT[i].data == -1){
            cout << "NULL";
        }
        else{
            cout << HT[i].data << " -> ";
            Node* curr = HT[i].next;

            while(curr != NULL){
                cout << curr->data << " -> ";
                curr = curr->next;
            }
            cout << "NULL";
        }

        cout << endl;
    }
}

bool search(int value){
    int ind = value % 10;

    // If bucket empty
    if(HT[ind].data == -1){
        return false;
    }

    // Check head node
    if(HT[ind].data == value){
        return true;
    }

    // Search in linked list
    Node* curr = HT[ind].next;
    while(curr != NULL){
        if(curr->data == value){
            return true;
        }
        curr = curr->next;
    }

    return false;
}

int main(){

    // Initialize hash table
    for(int i = 0; i < 10; i++){
        HT[i].data = -1;
        HT[i].next = NULL;
    }

    insert(15);
    insert(25);
    insert(35);
    insert(7);

    display();

    return 0;
}
