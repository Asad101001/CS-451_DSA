/*
================================================================================
TASK 3: UTILIZING TEMPLATES ON STACK AND QUEUE
================================================================================

WHAT ARE TEMPLATES?
-------------------
Templates allow you to write ONE implementation that works with ANY data type.
Instead of writing separate Stack_int, Stack_double, Stack_string, etc.,
you write ONE template Stack<T> that works for all types.

TEMPLATE SYNTAX:
    template <typename T>    // T is a placeholder for any type
    
    or
    
    template <class T>       // Equivalent to typename

WHY USE TEMPLATES?
------------------
Without templates (BAD):
    struct IntStack { int data; ... };
    struct DoubleStack { double data; ... };
    struct StringStack { string data; ... };
    // Must rewrite same logic for each type!

With templates (GOOD):
    template <typename T>
    struct Stack { T data; ... };
    // Write once, use for all types!

HOW TEMPLATES WORK:
-------------------
Compiler generates type-specific code when you use the template:

    Stack<int> s1;     → Compiler creates Stack with T=int
    Stack<double> s2;  → Compiler creates Stack with T=double
    
This is called "template instantiation"

Python Comparison:
    Python doesn't need templates because it's dynamically typed:
    stack = []  # Can hold any type naturally
    
    C++ is statically typed, so templates provide type flexibility
*/

#include <iostream>
#include <string>
using namespace std;

//==============================================================================
// PART 1: TEMPLATE STACK (LINKED LIST IMPLEMENTATION)
//==============================================================================

/*
STACK NODE - Template Structure
--------------------------------
Works with any data type T
*/
template <typename T>
struct StackNode {
    T data;              // Can be int, double, string, or any type
    StackNode<T>* next;  // Pointer to next node
    
    /*
    MEMORY EXAMPLES:
    
    StackNode<int>:
        [data: int (4 bytes)][next: pointer (8 bytes)]
    
    StackNode<double>:
        [data: double (8 bytes)][next: pointer (8 bytes)]
    
    StackNode<string>:
        [data: string (varies)][next: pointer (8 bytes)]
    */
};

/*
STACK STRUCTURE - Template
---------------------------
*/
template <typename T>
struct Stack {
    StackNode<T>* top;  // Pointer to top node
    int size;           // Number of elements
};

/*
STACK OPERATIONS
----------------
All operations are templated to work with any type
*/

// Initialize stack
template <typename T>
void initStack(Stack<T>* stack) {
    stack->top = nullptr;
    stack->size = 0;
}

// Check if empty
template <typename T>
bool isStackEmpty(Stack<T>* stack) {
    return stack->top == nullptr;
}

// Get size
template <typename T>
int getStackSize(Stack<T>* stack) {
    return stack->size;
}

// Push operation - O(1)
template <typename T>
void push(Stack<T>* stack, T value) {
    // Create new node
    StackNode<T>* newNode = new StackNode<T>;
    newNode->data = value;
    newNode->next = stack->top;
    
    // Update top
    stack->top = newNode;
    stack->size++;
    
    /*
    TEMPLATE IN ACTION:
    
    If T = int:
        StackNode<int>* newNode = new StackNode<int>;
        newNode->data = 42;  // Stores integer
    
    If T = string:
        StackNode<string>* newNode = new StackNode<string>;
        newNode->data = "hello";  // Stores string
    
    Same code, different types!
    */
}

// Pop operation - O(1)
template <typename T>
T pop(Stack<T>* stack) {
    if (isStackEmpty(stack)) {
        cout << "Error: Stack underflow!" << endl;
        exit(1);
    }
    
    T value = stack->top->data;
    StackNode<T>* temp = stack->top;
    stack->top = stack->top->next;
    
    delete temp;
    stack->size--;
    
    return value;
}

// Peek operation - O(1)
template <typename T>
T peek(Stack<T>* stack) {
    if (isStackEmpty(stack)) {
        cout << "Error: Stack is empty!" << endl;
        exit(1);
    }
    return stack->top->data;
}

// Display stack
template <typename T>
void displayStack(Stack<T>* stack) {
    if (isStackEmpty(stack)) {
        cout << "Stack is empty" << endl;
        return;
    }
    
    cout << "Stack (top to bottom): ";
    StackNode<T>* current = stack->top;
    while (current != nullptr) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

// Destroy stack
template <typename T>
void destroyStack(Stack<T>* stack) {
    while (!isStackEmpty(stack)) {
        pop(stack);
    }
}

//==============================================================================
// PART 2: TEMPLATE QUEUE (LINKED LIST IMPLEMENTATION)
//==============================================================================

/*
QUEUE NODE - Template Structure
--------------------------------
*/
template <typename T>
struct QueueNode {
    T data;
    QueueNode<T>* next;
};

/*
QUEUE STRUCTURE - Template
---------------------------
*/
template <typename T>
struct Queue {
    QueueNode<T>* front;
    QueueNode<T>* rear;
    int size;
};

/*
QUEUE OPERATIONS
----------------
*/

// Initialize queue
template <typename T>
void initQueue(Queue<T>* queue) {
    queue->front = nullptr;
    queue->rear = nullptr;
    queue->size = 0;
}

// Check if empty
template <typename T>
bool isQueueEmpty(Queue<T>* queue) {
    return queue->front == nullptr;
}

// Get size
template <typename T>
int getQueueSize(Queue<T>* queue) {
    return queue->size;
}

// Enqueue operation - O(1)
template <typename T>
void enqueue(Queue<T>* queue, T value) {
    QueueNode<T>* newNode = new QueueNode<T>;
    newNode->data = value;
    newNode->next = nullptr;
    
    if (queue->rear == nullptr) {
        queue->front = newNode;
        queue->rear = newNode;
    }
    else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
    
    queue->size++;
}

// Dequeue operation - O(1)
template <typename T>
T dequeue(Queue<T>* queue) {
    if (isQueueEmpty(queue)) {
        cout << "Error: Queue underflow!" << endl;
        exit(1);
    }
    
    T value = queue->front->data;
    QueueNode<T>* temp = queue->front;
    queue->front = queue->front->next;
    
    if (queue->front == nullptr) {
        queue->rear = nullptr;
    }
    
    delete temp;
    queue->size--;
    
    return value;
}

// Front operation - O(1)
template <typename T>
T frontElement(Queue<T>* queue) {
    if (isQueueEmpty(queue)) {
        cout << "Error: Queue is empty!" << endl;
        exit(1);
    }
    return queue->front->data;
}

// Display queue
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

// Destroy queue
template <typename T>
void destroyQueue(Queue<T>* queue) {
    while (!isQueueEmpty(queue)) {
        dequeue(queue);
    }
}

//==============================================================================
// PART 3: CUSTOM DATA TYPE EXAMPLE
//==============================================================================

/*
CUSTOM STRUCT - To demonstrate templates with user-defined types
-----------------------------------------------------------------
Templates work with ANY type, including structs and classes!
*/
struct Student {
    string name;
    int rollNumber;
    double gpa;
    
    // Overload << operator for easy printing
    friend ostream& operator<<(ostream& os, const Student& s) {
        os << "[" << s.name << ", Roll:" << s.rollNumber << ", GPA:" << s.gpa << "]";
        return os;
    }
};

//==============================================================================
// DEMONSTRATIONS
//==============================================================================

void demonstrateStackTemplates() {
    cout << "\n====================================================\n";
    cout << "  STACK TEMPLATE DEMONSTRATIONS\n";
    cout << "====================================================\n\n";
    
    // 1. Stack of integers
    cout << "1. Stack<int> - Integer Stack:\n";
    Stack<int> intStack;
    initStack(&intStack);
    
    push(&intStack, 10);
    push(&intStack, 20);
    push(&intStack, 30);
    displayStack(&intStack);
    cout << "   Popped: " << pop(&intStack) << endl;
    displayStack(&intStack);
    
    // 2. Stack of doubles
    cout << "\n2. Stack<double> - Double Stack:\n";
    Stack<double> doubleStack;
    initStack(&doubleStack);
    
    push(&doubleStack, 3.14);
    push(&doubleStack, 2.718);
    push(&doubleStack, 1.414);
    displayStack(&doubleStack);
    cout << "   Top: " << peek(&doubleStack) << endl;
    
    // 3. Stack of strings
    cout << "\n3. Stack<string> - String Stack:\n";
    Stack<string> stringStack;
    initStack(&stringStack);
    
    push(&stringStack, string("Hello"));
    push(&stringStack, string("World"));
    push(&stringStack, string("Templates"));
    displayStack(&stringStack);
    
    // 4. Stack of custom type (Student)
    cout << "\n4. Stack<Student> - Custom Type Stack:\n";
    Stack<Student> studentStack;
    initStack(&studentStack);
    
    Student s1 = {"Alice", 101, 3.8};
    Student s2 = {"Bob", 102, 3.6};
    Student s3 = {"Charlie", 103, 3.9};
    
    push(&studentStack, s1);
    push(&studentStack, s2);
    push(&studentStack, s3);
    displayStack(&studentStack);
    
    cout << "   Popped: " << pop(&studentStack) << endl;
    displayStack(&studentStack);
    
    /*
    KEY INSIGHT:
    Same push(), pop(), peek() functions work for:
    - int
    - double
    - string
    - Student
    - ANY type!
    
    This is the power of templates!
    */
    
    // Cleanup
    destroyStack(&intStack);
    destroyStack(&doubleStack);
    destroyStack(&stringStack);
    destroyStack(&studentStack);
}

void demonstrateQueueTemplates() {
    cout << "\n====================================================\n";
    cout << "  QUEUE TEMPLATE DEMONSTRATIONS\n";
    cout << "====================================================\n\n";
    
    // 1. Queue of integers
    cout << "1. Queue<int> - Integer Queue:\n";
    Queue<int> intQueue;
    initQueue(&intQueue);
    
    enqueue(&intQueue, 100);
    enqueue(&intQueue, 200);
    enqueue(&intQueue, 300);
    displayQueue(&intQueue);
    cout << "   Dequeued: " << dequeue(&intQueue) << endl;
    displayQueue(&intQueue);
    
    // 2. Queue of characters
    cout << "\n2. Queue<char> - Character Queue:\n";
    Queue<char> charQueue;
    initQueue(&charQueue);
    
    enqueue(&charQueue, 'A');
    enqueue(&charQueue, 'B');
    enqueue(&charQueue, 'C');
    displayQueue(&charQueue);
    cout << "   Front: " << frontElement(&charQueue) << endl;
    
    // 3. Queue of strings
    cout << "\n3. Queue<string> - String Queue:\n";
    Queue<string> stringQueue;
    initQueue(&stringQueue);
    
    enqueue(&stringQueue, string("First"));
    enqueue(&stringQueue, string("Second"));
    enqueue(&stringQueue, string("Third"));
    displayQueue(&stringQueue);
    
    // 4. Queue of custom type
    cout << "\n4. Queue<Student> - Custom Type Queue:\n";
    Queue<Student> studentQueue;
    initQueue(&studentQueue);
    
    Student s1 = {"Diana", 201, 3.7};
    Student s2 = {"Eve", 202, 3.85};
    Student s3 = {"Frank", 203, 3.75};
    
    enqueue(&studentQueue, s1);
    enqueue(&studentQueue, s2);
    enqueue(&studentQueue, s3);
    displayQueue(&studentQueue);
    
    cout << "   Dequeued: " << dequeue(&studentQueue) << endl;
    displayQueue(&studentQueue);
    
    // Cleanup
    destroyQueue(&intQueue);
    destroyQueue(&charQueue);
    destroyQueue(&stringQueue);
    destroyQueue(&studentQueue);
}

//==============================================================================
// TEMPLATE SPECIALIZATION EXAMPLE (ADVANCED)
//==============================================================================

/*
TEMPLATE SPECIALIZATION
-----------------------
Sometimes you want different behavior for specific types.
This is called "template specialization".

Example: Special display for bool stack
*/

// Specialized display for bool stack
template <>
void displayStack<bool>(Stack<bool>* stack) {
    if (isStackEmpty(stack)) {
        cout << "Stack is empty" << endl;
        return;
    }
    
    cout << "Bool Stack (top to bottom): ";
    StackNode<bool>* current = stack->top;
    while (current != nullptr) {
        cout << (current->data ? "true" : "false") << " ";
        current = current->next;
    }
    cout << endl;
}

void demonstrateSpecialization() {
    cout << "\n====================================================\n";
    cout << "  TEMPLATE SPECIALIZATION EXAMPLE\n";
    cout << "====================================================\n\n";
    
    cout << "Stack<bool> with specialized display:\n";
    Stack<bool> boolStack;
    initStack(&boolStack);
    
    push(&boolStack, true);
    push(&boolStack, false);
    push(&boolStack, true);
    displayStack(&boolStack);  // Uses specialized version
    
    destroyStack(&boolStack);
}

//==============================================================================
// PRACTICAL APPLICATION: Expression Evaluator
//==============================================================================

void demonstrateApplication() {
    cout << "\n====================================================\n";
    cout << "  APPLICATION: Reverse Polish Notation Calculator\n";
    cout << "====================================================\n\n";
    
    // Expression: 5 3 + 2 *  (means: (5+3)*2 = 16)
    Stack<int> calcStack;
    initStack(&calcStack);
    
    cout << "RPN Expression: 5 3 + 2 *\n";
    cout << "Calculation steps:\n";
    
    // Push 5
    push(&calcStack, 5);
    cout << "  Push 5: ";
    displayStack(&calcStack);
    
    // Push 3
    push(&calcStack, 3);
    cout << "  Push 3: ";
    displayStack(&calcStack);
    
    // Addition (+)
    int b = pop(&calcStack);
    int a = pop(&calcStack);
    push(&calcStack, a + b);
    cout << "  Operator +: pop " << b << " and " << a << ", push " << (a+b) << ": ";
    displayStack(&calcStack);
    
    // Push 2
    push(&calcStack, 2);
    cout << "  Push 2: ";
    displayStack(&calcStack);
    
    // Multiplication (*)
    b = pop(&calcStack);
    a = pop(&calcStack);
    push(&calcStack, a * b);
    cout << "  Operator *: pop " << b << " and " << a << ", push " << (a*b) << ": ";
    displayStack(&calcStack);
    
    cout << "\nResult: " << pop(&calcStack) << endl;
    
    destroyStack(&calcStack);
}

//==============================================================================
// MAIN FUNCTION
//==============================================================================

int main() {
    cout << "========================================================\n";
    cout << "  TASK 3: UTILIZING TEMPLATES ON STACK AND QUEUE\n";
    cout << "========================================================\n";
    
    demonstrateStackTemplates();
    demonstrateQueueTemplates();
    demonstrateSpecialization();
    demonstrateApplication();
    
    cout << "\n========================================================\n";
    cout << "  Template demonstrations completed!\n";
    cout << "========================================================\n\n";
    
    return 0;
}

/*
================================================================================
KEY CONCEPTS SUMMARY
================================================================================

1. TEMPLATE BASICS:
   - template <typename T> - declare template with type parameter T
   - T is placeholder for any type (int, double, string, custom types)
   - Compiler generates type-specific code at compile time

2. TEMPLATE ADVANTAGES:
   - Code reuse - write once, use for all types
   - Type safety - compiler checks types at compile time
   - No runtime overhead - same performance as hand-coded versions
   - Works with built-in AND user-defined types

3. TEMPLATE SYNTAX:
   template <typename T>
   struct MyStruct {
       T data;  // T can be any type
   };
   
   template <typename T>
   void myFunction(T param) {
       // Use T as if it's a normal type
   }

4. HOW TEMPLATES WORK:
   Stack<int> s1;     → Compiler creates version with T=int
   Stack<double> s2;  → Compiler creates version with T=double
   
   This is called "template instantiation"

5. TEMPLATE SPECIALIZATION:
   Provide custom implementation for specific types:
   
   template <>
   void function<int>(...) {
       // Special behavior for int only
   }

6. TEMPLATES VS PYTHON:
   C++: template <typename T>
        - Static typing with generic capabilities
        - Type checking at compile time
        - No runtime overhead
   
   Python: No templates needed
        - Dynamic typing naturally generic
        - Type checking at runtime
        - Some runtime overhead

7. COMMON TEMPLATE USES:
   - Data structures (Stack, Queue, LinkedList, Tree, etc.)
   - Algorithms (sort, search, etc.)
   - Smart pointers
   - Containers (vector, map, set in STL)

8. TEMPLATE CONSTRAINTS:
   - Must be in header files (or same file)
   - Can't separate declaration and definition (usually)
   - Compilation errors can be cryptic
   - Code bloat if used excessively (each type creates new code)

9. BEST PRACTICES:
   - Use meaningful template parameter names (T for type, N for numbers)
   - Document type requirements (what operations T must support)
   - Provide specializations only when necessary
   - Consider concepts (C++20) for better error messages

================================================================================
PYTHON EQUIVALENT CONCEPTS:
================================================================================

C++ Template:
    template <typename T>
    struct Stack {
        T data;
    };
    
    Stack<int> intStack;
    Stack<string> strStack;

Python (no templates needed):
    class Stack:
        def __init__(self):
            self.data = None  # Can be any type
    
    int_stack = Stack()
    str_stack = Stack()

C++ uses templates for type safety while maintaining genericity.
Python achieves genericity through dynamic typing.

================================================================================
COMPILATION AND EXECUTION:
   g++ -std=c++11 task3_templates.cpp -o task3
   ./task3
================================================================================
*/
