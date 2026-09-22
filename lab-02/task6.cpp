#include <iostream>
using namespace std;

int main()
{
    int rows, cols;

    // 1. Read and validate rows and columns
    do
    {
        cout << "Enter number of students: ";
        cin >> rows;

        if (rows <= 0)
        {
            cout << "Rows must be greater than 0.\n";
        }

    } while (rows <= 0);

    do
    {
        cout << "Enter number of subjects: ";
        cin >> cols;

        if (cols <= 0)
        {
            cout << "Columns must be greater than 0.\n";
        }

    } while (cols <= 0);


    // 2. Allocate array of row pointers
    int** marks = new int*[rows];

    // Allocate each row separately
    for (int r = 0; r < rows; r++)
    {
        marks[r] = new int[cols];
    }


    // 3. Input marks and display matrix
    cout << "\nEnter marks for each student:\n";

    for (int r = 0; r < rows; r++)
    {
        cout << "Student " << r + 1 << ": ";

        for (int c = 0; c < cols; c++)
        {
            cin >> *(*(marks + r) + c);
        }
    }

    cout << "\nMarks Matrix:\n";

    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < cols; c++)
        {
            cout << *(*(marks + r) + c) << " ";
        }

        cout << endl;
    }


    // 4. Calculate totals
    int bestTotal = 0;
    int bestStudent = 1;

    // Determine first student's total first
    for (int c = 0; c < cols; c++)
    {
        bestTotal += *(*(marks + 0) + c);
    }

    // Calculate totals for remaining students
    cout << "\nTotals:\n";

    cout << "Student 1: " << bestTotal << endl;

    for (int r = 1; r < rows; r++)
    {
        int total = 0;

        for (int c = 0; c < cols; c++)
        {
            total += *(*(marks + r) + c);
        }

        cout << "Student " << r + 1 << ": " << total << endl;

        if (total > bestTotal)
        {
            bestTotal = total;
            bestStudent = r + 1;
        }
    }

    cout << "\nTop student: " << bestStudent << endl;
    cout << "Highest total: " << bestTotal << endl;


    // 5. Deallocate memory
    for (int r = 0; r < rows; r++)
    {
        delete[] marks[r];
    }

    delete[] marks;

    marks = nullptr;

    return 0;
}
