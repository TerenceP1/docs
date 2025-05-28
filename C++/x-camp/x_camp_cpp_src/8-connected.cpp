#include <iostream>
#include <vector>
#include <queue>
using namespace std;
vector<vector<bool>> mp; // true=W, false=.
int n, m;
int cx[8] = {1, 1, 1, 0, 0, -1, -1, -1};
int cy[8] = {0, 1, -1, 1, -1, 1, 0, -1};
bool isValid(int x, int y)
{
    return (x > -1) && (x < n) && (y > -1) && (y < m);
}
void floodfill(int x, int y)
{
    queue<pair<int, int>> q;
    q.push({x, y});
    mp[x][y] = true;
    while (!q.empty())
    {
        pair<int, int> tst = q.front();
        q.pop();
        for (int i = 0; i < 8; i++)
        {
            pair<int, int> ctst = {tst.first + cx[i], tst.second + cy[i]};
            if (isValid(ctst.first, ctst.second))
            {
                if (!mp[ctst.first][ctst.second])
                {
                    q.push(ctst);
                    mp[ctst.first][ctst.second] = true;
                }
            }
        }
    }
}
int main()
{
    cin >> n >> m;
    mp.resize(n);
    for (int i = 0; i < n; i++)
    {
        string tmp;
        cin >> tmp;
        mp[i].resize(m);
        for (int j = 0; j < m; j++)
        {
            mp[i][j] = (tmp[j] == 'W');
        }
    }
    int res = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (!mp[i][j])
            {
                res++;
                floodfill(i, j);
            }
        }
    }
    cout << res;
    return 0;
}