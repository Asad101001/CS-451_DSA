#include <iostream>
using namespace std;

void passByValue(int x) {
    x = 100; 
    cout << "Inside passByValue: " << x << endl;
}

void passByReference(int& x) {
    x = 200; 
    cout << "Inside passByReference: " << x << endl;
}

void passByPointer(int* x) {
    *x = 300;  
    cout << "Inside passByPointer: " << *x << endl;
}

void displayValue(const int& x) {
    cout << "Value (read-only): " << x << endl;
    // x = 50; ERROR: can't modify const reference
}

void modifyArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        arr[i] *= 2;  
    }
}

void displayArray(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int& getElement(int arr[], int index) {
    return arr[index]; 
}


int main() {
    // ============ TESTING PASS BY VALUE ============
    int num1 = 10;
    cout << "=== PASS BY VALUE ===" << endl;
    cout << "Before: " << num1 << endl;
    passByValue(num1);
    cout << "After: " << num1 << endl;  // Still 10 - unchanged
    
    // ============ TESTING PASS BY REFERENCE ============
    int num2 = 10;
    cout << "\n=== PASS BY REFERENCE ===" << endl;
    cout << "Before: " << num2 << endl;
    passByReference(num2);
    cout << "After: " << num2 << endl;  // Changed to 200
    
    // ============ TESTING PASS BY POINTER ============
    int num3 = 10;
    cout << "\n=== PASS BY POINTER ===" << endl;
    cout << "Before: " << num3 << endl;
    passByPointer(&num3);  // Pass address
    cout << "After: " << num3 << endl;  // Changed to 300
    
    // ============ TESTING CONST REFERENCE ============
    int num4 = 500;
    cout << "\n=== CONST REFERENCE ===" << endl;
    displayValue(num4);
    
    // ============ TESTING ARRAY MODIFICATION ============
    int myArray[5] = {1, 2, 3, 4, 5};
    cout << "\n=== ARRAY PASSING ===" << endl;
    cout << "Before: ";
    displayArray(myArray, 5);
    
    modifyArray(myArray, 5);
    cout << "After: ";
    displayArray(myArray, 5);
    
    // ============ RETURN BY REFERENCE ============
    cout << "\n=== RETURN BY REFERENCE ===" << endl;
    cout << "Element at index 2: " << getElement(myArray, 2) << endl;
    getElement(myArray, 2) = 999;  // Can assign to it!
    cout << "After assignment: " << getElement(myArray, 2) << endl;
    
    return 0;
}