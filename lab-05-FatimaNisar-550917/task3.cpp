#include <iostream>
#include <string>
using namespace std;

class Coach
{
public:
    int number, capacity, passengers;
    string type;
    Coach *next, *prev;

    Coach(int n, string t, int c, int p)
    {
        number = n;
        type = t;
        capacity = c;
        passengers = p;
        next = prev = this;
    }
};

class Train
{
    Coach *current;

public:

    Train()
    {
        current = nullptr;
    }

    void addCoach()
    {
        int n, c, p;
        string t;

        cout << "Coach number: ";
        cin >> n;
        cin.ignore();

        cout << "Coach type: ";
        getline(cin, t);

        cout << "Capacity: ";
        cin >> c;

        cout << "Passengers: ";
        cin >> p;

        Coach *x = new Coach(n, t, c, p);

        if (current == nullptr)
        {
            current = x;
        }
        else
        {
            Coach *last = current->prev;

            x->next = current;
            x->prev = last;
            last->next = x;
            current->prev = x;
        }

        cout << "Coach added.\n";
    }

    void insertCoach()
    {
        if (current == nullptr)
        {
            addCoach();
            return;
        }

        int after;
        cout << "Insert after coach number: ";
        cin >> after;

        Coach *p = current;

        do
        {
            if (p->number == after)
            {
                int n, c, passengers;
                string t;

                cout << "Coach number: ";
                cin >> n;
                cin.ignore();

                cout << "Coach type: ";
                getline(cin, t);

                cout << "Capacity: ";
                cin >> c;

                cout << "Passengers: ";
                cin >> passengers;

                Coach *x = new Coach(n, t, c, passengers);

                x->next = p->next;
                x->prev = p;
                p->next->prev = x;
                p->next = x;

                cout << "Coach inserted.\n";
                return;
            }

            p = p->next;

        } while (p != current);

        cout << "Coach not found.\n";
    }

    void removeCoach()
    {
        if (current == nullptr)
        {
            cout << "Train is empty.\n";
            return;
        }

        int n;
        cout << "Coach number to remove: ";
        cin >> n;

        Coach *p = current;

        do
        {
            if (p->number == n)
            {
                if (p->next == p)
                {
                    delete p;
                    current = nullptr;
                }
                else
                {
                    p->prev->next = p->next;
                    p->next->prev = p->prev;

                    if (p == current)
                        current = p->next;

                    delete p;
                }

                cout << "Coach removed.\n";
                return;
            }

            p = p->next;

        } while (p != current);

        cout << "Coach not found.\n";
    }

    void moveForward()
    {
        if (current == nullptr)
            cout << "Train is empty.\n";
        else
        {
            current = current->next;
            displayCurrent();
        }
    }

    void moveBackward()
    {
        if (current == nullptr)
            cout << "Train is empty.\n";
        else
        {
            current = current->prev;
            displayCurrent();
        }
    }

    void displayCurrent()
    {
        if (current == nullptr)
        {
            cout << "Train is empty.\n";
            return;
        }

        cout << "\nCoach: " << current->number
             << "\nType: " << current->type
             << "\nCapacity: " << current->capacity
             << "\nPassengers: " << current->passengers
             << "\nAvailable: "
             << current->capacity - current->passengers << "\n";
    }

    void display(bool forward)
    {
        if (current == nullptr)
        {
            cout << "Train is empty.\n";
            return;
        }

        Coach *p = current;

        do
        {
            cout << "\nCoach: " << p->number
                 << "\nType: " << p->type
                 << "\nCapacity: " << p->capacity
                 << "\nPassengers: " << p->passengers
                 << "\nAvailable: "
                 << p->capacity - p->passengers
                 << "\n-------------------";

            p = forward ? p->next : p->prev;

        } while (p != current);

        cout << endl;
    }

    void searchCoach()
    {
        if (current == nullptr)
        {
            cout << "Train is empty.\n";
            return;
        }

        int n;
        cout << "Coach number to search: ";
        cin >> n;

        Coach *p = current;

        do
        {
            if (p->number == n)
            {
                cout << "\nCoach found:\n";
                cout << "Number: " << p->number
                     << "\nType: " << p->type
                     << "\nCapacity: " << p->capacity
                     << "\nPassengers: " << p->passengers
                     << "\nAvailable: "
                     << p->capacity - p->passengers << "\n";
                return;
            }

            p = p->next;

        } while (p != current);

        cout << "Coach not found.\n";
    }

    void maximumCapacity()
    {
        if (current == nullptr)
        {
            cout << "Train is empty.\n";
            return;
        }

        Coach *max = current;
        Coach *p = current->next;

        while (p != current)
        {
            if (p->capacity - p->passengers >
                max->capacity - max->passengers)
                max = p;

            p = p->next;
        }

        cout << "\nCoach with maximum available seats:\n";
        cout << "Number: " << max->number
             << "\nType: " << max->type
             << "\nAvailable seats: "
             << max->capacity - max->passengers << "\n";
    }

    void reverseTrain()
    {
        if (current == nullptr)
        {
            cout << "Train is empty.\n";
            return;
        }

        Coach *p = current;

        do
        {
            Coach *temp = p->next;
            p->next = p->prev;
            p->prev = temp;
            p = temp;

        } while (p != current);

        cout << "Train direction reversed.\n";
    }

    ~Train()
    {
        if (current == nullptr)
            return;

        Coach *p = current->next;

        while (p != current)
        {
            Coach *temp = p->next;
            delete p;
            p = temp;
        }

        delete current;
    }
};

int main()
{
    Train train;
    int n, choice;

    cout << "Number of initial coaches: ";
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        cout << "\nCoach " << i + 1 << ":\n";
        train.addCoach();
    }

    do
    {
        cout << "\n\n========== TRAIN MENU ==========\n";
        cout << "1. Add Coach\n";
        cout << "2. Insert Coach\n";
        cout << "3. Remove Coach\n";
        cout << "4. Move Forward\n";
        cout << "5. Move Backward\n";
        cout << "6. Display Clockwise\n";
        cout << "7. Display Anti-clockwise\n";
        cout << "8. Search Coach\n";
        cout << "9. Maximum Available Capacity\n";
        cout << "10. Display Current Coach\n";
        cout << "11. Reverse Train\n";
        cout << "12. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            train.addCoach();
            break;

        case 2:
            train.insertCoach();
            break;

        case 3:
            train.removeCoach();
            break;

        case 4:
            train.moveForward();
            break;

        case 5:
            train.moveBackward();
            break;

        case 6:
            train.display(true);
            break;

        case 7:
            train.display(false);
            break;

        case 8:
            train.searchCoach();
            break;

        case 9:
            train.maximumCapacity();
            break;

        case 10:
            train.displayCurrent();
            break;

        case 11:
            train.reverseTrain();
            break;

        case 12:
            cout << "Exiting...\n";
            break;

        default:
            cout << "Invalid choice.\n";
        }

    } while (choice != 12);

    return 0;
}