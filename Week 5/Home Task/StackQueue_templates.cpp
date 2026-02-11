#include <iostream>
#include <stdexcept>  // For exception handling
#include <string>
using namespace std;



template <typename T>
class Stack {
private:    
    struct Node {
        T data;           
        Node* next;       
        
        Node(T value) : data(value), next(nullptr) {}
    };
    
    Node* topNode;        // Pointer to top of stack
    int stackSize;        // Current number of elements
    
public:
    // Constructor - Initialize empty stack
    Stack() : topNode(nullptr), stackSize(0) {
        /*
        Python: def __init__(self):
                    self.items = []
        */
    }
    
    // Destructor - Clean up memory
    ~Stack() {
        while (!isEmpty()) {
            pop();
        }
        /*
        Python: def __del__(self):
                    # Python has garbage collection, no manual cleanup needed
        */
    }
    
    // Push operation - Add element to top
    // Time Complexity: O(1)
    void push(T value) {
        Node* newNode = new Node(value);  // Create new node
        newNode->next = topNode;          // Link to current top
        topNode = newNode;                // Update top pointer
        stackSize++;
        
        /*
        Python equivalent:
            def push(self, value):
                self.items.append(value)
        
        Step-by-step visualization:
        Before: Stack: [1, 2, 3] (top is 3)
        Push(4)
        After:  Stack: [1, 2, 3, 4] (top is 4)
        */
    }
    
    // Pop operation - Remove and return top element
    // Time Complexity: O(1)
    T pop() {
        if (isEmpty()) {
            throw runtime_error("Stack Underflow: Cannot pop from empty stack");
        }
        
        Node* temp = topNode;       // Save current top
        T value = topNode->data;    // Save data to return
        topNode = topNode->next;    // Move top to next node
        delete temp;                // Free memory
        stackSize--;
        
        return value;
        
        /*
        Python equivalent:
            def pop(self):
                if not self.items:
                    raise IndexError("Stack is empty")
                return self.items.pop()
        */
    }
    
    // Peek/Top - Return top element without removing
    // Time Complexity: O(1)
    T top() const {
        if (isEmpty()) {
            throw runtime_error("Stack is empty");
        }
        return topNode->data;
        
        /*
        Python equivalent:
            def top(self):
                if not self.items:
                    raise IndexError("Stack is empty")
                return self.items[-1]
        */
    }
    
    // Check if stack is empty
    // Time Complexity: O(1)
    bool isEmpty() const {
        return topNode == nullptr;
        
        /*
        Python: def is_empty(self):
                    return len(self.items) == 0
        */
    }
    
    // Get current size
    // Time Complexity: O(1)
    int size() const {
        return stackSize;
        
        /*
        Python: def size(self):
                    return len(self.items)
        */
    }
    
    // Display stack contents (for debugging)
    void display() const {
        if (isEmpty()) {
            cout << "Stack is empty" << endl;
            return;
        }
        
        cout << "Stack (top to bottom): ";
        Node* current = topNode;
        while (current != nullptr) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }
};

//==============================================================================
// QUEUE IMPLEMENTATION USING TEMPLATES
//==============================================================================

/*
QUEUE: First-In-First-Out (FIFO) Data Structure
------
Python equivalent:
    from collections import deque
    queue = deque()
    queue.append(item)    # enqueue
    queue.popleft()       # dequeue
    queue[0]              # front
*/

template <typename T>
class Queue {
private:
    // Node structure for linked list implementation
    struct Node {
        T data;
        Node* next;
        
        Node(T value) : data(value), next(nullptr) {}
    };
    
    Node* frontNode;      // Pointer to front of queue
    Node* rearNode;       // Pointer to rear of queue
    int queueSize;        // Current number of elements
    
public:
    // Constructor
    Queue() : frontNode(nullptr), rearNode(nullptr), queueSize(0) {
        /*
        Python: def __init__(self):
                    self.items = deque()
        */
    }
    
    // Destructor
    ~Queue() {
        while (!isEmpty()) {
            dequeue();
        }
    }
    
    // Enqueue operation - Add element to rear
    // Time Complexity: O(1)
    void enqueue(T value) {
        Node* newNode = new Node(value);
        
        if (isEmpty()) {
            // First element - both front and rear point to it
            frontNode = rearNode = newNode;
        } else {
            // Add to rear
            rearNode->next = newNode;
            rearNode = newNode;
        }
        queueSize++;
        
        /*
        Python equivalent:
            def enqueue(self, value):
                self.items.append(value)
        
        Visualization:
        Before: Queue: [1, 2, 3] (front=1, rear=3)
        Enqueue(4)
        After:  Queue: [1, 2, 3, 4] (front=1, rear=4)
        */
    }
    
    // Dequeue operation - Remove and return front element
    // Time Complexity: O(1)
    T dequeue() {
        if (isEmpty()) {
            throw runtime_error("Queue Underflow: Cannot dequeue from empty queue");
        }
        
        Node* temp = frontNode;
        T value = frontNode->data;
        frontNode = frontNode->next;
        
        // If queue becomes empty, update rear too
        if (frontNode == nullptr) {
            rearNode = nullptr;
        }
        
        delete temp;
        queueSize--;
        
        return value;
        
        /*
        Python equivalent:
            def dequeue(self):
                if not self.items:
                    raise IndexError("Queue is empty")
                return self.items.popleft()
        
        Visualization:
        Before: Queue: [1, 2, 3] (front=1, rear=3)
        Dequeue()
        After:  Queue: [2, 3] (front=2, rear=3)
        Returns: 1
        */
    }
    
    // Front - Return front element without removing
    // Time Complexity: O(1)
    T front() const {
        if (isEmpty()) {
            throw runtime_error("Queue is empty");
        }
        return frontNode->data;
        
        /*
        Python: def front(self):
                    if not self.items:
                        raise IndexError("Queue is empty")
                    return self.items[0]
        */
    }
    
    // Rear - Return rear element without removing
    // Time Complexity: O(1)
    T rear() const {
        if (isEmpty()) {
            throw runtime_error("Queue is empty");
        }
        return rearNode->data;
        
        /*
        Python: def rear(self):
                    if not self.items:
                        raise IndexError("Queue is empty")
                    return self.items[-1]
        */
    }
    
    // Check if queue is empty
    bool isEmpty() const {
        return frontNode == nullptr;
    }
    
    // Get current size
    int size() const {
        return queueSize;
    }
    
    // Display queue contents
    void display() const {
        if (isEmpty()) {
            cout << "Queue is empty" << endl;
            return;
        }
        
        cout << "Queue (front to rear): ";
        Node* current = frontNode;
        while (current != nullptr) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }
};

//==============================================================================
// DEMONSTRATION AND TEST CASES
//==============================================================================

void demonstrateStack() {
    cout << "\n========== STACK DEMONSTRATION ==========" << endl;
    
    // Create a stack of integers
    Stack<int> intStack;
    
    cout << "\n1. Pushing elements 10, 20, 30, 40, 50" << endl;
    intStack.push(10);
    intStack.push(20);
    intStack.push(30);
    intStack.push(40);
    intStack.push(50);
    intStack.display();
    
    cout << "\n2. Top element: " << intStack.top() << endl;
    cout << "   Size: " << intStack.size() << endl;
    
    cout << "\n3. Popping two elements:" << endl;
    cout << "   Popped: " << intStack.pop() << endl;
    cout << "   Popped: " << intStack.pop() << endl;
    intStack.display();
    
    // Create a stack of strings
    cout << "\n4. Creating a Stack of strings:" << endl;
    Stack<string> stringStack;
    stringStack.push("Hello");
    stringStack.push("World");
    stringStack.push("DSA");
    stringStack.display();
    
    /*
    Python equivalent demonstration:
    
    stack = []
    print("Pushing elements 10, 20, 30, 40, 50")
    for item in [10, 20, 30, 40, 50]:
        stack.append(item)
    print(f"Stack: {stack}")
    
    print(f"Top element: {stack[-1]}")
    print(f"Size: {len(stack)}")
    
    print("Popping two elements:")
    print(f"Popped: {stack.pop()}")
    print(f"Popped: {stack.pop()}")
    print(f"Stack: {stack}")
    */
}

void demonstrateQueue() {
    cout << "\n========== QUEUE DEMONSTRATION ==========" << endl;
    
    // Create a queue of integers
    Queue<int> intQueue;
    
    cout << "\n1. Enqueuing elements 10, 20, 30, 40, 50" << endl;
    intQueue.enqueue(10);
    intQueue.enqueue(20);
    intQueue.enqueue(30);
    intQueue.enqueue(40);
    intQueue.enqueue(50);
    intQueue.display();
    
    cout << "\n2. Front element: " << intQueue.front() << endl;
    cout << "   Rear element: " << intQueue.rear() << endl;
    cout << "   Size: " << intQueue.size() << endl;
    
    cout << "\n3. Dequeuing two elements:" << endl;
    cout << "   Dequeued: " << intQueue.dequeue() << endl;
    cout << "   Dequeued: " << intQueue.dequeue() << endl;
    intQueue.display();
    
    // Create a queue of doubles
    cout << "\n4. Creating a Queue of doubles:" << endl;
    Queue<double> doubleQueue;
    doubleQueue.enqueue(3.14);
    doubleQueue.enqueue(2.71);
    doubleQueue.enqueue(1.41);
    doubleQueue.display();
    
    /*
    Python equivalent demonstration:
    
    from collections import deque
    queue = deque()
    
    print("Enqueuing elements 10, 20, 30, 40, 50")
    for item in [10, 20, 30, 40, 50]:
        queue.append(item)
    print(f"Queue: {list(queue)}")
    
    print(f"Front element: {queue[0]}")
    print(f"Rear element: {queue[-1]}")
    print(f"Size: {len(queue)}")
    
    print("Dequeuing two elements:")
    print(f"Dequeued: {queue.popleft()}")
    print(f"Dequeued: {queue.popleft()}")
    print(f"Queue: {list(queue)}")
    */
}

void demonstrateApplications() {
    cout << "\n========== PRACTICAL APPLICATIONS ==========" << endl;
    
    // Application 1: Parentheses Matching using Stack
    cout << "\n1. STACK APPLICATION - Parentheses Matching:" << endl;
    string expr = "((a+b)*c)";
    Stack<char> parenStack;
    
    cout << "   Expression: " << expr << endl;
    bool balanced = true;
    
    for (char ch : expr) {
        if (ch == '(') {
            parenStack.push(ch);
        } else if (ch == ')') {
            if (parenStack.isEmpty()) {
                balanced = false;
                break;
            }
            parenStack.pop();
        }
    }
    
    if (!parenStack.isEmpty()) balanced = false;
    cout << "   Result: " << (balanced ? "Balanced" : "Not Balanced") << endl;
    
    // Application 2: Task Scheduling using Queue
    cout << "\n2. QUEUE APPLICATION - Task Scheduling:" << endl;
    Queue<string> taskQueue;
    
    cout << "   Adding tasks to queue..." << endl;
    taskQueue.enqueue("Task1: Send Email");
    taskQueue.enqueue("Task2: Update Database");
    taskQueue.enqueue("Task3: Generate Report");
    taskQueue.display();
    
    cout << "\n   Processing tasks in FIFO order:" << endl;
    while (!taskQueue.isEmpty()) {
        string task = taskQueue.dequeue();
        cout << "   Processing: " << task << endl;
    }
}

//==============================================================================
// MAIN FUNCTION
//==============================================================================

int main() {
    cout << "==================================================" << endl;
    cout << "  STACK AND QUEUE USING C++ TEMPLATES" << endl;
    cout << "  Data Structures Course - Educational Demo" << endl;
    cout << "==================================================" << endl;
    
    try {
        demonstrateStack();
        demonstrateQueue();
        demonstrateApplications();
        
        cout << "\n==================================================" << endl;
        cout << "  All demonstrations completed successfully!" << endl;
        cout << "==================================================" << endl;
        
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}

/*
================================================================================
KEY CONCEPTS SUMMARY
================================================================================

1. TEMPLATES IN C++:
   - Allow generic programming (type-independent code)
   - Template parameter T is replaced at compile time
   - Python doesn't need this due to dynamic typing

2. STACK (LIFO):
   - Operations: push(), pop(), top(), isEmpty(), size()
   - Time Complexity: All operations O(1)
   - Applications: Function calls, undo mechanisms, expression evaluation

3. QUEUE (FIFO):
   - Operations: enqueue(), dequeue(), front(), rear(), isEmpty(), size()
   - Time Complexity: All operations O(1)
   - Applications: Task scheduling, BFS, printer queues

4. MEMORY MANAGEMENT:
   - C++: Manual (new/delete) - must implement destructor
   - Python: Automatic garbage collection

5. EXCEPTION HANDLING:
   - C++: throw/try/catch with runtime_error
   - Python: raise/try/except with built-in exceptions

================================================================================
COMPILATION AND EXECUTION
================================================================================

To compile and run this program:

    g++ -std=c++11 stack_queue_templates.cpp -o stack_queue
    ./stack_queue

Expected Output:
    - Stack demonstrations with different data types
    - Queue demonstrations with different data types
    - Practical applications showing real-world usage

================================================================================
*/