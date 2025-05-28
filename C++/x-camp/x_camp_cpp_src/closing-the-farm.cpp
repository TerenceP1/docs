// closing-the-farm.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <set>
#include <queue>
using namespace std;

vector<vector<int>> paths; // Stores all connections using adjacency list
vector<bool> state;        // Stores the state of each farm. True if the barn is open
int n;

// Return whether the farm is fully connected

bool isConnected()
{
    int start; // Store the first barn not shut down

    // Search for starting point

    for (int i = 0; i < n; i++)
    {
        if (state[i])
        {
            start = i;
            break;
        }
    }

    // BFS floodfill from start

    queue<int> q; // Search queue
    set<int> vst; // Stores every spot found
    q.push(start);
    vst.insert(start);
    while (!q.empty())
    {
        int tst = q.front();
        q.pop();
        for (int i : paths[tst])
        {
            if (state[i])
            {
                if (vst.find(i) == vst.end())
                {
                    vst.insert(i);
                    q.push(i);
                }
            }
        }
    }

    // Check if every barn is reachable

    for (int i = 0; i < n; i++)
    {
        if (state[i])
        {
            if (vst.find(i) == vst.end())
            {
                return false;
            }
        }
    }
    return true;
}

int main()
{
    int m;
    cin >> n >> m;
    paths.resize(n);
    state.resize(n);
    for (int i = 0; i < n; i++)
    {
        state[i] = true;
    }
    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        paths[a].push_back(b);
        paths[b].push_back(a);
    }
    for (int i = 0; i < n; i++)
    {
        if (isConnected())
        {
            cout << "YES\n";
        }
        else
        {
            cout << "NO\n";
        }
        int x;
        cin >> x;
        state[x - 1] = false;
    }
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started:
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
