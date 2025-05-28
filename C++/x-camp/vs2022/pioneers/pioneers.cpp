// pioneers.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <queue>
#include <map>
#include <vector>
using namespace std;
map<pair<int, int>, int> people;
int n, m, a, b;
int mvmap[4][2]{
    {0, 1},
    {0, -1},
    {1, 0},
    {-1, 0} };
bool isValid(int x, int y)
{
    return (x > -1) && (x < n) && (y > -1) && (y < m);
}
int main()
{
    cin >> n >> m >> a >> b;
    vector<pair<int, int>> infecters(a);
    vector<pair<int, int>> leaders(b);
    queue<pair<pair<int, int>, int>> q;
    for (int i = 0; i < a; i++)
    {
        cin >> infecters[i].first >> infecters[i].second;
        infecters[i].first--;
        infecters[i].second--;
        q.push({ infecters[i], 0 });
    }
    for (int i = 0; i < b; i++)
    {
        cin >> leaders[i].first >> leaders[i].second;
        leaders[i].first--;
        leaders[i].second--;
    }
    while (!q.empty())
    {
        pair<pair<int, int>, int> tst = q.front();
        q.pop();
        people.insert(tst);
        for (int i = 0; i < 4; i++)
        {
            pair<int, int> tmp = tst.first;
            tmp.first += mvmap[i][0];
            tmp.second += mvmap[i][1];
            if (isValid(tmp.first, tmp.second))
            {
                if (people.find(tmp) == people.end())
                {
                    q.push({ tmp, tst.second + 1 });
                }
            }
        }
    }
    for (int i = 0; i < b; i++)
    {
        cout << people.find({ leaders[i].first, leaders[i].second })->second << endl;
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
