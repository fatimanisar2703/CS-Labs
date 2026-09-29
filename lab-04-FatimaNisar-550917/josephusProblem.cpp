#include <iostream>
using namespace std;

struct Node
{
    int id;
    Node* next;
};

// Creates the circular linked list
Node* createCircle(int n)
{
    Node* head = new Node;
    head->id = 1;

    Node* temp = head;

    for (int i = 2; i <= n; i++)
    {
        Node* newNode = new Node;
        newNode->id = i;
        temp->next = newNode;
        temp = newNode;
    }

    // Connect last node back to first
    temp->next = head;

    return head;
}

void josephus(int n, int k)
{
    Node* head = createCircle(n);
    Node* current = head;
    Node* previous = NULL;

    cout << "Eliminated order: ";

    while (current->next != current)
    {
        // Move k-1 positions
        for (int i = 1; i < k; i++)
        {
            previous = current;
            current = current->next;
        }

        cout << current->id << " ";

        // Remove current person
        previous->next = current->next;
        delete current;
        current = previous->next;
    }

    cout << endl;
    cout << "Survivor: " << current->id << endl;

    delete current;
}

int main()
{
    int n, k;

    cout << "Enter number of people: ";
    cin >> n;

    cout << "Enter step count: ";
    cin >> k;

    if (n <= 0 || k <= 0)
    {
        cout << "Invalid input." << endl;
        return 0;
    }

    josephus(n, k);

    return 0;
}