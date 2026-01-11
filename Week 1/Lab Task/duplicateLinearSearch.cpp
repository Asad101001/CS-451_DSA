#include <iostream>
using namespace std;

int main (){
    int array[8] = {1,6,12,75,75,6,9};
    bool found = false;
    int match ;
    cout << "Enter number ";
    cin >> match;

    for (int i = 0; i < 8; i++)
    {
        if (array[i] == match)
        {
            cout << "Number found @ index " << i << endl;
            found = true;
        }
    }

    if (found == false)
    {
        cout << "Number not found!";
    }

    return 0;
}