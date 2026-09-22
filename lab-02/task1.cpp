#include <iostream>
using namespace std;

int main() {

    //Memory occupied by data types

    cout << "Memory occupied by data types:\n";
    cout << "int     : " << sizeof(int)   << " bytes\n";
    cout << "long    : " << sizeof(long)    << " bytes\n";
    cout << "double  : " << sizeof(double)  << " bytes\n";
    cout << "float   : " << sizeof(float)   << " bytes\n";
    cout << "char    : " << sizeof(char) << " bytes\n";

    //Memory occupied by pointers

    cout << "\nMemory occupied by pointers of data types:\n";
    cout << "int     : " << sizeof(int*)   << " bytes\n";
    cout << "long    : " << sizeof(long*)    << " bytes\n";
    cout << "double  : " << sizeof(double*)  << " bytes\n";
    cout << "float   : " << sizeof(float*)   << " bytes\n";
    cout << "char    : " << sizeof(char*) << " bytes\n";

    return 0;
}
