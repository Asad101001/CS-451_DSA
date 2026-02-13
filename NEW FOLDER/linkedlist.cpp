#include <iostream>
using namespace std;

class Node{
public:
    int data;
    Node* next;

    Node (int val){
        data = val;
        next = NULL;
    }
};

class List{
    Node *head;
    Node *tail;

public:
    List(){
        head = tail = NULL;
    }

    void insert(int val){
        Node* newNode = new Node (val);
        if (head==NULL){
            head = tail = newNode;
            return;
        }
        else{
            newNode->next = head;
        }
    }

    void display(){
        Node *temp = head;
        while(temp->next != NULL){
            cout << temp->data << "";
            temp = temp->next;
        }
        cout << endl;
    }

};

int main(){

    List LL;

    LL.insert(12);
    LL.insert(21);

    LL.display();

    return 0;

}