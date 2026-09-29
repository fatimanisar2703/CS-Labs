#include <iostream>
#include <string>
using namespace std;

struct Node
{
    int bit;
    Node* next;
    Node* prev;
};

// Stores each binary digit in a node
Node* createNumber(string binary)
{
    Node* head = NULL;
    Node* tail = NULL;

    for (int i = 0; i < binary.length(); i++)
    {
        Node* newNode = new Node;
        newNode->bit = binary[i] - '0';
        newNode->next = NULL;
        newNode->prev = tail;

        if (head == NULL)
            head = newNode;
        else
            tail->next = newNode;

        tail = newNode;
    }

    return head;
}

Node* getTail(Node* head)
{
    Node* temp = head;

    while (temp->next != NULL)
        temp = temp->next;

    return temp;
}

void display(Node* head)
{
    Node* temp = head;

    while (temp != NULL)
    {
        cout << temp->bit;
        temp = temp->next;
    }

    cout << endl;
}

// Flip every bit for 1's complement
void onesComplement(Node* head)
{
    Node* temp = head;

    while (temp != NULL)
    {
        if (temp->bit == 0)
            temp->bit = 1;
        else
            temp->bit = 0;

        temp = temp->next;
    }
}

// Add 1 after taking 1's complement
void twosComplement(Node* head)
{
    onesComplement(head);

    Node* temp = getTail(head);
    int carry = 1;

    while (temp != NULL && carry == 1)
    {
        if (temp->bit == 0)
        {
            temp->bit = 1;
            carry = 0;
        }
        else
        {
            temp->bit = 0;
        }

        temp = temp->prev;
    }
}

int toDecimal(Node* head)
{
    int value = 0;
    Node* temp = head;

    while (temp != NULL)
    {
        value = value * 2 + temp->bit;
        temp = temp->next;
    }

    return value;
}

string toString(Node* head)
{
    string result = "";
    Node* temp = head;

    while (temp != NULL)
    {
        result += char(temp->bit + '0');
        temp = temp->next;
    }

    return result;
}

// Adds two binary numbers
Node* addBinary(Node* a, Node* b)
{
    string x = toString(a);
    string y = toString(b);

    int i = x.length() - 1;
    int j = y.length() - 1;
    int carry = 0;

    string result = "";

    while (i >= 0 || j >= 0 || carry == 1)
    {
        int sum = carry;

        if (i >= 0)
            sum += x[i--] - '0';

        if (j >= 0)
            sum += y[j--] - '0';

        result = char((sum % 2) + '0') + result;
        carry = sum / 2;
    }

    return createNumber(result);
}

// Multiplies two binary numbers
Node* multiplyBinary(Node* a, Node* b)
{
    int x = toDecimal(a);
    int y = toDecimal(b);

    int result = x * y;

    if (result == 0)
        return createNumber("0");

    string binary = "";

    while (result > 0)
    {
        binary = char((result % 2) + '0') + binary;
        result = result / 2;
    }

    return createNumber(binary);
}

void deleteList(Node* head)
{
    Node* temp;

    while (head != NULL)
    {
        temp = head;
        head = head->next;
        delete temp;
    }
}

int main()
{
    string binary1, binary2;
    int choice;

    cout << "Enter first binary number: ";
    cin >> binary1;

    Node* number1 = createNumber(binary1);

    cout << "First binary number: ";
    display(number1);

    cout << "\n1. 1's Complement" << endl;
    cout << "2. 2's Complement" << endl;
    cout << "3. Binary Addition" << endl;
    cout << "4. Binary Multiplication" << endl;
    cout << "5. Convert to Decimal" << endl;
    cout << "Enter choice: ";
    cin >> choice;

    if (choice == 1)
    {
        onesComplement(number1);

        cout << "1's Complement: ";
        display(number1);
    }
    else if (choice == 2)
    {
        twosComplement(number1);

        cout << "2's Complement: ";
        display(number1);
    }
    else if (choice == 3)
    {
        cout << "Enter second binary number: ";
        cin >> binary2;

        Node* number2 = createNumber(binary2);
        Node* result = addBinary(number1, number2);

        cout << "Result: ";
        display(result);

        deleteList(number2);
        deleteList(result);
    }
    else if (choice == 4)
    {
        cout << "Enter second binary number: ";
        cin >> binary2;

        Node* number2 = createNumber(binary2);
        Node* result = multiplyBinary(number1, number2);

        cout << "Result: ";
        display(result);

        deleteList(number2);
        deleteList(result);
    }
    else if (choice == 5)
    {
        cout << "Decimal value: " << toDecimal(number1) << endl;
    }

    deleteList(number1);

    return 0;
}