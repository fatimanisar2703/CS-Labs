#include <iostream>
using namespace std;
 
int main()
{
    int a[50][50];
    int rows, cols;
 
    cout << "Enter number of rows: ";
    cin >> rows;
    cout << "Enter number of columns: ";
    cin >> cols;
 
    cout << "Enter the elements:" << endl;
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            cin >> a[i][j];
 
    int low = 0;
    int high = cols - 1;
 
    while (low <= high)
    {
        int mid = (low + high) / 2;
 
        int maxRow = 0;
        for (int i = 1; i < rows; i++)
        {
            if (a[i][mid] > a[maxRow][mid])
                maxRow = i;
        }
 
        int left = -1;
        int right = -1;
        if (mid > 0)
            left = a[maxRow][mid - 1];
        if (mid < cols - 1)
            right = a[maxRow][mid + 1];
 
        if (a[maxRow][mid] >= left && a[maxRow][mid] >= right)
        {
            cout << "Peak element: " << a[maxRow][mid] << endl;
            cout << "Position: (" << maxRow << ", " << mid << ")" << endl;
            return 0;
        }
        else if (left > a[maxRow][mid])
            high = mid - 1;
        else
            low = mid + 1;
    }
 
    return 0;
}
