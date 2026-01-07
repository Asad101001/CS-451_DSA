// Detailed Introduction to Data Structures and Algorithms (DSA) Concepts for Beginners in C++
// This file provides a comprehensive overview of fundamental DSA concepts with C++ implementations.
// Each section includes explanations, code examples, and key points to understand.

// Include necessary headers
#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <queue>
#include <list>
using namespace std;

// ===========================================
// 1. ARRAYS
// ===========================================
// Arrays are fixed-size containers that store elements of the same type in contiguous memory.
// Time Complexity: Access O(1), Insert/Delete O(n) in worst case.
// Use cases: When size is known and doesn't change frequently.

void demonstrateArrays() {
    cout << "=== ARRAYS ===" << endl;

    // Static array
    int arr[5] = {1, 2, 3, 4, 5};

    // Accessing elements
    cout << "Array elements: ";
    for(int i = 0; i < 5; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    // Dynamic array using vector (recommended in C++)
    vector<int> vec = {1, 2, 3, 4, 5};
    vec.push_back(6); // Add element
    cout << "Vector after adding 6: ";
    for(int num : vec) {
        cout << num << " ";
    }
    cout << endl << endl;
}

// ===========================================
// 2. LINKED LISTS
// ===========================================
// Linked lists are dynamic data structures where elements are stored in nodes.
// Each node contains data and a pointer to the next node.
// Time Complexity: Access O(n), Insert/Delete O(1) at known position.
// Use cases: When frequent insertions/deletions are needed.

struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

void demonstrateLinkedList() {
    cout << "=== LINKED LISTS ===" << endl;

    // Creating nodes
    Node* head = new Node(1);
    head->next = new Node(2);
    head->next->next = new Node(3);

    // Traversing
    cout << "Linked list: ";
    Node* current = head;
    while(current != nullptr) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;

    // Using std::list (doubly linked list)
    list<int> myList = {1, 2, 3};
    myList.push_back(4);
    cout << "std::list: ";
    for(int num : myList) {
        cout << num << " ";
    }
    cout << endl << endl;

    // Clean up memory
    delete head->next->next;
    delete head->next;
    delete head;
}

// ===========================================
// 3. STACKS
// ===========================================
// Stacks follow LIFO (Last In, First Out) principle.
// Operations: push (add), pop (remove), top (peek).
// Time Complexity: All operations O(1).
// Use cases: Function calls, undo operations, expression evaluation.

void demonstrateStack() {
    cout << "=== STACKS ===" << endl;

    stack<int> s;
    s.push(1);
    s.push(2);
    s.push(3);

    cout << "Stack top: " << s.top() << endl;
    s.pop();
    cout << "After pop, top: " << s.top() << endl;

    // Manual stack implementation
    cout << "Manual stack operations: ";
    vector<int> manualStack;
    manualStack.push_back(1);
    manualStack.push_back(2);
    manualStack.push_back(3);
    cout << "Top: " << manualStack.back() << endl;
    manualStack.pop_back();
    cout << "After pop, top: " << manualStack.back() << endl << endl;
}

// ===========================================
// 4. QUEUES
// ===========================================
// Queues follow FIFO (First In, First Out) principle.
// Operations: enqueue (add), dequeue (remove), front (peek).
// Time Complexity: All operations O(1).
// Use cases: Task scheduling, breadth-first search.

void demonstrateQueue() {
    cout << "=== QUEUES ===" << endl;

    queue<int> q;
    q.push(1);
    q.push(2);
    q.push(3);

    cout << "Queue front: " << q.front() << endl;
    q.pop();
    cout << "After dequeue, front: " << q.front() << endl;

    // Manual queue implementation
    cout << "Manual queue operations: ";
    deque<int> manualQueue;
    manualQueue.push_back(1);
    manualQueue.push_back(2);
    manualQueue.push_back(3);
    cout << "Front: " << manualQueue.front() << endl;
    manualQueue.pop_front();
    cout << "After dequeue, front: " << manualQueue.front() << endl << endl;
}

// ===========================================
// 5. SORTING ALGORITHMS
// ===========================================
// Sorting arranges elements in a specific order (ascending/descending).
// Common algorithms: Bubble Sort, Insertion Sort, Selection Sort.

// Bubble Sort: Repeatedly swap adjacent elements if they are in wrong order.
// Time Complexity: O(n^2) worst/average, O(n) best case.
void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for(int i = 0; i < n-1; i++) {
        for(int j = 0; j < n-i-1; j++) {
            if(arr[j] > arr[j+1]) {
                swap(arr[j], arr[j+1]);
            }
        }
    }
}

// Insertion Sort: Build sorted array one element at a time.
// Time Complexity: O(n^2) worst/average, O(n) best case.
void insertionSort(vector<int>& arr) {
    int n = arr.size();
    for(int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while(j >= 0 && arr[j] > key) {
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = key;
    }
}

// Selection Sort: Find minimum element and place it at beginning.
// Time Complexity: O(n^2) always.
void selectionSort(vector<int>& arr) {
    int n = arr.size();
    for(int i = 0; i < n-1; i++) {
        int minIdx = i;
        for(int j = i+1; j < n; j++) {
            if(arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }
        swap(arr[i], arr[minIdx]);
    }
}

void demonstrateSorting() {
    cout << "=== SORTING ALGORITHMS ===" << endl;

    vector<int> arr = {64, 34, 25, 12, 22, 11, 90};

    cout << "Original array: ";
    for(int num : arr) cout << num << " ";
    cout << endl;

    // Bubble Sort
    vector<int> bubbleArr = arr;
    bubbleSort(bubbleArr);
    cout << "Bubble Sort: ";
    for(int num : bubbleArr) cout << num << " ";
    cout << endl;

    // Insertion Sort
    vector<int> insertArr = arr;
    insertionSort(insertArr);
    cout << "Insertion Sort: ";
    for(int num : insertArr) cout << num << " ";
    cout << endl;

    // Selection Sort
    vector<int> selectArr = arr;
    selectionSort(selectArr);
    cout << "Selection Sort: ";
    for(int num : selectArr) cout << num << " ";
    cout << endl << endl;
}

// ===========================================
// 6. SEARCHING ALGORITHMS
// ===========================================
// Searching finds the position of a target element in a data structure.

// Linear Search: Check each element sequentially.
// Time Complexity: O(n)
int linearSearch(const vector<int>& arr, int target) {
    for(int i = 0; i < arr.size(); i++) {
        if(arr[i] == target) return i;
    }
    return -1;
}

// Binary Search: Divide and conquer on sorted array.
// Time Complexity: O(log n)
int binarySearch(const vector<int>& arr, int target) {
    int left = 0, right = arr.size() - 1;
    while(left <= right) {
        int mid = left + (right - left) / 2;
        if(arr[mid] == target) return mid;
        else if(arr[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

void demonstrateSearching() {
    cout << "=== SEARCHING ALGORITHMS ===" << endl;

    vector<int> arr = {2, 3, 4, 10, 40};
    int target = 10;

    // Linear Search
    int linearResult = linearSearch(arr, target);
    cout << "Linear Search for " << target << ": ";
    if(linearResult != -1) cout << "Found at index " << linearResult << endl;
    else cout << "Not found" << endl;

    // Binary Search
    int binaryResult = binarySearch(arr, target);
    cout << "Binary Search for " << target << ": ";
    if(binaryResult != -1) cout << "Found at index " << binaryResult << endl;
    else cout << "Not found" << endl << endl;
}

// ===========================================
// 7. TIME COMPLEXITY BASICS
// ===========================================
// Time complexity measures how the runtime of an algorithm grows with input size.
// Common complexities: O(1), O(log n), O(n), O(n log n), O(n^2), O(2^n)

void demonstrateTimeComplexity() {
    cout << "=== TIME COMPLEXITY BASICS ===" << endl;
    cout << "O(1): Constant time - accessing array element" << endl;
    cout << "O(log n): Logarithmic time - binary search" << endl;
    cout << "O(n): Linear time - linear search" << endl;
    cout << "O(n log n): Linearithmic time - merge sort, quick sort" << endl;
    cout << "O(n^2): Quadratic time - bubble sort, nested loops" << endl;
    cout << "O(2^n): Exponential time - recursive fibonacci without memoization" << endl;
    cout << endl;
}

// ===========================================
// MAIN FUNCTION
// ===========================================
int main() {
    cout << "WELCOME TO DSA CONCEPTS IN C++ FOR BEGINNERS!" << endl;
    cout << "This program demonstrates fundamental data structures and algorithms." << endl << endl;

    demonstrateArrays();
    demonstrateLinkedList();
    demonstrateStack();
    demonstrateQueue();
    demonstrateSorting();
    demonstrateSearching();
    demonstrateTimeComplexity();

    cout << "Congratulations! You've completed the DSA introduction." << endl;
    cout << "Next steps: Practice implementing these concepts, solve problems on platforms like LeetCode," << endl;
    cout << "and explore more advanced topics like trees, graphs, and dynamic programming." << endl;

    return 0;
}
