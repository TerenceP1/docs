#include <iostream>
#include <queue>
#include <vector>
#include <map>
using namespace std;
int n, m, x1, y1, x2, y2;
int main()
{
    cin >> n >> m;
    vector<bool> tmpv(m);
    vector<vector<bool>> map1(n, tmpv);
    map<pair<int, int>, int> itms;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            bool tmp;
            cin >> tmp;
            map1[i][j] = tmp;
        }
    }
    cin >> x1 >> y1 >> x2 >> y2;
    queue<pair<pair<int, int>, int>> q;
    q.push({{x1, y1}, 0});
    while (!q.empty())
    {
        pair<pair<int, int>, int> tst = q.front();
        map1[tst.first.first][tst.first.second] = true;
        q.pop();
        itms.insert(tst);
        for (int i = tst.first.first + 1; i < n && map1[i][tst.first.second]; i++)
        {
            q.push({{i, tst.first.second}, tst.second + 1});
            map1[i][tst.first.second] = true;
        }
        for (int i = tst.first.first - 1; i > -1 && map1[i][tst.first.second]; i--)
        {
            q.push({{i, tst.first.second}, tst.second + 1});
            map1[i][tst.first.second] = true;
        }
        for (int i = tst.first.second + 1; i < n && map1[i][tst.first.first]; i++)
        {
            q.push({{i, tst.first.first}, tst.second + 1});
            map1[i][tst.first.first] = true;
        }
        for (int i = tst.first.second - 1; i > -1 && map1[i][tst.first.first]; i--)
        {
            q.push({{i, tst.first.first}, tst.second + 1});
            map1[i][tst.first.first] = true;
        }
    }
    if (itms.find({x2, y2}) == itms.end())
    {
        cout << -1;
        return 0;
    }
    cout << itms.find({x2, y2})->second;
}