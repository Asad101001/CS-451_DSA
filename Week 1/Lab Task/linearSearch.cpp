#include <iostream>
using namespace std;

int main (){
    int array[6] = {1,6,12,75,9};
    bool found = false;
    int match ;
    cout << "Enter number ";
    cin >> match;

    for (int i = 0; i < 6; i++)
    {
        if (array[i] == match)
        {
            cout << "Number found @ index " << i;
            found = true;
            break;
        }
    }

    if (found == false)
    {
        cout << "Number not found!";
    }

    return 0;
}