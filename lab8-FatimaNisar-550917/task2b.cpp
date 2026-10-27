#include <iostream>
#include <iomanip>
using namespace std;
 
int N;
int board[20][20];
int dx[8] = {2, 1, -1, -2, -2, -1, 1, 2};
int dy[8] = {1, 2, 2, 1, -1, -2, -2, -1};
 
bool isSafe(int x, int y)
{
    return x >= 0 && y >= 0 && x < N && y < N && board[x][y] == -1;
}
 
int countMoves(int x, int y)
{
    int count = 0;
    for (int i = 0; i < 8; i++)
        if (isSafe(x + dx[i], y + dy[i]))
            count++;
    return count;
}
 
bool solve(int x, int y)
{
    board[x][y] = 0;
 
    for (int move = 1; move < N * N; move++)
    {
        int best = -1;
        int minCount = 9;
 
        for (int i = 0; i < 8; i++)
        {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (isSafe(nx, ny))
            {
                int c = countMoves(nx, ny);
                if (c < minCount)
                {
                    minCount = c;
                    best = i;
                }
            }
        }
 
        if (best == -1)
            return false;
 
        x += dx[best];
        y += dy[best];
        board[x][y] = move;
    }
 
    return true;
}
 
int main()
{
    int startX, startY;
 
    cout << "Enter board size N: ";
    cin >> N;
    cout << "Enter starting row: ";
    cin >> startX;
    cout << "Enter starting column: ";
    cin >> startY;
 
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            board[i][j] = -1;
 
    if (solve(startX, startY))
    {
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
                cout << setw(3) << board[i][j];
            cout << endl;
        }
    }
    else
        cout << "No tour found" << endl;
 
    return 0;
}
