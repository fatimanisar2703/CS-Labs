#include <iostream>
#include <string>
using namespace std;

class Tab
{
public:
    int id;
    string title;
    string url;

    Tab* next;
    Tab* prev;

    Tab(int i, string t, string u)
    {
        id = i;
        title = t;
        url = u;

        next = this;
        prev = this;
    }
};

class Browser
{
private:
    Tab* current;

public:

    Browser()
    {
        current = nullptr;
    }

    // Open a new tab after the current tab
    void openNewTab()
    {
        int id;
        string title;
        string url;

        cout << "\nEnter Tab ID: ";
        cin >> id;

        cin.ignore();

        cout << "Enter Website Title: ";
        getline(cin, title);

        cout << "Enter URL: ";
        getline(cin, url);

        Tab* newTab = new Tab(id, title, url);

        // If list is empty
        if (current == nullptr)
        {
            current = newTab;

            cout << "\nTab opened successfully.\n";
            return;
        }

        // Insert after current
        newTab->next = current->next;
        newTab->prev = current;

        current->next->prev = newTab;
        current->next = newTab;

        // New tab becomes current
        current = newTab;

        cout << "\nTab opened successfully.\n";
    }

    // Close the current tab
    void closeCurrentTab()
    {
        if (current == nullptr)
        {
            cout << "\nNo tabs are open.\n";
            return;
        }

        // Only one tab
        if (current->next == current)
        {
            delete current;
            current = nullptr;

            cout << "\nCurrent tab closed.\n";
            return;
        }

        Tab* temp = current;

        // Connect previous and next nodes
        current->prev->next = current->next;
        current->next->prev = current->prev;

        // Move current to next tab
        current = current->next;

        delete temp;

        cout << "\nCurrent tab closed.\n";
    }

    // Move to next tab
    void moveNext()
    {
        if (current == nullptr)
        {
            cout << "\nNo tabs are open.\n";
            return;
        }

        current = current->next;

        cout << "\nMoved to next tab.\n";
        displayCurrentTab();
    }

    // Move to previous tab
    void movePrevious()
    {
        if (current == nullptr)
        {
            cout << "\nNo tabs are open.\n";
            return;
        }

        current = current->prev;

        cout << "\nMoved to previous tab.\n";
        displayCurrentTab();
    }

    // Display current tab
    void displayCurrentTab()
    {
        if (current == nullptr)
        {
            cout << "\nNo tabs are open.\n";
            return;
        }

        cout << "\n---------- CURRENT TAB ----------\n";
        cout << "Tab ID: " << current->id << endl;
        cout << "Title: " << current->title << endl;
        cout << "URL: " << current->url << endl;
        cout << "---------------------------------\n";
    }

    // Display all tabs in forward direction
    void displayAllTabsForward()
    {
        if (current == nullptr)
        {
            cout << "\nNo tabs are open.\n";
            return;
        }

        cout << "\n========== TABS FORWARD ==========\n";

        Tab* start = current;
        Tab* temp = current;

        do
        {
            cout << "Tab ID: " << temp->id << endl;
            cout << "Title: " << temp->title << endl;
            cout << "URL: " << temp->url << endl;
            cout << "---------------------------------\n";

            temp = temp->next;

        } while (temp != start);
    }

    // Display all tabs in backward direction
    void displayAllTabsBackward()
    {
        if (current == nullptr)
        {
            cout << "\nNo tabs are open.\n";
            return;
        }

        cout << "\n========= TABS BACKWARD ==========\n";

        Tab* start = current;
        Tab* temp = current;

        do
        {
            cout << "Tab ID: " << temp->id << endl;
            cout << "Title: " << temp->title << endl;
            cout << "URL: " << temp->url << endl;
            cout << "---------------------------------\n";

            temp = temp->prev;

        } while (temp != start);
    }

    // Search for a tab by ID
    void searchTab()
    {
        if (current == nullptr)
        {
            cout << "\nNo tabs are open.\n";
            return;
        }

        int searchID;

        cout << "\nEnter Tab ID to search: ";
        cin >> searchID;

        Tab* start = current;
        Tab* temp = current;

        do
        {
            if (temp->id == searchID)
            {
                cout << "\nTab found!\n";
                cout << "Tab ID: " << temp->id << endl;
                cout << "Title: " << temp->title << endl;
                cout << "URL: " << temp->url << endl;

                return;
            }

            temp = temp->next;

        } while (temp != start);

        cout << "\nTab not found.\n";
    }

    // Destructor
    ~Browser()
    {
        if (current == nullptr)
            return;

        Tab* start = current;
        Tab* temp = current->next;

        while (temp != start)
        {
            Tab* nextTab = temp->next;

            delete temp;

            temp = nextTab;
        }

        delete current;
        current = nullptr;
    }
};


int main()
{
    Browser browser;

    int choice;

    do
    {
        cout << "\n\n====================================\n";
        cout << "       BROWSER TAB MANAGER\n";
        cout << "====================================\n";

        cout << "1. Open New Tab\n";
        cout << "2. Close Current Tab\n";
        cout << "3. Move Next\n";
        cout << "4. Move Previous\n";
        cout << "5. Display Current Tab\n";
        cout << "6. Display All Tabs Forward\n";
        cout << "7. Display All Tabs Backward\n";
        cout << "8. Search Tab\n";
        cout << "9. Exit\n";

        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            browser.openNewTab();
            break;

        case 2:
            browser.closeCurrentTab();
            break;

        case 3:
            browser.moveNext();
            break;

        case 4:
            browser.movePrevious();
            break;

        case 5:
            browser.displayCurrentTab();
            break;

        case 6:
            browser.displayAllTabsForward();
            break;

        case 7:
            browser.displayAllTabsBackward();
            break;

        case 8:
            browser.searchTab();
            break;

        case 9:
            cout << "\nExiting Browser Tab Manager...\n";
            break;

        default:
            cout << "\nInvalid choice. Please try again.\n";
        }

    } while (choice != 9);

    return 0;
}