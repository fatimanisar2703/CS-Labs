#include <iostream>
#include <string>
using namespace std;

class StringPool
{
private:
    string** stringPool;
    int currentSize;
    int maxSize;
    int leakCount;   // keeps track of how many strings got leaked

public:
    StringPool()
    {
        maxSize = 5;
        currentSize = 0;
        leakCount = 0;
        stringPool = new string*[maxSize];
    }

    // adds a new string to the pool
    void addString(string str)
    {
        if (currentSize == maxSize)
        {
            cout << "Pool is full, cannot add " << str << endl;
            return;
        }

        stringPool[currentSize] = new string(str);
        currentSize++;
        cout << str << " added to pool." << endl;
    }

    // removes a string but does NOT free its memory (causes a leak)
    void removeString(int index)
    {
        if (index < 0 || index >= currentSize)
        {
            cout << "Invalid index." << endl;
            return;
        }

        cout << "Removing " << *stringPool[index] << " without freeing memory." << endl;

        for (int i = index; i < currentSize - 1; i++)
        {
            stringPool[i] = stringPool[i + 1];
        }
        currentSize--;
        leakCount++;   // the pointer we just dropped is now a leak
    }

    // removes a string and properly frees its memory
    void removeAndFree(int index)
    {
        if (index < 0 || index >= currentSize)
        {
            cout << "Invalid index." << endl;
            return;
        }

        cout << "Removing " << *stringPool[index] << " and freeing its memory." << endl;
        delete stringPool[index];
        stringPool[index] = nullptr;

        for (int i = index; i < currentSize - 1; i++)
        {
            stringPool[i] = stringPool[i + 1];
        }
        currentSize--;
    }

    void displayPool()
    {
        cout << "Pool contents: ";
        for (int i = 0; i < currentSize; i++)
        {
            cout << *stringPool[i] << " ";
        }
        cout << endl;
        cout << "Leaked strings so far: " << leakCount << endl;
    }

    ~StringPool()
    {
        for (int i = 0; i < currentSize; i++)
        {
            delete stringPool[i];
        }
        delete[] stringPool;
        stringPool = nullptr;
    }
};

int main()
{
    StringPool pool;

    pool.addString("Mango");
    pool.addString("Papaya");
    pool.addString("Kiwi");
    pool.addString("Guava");
    pool.addString("Lychee");

    pool.displayPool();

    cout << "\nRemoving strings the wrong way (leak created):" << endl;
    pool.removeString(0);   // Mango leaked
    pool.removeString(0);   // Papaya leaked

    pool.displayPool();

    cout << "\nLeak detected! Now removing the rest properly:" << endl;
    pool.removeAndFree(0);   // Kiwi freed correctly

    pool.displayPool();

    return 0;
}