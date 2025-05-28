#include <iostream>
#include <vector>
#include <set>
#include <queue>
using namespace std;
struct Tree
{
    Tree *parent = nullptr;
    vector<Tree *> children;
    int childrenCount = 0;
};
int count(Tree *tr)
{
    for (int i = 0; i < tr->children.size(); i++)
    {
        tr->childrenCount += count(tr->children[i]);
    }
}
int main()
{
    vector<vector<bool>> in;
    int len;
    cin >> len;
    for (int i = 0; i < len; i++)
    {
        string tmp;
        cin >> tmp;
        for (int j = 0; j < len; j++)
        {
            in[i][j] = tmp[j];
        }
    }
    vector<Tree *> all(len);
    vector<set<int>> mp(len);
    for (int i = 0; i < len; i++)
    {
        for (int j = 0; j < len; j++)
        {
            mp[i].insert(j);
        }
    }
    queue<int> q;
    set<int> tested;
    q.push(0);
    for (int i = 0; i < len; i++)
    {
        all[i] = new Tree;
    }
    while (!q.empty())
    {
        int ft = q.front();
        q.pop();
        tested.insert(ft);
        for (int i : mp[ft])
        {
            if (tested.find(i) == tested.end())
            {
                if (all[i]->parent != nullptr)
                {
                    all[i]->parent = all[ft];
                }
                tested.insert(i);
                q.push(i);
                all[ft]->children.push_back(all[i]);
            }
        }
    }
    count(all[0]);
    for (int i = 0; i < all.size(); i++)
    {
        cout << all[i]->childrenCount << endl;
    }
}