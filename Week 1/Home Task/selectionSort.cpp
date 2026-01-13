#include <iostream>
#include <vector>
using namespace std;


void selectionSort(vector<int>& arr) {
    int n = arr.size();

    for (int i = 0; i < n - 1; i++) {
        
        int min = i;
        
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min]) {
                min = j;
            }
        }
        
        if (min != i) {
            int temp = arr[i];
            arr[i] = arr[min];
            arr[min] = temp;
        }
    }
}

int main (){

    vector<int> arr = {16, 92, 17, 35, 42, 67, 1, 11, 2, 0};
    cout << "Before selection sorting" <<endl;
    for (int x : arr) cout << x << " ";
    cout << endl;

    selectionSort(arr);

    cout << "-------Sorting-------"<< endl;

    cout << "After selection sorting"<< endl;
    for (int x : arr) cout << x << " ";
    cout << endl;
    
}