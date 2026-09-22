#include <iostream>
using namespace std;

struct Node
{
    int data;
    Node *next;
    Node(int value) : data(value), next(nullptr) {}
};

class LinkedList
{
private:
    Node *head;

public:
    LinkedList() : head(nullptr) {}

    ~LinkedList()
    {
        while (head != nullptr)
        {
            Node *toDelete = head;
            head = head->next;
            delete toDelete;
        }
    }

    void insertAtHead(int value)
    {
        Node *newNode = new Node(value);
        newNode->next = head;
        head = newNode;
        cout << value << " inserted at head." << endl;
    }

    void insertAtThird(int value)
    {
        Node *newNode = new Node(value);

        if (head == nullptr || head->next == nullptr)
        {
            cout << "Fewer than 2 nodes, inserting at the end instead." << endl;
            if (head == nullptr) head = newNode;
            else head->next = newNode;
            return;
        }

        Node *current = head;
        for (int i = 1; i < 2; i++)
            current = current->next;

        newNode->next = current->next;
        current->next = newNode;
        cout << value << " inserted at the 3rd position." << endl;
    }

    void displayList()
    {
        Node *current = head;
        while (current != nullptr)
        {
            cout << current->data << " -> ";
            current = current->next;
        }
        cout << "NULL" << endl;
    }

    void deleteLast()
    {
        if (head == nullptr)
        {
            cout << "List is empty." << endl;
            return;
        }
        if (head->next == nullptr)
        {
            cout << head->data << " deleted." << endl;
            delete head;
            head = nullptr;
            return;
        }

        Node *current = head;
        while (current->next->next != nullptr)
            current = current->next;

        cout << current->next->data << " deleted." << endl;
        delete current->next;
        current->next = nullptr;
    }

    int countNodes()
    {
        int count = 0;
        for (Node *current = head; current != nullptr; current = current->next)
            count++;
        return count;
    }

    void reverseList()
    {
        Node *prev = nullptr;
        Node *current = head;
        while (current != nullptr)
        {
            Node *nextNode = current->next;
            current->next = prev;
            prev = current;
            current = nextNode;
        }
        head = prev;
        cout << "List reversed." << endl;
    }

    void searchValue(int value)
    {
        int position = 0;
        for (Node *current = head; current != nullptr; current = current->next, position++)
        {
            if (current->data == value)
            {
                cout << "Found at position " << position << "." << endl;
                return;
            }
        }
        cout << "Value not found." << endl;
    }
};

void printMenu()
{
    cout << "\n1. Insert at head\n2. Insert at 3rd position\n3. Display list\n"
         << "4. Delete last node\n5. Count nodes\n6. Reverse list\n7. Search\n0. Exit\n"
         << "Enter your choice: ";
}

int main()
{
    LinkedList list;
    int choice, value;

    do
    {
        printMenu();
        cin >> choice;

        switch (choice)
        {
            case 1:
                cout << "Value: ";
                cin >> value;
                list.insertAtHead(value);
                break;
            case 2:
                cout << "Value: ";
                cin >> value;
                list.insertAtThird(value);
                break;
            case 3:
                list.displayList();
                break;
            case 4:
                list.deleteLast();
                list.displayList();
                break;
            case 5:
                cout << "Nodes: " << list.countNodes() << endl;
                break;
            case 6:
                list.reverseList();
                list.displayList();
                break;
            case 7:
                cout << "Value: ";
                cin >> value;
                list.searchValue(value);
                break;
            case 0:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice." << endl;
        }
    } while (choice != 0);

    return 0;
}