#include <iostream>
using namespace std;

const int MAX = 100;

class WaitingRoom {
    int patients[MAX];
    int frontIndex;
    int rearIndex;
    int count;
    int nextID;

public:
    WaitingRoom() {
        frontIndex = 0;
        rearIndex = -1;
        count = 0;
        nextID = 1;
    }

    bool isEmpty() {
        return count == 0;
    }

    bool isFull() {
        return count == MAX;
    }

    // Register a new patient
    void RegisterPatient() {
        if (isFull()) {
            cout << "Waiting room is full.\n";
            return;
        }

        int id = nextID++;

        rearIndex = (rearIndex + 1) % MAX;
        patients[rearIndex] = id;
        count++;

        cout << "Patient registered successfully.\n";
        cout << "Patient ID: " << id << endl;
    }

    // Serve the first waiting patient
    void ServePatient() {
        if (isEmpty()) {
            cout << "No patients are waiting.\n";
            return;
        }

        cout << "Patient " << patients[frontIndex]
             << " is being served.\n";

        frontIndex = (frontIndex + 1) % MAX;
        count--;
    }

    // Cancel all waiting appointments
    void CancelAll() {
        if (isEmpty()) {
            cout << "No appointments to cancel.\n";
            return;
        }

        count = 0;
        frontIndex = 0;
        rearIndex = -1;

        cout << "All waiting appointments cancelled.\n";
    }

    // Check whether the doctor can go home
    bool CanDoctorGoHome() {
        return isEmpty();
    }

    // Display all waiting patients in sorted order
    void ShowAllPatient() {
        if (isEmpty()) {
            cout << "No patients are waiting.\n";
            return;
        }

        cout << "Waiting patient IDs: ";

        for (int i = 0; i < count; i++) {
            int index = (frontIndex + i) % MAX;
            cout << patients[index] << " ";
        }

        cout << endl;
    }
};

int main() {
    WaitingRoom room;
    int choice;

    do {
        cout << "\n--- Emergency Ward Menu ---\n";
        cout << "1. Register patient\n";
        cout << "2. Serve patient\n";
        cout << "3. Cancel all appointments\n";
        cout << "4. Check if doctor can go home\n";
        cout << "5. Show all waiting patients\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";

        cin >> choice;

        switch (choice) {
            case 1:
                room.RegisterPatient();
                break;

            case 2:
                room.ServePatient();
                break;

            case 3:
                room.CancelAll();
                break;

            case 4:
                if (room.CanDoctorGoHome())
                    cout << "Yes, no patients are waiting.\n";
                else
                    cout << "No, patients are still waiting.\n";
                break;

            case 5:
                room.ShowAllPatient();
                break;

            case 0:
                cout << "Program ended.\n";
                break;

            default:
                cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 0);

    return 0;
}
