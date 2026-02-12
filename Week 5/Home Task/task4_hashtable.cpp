/*
================================================================================
TASK 4: HASH TABLE WITH LINEAR AND QUADRATIC PROBING
================================================================================

WHAT IS A HASH TABLE?
---------------------
A hash table is a data structure that stores key-value pairs and provides
O(1) average-time insertion, deletion, and search operations.

Think of it like:
- A library catalog: Book title (key) → Shelf location (value)
- Phone directory: Name (key) → Phone number (value)
- Dictionary: Word (key) → Definition (value)

HOW DOES IT WORK?
-----------------
1. Hash Function: Converts key to an array index
   Example: hash("Alice") → 5 (store at index 5)

2. Direct Access: Use index to access/store value instantly
   table[5] = "Alice's data"

COLLISION PROBLEM:
------------------
What if hash("Alice") = 5 AND hash("Bob") = 5?
Both want the same index! This is a COLLISION.

COLLISION RESOLUTION STRATEGIES:
---------------------------------
1. SEPARATE CHAINING: Each index stores a linked list
   table[5] → [Alice] → [Bob] → NULL

2. OPEN ADDRESSING: Find another empty spot in the array
   a) LINEAR PROBING: Try next index (5, 6, 7, 8, ...)
   b) QUADRATIC PROBING: Try quadratic sequence (5, 6, 9, 14, ...)

This file implements LINEAR and QUADRATIC PROBING.

Python Comparison:
    # Python dictionary is a hash table
    d = {}
    d["Alice"] = 25    # O(1) insertion
    print(d["Alice"])  # O(1) lookup
    
    # Python handles collisions automatically (separate chaining)
*/

#include <iostream>
#include <string>
using namespace std;

//==============================================================================
// CONSTANTS AND ENUMS
//==============================================================================

const int TABLE_SIZE = 11;  // Prime number for better distribution

// Status of each cell in hash table
enum CellStatus {
    EMPTY,     // Never used
    OCCUPIED,  // Currently has data
    DELETED    // Had data but was deleted (important for probing!)
};

/*
WHY DELETED STATE?

Without DELETED:
    Insert "Alice" at index 5
    Insert "Bob" at index 6 (collision, linear probe)
    Delete "Alice" → index 5 becomes EMPTY
    Search "Bob" → starts at 5, sees EMPTY, stops! Can't find Bob!

With DELETED:
    Delete "Alice" → index 5 becomes DELETED
    Search "Bob" → starts at 5, sees DELETED, continues probing → finds Bob!
*/

//==============================================================================
// HASH TABLE ENTRY
//==============================================================================

template <typename K, typename V>
struct HashEntry {
    K key;               // The key (e.g., "Alice")
    V value;             // The value (e.g., phone number)
    CellStatus status;   // EMPTY, OCCUPIED, or DELETED
    
    HashEntry() : status(EMPTY) {}  // Default constructor
};

//==============================================================================
// HASH TABLE STRUCTURE
//==============================================================================

template <typename K, typename V>
struct HashTable {
    HashEntry<K, V>* table;  // Array of entries
    int size;                // Current number of elements
    int capacity;            // Maximum capacity
    
    /*
    MEMORY LAYOUT:
    
    table → [Entry0][Entry1][Entry2]...[Entry_capacity-1]
    
    Each Entry has: key, value, status
    */
};

//==============================================================================
// HASH FUNCTIONS
//==============================================================================

/*
HASH FUNCTION FOR INTEGERS
---------------------------
Simple modulo hash: key % table_size

Example: hash(25) = 25 % 11 = 3
*/
int hashInt(int key, int tableSize) {
    return key % tableSize;
}

/*
HASH FUNCTION FOR STRINGS
--------------------------
Convert string to number, then modulo

Algorithm: Polynomial rolling hash
    hash = (s[0] * 31^(n-1) + s[1] * 31^(n-2) + ... + s[n-1]) % tableSize
    
Simplified version for educational purposes:
*/
int hashString(const string& key, int tableSize) {
    int hash = 0;
    for (int i = 0; i < key.length(); i++) {
        hash = (hash * 31 + key[i]) % tableSize;
    }
    return hash;
    
    /*
    EXAMPLE:
    hashString("Alice", 11)
    
    hash = 0
    hash = (0 * 31 + 'A') % 11 = 65 % 11 = 10
    hash = (10 * 31 + 'l') % 11 = 418 % 11 = 0
    hash = (0 * 31 + 'i') % 11 = 105 % 11 = 6
    hash = (6 * 31 + 'c') % 11 = 285 % 11 = 10
    hash = (10 * 31 + 'e') % 11 = 411 % 11 = 4
    
    Final hash = 4
    */
}

// Generic hash function (we'll use string version)
template <typename K>
int hashFunction(K key, int tableSize) {
    // For demonstration, we'll assume K is string
    // In real implementation, you'd specialize for different types
    return hashString(key, tableSize);
}

//==============================================================================
// LINEAR PROBING HASH TABLE
//==============================================================================

/*
LINEAR PROBING
--------------
When collision occurs, try next indices linearly:
    index, index+1, index+2, index+3, ...

Formula: h(key, i) = (hash(key) + i) % tableSize
where i = 0, 1, 2, 3, ...

Example:
    hash("Alice") = 5
    If index 5 is occupied:
        Try (5 + 1) % 11 = 6
        Try (5 + 2) % 11 = 7
        Try (5 + 3) % 11 = 8
        ... until empty spot found

ADVANTAGES:
    ✓ Simple to implement
    ✓ Good cache performance (sequential access)

DISADVANTAGES:
    ✗ Primary clustering (consecutive occupied cells)
    ✗ Performance degrades as table fills up
*/

template <typename K, typename V>
struct LinearProbingHashTable {
    HashEntry<K, V>* table;
    int capacity;
    int size;
    
    LinearProbingHashTable(int cap = TABLE_SIZE) {
        capacity = cap;
        size = 0;
        table = new HashEntry<K, V>[capacity];
    }
    
    ~LinearProbingHashTable() {
        delete[] table;
    }
};

/*
INSERT WITH LINEAR PROBING
---------------------------
*/
template <typename K, typename V>
void linearInsert(LinearProbingHashTable<K, V>* ht, K key, V value) {
    if (ht->size >= ht->capacity) {
        cout << "Error: Hash table is full!" << endl;
        return;
    }
    
    // Calculate initial hash
    int index = hashFunction(key, ht->capacity);
    int i = 0;  // Probe counter
    
    // Linear probing: try index, index+1, index+2, ...
    while (i < ht->capacity) {
        int probedIndex = (index + i) % ht->capacity;
        
        /*
        PROBING SEQUENCE EXAMPLE:
        If hash(key) = 5 and capacity = 11:
        
        i=0: (5 + 0) % 11 = 5
        i=1: (5 + 1) % 11 = 6
        i=2: (5 + 2) % 11 = 7
        i=3: (5 + 3) % 11 = 8
        ...
        i=6: (5 + 6) % 11 = 0  (wraps around)
        */
        
        // Check if spot is available
        if (ht->table[probedIndex].status == EMPTY || 
            ht->table[probedIndex].status == DELETED) {
            
            // Found empty spot - insert here
            ht->table[probedIndex].key = key;
            ht->table[probedIndex].value = value;
            ht->table[probedIndex].status = OCCUPIED;
            ht->size++;
            
            cout << "  Inserted '" << key << "' at index " << probedIndex;
            if (i > 0) {
                cout << " (after " << i << " probes)";
            }
            cout << endl;
            return;
        }
        
        // If key already exists, update value
        if (ht->table[probedIndex].status == OCCUPIED && 
            ht->table[probedIndex].key == key) {
            ht->table[probedIndex].value = value;
            cout << "  Updated '" << key << "' at index " << probedIndex << endl;
            return;
        }
        
        i++;  // Try next position
    }
    
    cout << "Error: Could not insert (table full)" << endl;
}

/*
SEARCH WITH LINEAR PROBING
---------------------------
*/
template <typename K, typename V>
bool linearSearch(LinearProbingHashTable<K, V>* ht, K key, V* result) {
    int index = hashFunction(key, ht->capacity);
    int i = 0;
    
    while (i < ht->capacity) {
        int probedIndex = (index + i) % ht->capacity;
        
        // If empty (never used), key doesn't exist
        if (ht->table[probedIndex].status == EMPTY) {
            return false;
        }
        
        // If occupied and key matches, found it!
        if (ht->table[probedIndex].status == OCCUPIED && 
            ht->table[probedIndex].key == key) {
            *result = ht->table[probedIndex].value;
            return true;
        }
        
        // If deleted or wrong key, continue probing
        i++;
    }
    
    return false;  // Not found after checking entire table
}

/*
DELETE WITH LINEAR PROBING
---------------------------
*/
template <typename K, typename V>
bool linearDelete(LinearProbingHashTable<K, V>* ht, K key) {
    int index = hashFunction(key, ht->capacity);
    int i = 0;
    
    while (i < ht->capacity) {
        int probedIndex = (index + i) % ht->capacity;
        
        if (ht->table[probedIndex].status == EMPTY) {
            return false;  // Not found
        }
        
        if (ht->table[probedIndex].status == OCCUPIED && 
            ht->table[probedIndex].key == key) {
            
            // Mark as DELETED (not EMPTY!)
            ht->table[probedIndex].status = DELETED;
            ht->size--;
            cout << "  Deleted '" << key << "' from index " << probedIndex << endl;
            return true;
        }
        
        i++;
    }
    
    return false;
}

/*
DISPLAY LINEAR PROBING TABLE
-----------------------------
*/
template <typename K, typename V>
void displayLinear(LinearProbingHashTable<K, V>* ht) {
    cout << "\nHash Table Contents (Linear Probing):\n";
    cout << "Index | Status    | Key       | Value\n";
    cout << "------|-----------|-----------|----------\n";
    
    for (int i = 0; i < ht->capacity; i++) {
        cout << "  " << i << "   | ";
        
        if (ht->table[i].status == EMPTY) {
            cout << "EMPTY     | -         | -\n";
        }
        else if (ht->table[i].status == DELETED) {
            cout << "DELETED   | -         | -\n";
        }
        else {
            cout << "OCCUPIED  | " << ht->table[i].key << " | " 
                 << ht->table[i].value << "\n";
        }
    }
    cout << "Size: " << ht->size << "/" << ht->capacity << endl;
}

//==============================================================================
// QUADRATIC PROBING HASH TABLE
//==============================================================================

/*
QUADRATIC PROBING
-----------------
When collision occurs, try indices using quadratic function:
    index, index+1², index+2², index+3², ...

Formula: h(key, i) = (hash(key) + i²) % tableSize
where i = 0, 1, 2, 3, ...

Example:
    hash("Alice") = 5
    If index 5 is occupied:
        Try (5 + 1²) % 11 = 6
        Try (5 + 2²) % 11 = 9
        Try (5 + 3²) % 11 = 3  (14 % 11)
        Try (5 + 4²) % 11 = 10 (21 % 11)
        ... until empty spot found

ADVANTAGES:
    ✓ Reduces primary clustering
    ✓ Better distribution than linear probing

DISADVANTAGES:
    ✗ Secondary clustering (keys with same hash follow same sequence)
    ✗ May not probe all positions (if table size not prime)
    ✗ Slightly more complex than linear

IMPORTANT: Table size should be prime for quadratic probing to work well!
*/

template <typename K, typename V>
struct QuadraticProbingHashTable {
    HashEntry<K, V>* table;
    int capacity;
    int size;
    
    QuadraticProbingHashTable(int cap = TABLE_SIZE) {
        capacity = cap;
        size = 0;
        table = new HashEntry<K, V>[capacity];
    }
    
    ~QuadraticProbingHashTable() {
        delete[] table;
    }
};

/*
INSERT WITH QUADRATIC PROBING
------------------------------
*/
template <typename K, typename V>
void quadraticInsert(QuadraticProbingHashTable<K, V>* ht, K key, V value) {
    if (ht->size >= ht->capacity) {
        cout << "Error: Hash table is full!" << endl;
        return;
    }
    
    int index = hashFunction(key, ht->capacity);
    int i = 0;
    
    while (i < ht->capacity) {
        // Quadratic probing: (index + i²) % capacity
        int probedIndex = (index + i * i) % ht->capacity;
        
        /*
        QUADRATIC SEQUENCE EXAMPLE:
        If hash(key) = 5 and capacity = 11:
        
        i=0: (5 + 0²) % 11 = 5
        i=1: (5 + 1²) % 11 = 6
        i=2: (5 + 4) % 11 = 9
        i=3: (5 + 9) % 11 = 3   (14 % 11)
        i=4: (5 + 16) % 11 = 10  (21 % 11)
        i=5: (5 + 25) % 11 = 8   (30 % 11)
        
        Notice: Not sequential! Reduces clustering.
        */
        
        if (ht->table[probedIndex].status == EMPTY || 
            ht->table[probedIndex].status == DELETED) {
            
            ht->table[probedIndex].key = key;
            ht->table[probedIndex].value = value;
            ht->table[probedIndex].status = OCCUPIED;
            ht->size++;
            
            cout << "  Inserted '" << key << "' at index " << probedIndex;
            if (i > 0) {
                cout << " (after " << i << " probes, sequence: ";
                for (int j = 0; j <= i; j++) {
                    cout << (index + j * j) % ht->capacity;
                    if (j < i) cout << "→";
                }
                cout << ")";
            }
            cout << endl;
            return;
        }
        
        if (ht->table[probedIndex].status == OCCUPIED && 
            ht->table[probedIndex].key == key) {
            ht->table[probedIndex].value = value;
            cout << "  Updated '" << key << "' at index " << probedIndex << endl;
            return;
        }
        
        i++;
    }
    
    cout << "Error: Could not insert" << endl;
}

/*
SEARCH WITH QUADRATIC PROBING
------------------------------
*/
template <typename K, typename V>
bool quadraticSearch(QuadraticProbingHashTable<K, V>* ht, K key, V* result) {
    int index = hashFunction(key, ht->capacity);
    int i = 0;
    
    while (i < ht->capacity) {
        int probedIndex = (index + i * i) % ht->capacity;
        
        if (ht->table[probedIndex].status == EMPTY) {
            return false;
        }
        
        if (ht->table[probedIndex].status == OCCUPIED && 
            ht->table[probedIndex].key == key) {
            *result = ht->table[probedIndex].value;
            return true;
        }
        
        i++;
    }
    
    return false;
}

/*
DELETE WITH QUADRATIC PROBING
------------------------------
*/
template <typename K, typename V>
bool quadraticDelete(QuadraticProbingHashTable<K, V>* ht, K key) {
    int index = hashFunction(key, ht->capacity);
    int i = 0;
    
    while (i < ht->capacity) {
        int probedIndex = (index + i * i) % ht->capacity;
        
        if (ht->table[probedIndex].status == EMPTY) {
            return false;
        }
        
        if (ht->table[probedIndex].status == OCCUPIED && 
            ht->table[probedIndex].key == key) {
            
            ht->table[probedIndex].status = DELETED;
            ht->size--;
            cout << "  Deleted '" << key << "' from index " << probedIndex << endl;
            return true;
        }
        
        i++;
    }
    
    return false;
}

/*
DISPLAY QUADRATIC PROBING TABLE
--------------------------------
*/
template <typename K, typename V>
void displayQuadratic(QuadraticProbingHashTable<K, V>* ht) {
    cout << "\nHash Table Contents (Quadratic Probing):\n";
    cout << "Index | Status    | Key       | Value\n";
    cout << "------|-----------|-----------|----------\n";
    
    for (int i = 0; i < ht->capacity; i++) {
        cout << "  " << i << "   | ";
        
        if (ht->table[i].status == EMPTY) {
            cout << "EMPTY     | -         | -\n";
        }
        else if (ht->table[i].status == DELETED) {
            cout << "DELETED   | -         | -\n";
        }
        else {
            cout << "OCCUPIED  | " << ht->table[i].key << " | " 
                 << ht->table[i].value << "\n";
        }
    }
    cout << "Size: " << ht->size << "/" << ht->capacity << endl;
}

//==============================================================================
// DEMONSTRATIONS
//==============================================================================

void demonstrateLinearProbing() {
    cout << "\n====================================================\n";
    cout << "  LINEAR PROBING DEMONSTRATION\n";
    cout << "====================================================\n\n";
    
    LinearProbingHashTable<string, int> ht(11);
    
    cout << "Inserting key-value pairs:\n";
    linearInsert(&ht, string("Alice"), 25);
    linearInsert(&ht, string("Bob"), 30);
    linearInsert(&ht, string("Charlie"), 35);
    linearInsert(&ht, string("Diana"), 28);
    linearInsert(&ht, string("Eve"), 32);
    
    displayLinear(&ht);
    
    // Search
    cout << "\nSearching:\n";
    int value;
    if (linearSearch(&ht, string("Charlie"), &value)) {
        cout << "  Found Charlie: " << value << endl;
    }
    
    if (!linearSearch(&ht, string("Frank"), &value)) {
        cout << "  Frank not found" << endl;
    }
    
    // Delete
    cout << "\nDeleting Bob:\n";
    linearDelete(&ht, string("Bob"));
    displayLinear(&ht);
    
    // Insert after delete
    cout << "\nInserting Frank (will use deleted spot):\n";
    linearInsert(&ht, string("Frank"), 27);
    displayLinear(&ht);
}

void demonstrateQuadraticProbing() {
    cout << "\n====================================================\n";
    cout << "  QUADRATIC PROBING DEMONSTRATION\n";
    cout << "====================================================\n\n";
    
    QuadraticProbingHashTable<string, int> ht(11);
    
    cout << "Inserting key-value pairs:\n";
    quadraticInsert(&ht, string("Alice"), 25);
    quadraticInsert(&ht, string("Bob"), 30);
    quadraticInsert(&ht, string("Charlie"), 35);
    quadraticInsert(&ht, string("Diana"), 28);
    quadraticInsert(&ht, string("Eve"), 32);
    
    displayQuadratic(&ht);
    
    // Search
    cout << "\nSearching:\n";
    int value;
    if (quadraticSearch(&ht, string("Diana"), &value)) {
        cout << "  Found Diana: " << value << endl;
    }
    
    // Delete
    cout << "\nDeleting Charlie:\n";
    quadraticDelete(&ht, string("Charlie"));
    displayQuadratic(&ht);
    
    // Insert after delete
    cout << "\nInserting George:\n";
    quadraticInsert(&ht, string("George"), 29);
    displayQuadratic(&ht);
}

void compareProbing() {
    cout << "\n====================================================\n";
    cout << "  COMPARING LINEAR VS QUADRATIC PROBING\n";
    cout << "====================================================\n\n";
    
    cout << "Same keys inserted in both tables:\n\n";
    
    LinearProbingHashTable<string, int> linear(11);
    QuadraticProbingHashTable<string, int> quadratic(11);
    
    string keys[] = {"Alice", "Bob", "Charlie", "Diana", "Eve", "Frank"};
    int values[] = {25, 30, 35, 28, 32, 27};
    
    for (int i = 0; i < 6; i++) {
        linearInsert(&linear, keys[i], values[i]);
        quadraticInsert(&quadratic, keys[i], values[i]);
    }
    
    displayLinear(&linear);
    displayQuadratic(&quadratic);
    
    cout << "\nNotice the different distributions!\n";
    cout << "Linear: More clustering (consecutive occupied cells)\n";
    cout << "Quadratic: Better distribution (less clustering)\n";
}

//==============================================================================
// MAIN FUNCTION
//==============================================================================

int main() {
    cout << "========================================================\n";
    cout << "  TASK 4: HASH TABLE WITH LINEAR & QUADRATIC PROBING\n";
    cout << "========================================================\n";
    
    demonstrateLinearProbing();
    demonstrateQuadraticProbing();
    compareProbing();
    
    cout << "\n========================================================\n";
    cout << "  All demonstrations completed!\n";
    cout << "========================================================\n\n";
    
    return 0;
}

/*
================================================================================
KEY CONCEPTS SUMMARY
================================================================================

1. HASH TABLE BASICS:
   - Stores key-value pairs
   - O(1) average insertion, deletion, search
   - Uses hash function to convert key → index

2. HASH FUNCTION:
   - Converts key to array index: hash(key) % tableSize
   - Good hash function distributes keys uniformly
   - Prime table size helps reduce collisions

3. COLLISION RESOLUTION:
   
   LINEAR PROBING:
   - Try: h(key, i) = (hash(key) + i) % size
   - Sequence: 0, 1, 2, 3, 4, ...
   - Simple but causes primary clustering
   
   QUADRATIC PROBING:
   - Try: h(key, i) = (hash(key) + i²) % size
   - Sequence: 0, 1, 4, 9, 16, ...
   - Reduces clustering but needs prime table size

4. DELETED STATE:
   - Can't use EMPTY after deletion
   - Would break probe sequence
   - DELETED allows probing to continue

5. TIME COMPLEXITY:
   - Average case: O(1) for all operations
   - Worst case: O(n) when many collisions
   - Load factor α = n/m affects performance
     (n = elements, m = table size)
   - Keep α < 0.7 for good performance

6. ADVANTAGES:
   ✓ Fast average-case performance
   ✓ Simple implementation
   ✓ Memory efficient (no extra pointers)

7. DISADVANTAGES:
   ✗ Performance degrades as table fills
   ✗ Requires good hash function
   ✗ Clustering can occur

8. PYTHON EQUIVALENT:
   d = {}                  # Hash table (dict)
   d["Alice"] = 25        # Insert
   value = d["Alice"]     # Search
   del d["Alice"]         # Delete
   
   Python uses separate chaining internally

================================================================================
COMPILATION AND EXECUTION:
   g++ -std=c++11 task4_hashtable.cpp -o task4
   ./task4
================================================================================
*/
