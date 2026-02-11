#include <iostream>
#include <cstdlib>  
using namespace std;

template <typename T>
struct StackNode {
    T data;              // The actual value stored
    StackNode<T>* next;  // Pointer to next node (towards bottom of stack)
};

template <typename T>
struct Stack {
    StackNode<T>* top;  // Pointer to the top node
    int size;           // Number of elements in stack
};


template <typename T>
void initStack(Stack<T>* stack) {
    stack->top = nullptr;  // Empty stack - top points to nothing
    stack->size = 0;       // No elements yet

}

template <typename T>
void push(Stack<T>* stack, T value) {

    StackNode<T>* newNode = new StackNode<T>;
    
    newNode->data = value;
    
    newNode->next = stack->top;
    
    stack->top = newNode;
    
    stack->size++;

}

template <typename T>
T pop(Stack<T>* stack) {
    
    if (stack->top == nullptr) {
        cout << "Error: Stack Underflow - Cannot pop from empty stack!" << endl;
        exit(1);
    }
    
    T value = stack->top->data;
    
    StackNode<T>* temp = stack->top;
    
    stack->top = stack->top->next;
    
    delete temp;
    
    stack->size--;
    
    return value;
    
}

template <typename T>
T peek(Stack<T>* stack) {
    if (stack->top == nullptr) {
        cout << "Error: Stack is empty!" << endl;
        exit(1);
    }
    
    return stack->top->data;
    
}

template <typename T>
bool isEmpty(Stack<T>* stack) {
    return stack->top == nullptr;
}

template <typename T>
int getSize(Stack<T>* stack) {
    return stack->size;
}

template <typename T>
void displayStack(Stack<T>* stack) {
    if (isEmpty(stack)) {
        cout << "Stack is empty" << endl;
        return;
    }
    
    cout << "Stack (top to bottom): ";
    StackNode<T>* current = stack->top;
    
    // Traverse the linked list
    while (current != nullptr) {
        cout << current->data << " ";
        current = current->next;  // Move to next node
    }
    cout << endl;
    
    /*
    TRAVERSAL VISUALIZATION:
    
    current → [30] → [20] → [10] → NULL
    Print 30
              current → [20] → [10] → NULL
              Print 20
                        current → [10] → NULL
                        Print 10
                                  current → NULL
                                  Stop (current == nullptr)
    */
}

//==============================================================================
// PART 3: QUEUE - DETAILED EXPLANATION  
//==============================================================================

/*
QUEUE: First-In-First-Out (FIFO)
---------------------------------

REAL-WORLD ANALOGY:
A queue at a ticket counter:
- People JOIN at the BACK (rear/tail)
- People LEAVE from the FRONT
- The FIRST person in line is the FIRST to be served

VISUAL REPRESENTATION:

    enqueue(10)              enqueue(20)              dequeue()
    
    front → [10] ← rear     front → [10] → [20] ← rear    front → [20] ← rear
    
WHY TWO POINTERS (FRONT AND REAR)?
- To make both enqueue and dequeue O(1)
- Front pointer: for efficient removal
- Rear pointer: for efficient addition

QUEUE OPERATIONS:
- enqueue(value) : Add element to rear
- dequeue()      : Remove and return front element
- front()/peek() : Look at front element without removing
- isEmpty()      : Check if queue is empty
*/

// Node structure for Queue
template <typename T>
struct QueueNode {
    T data;
    QueueNode<T>* next;
};

// Queue structure with TWO pointers
template <typename T>
struct Queue {
    QueueNode<T>* front;  // Points to first element (for dequeue)
    QueueNode<T>* rear;   // Points to last element (for enqueue)
    int size;
    
    /*
    WHY TWO POINTERS?
    
    With only front pointer:
        enqueue would be O(n) - need to traverse to end
        dequeue would be O(1)
    
    With both front and rear:
        enqueue is O(1) - direct access to rear
        dequeue is O(1) - direct access to front
    */
};

/*
CREATING A QUEUE - INITIALIZATION
----------------------------------
*/
template <typename T>
void initQueue(Queue<T>* queue) {
    queue->front = nullptr;  // Empty queue
    queue->rear = nullptr;   // Empty queue
    queue->size = 0;
    
    /*
    Python equivalent:
        from collections import deque
        queue = deque()
    
    Or using list (but inefficient):
        queue = []
    */
}

/*
ENQUEUE OPERATION - Adding to Queue
------------------------------------
Steps:
1. Create new node with data
2. If queue is empty, both front and rear point to new node
3. If queue has elements, link rear to new node and update rear
4. Increment size

TIME COMPLEXITY: O(1)
*/
template <typename T>
void enqueue(Queue<T>* queue, T value) {
    // Step 1: Create new node
    QueueNode<T>* newNode = new QueueNode<T>;
    newNode->data = value;
    newNode->next = nullptr;  // New node will be at the end
    
    // Step 2: Check if queue is empty
    if (queue->rear == nullptr) {
        // First element - both front and rear point to it
        queue->front = newNode;
        queue->rear = newNode;
        
        /*
        VISUAL:
        front → [10] ← rear
                 ↓
               NULL
        */
    }
    else {
        // Step 3: Add to rear
        queue->rear->next = newNode;  // Link current rear to new node
        queue->rear = newNode;         // Update rear to new node
        
        /*
        VISUAL STEP-BY-STEP for enqueue(30):
        
        Before:
        front → [10] → [20] ← rear
                        ↓
                      NULL
        
        After rear->next = newNode:
        front → [10] → [20] → [30] ← newNode
                 ↑            ↑
               rear          NULL
        
        After rear = newNode:
        front → [10] → [20] → [30] ← rear
                               ↓
                             NULL
        */
    }
    
    // Step 4: Increment size
    queue->size++;
}

/*
DEQUEUE OPERATION - Removing from Queue
----------------------------------------
Steps:
1. Check if queue is empty (underflow)
2. Save front node's data
3. Move front pointer to next node
4. If queue becomes empty, update rear to nullptr too
5. Delete old front node
6. Decrement size
7. Return saved data

TIME COMPLEXITY: O(1)
*/
template <typename T>
T dequeue(Queue<T>* queue) {
    // Step 1: Check for underflow
    if (queue->front == nullptr) {
        cout << "Error: Queue Underflow - Cannot dequeue from empty queue!" << endl;
        exit(1);
    }
    
    // Step 2: Save data to return
    T value = queue->front->data;
    
    // Step 3: Save pointer to node we're deleting
    QueueNode<T>* temp = queue->front;
    
    // Step 4: Move front to next node
    queue->front = queue->front->next;
    
    // Step 5: IMPORTANT - If queue becomes empty, update rear too!
    if (queue->front == nullptr) {
        queue->rear = nullptr;
    }
    
    /*
    WHY UPDATE REAR?
    
    If we remove the last element:
    Before: front → [10] ← rear
    
    After front = front->next:
    front → NULL
    But rear still points to [10]! (DANGLING POINTER)
    
    We must set rear = nullptr to avoid accessing freed memory
    */
    
    // Step 6: Free memory
    delete temp;
    
    // Step 7: Decrement size
    queue->size--;
    
    return value;
    
    /*
    Python equivalent:
        if not queue:
            raise IndexError("Queue is empty")
        return queue.popleft()  # Using deque
    */
}

/*
FRONT/PEEK OPERATION
--------------------
Return front element without removing

TIME COMPLEXITY: O(1)
*/
template <typename T>
T frontElement(Queue<T>* queue) {
    if (queue->front == nullptr) {
        cout << "Error: Queue is empty!" << endl;
        exit(1);
    }
    return queue->front->data;
}

/*
REAR OPERATION
--------------
Return rear element without removing

TIME COMPLEXITY: O(1)
*/
template <typename T>
T rearElement(Queue<T>* queue) {
    if (queue->rear == nullptr) {
        cout << "Error: Queue is empty!" << endl;
        exit(1);
    }
    return queue->rear->data;
}

/*
IS EMPTY CHECK FOR QUEUE
------------------------
*/
template <typename T>
bool isQueueEmpty(Queue<T>* queue) {
    return queue->front == nullptr;
    
    // Could also check: queue->rear == nullptr
    // Or: queue->size == 0
}

/*
GET QUEUE SIZE
--------------
*/
template <typename T>
int getQueueSize(Queue<T>* queue) {
    return queue->size;
}

/*
DISPLAY QUEUE - For Debugging
------------------------------
*/
template <typename T>
void displayQueue(Queue<T>* queue) {
    if (isQueueEmpty(queue)) {
        cout << "Queue is empty" << endl;
        return;
    }
    
    cout << "Queue (front to rear): ";
    QueueNode<T>* current = queue->front;
    
    while (current != nullptr) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

//==============================================================================
// PART 4: CLEANUP - FREEING MEMORY
//==============================================================================

/*
DESTROY STACK - Free All Memory
--------------------------------
VERY IMPORTANT: Prevent memory leaks!

When you're done with a stack, you must free all nodes
*/
template <typename T>
void destroyStack(Stack<T>* stack) {
    while (!isEmpty(stack)) {
        pop(stack);  // pop() already deletes nodes
    }
    
    /*
    Why is this necessary?
    
    Without cleanup:
    - All nodes remain in memory after program ends
    - Operating system must reclaim memory
    - In long-running programs, causes memory leaks
    
    Python comparison:
    - Python's garbage collector handles this automatically
    - When stack goes out of scope, memory is freed
    */
}

/*
DESTROY QUEUE - Free All Memory
--------------------------------
*/
template <typename T>
void destroyQueue(Queue<T>* queue) {
    while (!isQueueEmpty(queue)) {
        dequeue(queue);  // dequeue() already deletes nodes
    }
}

//==============================================================================
// PART 5: DEMONSTRATIONS AND APPLICATIONS
//==============================================================================

void demonstrateStack() {
    cout << "\n========================================" << endl;
    cout << "    STACK DEMONSTRATION (LIFO)" << endl;
    cout << "========================================\n" << endl;
    
    // Create a stack
    Stack<int> myStack;
    initStack(&myStack);
    
    cout << "1. Pushing elements: 10, 20, 30, 40, 50" << endl;
    push(&myStack, 10);
    push(&myStack, 20);
    push(&myStack, 30);
    push(&myStack, 40);
    push(&myStack, 50);
    displayStack(&myStack);
    
    cout << "\n2. Stack size: " << getSize(&myStack) << endl;
    cout << "   Top element (peek): " << peek(&myStack) << endl;
    
    cout << "\n3. Popping 2 elements:" << endl;
    cout << "   Popped: " << pop(&myStack) << endl;
    cout << "   Popped: " << pop(&myStack) << endl;
    displayStack(&myStack);
    
    cout << "\n4. After operations:" << endl;
    cout << "   New top: " << peek(&myStack) << endl;
    cout << "   Size: " << getSize(&myStack) << endl;
    
    // Test with different type - strings
    cout << "\n5. Stack with strings:" << endl;
    Stack<string> stringStack;
    initStack(&stringStack);
    push(&stringStack, string("Hello"));
    push(&stringStack, string("World"));
    push(&stringStack, string("DSA"));
    displayStack(&stringStack);
    
    // Cleanup
    destroyStack(&myStack);
    destroyStack(&stringStack);
}

void demonstrateQueue() {
    cout << "\n========================================" << endl;
    cout << "    QUEUE DEMONSTRATION (FIFO)" << endl;
    cout << "========================================\n" << endl;
    
    // Create a queue
    Queue<int> myQueue;
    initQueue(&myQueue);
    
    cout << "1. Enqueuing elements: 10, 20, 30, 40, 50" << endl;
    enqueue(&myQueue, 10);
    enqueue(&myQueue, 20);
    enqueue(&myQueue, 30);
    enqueue(&myQueue, 40);
    enqueue(&myQueue, 50);
    displayQueue(&myQueue);
    
    cout << "\n2. Queue info:" << endl;
    cout << "   Size: " << getQueueSize(&myQueue) << endl;
    cout << "   Front element: " << frontElement(&myQueue) << endl;
    cout << "   Rear element: " << rearElement(&myQueue) << endl;
    
    cout << "\n3. Dequeuing 2 elements:" << endl;
    cout << "   Dequeued: " << dequeue(&myQueue) << endl;
    cout << "   Dequeued: " << dequeue(&myQueue) << endl;
    displayQueue(&myQueue);
    
    cout << "\n4. After operations:" << endl;
    cout << "   New front: " << frontElement(&myQueue) << endl;
    cout << "   New rear: " << rearElement(&myQueue) << endl;
    cout << "   Size: " << getQueueSize(&myQueue) << endl;
    
    // Test with doubles
    cout << "\n5. Queue with doubles:" << endl;
    Queue<double> doubleQueue;
    initQueue(&doubleQueue);
    enqueue(&doubleQueue, 3.14);
    enqueue(&doubleQueue, 2.71);
    enqueue(&doubleQueue, 1.41);
    displayQueue(&doubleQueue);
    
    // Cleanup
    destroyQueue(&myQueue);
    destroyQueue(&doubleQueue);
}

// Application: Reverse a string using stack
void reverseStringDemo() {
    cout << "\n========================================" << endl;
    cout << "    APPLICATION: Reverse String" << endl;
    cout << "========================================\n" << endl;
    
    string original = "HELLO";
    Stack<char> charStack;
    initStack(&charStack);
    
    cout << "Original string: " << original << endl;
    
    // Push all characters
    for (int i = 0; i < original.length(); i++) {
        push(&charStack, original[i]);
    }
    
    // Pop all characters to reverse
    cout << "Reversed string: ";
    while (!isEmpty(&charStack)) {
        cout << pop(&charStack);
    }
    cout << endl;
    
    /*
    How it works:
    Push H → E → L → L → O  (top)
    Pop  O → L → L → E → H   (LIFO reverses order!)
    */
    
    destroyStack(&charStack);
}

// Application: Check balanced parentheses
void balancedParenthesesDemo() {
    cout << "\n========================================" << endl;
    cout << "    APPLICATION: Balanced Parentheses" << endl;
    cout << "========================================\n" << endl;
    
    string expr1 = "((a+b)*c)";
    string expr2 = "((a+b)*c";
    
    // Check expression 1
    Stack<char> stack1;
    initStack(&stack1);
    bool balanced = true;
    
    cout << "Expression: " << expr1 << endl;
    
    for (int i = 0; i < expr1.length(); i++) {
        if (expr1[i] == '(') {
            push(&stack1, '(');
        }
        else if (expr1[i] == ')') {
            if (isEmpty(&stack1)) {
                balanced = false;
                break;
            }
            pop(&stack1);
        }
    }
    
    if (!isEmpty(&stack1)) balanced = false;
    cout << "Result: " << (balanced ? "Balanced ✓" : "Not Balanced ✗") << endl;
    
    destroyStack(&stack1);
}

//==============================================================================
// MAIN FUNCTION
//==============================================================================

int main() {
    cout << "================================================" << endl;
    cout << "  STACK & QUEUE - Procedural Implementation" << endl;
    cout << "  Using Templates, Pointers, and Dynamic Memory" << endl;
    cout << "================================================" << endl;
    
    demonstrateStack();
    demonstrateQueue();
    reverseStringDemo();
    balancedParenthesesDemo();
    
    cout << "\n================================================" << endl;
    cout << "  All demonstrations completed!" << endl;
    cout << "================================================\n" << endl;
    
    return 0;
}

/*
================================================================================
KEY CONCEPTS SUMMARY
================================================================================

1. POINTERS:
   - Store memory addresses
   - & operator: get address
   - * operator: dereference (get value at address)
   - nullptr: points to nothing

2. DYNAMIC MEMORY:
   C++:  new/delete
   C:    malloc/free
   Python: automatic garbage collection

3. TEMPLATES:
   - Write code once, use for any type
   - template <typename T>
   - Compiler generates type-specific code

4. STACK (LIFO):
   - push: O(1)
   - pop: O(1)
   - peek: O(1)
   - One pointer: top

5. QUEUE (FIFO):
   - enqueue: O(1)
   - dequeue: O(1)
   - Two pointers: front and rear

6. MEMORY LEAKS:
   - Always delete/free what you new/malloc
   - Use destroy functions before program ends

================================================================================
COMPILATION:
    g++ -std=c++11 stack_queue_procedural.cpp -o stack_queue
    ./stack_queue
================================================================================
*/