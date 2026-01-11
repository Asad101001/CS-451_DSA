#include <iostream>
using namespace std;

int main (){

    int arr[7] = {46,61,1,5,67,101,21};
    int n = sizeof(arr) / sizeof(arr[0]);

    bool sorted;

    do{
        sorted = false;
        for (int i = 0; i < n - 1; i++){
            for (int j = 0; j < n - 1; j++)
            {
                if (arr[j] > arr[j + 1])
                {
                    int temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                    sorted = true;
                }
            }
        }
    } while (sorted);

    for (int x:arr){
        cout << x << "" << endl;
    }

    return 0;
}