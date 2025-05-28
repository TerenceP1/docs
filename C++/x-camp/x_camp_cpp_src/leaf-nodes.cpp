#include <iostream>
#include <vector>
using namespace std;
int main()
{
    int n;
    cin >> n;
    int fc = 0;
    vector<int> itms;
    for (int i = 0; i < n; i++)
    {
        string tmp;
        cin >> tmp;
        int count = 0;
        for (int i = 0; i < n; i++)
        {
            if (tmp[i] == ' ')
            {
                count++;
            }
        }
        if (count == 1)
        {
            itms.push_back(i + 1);
            fc++;
        }
    }
    cout << fc << endl;
    for (int i : itms)
    {
        cout << i << endl;
    }
}