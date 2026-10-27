#include <iostream>
using namespace std;
 
int peg[3][30];
int top[3] = {0, 0, 0};
char name[3] = {'A', 'B', 'C'};
 
void moveBetween(int a, int b)
{
    int from = a;
    int to = b;
 
    if (top[a] == 0 || (top[b] > 0 && peg[b][top[b] - 1] < peg[a][top[a] - 1]))
    {
        from = b;
        to = a;
    }
 
    int disk = peg[from][top[from] - 1];
    top[from]--;
    peg[to][top[to]] = disk;
    top[to]++;
    cout << "Move disk " << disk << " from " << name[from] << " to " << name[to] << endl;
}
 
int main()
{
    int n;
    cout << "Enter number of disks: ";
    cin >> n;
 
    int first = 2;
    int second = 1;
 
    if (n % 2 == 0)
    {
        first = 1;
        second = 2;
    }
 
    for (int i = n; i >= 1; i--)
    {
        peg[0][top[0]] = i;
        top[0]++;
    }
 
    int totalMoves = (1 << n) - 1;
 
    for (int i = 1; i <= totalMoves; i++)
    {
        if (i % 3 == 1)
            moveBetween(0, first);
        else if (i % 3 == 2)
            moveBetween(0, second);
        else
            moveBetween(first, second);
    }
 
    cout << "Total moves: " << totalMoves << endl;
    return 0;
}
