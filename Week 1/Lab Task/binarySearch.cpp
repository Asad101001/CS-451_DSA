#include <iostream>
using namespace std;

int main (){
    int l = 0, r = 10, mid;
    int arr[11] = {1,5,6,11,49,77,88,91,99,101};
    int match;
    cout << "Enter a number ";
    cin >> match;

    while (l<= r)
    {
        mid = (l+r)/2;
        if (match == arr[mid])
        {
            cout << "Found @ index " << mid;
            break;

        }

        if (match < arr[mid])
        {
            r=mid-1;
        }
        else
            l = mid + 1;
    }

    if (l>r)
        cout << "Number not found !";
}