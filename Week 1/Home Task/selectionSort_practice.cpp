#include <iostream>
using namespace std;

int main(){

    int arr[] = {99,1001,67,41,2,71,9,88,69};
    int n = sizeof(arr) / sizeof(arr[0]);

    for (int i = 0; i < n - 1; i++)
    {
        int minIndex = i;

        for (int j = 0; j < n ;j++){
            if (arr[j]<arr[minIndex]){
                minIndex = j;
            }
            int temp = arr[i];
            arr[i] = arr[minIndex];
            arr[minIndex]=temp;
        }
    }

    for (int x:arr){
        cout << x << "" << endl;
    }

    return 0;
}