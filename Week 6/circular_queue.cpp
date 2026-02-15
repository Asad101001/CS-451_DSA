/*
================================================================================
TASK 1: CIRCULAR QUEUE USING STATIC MEMORY (ARRAY)
================================================================================

WHAT IS A CIRCULAR QUEUE?
--------------------------
A circular queue is a linear data structure that uses a FIXED-SIZE array and
treats the array as if it's circular (the end connects back to the beginning).

WHY CIRCULAR QUEUE?
-------------------
Problem with normal array queue:

Normal Queue:
    [X][X][X][ ][ ]  ← front=0, rear=3, 2 elements
    Dequeue 2 times:
    [ ][ ][X][ ][ ]  ← front=2, rear=3, WASTED SPACE!
    
    Can't use front positions even though they're empty!

Circular Queue Solution:
    [10][20][30][ ][ ]  ← front=0, rear=2
    Dequeue twice, enqueue 40, 50:
    [40][50][30][ ][ ]  ← front=2, rear=1 (wraps around!)
    
    Reuses empty positions efficiently!

CIRCULAR ARRAY CONCEPT:
-----------------------
Imagine the array bent into a circle:

    Index:  0   1   2   3   4
    Array: [10][20][30][40][50]
            ↑                ↑
         rear              front
         
    After reaching index 4, next index is 0 (wraps around)
    Formula: nextIndex = (currentIndex + 1) % SIZE

Python Comparison:
    from collections import deque
    queue = deque(maxlen=5)  # Fixed size
    queue.append(x)   # enqueue
    queue.popleft()   # dequeue
*/

#include <iostream>
using namespace std;

//==============================================================================
// CIRCULAR QUEUE STRUCTURE
//==============================================================================

template <typename T>
struct CircularQueue {
    T* arr;          // Pointer to array (static memory)
    int front;       // Index of front element
    int rear;        // Index of rear element
    int capacity;    // Maximum capacity
    int count;       // Current number of elements
    
    /*
    WHY BOTH rear AND count?
    
    Without count, we can't distinguish between:
    - Empty queue: front == rear
    - Full queue: front == rear (after wrapping)
    
    With count:
    - Empty: count == 0
    - Full: count == capacity
    */
};

//==============================================================================
// INITIALIZATION
//==============================================================================

/*
CREATE CIRCULAR QUEUE
---------------------
Allocate array of given capacity and initialize pointers

Time Complexity: O(1)
Space Complexity: O(capacity)
*/
template <typename T>
void initCircularQueue(CircularQueue<T>* queue, int capacity) {
    queue->arr = new T[capacity];  // Allocate array
    queue->capacity = capacity;
    queue->front = 0;
    queue->rear = -1;   // -1 indicates empty queue
    queue->count = 0;
    
    /*
    MEMORY LAYOUT:
    
    queue->arr → [  ][  ][  ][  ][  ]  (capacity = 5)
                  0   1   2   3   4
    front = 0
    rear = -1
    count = 0
    
    Python: queue = [None] * capacity
    */
}

//==============================================================================
// HELPER FUNCTIONS
//==============================================================================

/*
CHECK IF QUEUE IS FULL
Time Complexity: O(1)
*/
template <typename T>
bool isFull(CircularQueue<T>* queue) {
    return queue->count == queue->capacity;
    
    /*
    Alternative (without count):
        return (rear + 1) % capacity == front
    But this wastes one space to distinguish full from empty
    */
}

template <typename T>
bool isEmpty(CircularQueue<T>* queue) {
    return queue->count == 0;
}


template <typename T>
int size(CircularQueue<T>* queue) {
    return queue->count;
}

template <typename T>
void enqueue(CircularQueue<T>* queue, T value) {
    // Step 1: Check overflow
    if (isFull(queue)) {
        cout << "Error: Queue Overflow - Queue is full!" << endl;
        return;
    }
    
    // Step 2: Calculate new rear position (circular)
    queue->rear = (queue->rear + 1) % queue->capacity;
    
    /*
    VISUAL EXAMPLE (capacity = 5):
    
    Before: [10][20][30][40][  ]
            front=0, rear=3, count=4
    
    Enqueue(50):
    rear = (3 + 1) % 5 = 4
    
    After: [10][20][30][40][50]
           front=0, rear=4, count=5
    
    Enqueue(60) with wraparound:
    After dequeue twice: [  ][  ][30][40][50]
                         front=2, rear=4, count=3
    
    Enqueue(60):
    rear = (4 + 1) % 5 = 0  (WRAPS!)
    
    Result: [60][  ][30][40][50]
            front=2, rear=0, count=4
    */
    
    // Step 3: Insert element
    queue->arr[queue->rear] = value;
    
    // Step 4: Increment count
    queue->count++;
}

//==============================================================================
// DEQUEUE OPERATION
//==============================================================================

/*
DEQUEUE - Remove and return front element
------------------------------------------

Steps:
1. Check if queue is empty
2. Get element at front
3. Move front forward using modulo (circular wrap)
4. Decrement count
5. Return element

Time Complexity: O(1)
*/
template <typename T>
T dequeue(CircularQueue<T>* queue) {
    // Step 1: Check underflow
    if (isEmpty(queue)) {
        cout << "Error: Queue Underflow - Queue is empty!" << endl;
        exit(1);
    }
    
    // Step 2: Get front element
    T value = queue->arr[queue->front];
    
    // Step 3: Move front forward (circular)
    queue->front = (queue->front + 1) % queue->capacity;
    
    /*
    VISUAL EXAMPLE (capacity = 5):
    
    Before: [60][70][30][40][50]
            front=2, rear=1, count=5
    
    Dequeue():
    value = arr[2] = 30
    front = (2 + 1) % 5 = 3
    
    After:  [60][70][  ][40][50]
            front=3, rear=1, count=4
    
    Dequeue() with wraparound:
    Before: [60][70][  ][  ][  ]
            front=4, rear=1, count=2
    
    value = arr[4] = 50
    front = (4 + 1) % 5 = 0  (WRAPS!)
    
    After:  [60][70][  ][  ][  ]
            front=0, rear=1, count=1
    */
    
    // Step 4: Decrement count
    queue->count--;
    
    return value;
}

//==============================================================================
// PEEK OPERATIONS
//==============================================================================

/*
FRONT - Get front element without removing
Time Complexity: O(1)
*/
template <typename T>
T getFront(CircularQueue<T>* queue) {
    if (isEmpty(queue)) {
        cout << "Error: Queue is empty!" << endl;
        exit(1);
    }
    return queue->arr[queue->front];
}

/*
REAR - Get rear element without removing
Time Complexity: O(1)
*/
template <typename T>
T getRear(CircularQueue<T>* queue) {
    if (isEmpty(queue)) {
        cout << "Error: Queue is empty!" << endl;
        exit(1);
    }
    return queue->arr[queue->rear];
}

//==============================================================================
// DISPLAY FUNCTION
//==============================================================================

/*
DISPLAY - Print queue elements from front to rear
--------------------------------------------------
Important: Must handle circular nature correctly!
*/
template <typename T>
void display(CircularQueue<T>* queue) {
    if (isEmpty(queue)) {
        cout << "Queue is empty" << endl;
        return;
    }
    
    cout << "Queue (front to rear): ";
    
    // Start from front and traverse circularly
    int i = queue->front;
    int elementsDisplayed = 0;
    
    while (elementsDisplayed < queue->count) {
        cout << queue->arr[i] << " ";
        i = (i + 1) % queue->capacity;  // Move circularly
        elementsDisplayed++;
    }
    
    cout << endl;
    cout << "  [front=" << queue->front << ", rear=" << queue->rear 
         << ", count=" << queue->count << "]" << endl;
    
    /*
    EXAMPLE:
    Array: [60][70][  ][40][50]
    front=3, rear=1, count=4
    
    Traversal:
    i=3: print 40, i=(3+1)%5=4
    i=4: print 50, i=(4+1)%5=0
    i=0: print 60, i=(0+1)%5=1
    i=1: print 70
    
    Output: 40 50 60 70
    */
}

//==============================================================================
// CLEANUP
//==============================================================================

/*
DESTROY - Free allocated memory
Time Complexity: O(1)
*/
template <typename T>
void destroyCircularQueue(CircularQueue<T>* queue) {
    delete[] queue->arr;
    queue->arr = nullptr;
    queue->count = 0;
}

//==============================================================================
// DEMONSTRATION
//==============================================================================

void demonstrateCircularQueue() {
    cout << "\n====================================================\n";
    cout << "  CIRCULAR QUEUE DEMONSTRATION (Array-based)\n";
    cout << "====================================================\n\n";
    
    // Create circular queue with capacity 5
    CircularQueue<int> queue;
    initCircularQueue(&queue, 5);
    
    cout << "1. Created queue with capacity: 5\n\n";
    
    // Enqueue elements
    cout << "2. Enqueuing: 10, 20, 30, 40, 50\n";
    enqueue(&queue, 10);
    enqueue(&queue, 20);
    enqueue(&queue, 30);
    enqueue(&queue, 40);
    enqueue(&queue, 50);
    display(&queue);
    
    // Try to enqueue when full
    cout << "\n3. Trying to enqueue 60 (queue is full):\n";
    enqueue(&queue, 60);
    
    // Dequeue some elements
    cout << "\n4. Dequeuing 2 elements:\n";
    cout << "   Dequeued: " << dequeue(&queue) << endl;
    cout << "   Dequeued: " << dequeue(&queue) << endl;
    display(&queue);
    
    // Now enqueue (demonstrating circular nature)
    cout << "\n5. Enqueuing 60, 70 (using freed space - circular!):\n";
    enqueue(&queue, 60);
    enqueue(&queue, 70);
    display(&queue);
    
    cout << "\n6. Front element: " << getFront(&queue) << endl;
    cout << "   Rear element: " << getRear(&queue) << endl;
    cout << "   Size: " << size(&queue) << endl;
    
    // Dequeue all
    cout << "\n7. Dequeuing all elements:\n";
    while (!isEmpty(&queue)) {
        cout << "   Dequeued: " << dequeue(&queue) << endl;
    }
    display(&queue);
    
    // Test with strings
    cout << "\n8. Testing with strings (capacity=3):\n";
    CircularQueue<string> strQueue;
    initCircularQueue(&strQueue, 3);
    
    enqueue(&strQueue, string("Hello"));
    enqueue(&strQueue, string("World"));
    enqueue(&strQueue, string("DSA"));
    display(&strQueue);
    
    dequeue(&strQueue);
    enqueue(&strQueue, string("Circular"));
    display(&strQueue);
    
    // Cleanup
    destroyCircularQueue(&queue);
    destroyCircularQueue(&strQueue);
}

//==============================================================================
// MAIN FUNCTION
//==============================================================================

int main() {
    cout << "========================================================\n";
    cout << "  TASK 1: CIRCULAR QUEUE USING STATIC MEMORY (ARRAY)\n";
    cout << "========================================================\n";
    
    demonstrateCircularQueue();
    
    cout << "\n========================================================\n";
    cout << "  Demonstration completed successfully!\n";
    cout << "========================================================\n\n";
    
    return 0;
}

