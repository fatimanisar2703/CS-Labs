#include <iostream>
using namespace std;

int main()
{
    int n;

    // Read and validate n
    do
    {
        cout << "Enter number of marks (1-10): ";
        cin >> n;

        if (n < 1 || n > 10)
        {
            cout << "Invalid input. Enter a value from 1 to 10.\n";
        }

    } while (n < 1 || n > 10);

    // Allocate original block
    int* marks = new int[n];

    // Read original marks
    cout << "Enter " << n << " marks: ";

    for (int i = 0; i < n; i++)
    {
        cin >> *(marks + i);
    }

    // Allocate new block with space for one additional mark
    int* newMarks = new int[n + 1];

    // Copy original marks using pointer notation
    for (int i = 0; i < n; i++)
    {
        *(newMarks + i) = *(marks + i);
    }

    // Read new student's mark into final position
    cout << "Enter new mark: ";
    cin >> *(newMarks + n);

    // Release old block
    delete[] marks;

    // Make original pointer refer to new block
    marks = newMarks;

    // Update size
    n = n + 1;

    // Display all values
    cout << "All marks: ";

    for (int i = 0; i < n; i++)
    {
        cout << *(marks + i) << " ";
    }

    cout << endl;

    // Release final block exactly once
    delete[] marks;

    // Reset pointer
    marks = nullptr;

    return 0;
}
