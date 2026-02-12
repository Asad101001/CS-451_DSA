#include <iostream>
using namespace std;

const int SIZE = 10;
int hashTable[SIZE];

// Initialize table with -1 (empty)
void initHashTable() {
    for (int i = 0; i < SIZE; i++)
        hashTable[i] = -1;
}

int hashFunc(int key) {
    return key % SIZE;
}

bool insert(int key) {
    int index = hashFunc(key);
    int startIndex = index;

    while (hashTable[index] != -1) {
        index = (index + 1) % SIZE;  // linear probing
        if (index == startIndex) {   // table full
            cout << "Hash Table is full!" << endl;
            return false;
        }
    }

    hashTable[index] = key;
    cout << "Inserted " << key << " at index " << index << endl;
    return true;
}

bool search(int key) {
    int index = hashFunc(key);
    int startIndex = index;

    while (hashTable[index] != -1) {
        if (hashTable[index] == key) {
            cout << "Key " << key << " found at index " << index << endl;
            return true;
        }
        index = (index + 1) % SIZE;
        if (index == startIndex)
            break;  // full circle
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
