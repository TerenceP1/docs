#include <iostream>
#include <vector>
#include <queue>
using namespace std;
struct node
{
    int father = 0x7fffffff;
    int val;
};
int main()
{
    int n;
    cin >> n;
    vector<node *> itms(n);
    vector<vector<int>> lst;
    for (int i = 0; i < n; i++)
    {
        int a, b;
        cin >> a >> b;
        lst[a - 1].push_back(b - 1);
    }
    queue<int> q;
    q.push(0);
    while (!q.empty())
    {
        int tst = q.front();
        q.pop();
        for (int i : lst[tst])
        {
            itms[i]->father = tst;
        }
    }
    for (int i = 1; i < n; i++)
    {
        cout << itms[i]->father << endl;
    }
}