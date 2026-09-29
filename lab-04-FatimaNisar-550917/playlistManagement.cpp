#include <iostream>
#include <string>
using namespace std;

struct Node
{
    int id;
    string name;
    string duration;
    Node* next;
    Node* prev;
};

Node* head = NULL;
Node* tail = NULL;
Node* current = NULL;

void addSong(int id, string name, string duration)
{
    Node* newNode = new Node;
    newNode->id = id;
    newNode->name = name;
    newNode->duration = duration;
    newNode->next = NULL;
    newNode->prev = NULL;

    if (head == NULL)
    {
        head = tail = newNode;
        current = head;
    }
    else
    {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
}

void deleteSong(int id)
{
    Node* temp = head;

    while (temp != NULL && temp->id != id)
        temp = temp->next;

    if (temp == NULL)
    {
        cout << "Song not found." << endl;
        return;
    }

    if (temp->prev != NULL)
        temp->prev->next = temp->next;
    else
        head = temp->next;

    if (temp->next != NULL)
        temp->next->prev = temp->prev;
    else
        tail = temp->prev;

    if (current == temp)
        current = head;

    delete temp;
    cout << "Song deleted." << endl;
}

void displayForward()
{
    Node* temp = head;

    while (temp != NULL)
    {
        cout << temp->id << "  "
             << temp->name << "  "
             << temp->duration << endl;
        temp = temp->next;
    }
}

void displayBackward()
{
    Node* temp = tail;

    while (temp != NULL)
    {
        cout << temp->id << "  "
             << temp->name << "  "
             << temp->duration << endl;
        temp = temp->prev;
    }
}

void searchSong(int id)
{
    Node* temp = head;

    while (temp != NULL)
    {
        if (temp->id == id)
        {
            cout << "ID: " << temp->id << endl;
            cout << "Name: " << temp->name << endl;
            cout << "Duration: " << temp->duration << endl;
            return;
        }

        temp = temp->next;
    }

    cout << "Song not found." << endl;
}

void nextSong()
{
    if (current == NULL)
    {
        cout << "Playlist is empty." << endl;
        return;
    }

    if (current->next != NULL)
        current = current->next;

    cout << "Playing: " << current->name << endl;
}

void previousSong()
{
    if (current == NULL)
    {
        cout << "Playlist is empty." << endl;
        return;
    }

    if (current->prev != NULL)
        current = current->prev;

    cout << "Playing: " << current->name << endl;
}

void reversePlaylist()
{
    Node* temp = head;

    while (temp != NULL)
    {
        Node* nextNode = temp->next;
        temp->next = temp->prev;
        temp->prev = nextNode;
        temp = nextNode;
    }

    Node* tempHead = head;
    head = tail;
    tail = tempHead;

    cout << "Playlist reversed." << endl;
}

int main()
{
    int choice;
    int id;
    string name, duration;

    do
    {
        cout << "\n1. Add Song" << endl;
        cout << "2. Delete Song" << endl;
        cout << "3. Display Forward" << endl;
        cout << "4. Display Backward" << endl;
        cout << "5. Search Song" << endl;
        cout << "6. Play Next" << endl;
        cout << "7. Play Previous" << endl;
        cout << "8. Reverse Playlist" << endl;
        cout << "9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1)
        {
            cout << "Enter song ID: ";
            cin >> id;

            cin.ignore();
            cout << "Enter song name: ";
            getline(cin, name);

            cout << "Enter duration: ";
            getline(cin, duration);

            addSong(id, name, duration);
        }
        else if (choice == 2)
        {
            cout << "Enter song ID: ";
            cin >> id;
            deleteSong(id);
        }
        else if (choice == 3)
        {
            displayForward();
        }
        else if (choice == 4)
        {
            displayBackward();
        }
        else if (choice == 5)
        {
            cout << "Enter song ID: ";
            cin >> id;
            searchSong(id);
        }
        else if (choice == 6)
        {
            nextSong();
        }
        else if (choice == 7)
        {
            previousSong();
        }
        else if (choice == 8)
        {
            reversePlaylist();
        }

    } while (choice != 9);

    return 0;
}