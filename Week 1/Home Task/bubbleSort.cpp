#include <iostream> 
#include <vector>
using namespace std;

void bubbleSort (vector<int>&arr){
    int n = arr.size();
    bool flag = false;

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - 1;j++){
            if (arr[j]>arr[j+1]){
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j + 1] = temp;
                flag = true;
            }
        }
        if (!flag) break;    
    }
}

int main(){
    vector<int> arrX = {99,64,75,11,12,98,91,1};
    cout << "Before bubble sorting" <<endl;
    for (int x : arrX) cout << x << " ";
    cout << endl;

    bubbleSort(arrX);

    cout << "-------Sorting-------"<< endl;

    cout << "After bubble sorting"<< endl;
    for (int x : arrX) cout << x << " ";
    cout << endl;
}