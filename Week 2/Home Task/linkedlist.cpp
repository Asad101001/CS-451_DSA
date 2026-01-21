#include <iostream>
#include <stdlib.h>  
using namespace std;

struct Node {
    int data;       
    Node* next;   
};

Node* list = NULL;  

void insert(int value) {
    
    Node* temp = new Node(); 
    //This method below is more C than  C++, leading to some discrepancies
    temp = (Node *)malloc(sizeof(Node));
    //only writing Node* temp; -> works in C not C++
    //temp = (Node *)malloc(sizeof(Node)); //malloc -> allocates memory & sizeof defines size in bits of memory to be allocated : Node
    
    temp->data = value;
    
    // STEP 3: Initialize next pointer
    temp->next = NULL;
    /*
    WHY SET TO NULL?
      - This will be the last node
      - NULL marks end of list
      - Prevents garbage pointer values
    */
    
    // STEP 4: Insert into list
    if (list == NULL) {
        // Case 1: Empty list - new node becomes head
        list = temp;
        /*
        BEFORE:  list → NULL
        AFTER:   list → [value|NULL]
        */
    } 
    else {
        // Case 2: Non-empty list - traverse to end
        Node* cur = list;  // Start at head
        
        /*
        TRAVERSAL LOGIC:
          while (cur->next != NULL)
          - Keep moving until we find the last node
          - Last node has next = NULL
          - cur will point to the last node
          
        EXAMPLE:
          list → [10|•]→[20|NULL]
          cur starts at 10
          cur->next is 20 (not NULL), move to 20
          cur->next is NULL, stop
          cur now points to node with 20
        */
        while (cur->next != NULL) {
            cur = cur->next;  // Move to next node
        }
        
        // Link last node to new node
        cur->next = temp;
        /*
        BEFORE: list → [10|•]→[20|NULL]
                                   temp → [30|NULL]
        
        AFTER:  list → [10|•]→[20|•]→[30|NULL]
        */
    }
}

/*
TIME COMPLEXITY:
  - Finding end: O(n) - must traverse entire list
  - Insertion itself: O(1) - just update pointer
  - Overall: O(n) for insert at end
  
SPACE COMPLEXITY: O(1) - only creates one node
*/

// ============================================
// DISPLAY FUNCTION
// ============================================

void display() {
    Node* cur = list;  // Start from head
    
    /*
    TRAVERSAL PATTERN:
      1. Start at head (cur = list)
      2. Process current node (print data)
      3. Move to next (cur = cur->next)
      4. Repeat until NULL
      
    This is the FUNDAMENTAL linked list operation
    Used in: display, search, delete, count, etc.
    */
    
    while (cur != NULL) {
        cout << cur->data << " -> ";
        cur = cur->next;  // Move pointer to next node
    }
    cout << "NULL" << endl;
    
    /*
    EXAMPLE OUTPUT:
      10 -> 20 -> 30 -> NULL
      
    WHY PRINT "NULL"?
      - Shows end of list visually
      - Helps debug (ensures list is properly terminated)
    */
}

/*
TIME COMPLEXITY: O(n) - visits every node once
SPACE COMPLEXITY: O(1) - only uses one pointer
*/

// ============================================
// SEARCH FUNCTION (NEW)
// ============================================

bool search(int value) {
    /*
    SEARCH STRATEGY:
      - Linear search (only option for linked lists)
      - Start from head, check each node
      - Return true if found, false if reach end
      
    WHY LINEAR ONLY?
      - No random access (can't jump to middle)
      - Must traverse sequentially
      - Unlike arrays (can do binary search)
    */
    
    Node* cur = list;  // Start at head
    int position = 0;  // Track position (optional, for output)
    
    while (cur != NULL) {
        if (cur->data == value) {
            // FOUND!
            cout << "Value " << value << " found at position " << position << endl;
            return true;
        }
        
        // Move to next node
        cur = cur->next;
        position++;
    }
    
    // Reached end without finding
    cout << "Value " << value << " not found in list" << endl;
    return false;
}

/*
SEARCH TRACE EXAMPLE:
  List: 10 -> 20 -> 30 -> NULL
  Search for 20:
  
  Step 1: cur points to 10
          10 == 20? No
          Move to next
          
  Step 2: cur points to 20
          20 == 20? Yes!
          Return true
          
  Search for 99:
  
  Step 1: cur points to 10, not 99, move
  Step 2: cur points to 20, not 99, move
  Step 3: cur points to 30, not 99, move
  Step 4: cur is NULL, exit loop
          Return false

TIME COMPLEXITY:
  Best case:  O(1) - found at head
  Average:    O(n/2) = O(n) - found in middle
  Worst case: O(n) - found at end or not found
  
SPACE COMPLEXITY: O(1) - only uses cur and position
*/

// ============================================
// ALTERNATIVE SEARCH (WITH INDEX)
// ============================================

int searchWithIndex(int value) {
    /*
    RETURNS:
      - Index/position if found
      - -1 if not found (common convention)
    */
    
    Node* cur = list;
    int index = 0;
    
    while (cur != NULL) {
        if (cur->data == value) {
            return index;  // Return position
        }
        cur = cur->next;
        index++;
    }
    
    return -1;  // Not found
}

/*
USAGE:
  int pos = searchWithIndex(20);
  if (pos != -1) {
      cout << "Found at index " << pos << endl;
  } else {
      cout << "Not found" << endl;
  }
*/

// ============================================
// COUNT OCCURRENCES (BONUS)
// ============================================

int countOccurrences(int value) {
    /*
    USEFUL FOR:
      - Finding duplicates
      - Frequency analysis
      - Checking if unique
    */
    
    Node* cur = list;
    int count = 0;
    
    while (cur != NULL) {
        if (cur->data == value) {
            count++;
        }
        cur = cur->next;
    }
    
    return count;
}

// ============================================
// MAIN FUNCTION
// ============================================

int main() {
    int choice, val;
    
    /*
    MENU-DRIVEN PROGRAM:
      - Common pattern for interactive programs
      - Loop until user chooses exit
      - Switch/if-else for different operations
    */
    
    while (true) {  // Infinite loop (break to exit)
        cout << "\n=== LINKED LIST OPERATIONS ===" << endl;
        cout << "1- Insert (at end)" << endl;
        cout << "2- Display" << endl;
        cout << "3- Search" << endl;
        cout << "4- Search with index" << endl;
        cout << "5- Count occurrences" << endl;
        cout << "6- Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        
        if (choice == 1) {
            // INSERT
            cout << "Enter value: ";
            cin >> val;
            insert(val);
            cout << "✓ Inserted " << val << endl;
        }
        else if (choice == 2) {
            // DISPLAY
            cout << "List: ";
            display();
        }
        else if (choice == 3) {
            // SEARCH (BOOLEAN)
            cout << "Enter value to search: ";
            cin >> val;
            search(val);  // Prints result internally
        }
        else if (choice == 4) {
            // SEARCH WITH INDEX
            cout << "Enter value to search: ";
            cin >> val;
            int index = searchWithIndex(val);
            if (index != -1) {
                cout << "✓ Found at position " << index << endl;
            } else {
                cout << "✗ Not found" << endl;
            }
        }
        else if (choice == 5) {
            // COUNT OCCURRENCES
            cout << "Enter value to count: ";
            cin >> val;
            int count = countOccurrences(val);
            cout << "Value " << val << " appears " << count << " time(s)" << endl;
        }
        else if (choice == 6) {
            // EXIT
            cout << "Exiting..." << endl;
            break;  // Exit while loop
        }
        else {
            // INVALID INPUT
            cout << "Invalid choice! Try again." << endl;
        }
    }
    
    /*
    MEMORY CLEANUP (IMPORTANT!):
      Your code doesn't free allocated memory
      This causes MEMORY LEAK
      
    Should add:
      while (list != NULL) {
          Node* temp = list;
          list = list->next;
          delete temp;  // or free(temp) if used malloc
      }
    */
    
    return 0;
}

/*
╔════════════════════════════════════════════════════════════╗
║                  TECHNICAL KNOWLEDGE                       ║
╚════════════════════════════════════════════════════════════╝

1. POINTER ARITHMETIC:
   Node* cur = list;
   - cur is a POINTER variable (holds memory address)
   - cur = cur->next; (changes what address cur points to)
   - Does NOT move memory, just updates pointer

2. HEAP vs STACK:
   int x = 10;           ← Stack (automatic)
   Node* n = new Node(); ← Heap (manual, persists)
   
3. DEREFERENCING:
   Node* ptr;
   ptr->data    ≡  (*ptr).data
   - Arrow operator is syntactic sugar
   - Dereferences pointer and accesses member

4. NULL POINTER DANGERS:
   Node* ptr = NULL;
   ptr->data;  ← CRASH! (Segmentation fault)
   - Always check: if (ptr != NULL) before accessing

5. MEMORY LEAK:
   Node* temp = new Node();
   temp = new Node();  ← First node lost! Memory leaked
   
6. THIS vs ARRAY:
   Array:       O(1) access, O(n) insert
   Linked List: O(n) access, O(1) insert at head

╔════════════════════════════════════════════════════════════╗
║                  COMMON OPERATIONS                         ║
╚════════════════════════════════════════════════════════════╝

OPERATION           TIME        SPACE
Insert at head      O(1)        O(1)
Insert at tail      O(n)        O(1)
Insert at position  O(n)        O(1)
Delete at head      O(1)        O(1)
Delete at tail      O(n)        O(1)
Search              O(n)        O(1)
Access by index     O(n)        O(1)
Display/Traverse    O(n)        O(1)

╔════════════════════════════════════════════════════════════╗
║                  INTERVIEW QUESTIONS                       ║
╚════════════════════════════════════════════════════════════╝

Q: Why use linked list over array?
A: Dynamic size, O(1) insert at head, no shifting needed

Q: How to search in linked list?
A: Linear search only - traverse and compare each node

Q: What is time complexity of search?
A: O(n) - must check up to n nodes in worst case

Q: How to detect end of list?
A: Check if current->next == NULL

Q: What happens if you access NULL pointer?
A: Segmentation fault - program crashes

Q: Difference between malloc and new?
A: malloc is C (manual, returns void*), new is C++ (safer, typed)

╔════════════════════════════════════════════════════════════╗
║                  IMPROVEMENTS TO YOUR CODE                 ║
╚════════════════════════════════════════════════════════════╝

1. REMOVE REDUNDANT ALLOCATION:
   Current:
     Node* temp = new Node();
     temp = (Node*)malloc(sizeof(Node)); ← Memory leak!
   
   Fix (choose one):
     Node* temp = new Node();  // C++ way (BETTER)
     OR
     Node* temp = (Node*)malloc(sizeof(Node));  // C way

2. ADD DESTRUCTOR/CLEANUP:
   Before return 0:
     while (list != NULL) {
         Node* temp = list;
         list = list->next;
         delete temp;  // Free memory
     }

3. USE nullptr INSTEAD OF NULL:
   Node* list = nullptr;  // C++11 onwards (type-safe)

4. ADD ERROR HANDLING:
   if (temp == NULL) {
       cout << "Memory allocation failed!" << endl;
       return;
   }

5. MAKE FUNCTIONS RETURN STATUS:
   bool insert(int value);  // Returns true if success
   
╔════════════════════════════════════════════════════════════╗
║                  PRACTICE EXERCISES                        ║
╚════════════════════════════════════════════════════════════╝

1. Implement delete function (remove a value)
2. Add insert at beginning (O(1) operation)
3. Reverse the linked list
4. Find middle element in one pass
5. Detect if list has a cycle
6. Merge two sorted linked lists
*/