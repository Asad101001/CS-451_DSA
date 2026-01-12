// 11_sorting_comparison.cpp
// Side-by-side comparison and performance analysis

#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <iomanip>
using namespace std;
using namespace chrono;

// ============ INSTRUMENTED VERSIONS ============
// Track comparisons, swaps, and passes

struct SortStats {
    int comparisons;
    int swaps;
    int passes;
    long long timeMs;
    
    SortStats() : comparisons(0), swaps(0), passes(0), timeMs(0) {}
    
    void print(const string& name) {
        cout << "\n" << name << " Statistics:" << endl;
        cout << "  Comparisons: " << comparisons << endl;
        cout << "  Swaps:       " << swaps << endl;
        cout << "  Passes:      " << passes << endl;
        cout << "  Time (μs):   " << timeMs << endl;
    }
};

// Bubble Sort with statistics
SortStats bubbleSortInstrumented(vector<int>& arr) {
    SortStats stats;
    auto start = high_resolution_clock::now();
    
    int n = arr.size();
    
    for (int i = 0; i < n - 1; i++) {
        stats.passes++;
        bool swapped = false;
        
        for (int j = 0; j < n - 1 - i; j++) {
            stats.comparisons++;
            
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                stats.swaps++;
                swapped = true;
            }
        }
        
        if (!swapped) break;
    }
    
    auto end = high_resolution_clock::now();
    stats.timeMs = duration_cast<microseconds>(end - start).count();
    
    return stats;
}

// Selection Sort with statistics
SortStats selectionSortInstrumented(vector<int>& arr) {
    SortStats stats;
    auto start = high_resolution_clock::now();
    
    int n = arr.size();
    
    for (int i = 0; i < n - 1; i++) {
        stats.passes++;
        int minIndex = i;
        
        for (int j = i + 1; j < n; j++) {
            stats.comparisons++;
            
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        
        if (minIndex != i) {
            swap(arr[i], arr[minIndex]);
            stats.swaps++;
        }
    }
    
    auto end = high_resolution_clock::now();
    stats.timeMs = duration_cast<microseconds>(end - start).count();
    
    return stats;
}

// ============ COMPARISON TESTS ============

void compareOnArray(vector<int> arr, const string& testName) {
    cout << "\n" << string(60, '=') << endl;
    cout << "TEST: " << testName << endl;
    cout << string(60, '=') << endl;
    
    cout << "Input: [";
    for (int i = 0; i < min(10, (int)arr.size()); i++) {
        cout << arr[i];
        if (i < min(9, (int)arr.size() - 1)) cout << ", ";
    }
    if (arr.size() > 10) cout << "...";
    cout << "] (size: " << arr.size() << ")" << endl;
    
    // Test Bubble Sort
    vector<int> arr1 = arr;
    SortStats bubbleStats = bubbleSortInstrumented(arr1);
    bubbleStats.print("Bubble Sort");
    
    // Test Selection Sort
    vector<int> arr2 = arr;
    SortStats selectionStats = selectionSortInstrumented(arr2);
    selectionStats.print("Selection Sort");
    
    // Comparison
    cout << "\nComparison:" << endl;
    cout << "  Fewer comparisons:  " 
         << (bubbleStats.comparisons < selectionStats.comparisons ? "Bubble" : 
             bubbleStats.comparisons > selectionStats.comparisons ? "Selection" : "Tie")
         << endl;
    cout << "  Fewer swaps:        " 
         << (bubbleStats.swaps < selectionStats.swaps ? "Bubble" : 
             bubbleStats.swaps > selectionStats.swaps ? "Selection" : "Tie")
         << endl;
    cout << "  Fewer passes:       " 
         << (bubbleStats.passes < selectionStats.passes ? "Bubble" : 
             bubbleStats.passes > selectionStats.passes ? "Selection" : "Tie")
         << endl;
    cout << "  Faster:             " 
         << (bubbleStats.timeMs < selectionStats.timeMs ? "Bubble" : 
             bubbleStats.timeMs > selectionStats.timeMs ? "Selection" : "Tie")
         << endl;
}

// ============ VISUALIZATION ============

void visualizeSort(const string& name, vector<int> arr) {
    cout << "\n" << name << " VISUALIZATION" << endl;
    cout << string(50, '-') << endl;
    
    int n = arr.size();
    
    // Print initial state
    cout << "Start: ";
    for (int x : arr) cout << x << " ";
    cout << endl << endl;
    
    if (name == "Bubble Sort") {
        // Bubble sort visualization
        for (int i = 0; i < n - 1; i++) {
            bool swapped = false;
            cout << "Pass " << (i + 1) << ":" << endl;
            
            for (int j = 0; j < n - 1 - i; j++) {
                // Show comparison
                cout << "  [";
                for (int k = 0; k < n; k++) {
                    if (k == j || k == j + 1) {
                        cout << "*" << arr[k] << "*";
                    } else {
                        cout << arr[k];
                    }
                    if (k < n - 1) cout << " ";
                }
                cout << "]";
                
                if (arr[j] > arr[j + 1]) {
                    swap(arr[j], arr[j + 1]);
                    cout << " → SWAP";
                    swapped = true;
                } else {
                    cout << " → ok";
                }
                cout << endl;
            }
            
            if (!swapped) {
                cout << "  No swaps - sorted!" << endl;
                break;
            }
            cout << endl;
        }
    } else {
        // Selection sort visualization
        for (int i = 0; i < n - 1; i++) {
            cout << "Pass " << (i + 1) << ":" << endl;
            
            int minIndex = i;
            cout << "  Find min in: ";
            for (int k = i; k < n; k++) {
                cout << arr[k] << " ";
            }
            cout << endl;
            
            for (int j = i + 1; j < n; j++) {
                if (arr[j] < arr[minIndex]) {
                    minIndex = j;
                }
            }
            
            cout << "  Min = " << arr[minIndex] << " at index " << minIndex << endl;
            
            if (minIndex != i) {
                cout << "  Swap " << arr[i] << " ↔ " << arr[minIndex] << ": ";
                swap(arr[i], arr[minIndex]);
            } else {
                cout << "  No swap needed: ";
            }
            
            for (int x : arr) cout << x << " ";
            cout << endl << endl;
        }
    }
    
    cout << "Final: ";
    for (int x : arr) cout << x << " ";
    cout << endl;
}

// ============ PRACTICE PROBLEMS ============

void practiceProblems() {
    cout << "\n" << string(60, '=') << endl;
    cout << "PRACTICE PROBLEMS" << endl;
    cout << string(60, '=') << endl;
    
    cout << "\nProblem 1: What will be the array after first pass of bubble sort?" << endl;
    cout << "Input: [3, 1, 4, 1, 5, 9, 2, 6]" << endl;
    vector<int> p1 = {3, 1, 4, 1, 5, 9, 2, 6};
    
    // Simulate one pass
    for (int j = 0; j < 7; j++) {
        if (p1[j] > p1[j + 1]) {
            swap(p1[j], p1[j + 1]);
        }
    }
    
    cout << "Answer: [";
    for (int i = 0; i < 8; i++) {
        cout << p1[i];
        if (i < 7) cout << ", ";
    }
    cout << "]" << endl;
    cout << "Explanation: Largest element (9) bubbled to the end" << endl;
    
    cout << "\nProblem 2: What will be array after first pass of selection sort?" << endl;
    cout << "Input: [3, 1, 4, 1, 5, 9, 2, 6]" << endl;
    vector<int> p2 = {3, 1, 4, 1, 5, 9, 2, 6};
    
    // Find minimum and swap
    int minIdx = 0;
    for (int j = 1; j < 8; j++) {
        if (p2[j] < p2[minIdx]) minIdx = j;
    }
    swap(p2[0], p2[minIdx]);
    
    cout << "Answer: [";
    for (int i = 0; i < 8; i++) {
        cout << p2[i];
        if (i < 7) cout << ", ";
    }
    cout << "]" << endl;
    cout << "Explanation: Minimum element (1) placed at beginning" << endl;
    
    cout << "\nProblem 3: How many comparisons for array of size 5?" << endl;
    cout << "Bubble Sort (worst): 4+3+2+1 = 10 comparisons" << endl;
    cout << "Selection Sort (always): 4+3+2+1 = 10 comparisons" << endl;
    
    cout << "\nProblem 4: How many swaps for reverse sorted [5,4,3,2,1]?" << endl;
    cout << "Bubble Sort: 10 swaps (every comparison swaps)" << endl;
    cout << "Selection Sort: 2 swaps (5↔1, then 4↔2)" << endl;
    
    cout << "\nProblem 5: Which is better for nearly sorted array [1,2,3,5,4]?" << endl;
    vector<int> p5a = {1, 2, 3, 5, 4};
    vector<int> p5b = {1, 2, 3, 5, 4};
    
    SortStats bs = bubbleSortInstrumented(p5a);
    SortStats ss = selectionSortInstrumented(p5b);
    
    cout << "Bubble Sort: " << bs.comparisons << " comparisons, " << bs.swaps << " swaps" << endl;
    cout << "Selection Sort: " << ss.comparisons << " comparisons, " << ss.swaps << " swaps" << endl;
    cout << "Winner: Bubble Sort (adaptive - detected nearly sorted)" << endl;
}

// ============ MAIN ============
int main() {
    cout << "BUBBLE SORT vs SELECTION SORT" << endl;
    cout << "Complete Comparison & Analysis" << endl;
    
    // Test 1: Random array
    vector<int> random = {64, 34, 25, 12, 22, 11, 90};
    compareOnArray(random, "Random Array");
    
    // Test 2: Already sorted (best case for bubble)
    vector<int> sorted = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    compareOnArray(sorted, "Already Sorted (Best case for Bubble)");
    
    // Test 3: Reverse sorted (worst case)
    vector<int> reverse = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    compareOnArray(reverse, "Reverse Sorted (Worst case)");
    
    // Test 4: Nearly sorted
    vector<int> nearly = {1, 2, 3, 4, 10, 6, 7, 8, 9, 5};
    compareOnArray(nearly, "Nearly Sorted");
    
    // Test 5: Many duplicates
    vector<int> dupes = {5, 2, 5, 2, 5, 2, 5, 2};
    compareOnArray(dupes, "Many Duplicates");
    
    // Test 6: Large array
    vector<int> large(100);
    for (int i = 0; i < 100; i++) large[i] = 100 - i;
    compareOnArray(large, "Large Array (100 elements, reverse sorted)");
    
    // Visualizations
    cout << "\n\n" << string(60, '=') << endl;
    cout << "VISUALIZATIONS" << endl;
    cout << string(60, '=') << endl;
    
    vector<int> vis = {5, 2, 8, 1, 9};
    visualizeSort("Bubble Sort", vis);
    
    vis = {5, 2, 8, 1, 9};
    visualizeSort("Selection Sort", vis);
    
    // Practice problems
    practiceProblems();
    
    // Summary table
    cout << "\n\n" << string(60, '=') << endl;
    cout << "SUMMARY TABLE" << endl;
    cout << string(60, '=') << endl;
    
    cout << "\n" << left << setw(25) << "Characteristic" 
         << setw(20) << "Bubble Sort" 
         << setw(20) << "Selection Sort" << endl;
    cout << string(65, '-') << endl;
    
    cout << setw(25) << "Time (Best)" << setw(20) << "O(n)" << setw(20) << "O(n²)" << endl;
    cout << setw(25) << "Time (Average)" << setw(20) << "O(n²)" << setw(20) << "O(n²)" << endl;
    cout << setw(25) << "Time (Worst)" << setw(20) << "O(n²)" << setw(20) << "O(n²)" << endl;
    cout << setw(25) << "Space" << setw(20) << "O(1)" << setw(20) << "O(1)" << endl;
    cout << setw(25) << "Stable" << setw(20) << "Yes" << setw(20) << "No" << endl;
    cout << setw(25) << "Adaptive" << setw(20) << "Yes" << setw(20) << "No" << endl;
    cout << setw(25) << "Comparisons (n=5)" << setw(20) << "10 (worst)" << setw(20) << "10 (always)" << endl;
    cout << setw(25) << "Swaps (n=5, worst)" << setw(20) << "10" << setw(20) << "4" << endl;
    cout << setw(25) << "Online" << setw(20) << "No" << setw(20) << "No" << endl;
    cout << setw(25) << "Best for" << setw(20) << "Nearly sorted" << setw(20) << "Min swaps" << endl;
    
    return 0;
}

/*
KEY INSIGHTS FROM TESTING:

1. ALREADY SORTED ARRAYS:
   - Bubble Sort: O(n) with optimization - MUCH faster
   - Selection Sort: Still O(n²) - no advantage

2. REVERSE SORTED (WORST CASE):
   - Bubble Sort: O(n²) comparisons, O(n²) swaps
   - Selection Sort: O(n²) comparisons, O(n) swaps
   - Selection better due to fewer swaps

3. RANDOM ARRAYS:
   - Usually similar performance
   - Selection slightly better due to predictable swaps

4. NEARLY SORTED:
   - Bubble Sort wins - adaptive behavior
   - Can detect sorting early

5. LARGE ARRAYS:
   - Both struggle at O(n²)
   - Use quicksort/mergesort instead

WHEN TO CHOOSE BUBBLE SORT:
✓ Data might be nearly sorted
✓ Need stable sorting
✓ Want to detect if already sorted
✓ Writing to memory is cheap

WHEN TO CHOOSE SELECTION SORT:
✓ Writing to memory is expensive
✓ Want predictable swaps
✓ Don't need stability
✓ Don't care about adaptivity

REAL WORLD:
In practice, use neither for large datasets!
- std::sort() in C++ (typically introsort)
- Quicksort for average O(n log n)
- Mergesort for guaranteed O(n log n) + stability

These algorithms are for:
- Learning fundamentals
- Very small arrays (< 20 elements)
- Educational purposes
- Interview questions

COMPLEXITY REMINDER:
O(n²) means:
  n=10   → ~100 operations
  n=100  → ~10,000 operations
  n=1000 → ~1,000,000 operations
  
O(n log n) means:
  n=1000 → ~10,000 operations
  
That's why we need better algorithms!
*/