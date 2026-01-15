#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
};

Node* list = NULL;

void insert(int value) {
    Node* temp = new Node();  
    temp->data = value;
    temp->next = NULL;

    if (list == NULL) {
        list = temp;
    } else {
        Node* cur = list;
        while (cur->next != NULL) {
            cur = cur->next;
        }
        cur->next = temp;
    }
}

void display() {
    Node* cur = list;
    while (cur != NULL) {
        cout << cur->data << " -> ";
        cur = cur->next;
    }
    cout << "NULL" << endl;
}

int main() {
    int choice, val;

    while (true) {
        cout << "\n1- Insert\n2- Display\n3- Exit\n";
        cin >> choice;

        if (choice == 1) {
            cout << "Enter value: ";
            cin >> val;
            insert(val);
        }
        else if (choice == 2) {
            display();
        }
        else if (choice == 3) {
            break;
        }
        else {
            cout << "Invalid choice" << endl;
        }
    }

    return 0;
}