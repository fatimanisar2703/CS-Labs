#include <iostream>
#include <string>
#include <cctype>
using namespace std;

bool isPalindrome(string str)
{
    string cleanString = "";

    // Remove spaces, punctuation and convert to lowercase
    for (char c : str)
    {
        if (isalnum(c))
        {
            cleanString += tolower(c);
        }
    }

    int start = 0;
    int end = cleanString.length() - 1;

    // Iterative palindrome checking
    while (start < end)
    {
        if (cleanString[start] != cleanString[end])
        {
            return false;
        }

        start++;
        end--;
    }

    return true;
}

int main()
{
    string str;

    cout << "Enter a string: ";
    getline(cin, str);

    if (isPalindrome(str))
    {
        cout << "The string is a palindrome." << endl;
    }
    else
    {
        cout << "The string is not a palindrome." << endl;
    }

    return 0;
}