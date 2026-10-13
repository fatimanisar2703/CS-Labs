
#include <iostream>
#include <iomanip>
using namespace std;

struct Request {
    int id;
    int arrivalTime;
    int processingTime;
};

class CircularQueue {
    Request* arr;
    int capacity;
    int count;
    int frontIndex;
    int rearIndex;

public:
    CircularQueue(int size = 4) {
        capacity = size;
        arr = new Request[capacity];
        count = 0;
        frontIndex = 0;
        rearIndex = -1;
    }

    ~CircularQueue() {
        delete[] arr;
    }

    bool isEmpty() {
        return count == 0;
    }

    bool isFull() {
        return count == capacity;
    }

    int size() {
        return count;
    }

    void resize(int newCapacity) {
        if (newCapacity < 4) newCapacity = 4;
        if (newCapacity < count) return;

        Request* temp = new Request[newCapacity];

        for (int i = 0; i < count; i++)
            temp[i] = arr[(frontIndex + i) % capacity];

        delete[] arr;
        arr = temp;
        capacity = newCapacity;
        frontIndex = 0;
        rearIndex = count - 1;

        cout << "Capacity changed to "
             << capacity << ".\n";
    }

    void enqueue(Request r) {
        if (isFull())
            resize(capacity * 2);

        rearIndex = (rearIndex + 1) % capacity;
        arr[rearIndex] = r;
        count++;

        cout << "Request " << r.id << " added.\n";
        display();
    }

    bool dequeue(Request& r) {
        if (isEmpty()) {
            cout << "Queue is empty.\n";
            return false;
        }

        r = arr[frontIndex];
        frontIndex = (frontIndex + 1) % capacity;
        count--;

        cout << "Request " << r.id << " removed.\n";

        if (capacity > 4 && count <= capacity / 4)
            resize(capacity / 2);

        display();
        return true;
    }

    Request front() {
        if (isEmpty()) return {-1, -1, -1};
        return arr[frontIndex];
    }

    void display() {
        cout << "Queue state: ";

        if (isEmpty()) {
            cout << "Empty\n";
            return;
        }

        for (int i = 0; i < count; i++) {
            Request r = arr[(frontIndex + i) % capacity];

            cout << "[ID=" << r.id
                 << ", Arrival=" << r.arrivalTime
                 << ", Processing=" << r.processingTime
                 << "] ";
        }

        cout << endl;
    }
};

int main() {
    CircularQueue q;
    int n;

    cout << "Enter number of print requests: ";
    cin >> n;

    while (n < 0) {
        cout << "Enter a non-negative number: ";
        cin >> n;
    }

    // Read requests from user
    for (int i = 1; i <= n; i++) {
        Request r;
        r.id = i;

        cout << "\nRequest ID: " << r.id << endl;

        do {
            cout << "Arrival time (>= 0): ";
            cin >> r.arrivalTime;
        } while (r.arrivalTime < 0);

        do {
            cout << "Processing time (> 0): ";
            cin >> r.processingTime;
        } while (r.processingTime <= 0);

        q.enqueue(r);
    }

    if (!q.isEmpty())
        cout << "\nFront request ID: " << q.front().id << endl;

    int serverAvailable = 0;
    double totalWaitingTime = 0;
    int processed = 0;

    cout << "\n--- Processing Print Requests ---\n";

    while (!q.isEmpty()) {
        Request r;

        if (q.dequeue(r)) {
            int startTime = r.arrivalTime;

            if (serverAvailable > startTime)
                startTime = serverAvailable;

            int waitingTime = startTime - r.arrivalTime;
            serverAvailable = startTime + r.processingTime;

            totalWaitingTime += waitingTime;
            processed++;

            cout << "ID: " << r.id
                 << " | Start: " << startTime
                 << " | Waiting: " << waitingTime
                 << " | Finish: " << serverAvailable
                 << endl;
        }
    }

    if (processed > 0) {
        cout << fixed << setprecision(2);
        cout << "\nAverage waiting time: "
             << totalWaitingTime / processed << endl;
    } else {
        cout << "No requests were processed.\n";
    }

    cout << "Queue empty: "
         << (q.isEmpty() ? "Yes" : "No") << endl;

    return 0;
}
