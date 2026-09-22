#include <iostream>
using namespace std;

// Function to swap the values of two variables using double pointers
void swapValues(int **x, int **y) {
    int temp = **x; // Dereference twice to get the value of 'a'
    **x = **y;      // Dereference twice to assign value of 'b' to 'a'
    **y = temp;     // Assign stored value of 'a' to 'b'
}

int main() {
    int a = 5, b = 10;
    
    int *pa = &a;
    int *pb = &b;
    
    int **ppa = &pa;
    int **ppb = &pb;

    cout << "Before swap: a = " << a << ", b = " << b << endl;

    // Pass double pointers to the function
    swapValues(ppa, ppb);

    cout << "After swap:  a = " << a << ", b = " << b << endl;

    return 0;
}
