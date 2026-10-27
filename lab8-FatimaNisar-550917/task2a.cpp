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
 
bool solve(int x, int y, int move)
{
    board[x][y] = move;
 
    if (move == N * N - 1)
        return true;
 
    for (int i = 0; i < 8; i++)
    {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (isSafe(nx, ny) && solve(nx, ny, move + 1))
            return true;
    }
 
    board[x][y] = -1;
    return false;
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
 
    if (solve(startX, startY, 0))
    {
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
                cout << setw(3) << board[i][j];
            cout << endl;
        }
    }
    else
        cout << "No tour exists" << endl;
 
    return 0;
}
