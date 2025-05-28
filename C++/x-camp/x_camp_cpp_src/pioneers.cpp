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
    {-1, 0}};
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
        q.push({infecters[i], 0});
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
                    q.push({tmp, tst.second + 1});
                }
            }
        }
    }
    for (int i = 0; i < b; i++)
    {
        cout << people.find({leaders[i].first, leaders[i].second})->second << endl;
    }
}