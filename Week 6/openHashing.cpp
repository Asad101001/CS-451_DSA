#include <iostream>
using namespace std;

struct Node{
    int data;
    Node* next;
};

Node hashTable[10];
// int 10 = 10;

void insert (int value){
    int ind = value % 10;
    if (hashTable[ind].data==-1)
    {
        hashTable[ind].data= value;
    }
    else{
        Node *temp = new Node();
        temp -> data = value;
        temp -> next = NULL;
        Node *curr = hashTable[ind].next;
        if (curr==NULL){
            hashTable[ind].next= temp;
        }
        else{
            while (curr->next != NULL)
            {
            }   
        }
    }
}


void display(){
    for (int i = 0; i < 10; i++){
        if (hashTable[i].data==-1){
            cout << "NULL";
        }
        else{
            cout << hashTable[i].data << " , ";

            Node *curr = hashTable[i].next;
            while (curr != NULL)
            {
                cout << curr -> data << " , ";
                curr = curr -> next;
            }
            cout << " null ";
            }
            cout << endl;
    }
}    

int main(){
    for (int i = 0; i < 10; i++){
        hashTable[i].data = -1;
        hashTable[i].next = NULL;
    }

    insert(90);
    insert(41);
    insert(71);
    insert(61);
    insert(22);
    display();
}
