#include <iostream>
#include <vector>
using namespace std;

void insertionSort(vector<int>& arr) {
    int n = arr.size();
    
    for (int i = 1; i < n; i++) {
        
        int hold = arr[i];      
        int gap = i - 1;         
        
       
        while (gap >= 0 && arr[gap] > hold) {
            arr[gap + 1] = arr[gap]; 
            gap--;
        }
        
        arr[gap + 1] = hold;
    }
}

int main() {

    vector<int> arr = {5, 2, 8, 1, 9};

    cout << "Before insertion sort: [ ";
    for (int x = 0; x < arr.size();x++)
    {
        cout << arr[x];
        cout << "  ";
    }
    cout << "]"<<endl;

    insertionSort(arr);

    cout << "After insertion sort: [ ";
    for (int x = 0; x < arr.size();x++)
    {
        cout << arr[x];
        cout << "  ";
    }
    cout << "]"<<endl;

        // cout << "After:  [";
        // for (int i = 0; i < arr1.size(); i++) {
        //     cout << arr1[i];
        //     if (i < arr1.size() - 1) cout << ", ";
        // }
        // cout << "]" << endl << endl;

        return 0;
}