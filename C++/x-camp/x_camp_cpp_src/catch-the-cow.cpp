#include <iostream>
#include <queue>
#include <set>
#include <map>
using namespace std;

// Store an iteration

struct itr
{
    int val;  // Iteration value
    int dst;  // Distance
    bool isF; // Is forward
};

int main()
{
    int n, k;
    cin >> n >> k;
    if (n == k)
    {
        cout << 0;
        return 0;
    }
    queue<itr> q; // Queue
    q.push({n, 0, true});
    q.push({k, 0, false});
    map<int, pair<int, bool>> vst; // Map of all past runs {val, {dst, isF}}
    vst.insert({n, {0, true}});
    vst.insert({k, {0, false}});
    while (!q.empty())
    {
        itr tst = q.front();
        q.pop();
        int nxts[3]{tst.val + 1, tst.val - 1, (tst.isF ? tst.val << 2 : tst.val >> 2)}; // All possible next steps
        int ln = 3 - (!tst.isF) * (tst.val % 2);
        for (int i = 0; i < ln; i++)
        {
            if (vst.find(nxts[i]) != vst.end())
            {
                pair<int, pair<int, bool>> pstres = *vst.find(nxts[i]);
                if (pstres.second.second != tst.isF)
                {
                    cout << pstres.second.first + tst.dst + 1;
                    return 0;
                }
            }
            else if (nxts[i] > -1)
            {
                vst.insert({nxts[i], {tst.dst + 1, tst.isF}});
                q.push({nxts[i], tst.dst + 1, tst.isF});
            }
        }
    }
}