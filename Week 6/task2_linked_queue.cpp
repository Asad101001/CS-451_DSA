/*
================================================================================
TASK 2: QUEUE USING DYNAMIC MEMORY (LINKED LIST)
================================================================================

WHAT IS A LINKED LIST QUEUE?
-----------------------------
A queue implemented using a singly linked list where:
- Elements are stored in dynamically allocated nodes
- Each node contains data and a pointer to the next node
- Front pointer points to first node (for dequeue)
- Rear pointer points to last node (for enqueue)

WHY LINKED LIST FOR QUEUE?
---------------------------
Array Queue Problems:
    ✗ Fixed size
    ✗ Wasted space (in simple array queue)
    ✗ Need modulo arithmetic (in circular queue)

Linked List Queue Advantages:
    ✓ Dynamic size (grows/shrinks as needed)
    ✓ No size limit (except system memory)
    ✓ No wasted space
    ✓ Simple logic (no modulo arithmetic)

MEMORY REPRESENTATION:
----------------------
Linked List Queue:
    front → [10|•]→[20|•]→[30|•]→[40|NULL] ← rear
             data next
             
Array Queue (for comparison):
    [10][20][30][40][  ][  ][  ]
     ↑              ↑
   front          rear

Python Comparison:
    from collections import deque
    queue = deque()      # No size limit
    queue.append(x)      # enqueue - O(1)
    queue.popleft()      # dequeue - O(1)
*/

#include <iostream>
using namespace std;

//==============================================================================
// NODE STRUCTURE
//==============================================================================

/*
QUEUE NODE
----------
Template structure to hold data and next pointer

Memory Layout of a Node:
+-------------------+
| data: value       | (size depends on T)
| next: address     | (8 bytes on 64-bit)
+-------------------+
*/
template <typename T>
struct QueueNode {
    T data;              // The value stored in this node
    QueueNode<T>* next;  // Pointer to next node in queue
    
    /*
    WHY TEMPLATE?
    Allows queue to store any type:
    - QueueNode<int>    → stores integers
    - QueueNode<double> → stores doubles
    - QueueNode<string> → stores strings
    
    Python doesn't need this - lists can hold any type
    */
};

//==============================================================================
// QUEUE STRUCTURE
//==============================================================================

/*
LINKED LIST QUEUE
-----------------
Contains two pointers and a size counter
*/
template <typename T>
struct Queue {
    QueueNode<T>* front;  // Points to first node (for dequeue)
    QueueNode<T>* rear;   // Points to last node (for enqueue)
    int size;             // Number of elements in queue
    
    /*
    WHY TWO POINTERS?
    
    With only front:
        - Dequeue: O(1) ✓
        - Enqueue: O(n) ✗ (must traverse to end)
    
    With front AND rear:
        - Dequeue: O(1) ✓
        - Enqueue: O(1) ✓ (direct access to rear)
    */
};

//==============================================================================
// INITIALIZATION
//==============================================================================

/*
INITIALIZE QUEUE
----------------
Create empty queue with nullptr pointers

Time Complexity: O(1)
Space Complexity: O(1)
*/
template <typename T>
void initQueue(Queue<T>* queue) {
    queue->front = nullptr;  // Empty queue
    queue->rear = nullptr;   // Empty queue
    queue->size = 0;
    
    /*
    VISUAL:
    front → NULL
    rear → NULL
    size = 0
    
    Python: queue = deque()
    */
}

//==============================================================================
// HELPER FUNCTIONS
//==============================================================================

/*
CHECK IF EMPTY
Time Complexity: O(1)
*/
template <typename T>
bool isEmpty(Queue<T>* queue) {
    return queue->front == nullptr;
    
    // Alternative: return queue->size == 0;
}

/*
GET SIZE
Time Complexity: O(1)
*/
template <typename T>
int getSize(Queue<T>* queue) {
    return queue->size;
}

//==============================================================================
// ENQUEUE OPERATION
//==============================================================================

/*
ENQUEUE - Add element to rear of queue
---------------------------------------

Steps:
1. Create new node with data
2. Set new node's next to nullptr (it will be last)
3. If queue is empty, both front and rear point to new node
4. Otherwise, link current rear to new node and update rear
5. Increment size

Time Complexity: O(1) - constant time operations
Space Complexity: O(1) - one new node

IMPORTANT: No overflow check needed (dynamic memory)!
Queue grows until system runs out of memory.
*/
template <typename T>
void enqueue(Queue<T>* queue, T value) {
    // Step 1: Allocate new node
    QueueNode<T>* newNode = new QueueNode<T>;
    newNode->data = value;
    newNode->next = nullptr;  // Will be last node
    
    /*
    MEMORY ALLOCATION:
    
    new QueueNode<T> allocates memory and returns address:
    
    0x1000: [value|NULL] ← newNode points here
    
    Python equivalent:
        new_node = {'data': value, 'next': None}
    */
    
    // Step 2: Check if queue is empty
    if (queue->rear == nullptr) {
        // First element - both front and rear point to it
        queue->front = newNode;
        queue->rear = newNode;
        
        /*
        VISUAL (first element):
        
        Before:
        front → NULL
        rear → NULL
        
        After enqueue(10):
        front → [10|NULL] ← rear
        */
    }
    else {
        // Step 3: Add to rear
        queue->rear->next = newNode;  // Link current rear to new node
        queue->rear = newNode;         // Update rear pointer
        
        /*
        VISUAL (adding to non-empty queue):
        
        Before enqueue(30):
        front → [10]→[20|NULL] ← rear
        
        Step 1 - Create node:
        newNode → [30|NULL]
        
        Step 2 - Link rear to new node:
        front → [10]→[20]→[30|NULL]
                      ↑    ↑
                    rear  newNode
        
        Step 3 - Update rear:
        front → [10]→[20]→[30|NULL] ← rear
        */
    }
    
    // Step 4: Increment size
    queue->size++;
}

//==============================================================================
// DEQUEUE OPERATION
//==============================================================================

/*
DEQUEUE - Remove and return front element
------------------------------------------

Steps:
1. Check if queue is empty (underflow)
2. Save data from front node
3. Save pointer to front node (for deletion)
4. Move front to next node
5. CRITICAL: If queue becomes empty, set rear to nullptr too!
6. Delete old front node (free memory)
7. Decrement size
8. Return saved data

Time Complexity: O(1)
Space Complexity: O(1)
*/
template <typename T>
T dequeue(Queue<T>* queue) {
    // Step 1: Check underflow
    if (isEmpty(queue)) {
        cout << "Error: Queue Underflow - Cannot dequeue from empty queue!" << endl;
        exit(1);
    }
    
    // Step 2: Save data to return
    T value = queue->front->data;
    
    // Step 3: Save pointer to node we're deleting
    QueueNode<T>* temp = queue->front;
    
    // Step 4: Move front to next node
    queue->front = queue->front->next;
    
    // Step 5: CRITICAL - If queue becomes empty, update rear!
    if (queue->front == nullptr) {
        queue->rear = nullptr;
    }
    
    /*
    WHY UPDATE REAR?
    
    Before dequeue (last element):
    front → [10|NULL] ← rear
    
    After front = front->next:
    front → NULL
    rear → [10|NULL]  ← DANGLING POINTER! (points to freed memory)
    
    Must set rear = nullptr to avoid accessing freed memory!
    
    Common mistake: Forgetting this step causes bugs!
    */
    
    // Step 6: Free memory
    delete temp;
    
    /*
    MEMORY DEALLOCATION:
    
    delete temp:
    - Calls destructor (if any)
    - Returns memory to system
    - temp still has old address (dangling pointer)
    
    Good practice:
        delete temp;
        temp = nullptr;  // Avoid dangling pointer
    
    Python: Automatic garbage collection, no manual delete needed
    */
    
    // Step 7: Decrement size
    queue->size--;
    
    return value;
    
    /*
    COMPLETE VISUAL:
    
    Before dequeue:
    front → [10]→[20]→[30|NULL] ← rear
    
    Save value = 10, temp points to first node
    
    Move front:
    temp → [10]
    front → [20]→[30|NULL] ← rear
    
    Delete temp:
    front → [20]→[30|NULL] ← rear
    [10] is freed
    */
}

//==============================================================================
// PEEK OPERATIONS
//==============================================================================

/*
GET FRONT - Peek at front element without removing
Time Complexity: O(1)
*/
template <typename T>
T getFront(Queue<T>* queue) {
    if (isEmpty(queue)) {
        cout << "Error: Queue is empty!" << endl;
        exit(1);
    }
    return queue->front->data;
    
    /*
    Python: queue[0] or queue.popleft() then append back
    */
}

/*
GET REAR - Peek at rear element without removing
Time Complexity: O(1)
*/
template <typename T>
T getRear(Queue<T>* queue) {
    if (isEmpty(queue)) {
        cout << "Error: Queue is empty!" << endl;
        exit(1);
    }
    return queue->rear->data;
    
    /*
    Python: queue[-1]
    */
}

//==============================================================================
// DISPLAY FUNCTION
//==============================================================================

/*
DISPLAY - Print all elements from front to rear
------------------------------------------------
Traverses the linked list without modifying it

Time Complexity: O(n) where n is number of elements
*/
template <typename T>
void display(Queue<T>* queue) {
    if (isEmpty(queue)) {
        cout << "Queue is empty" << endl;
        return;
    }
    
    cout << "Queue (front to rear): ";
    
    // Traverse from front to rear
    QueueNode<T>* current = queue->front;
    while (current != nullptr) {
        cout << current->data << " ";
        current = current->next;  // Move to next node
    }
    
    cout << endl;
    cout << "  [size=" << queue->size << "]" << endl;
    
    /*
    TRAVERSAL EXAMPLE:
    
    Queue: front → [10]→[20]→[30|NULL] ← rear
    
    current = front → [10]→...
    Print 10, current = current->next
    
    current → [20]→[30|NULL]
    Print 20, current = current->next
    
    current → [30|NULL]
    Print 30, current = current->next
    
    current → NULL
    Stop (while loop ends)
    
    Output: 10 20 30
    */
}

//==============================================================================
// CLEANUP
//==============================================================================

/*
DESTROY QUEUE - Free all memory
--------------------------------
Dequeues all elements to free all nodes

Time Complexity: O(n)
Space Complexity: O(1)

CRITICAL: Always call before program ends to prevent memory leaks!
*/
template <typename T>
void destroyQueue(Queue<T>* queue) {
    while (!isEmpty(queue)) {
        dequeue(queue);  // Each dequeue() deletes one node
    }
    
    /*
    WHY IS THIS NECESSARY?
    
    Without cleanup:
    - All nodes remain in memory after program ends
    - Operating system must reclaim memory
    - In long-running programs, causes MEMORY LEAKS
    
    Memory leak example:
        void processData() {
            Queue<int> q;
            initQueue(&q);
            enqueue(&q, 10);
            // ... use queue ...
            // Oops! Forgot to call destroyQueue(&q)
        }  // Function ends, but nodes still in memory!
    
    Python: Garbage collector handles this automatically
    */
}

//==============================================================================
// DEMONSTRATION
//==============================================================================

void demonstrateLinkedListQueue() {
    cout << "\n====================================================\n";
    cout << "  LINKED LIST QUEUE DEMONSTRATION\n";
    cout << "====================================================\n\n";
    
    // Create queue
    Queue<int> queue;
    initQueue(&queue);
    
    cout << "1. Created empty queue (dynamic memory)\n\n";
    
    // Enqueue elements
    cout << "2. Enqueuing: 10, 20, 30, 40, 50\n";
    enqueue(&queue, 10);
    enqueue(&queue, 20);
    enqueue(&queue, 30);
    enqueue(&queue, 40);
    enqueue(&queue, 50);
    display(&queue);
    
    cout << "\n3. Queue properties:\n";
    cout << "   Front element: " << getFront(&queue) << endl;
    cout << "   Rear element: " << getRear(&queue) << endl;
    cout << "   Size: " << getSize(&queue) << endl;
    
    // Dequeue some elements
    cout << "\n4. Dequeuing 2 elements:\n";
    cout << "   Dequeued: " << dequeue(&queue) << endl;
    cout << "   Dequeued: " << dequeue(&queue) << endl;
    display(&queue);
    
    // Enqueue more (showing dynamic growth)
    cout << "\n5. Enqueuing 60, 70, 80 (queue grows dynamically!):\n";
    enqueue(&queue, 60);
    enqueue(&queue, 70);
    enqueue(&queue, 80);
    display(&queue);
    
    // Dequeue all
    cout << "\n6. Dequeuing all elements:\n";
    while (!isEmpty(&queue)) {
        cout << "   Dequeued: " << dequeue(&queue) << endl;
    }
    display(&queue);
    
    // Test with different type
    cout << "\n7. Testing with strings:\n";
    Queue<string> strQueue;
    initQueue(&strQueue);
    
    enqueue(&strQueue, string("First"));
    enqueue(&strQueue, string("Second"));
    enqueue(&strQueue, string("Third"));
    display(&strQueue);
    
    cout << "   Front: " << getFront(&strQueue) << endl;
    dequeue(&strQueue);
    display(&strQueue);
    
    // Test with doubles
    cout << "\n8. Testing with doubles:\n";
    Queue<double> doubleQueue;
    initQueue(&doubleQueue);
    
    enqueue(&doubleQueue, 3.14);
    enqueue(&doubleQueue, 2.718);
    enqueue(&doubleQueue, 1.414);
    display(&doubleQueue);
    
    // Cleanup
    destroyQueue(&queue);
    destroyQueue(&strQueue);
    destroyQueue(&doubleQueue);
}

//==============================================================================
// APPLICATION: BFS-STYLE TRAVERSAL SIMULATION
//==============================================================================

void demonstrateApplication() {
    cout << "\n====================================================\n";
    cout << "  APPLICATION: Level-Order Processing\n";
    cout << "====================================================\n\n";
    
    Queue<string> taskQueue;
    initQueue(&taskQueue);
    
    cout << "Task Scheduler (FIFO processing):\n\n";
    
    // Add tasks
    cout << "Adding tasks to queue:\n";
    enqueue(&taskQueue, string("Task1: Send Email"));
    enqueue(&taskQueue, string("Task2: Update Database"));
    enqueue(&taskQueue, string("Task3: Generate Report"));
    enqueue(&taskQueue, string("Task4: Backup Files"));
    display(&taskQueue);
    
    // Process tasks
    cout << "\nProcessing tasks in FIFO order:\n";
    int taskNum = 1;
    while (!isEmpty(&taskQueue)) {
        string task = dequeue(&taskQueue);
        cout << "  [" << taskNum++ << "] Processing: " << task << endl;
        cout << "      Remaining tasks: " << getSize(&taskQueue) << endl;
    }
    
    destroyQueue(&taskQueue);
}

//==============================================================================
// MAIN FUNCTION
//==============================================================================

int main() {
    cout << "========================================================\n";
    cout << "  TASK 2: QUEUE USING DYNAMIC MEMORY (LINKED LIST)\n";
    cout << "========================================================\n";
    
    demonstrateLinkedListQueue();
    demonstrateApplication();
    
    cout << "\n========================================================\n";
    cout << "  All demonstrations completed successfully!\n";
    cout << "========================================================\n\n";
    
    return 0;
}

/*
================================================================================
KEY CONCEPTS SUMMARY
================================================================================

1. DYNAMIC MEMORY (new/delete):
   - new: Allocates memory on heap, returns address
   - delete: Frees memory and calls destructor
   - Must manually free all allocated memory to prevent leaks

2. LINKED LIST QUEUE:
   - Front pointer: for O(1) dequeue
   - Rear pointer: for O(1) enqueue
   - Size counter: track number of elements

3. ADVANTAGES:
   - Dynamic size (no fixed capacity)
   - No overflow (only limited by system memory)
   - Memory efficient (no pre-allocated space)
   - Simple logic (no modulo arithmetic)

4. DISADVANTAGES:
   - Extra memory for pointers (each node has 'next')
   - Cache unfriendly (nodes scattered in memory)
   - Must manually manage memory (new/delete)

5. TIME COMPLEXITIES:
   - Enqueue: O(1)
   - Dequeue: O(1)
   - Front/Rear: O(1)
   - isEmpty: O(1)
   - Display: O(n)
   - Destroy: O(n)

6. SPACE COMPLEXITY:
   - O(n) where n is number of elements
   - Each node uses: sizeof(T) + sizeof(pointer)

7. CRITICAL POINTS:
   - Update rear to nullptr when queue becomes empty
   - Always delete nodes to prevent memory leaks
   - Use destroyQueue() before program ends

8. COMPARISON WITH ARRAY QUEUE:
   
   | Feature | Array Queue | Linked List Queue |
   |---------|-------------|-------------------|
   | Size | Fixed | Dynamic |
   | Overflow | Yes | No (until memory full) |
   | Memory | Pre-allocated | As needed |
   | Cache | Friendly | Unfriendly |
   | Complexity | Modulo needed | Simple pointers |

================================================================================
COMPILATION AND EXECUTION:
   g++ -std=c++11 task2_linked_queue.cpp -o task2
   ./task2
================================================================================
*/
