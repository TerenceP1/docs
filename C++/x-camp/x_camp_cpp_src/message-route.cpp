#include <iostream>
#include <vector>
#include <queue>
#include <set>
using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;
    vector<int> *cns = new vector<int>[n];
    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        cns[a].push_back(b);
        cns[b].push_back(a);
    }
    queue<pair<pair<int, int>, vector<int>>> q;
    set<int> vst;
    q.push({{0, 0}, {}});
    while (!q.empty())
    {
        auto p = q.front();
        q.pop();
        vector<int> tst = cns[p.first.first];
        vst.insert(p.first.first);
        for (int i = 0; i < tst.size(); i++)
        {
            if (vst.find(tst[i]) == vst.end())
            {
                vst.insert(tst[i]);
                vector<int> tmp = p.second;
                tmp.push_back(tst[i]);
                q.push({{tst[i], p.first.second + 1}, tmp});
                if (tst[i] == n - 1)
                {
                    cout << p.first.second + 1 << endl;
                    for (int j = 0; j < tmp.size(); j++)
                    {
                        cout << tmp[j] << ' ';
                    }
                    return 0;
                }
            }
        }
    }
    cout << "IMPOSSIBLE";
    return 0;
}