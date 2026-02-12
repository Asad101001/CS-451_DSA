#include <iostream>
using namespace std;

const int MAX = 5;
int queueArr[MAX];
int front = 0;
int rear = 0;

bool isEmpty() {
    return front == rear;
}

bool isFull() {
    return rear == MAX;
}

bool enqueue(int val) {
    if (isFull()) {
        cout << "Queue is full!" << endl;
        return false;
    }
    queueArr[rear++] = val;  // add at rear and increment
    return true;
}

bool dequeue(int &val) {
    if (isEmpty()) {
        cout << "Queue is empty!" << endl;
        return false;
    }
    val = queueArr[front++]; // remove from front and increment
    return true;
}

void display() {
    if (isEmpty()) {
        cout << "Queue is empty!" << endl;
        return;
    }
    cout << "Queue elements: ";
    for (int i = front; i < rear; i++)
        cout << queueArr[i] << " ";
    cout << endl;
}

int main() {
    int val;

    enqueue(10);
    enqueue(20);
    enqueue(30);
    display();       
    dequeue(val);
    cout << "Dequeued: " << val << endl; 
    display();       
    enqueue(40);
    enqueue(50);
    enqueue(60);     
    display();       
    return 0;
}
