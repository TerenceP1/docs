// catch-the-cow.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

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
    q.push({ n, 0, true });
    q.push({ k, 0, false });
    map<int, pair<int, bool>> vst; // Map of all past runs {val, {dst, isF}}
    vst.insert({ n, {0, true} });
    vst.insert({ k, {0, false} });
    while (!q.empty())
    {
        itr tst = q.front();
        q.pop();
        int nxts[3]{ tst.val + 1, tst.val - 1, (tst.isF ? tst.val << 1 : tst.val >> 1) }; // All possible next steps
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
                vst.insert({ nxts[i], {tst.dst + 1, tst.isF} });
                q.push({ nxts[i], tst.dst + 1, tst.isF });
            }
        }
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
