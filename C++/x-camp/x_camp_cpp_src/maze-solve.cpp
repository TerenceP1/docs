#include <iostream>
#include <queue>
using namespace std;
int n, m;                // Size of map
bool **maze;             // The maze
int Sx, Sy, Ex, Ey;      // The coordinates of the start and end
int chX[4]{0, 1, 0, -1}; // The x changes for one movement
int chY[4]{1, 0, -1, 0}; // The y changes for one movement

// Is in bounds
bool isValid(int x, int y)
{
    return (x >= 0) && (x < n) && (y >= 0) && (y < m);
}

int main()
{
    // User input

    cin >> n >> m;
    maze = new bool *[n];
    for (int i = 0; i < n; i++)
    {
        maze[i] = new bool[m];
        string tmp; // Store the line of input
        cin >> tmp;
        for (int j = 0; j < m; j++)
        {
            switch (tmp[j])
            {
            case '.':
                maze[i][j] = false;
                break;
            case '#':
                maze[i][j] = true;
                break;
            case 'S':
                maze[i][j] = false;
                Sx = i;
                Sy = j;
                break;
            case 'G':
                maze[i][j] = false;
                Ex = i;
                Ey = j;
                break;
            default:
                break;
            }
        }
    }

    // Initialize search

    queue<pair<pair<int, int>, int>> q; // Queue of {{x coordinate, y coordinate}, distance} for search
    q.push({{Sx, Sy}, 0});              // Starting point of search

    // Search algorithm

    while (!q.empty())
    {
        pair<pair<int, int>, int> tst = q.front(); // What to test
        q.pop();
        // Try all possible next steps
        for (int i = 0; i < 4; i++)
        {
            pair<int, int> tmp = tst.first;
            tmp.first += chX[i];
            tmp.second += chY[i];
            if (isValid(tmp.first, tmp.second))
            {
                if (!maze[tmp.first][tmp.second])
                {
                    maze[tmp.first][tmp.second] = true;
                    q.push({tmp, tst.second + 1});
                    if (tmp.first == Ex && tmp.second == Ey)
                    {
                        cout << tst.second + 1;
                        return 0;
                    }
                }
            }
        }
    }
}