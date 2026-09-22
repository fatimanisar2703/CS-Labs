/*complete program that reads and displays
all three integers, releases the allocation correctly and
 resets the pointer.*/

#include <iostream>
using namespace std;

int main()
{
    int n = 3;

    int* values = new int[n];

    cout << "Enter 3 integers: ";

    for (int i = 0; i < n; i++)
    {
        cin >> values[i];
    }

    cout << "Values: ";

    for (int i = 0; i < n; i++)
    {
        cout << values[i] << " ";
    }

    cout << endl;

    delete[] values;
    values = nullptr;

    return 0;
}
