#include <iostream>
#include <string>
using namespace std;

class Photo
{
public:
    int id;
    string name;
    string date;
    string location;

    Photo* next;
    Photo* prev;

    Photo(int i, string n, string d, string l)
    {
        id = i;
        name = n;
        date = d;
        location = l;

        next = this;
        prev = this;
    }
};

class PhotoAlbum
{
private:
    Photo* current;

public:

    PhotoAlbum()
    {
        current = nullptr;
    }

    // Add photo at the end
    void addPhoto()
    {
        int id;
        string name;
        string date;
        string location;

        cout << "\nEnter Photo ID: ";
        cin >> id;

        cin.ignore();

        cout << "Enter Photo Name: ";
        getline(cin, name);

        cout << "Enter Date: ";
        getline(cin, date);

        cout << "Enter Location: ";
        getline(cin, location);

        Photo* newPhoto = new Photo(id, name, date, location);

        // Empty album
        if (current == nullptr)
        {
            current = newPhoto;

            cout << "\nPhoto added successfully.\n";
            return;
        }

        // Insert at the end
        Photo* last = current->prev;

        newPhoto->next = current;
        newPhoto->prev = last;

        last->next = newPhoto;
        current->prev = newPhoto;

        cout << "\nPhoto added successfully.\n";
    }

    // Insert photo after current photo
    void insertAfterCurrent()
    {
        if (current == nullptr)
        {
            cout << "\nAlbum is empty. Adding first photo.\n";
            addPhoto();
            return;
        }

        int id;
        string name;
        string date;
        string location;

        cout << "\nEnter Photo ID: ";
        cin >> id;

        cin.ignore();

        cout << "Enter Photo Name: ";
        getline(cin, name);

        cout << "Enter Date: ";
        getline(cin, date);

        cout << "Enter Location: ";
        getline(cin, location);

        Photo* newPhoto = new Photo(id, name, date, location);

        newPhoto->next = current->next;
        newPhoto->prev = current;

        current->next->prev = newPhoto;
        current->next = newPhoto;

        cout << "\nPhoto inserted successfully.\n";
    }

    // Remove photo using ID
    void removePhoto()
    {
        if (current == nullptr)
        {
            cout << "\nAlbum is empty.\n";
            return;
        }

        int searchID;

        cout << "\nEnter Photo ID to remove: ";
        cin >> searchID;

        Photo* start = current;
        Photo* temp = current;

        do
        {
            if (temp->id == searchID)
            {
                // Only one photo
                if (temp->next == temp)
                {
                    delete temp;
                    current = nullptr;

                    cout << "\nPhoto removed successfully.\n";
                    return;
                }

                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;

                // If current photo was removed
                if (temp == current)
                {
                    current = temp->next;
                }

                delete temp;

                cout << "\nPhoto removed successfully.\n";
                return;
            }

            temp = temp->next;

        } while (temp != start);

        cout << "\nPhoto not found.\n";
    }

    // Remove current photo
    void removeCurrentPhoto()
    {
        if (current == nullptr)
        {
            cout << "\nAlbum is empty.\n";
            return;
        }

        // Only one photo
        if (current->next == current)
        {
            delete current;
            current = nullptr;

            cout << "\nCurrent photo removed.\n";
            return;
        }

        Photo* temp = current;

        current->prev->next = current->next;
        current->next->prev = current->prev;

        current = current->next;

        delete temp;

        cout << "\nCurrent photo removed.\n";
    }

    // Move to next photo
    void moveNext()
    {
        if (current == nullptr)
        {
            cout << "\nAlbum is empty.\n";
            return;
        }

        current = current->next;

        cout << "\nMoved to next photo.\n";
        displayCurrentPhoto();
    }

    // Move to previous photo
    void movePrevious()
    {
        if (current == nullptr)
        {
            cout << "\nAlbum is empty.\n";
            return;
        }

        current = current->prev;

        cout << "\nMoved to previous photo.\n";
        displayCurrentPhoto();
    }

    // Display current photo
    void displayCurrentPhoto()
    {
        if (current == nullptr)
        {
            cout << "\nAlbum is empty.\n";
            return;
        }

        cout << "\n---------- CURRENT PHOTO ----------\n";
        cout << "Photo ID: " << current->id << endl;
        cout << "Name: " << current->name << endl;
        cout << "Date: " << current->date << endl;
        cout << "Location: " << current->location << endl;
        cout << "-----------------------------------\n";
    }

    // Display photos forward
    void displayForward()
    {
        if (current == nullptr)
        {
            cout << "\nAlbum is empty.\n";
            return;
        }

        cout << "\n========== ALBUM FORWARD ==========\n";

        Photo* start = current;
        Photo* temp = current;

        do
        {
            cout << "Photo ID: " << temp->id << endl;
            cout << "Name: " << temp->name << endl;
            cout << "Date: " << temp->date << endl;
            cout << "Location: " << temp->location << endl;
            cout << "-----------------------------------\n";

            temp = temp->next;

        } while (temp != start);
    }

    // Display photos backward
    void displayBackward()
    {
        if (current == nullptr)
        {
            cout << "\nAlbum is empty.\n";
            return;
        }

        cout << "\n========= ALBUM BACKWARD ==========\n";

        Photo* start = current;
        Photo* temp = current;

        do
        {
            cout << "Photo ID: " << temp->id << endl;
            cout << "Name: " << temp->name << endl;
            cout << "Date: " << temp->date << endl;
            cout << "Location: " << temp->location << endl;
            cout << "-----------------------------------\n";

            temp = temp->prev;

        } while (temp != start);
    }

    // Search photo by ID
    void searchPhoto()
    {
        if (current == nullptr)
        {
            cout << "\nAlbum is empty.\n";
            return;
        }

        int searchID;

        cout << "\nEnter Photo ID to search: ";
        cin >> searchID;

        Photo* start = current;
        Photo* temp = current;

        do
        {
            if (temp->id == searchID)
            {
                cout << "\nPhoto found!\n";
                cout << "Photo ID: " << temp->id << endl;
                cout << "Name: " << temp->name << endl;
                cout << "Date: " << temp->date << endl;
                cout << "Location: " << temp->location << endl;

                return;
            }

            temp = temp->next;

        } while (temp != start);

        cout << "\nPhoto not found.\n";
    }

    // Count photos
    void countPhotos()
    {
        if (current == nullptr)
        {
            cout << "\nTotal photos: 0\n";
            return;
        }

        int count = 0;

        Photo* start = current;
        Photo* temp = current;

        do
        {
            count++;
            temp = temp->next;

        } while (temp != start);

        cout << "\nTotal photos: " << count << endl;
    }

    // Destructor
    ~PhotoAlbum()
    {
        if (current == nullptr)
            return;

        Photo* start = current;
        Photo* temp = current->next;

        while (temp != start)
        {
            Photo* nextPhoto = temp->next;

            delete temp;

            temp = nextPhoto;
        }

        delete current;
        current = nullptr;
    }
};


int main()
{
    PhotoAlbum album;

    int numberOfPhotos;

    cout << "Enter number of initial photos: ";
    cin >> numberOfPhotos;

    for (int i = 0; i < numberOfPhotos; i++)
    {
        cout << "\nEnter details for Photo " << i + 1 << ":\n";
        album.addPhoto();
    }

    int choice;

    do
    {
        cout << "\n\n====================================\n";
        cout << "        CIRCULAR PHOTO ALBUM\n";
        cout << "====================================\n";

        cout << "1. Add Photo\n";
        cout << "2. Insert Photo After Current\n";
        cout << "3. Remove Photo by ID\n";
        cout << "4. Remove Current Photo\n";
        cout << "5. Move Next\n";
        cout << "6. Move Previous\n";
        cout << "7. Display Album Forward\n";
        cout << "8. Display Album Backward\n";
        cout << "9. Search Photo\n";
        cout << "10. Count Photos\n";
        cout << "11. Exit\n";

        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            album.addPhoto();
            break;

        case 2:
            album.insertAfterCurrent();
            break;

        case 3:
            album.removePhoto();
            break;

        case 4:
            album.removeCurrentPhoto();
            break;

        case 5:
            album.moveNext();
            break;

        case 6:
            album.movePrevious();
            break;

        case 7:
            album.displayForward();
            break;

        case 8:
            album.displayBackward();
            break;

        case 9:
            album.searchPhoto();
            break;

        case 10:
            album.countPhotos();
            break;

        case 11:
            cout << "\nExiting Photo Album...\n";
            break;

        default:
            cout << "\nInvalid choice. Please try again.\n";
        }

    } while (choice != 11);

    return 0;
}