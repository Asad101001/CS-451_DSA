#include <iostream>
using namespace std;

int main() {
    
    int num = 42;
    int* ptr = &num;  
    
    cout << "=== POINTERS ===" << endl;
    cout << "Value of num: " << num << endl;
    cout << "Address of num: " << &num << endl;  
    cout << "Value stored in ptr: " << ptr << endl; 
    cout << "Value at address ptr points to: " << *ptr << endl;
    

    *ptr = 100;  
    cout << "After *ptr = 100, num is now: " << num << endl;
    
    
    int original = 50;
    int& ref = original;  
    
    cout << "\n=== REFERENCES ===" << endl;
    cout << "Original: " << original << endl;
    cout << "Reference: " << ref << endl;
    
    ref = 200; 
    cout << "After ref = 200, original is: " << original << endl;
    
    cout << "\n=== POINTER VS REFERENCE ===" << endl;
    
    int a = 10, b = 20;
    

    int* p = &a;
    cout << "Pointer points to a: " << *p << endl;
    p = &b; 
    cout << "Pointer now points to b: " << *p << endl;
    
    int& r = a;
    cout << "Reference to a: " << r << endl;
    r = b; 
    cout << "After r = b, a is: " << a << " (copied value)" << endl;
    

    int* nullPtr = nullptr;  
    
    if (nullPtr == nullptr) {
        cout << "\nPointer is null - safe to check before dereferencing" << endl;
    }
    
    int arr[5] = {1, 2, 3, 4, 5};
    int* arrPtr = arr; 
    
    cout << "\n=== ARRAY POINTER RELATIONSHIP ===" << endl;
    cout << "First element: " << arr[0] << " or " << *arrPtr << endl;
    cout << "Second element: " << arr[1] << " or " << *(arrPtr + 1) << endl;
    
    arrPtr++;  
    cout << "After arrPtr++, points to: " << *arrPtr << endl;
    
    return 0;
}
