#include <iostream>
using namespace std;

const int SIZE = 10;
int hashTable[SIZE];

void initHashTable() {
    for (int i = 0; i < SIZE; i++)
        hashTable[i] = -1;  // -1 means empty
}

int hashFunc(int key) {
    return key % SIZE;
}

bool insert(int key) {
    int index = hashFunc(key);
    int i = 0;  // step counter

    while (i < SIZE) {
        int newIndex = (index + i * i) % SIZE;  // quadratic probing
        if (hashTable[newIndex] == -1) {
            hashTable[newIndex] = key;
            cout << "Inserted " << key << " at index " << newIndex << endl;
            return true;
        }
        i++;
    }

    cout << "Hash Table is full! Cannot insert " << key << endl;
    return false;
}

bool search(int key) {
    int index = hashFunc(key);
    int i = 0;

    while (i < SIZE) {
        int newIndex = (index + i * i) % SIZE;
        if (hashTable[newIndex] == key) {
            cout << "Key " << key << " found at index " << newIndex << endl;
            return true;
        }
        if (hashTable[newIndex] == -1) break; // empty spot, key not present
        i++;
    }

    cout << "Key " << key << " not found in hash table" << endl;
    return false;
}

void display() {
    cout << "Hash Table: ";
    for (int i = 0; i < SIZE; i++) {
        if (hashTable[i] != -1)
            cout << hashTable[i] << " ";
        else
            cout << "_ ";
    }
    cout << endl;
}

int main() {
    initHashTable();
    insert(10);
    insert(20);
    insert(30);
    insert(25);
    insert(35);
    display();
    search(20);
    search(50);
    return 0;
}
