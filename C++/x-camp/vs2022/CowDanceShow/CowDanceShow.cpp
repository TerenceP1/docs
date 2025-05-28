// CowDanceShow.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <queue>
#include <set>
using namespace std;

int getT(int n, int k, vector<int>d) {
    multiset<int> st;
    vector<int>tmp(k, 0);
    st.insert(tmp.begin(), tmp.end());
    for (int i = 0;i < n;i++) {
        auto frst = st.begin();
        int add = *frst + d[i];
        st.erase(frst);
        st.insert(add);
    }
    auto lst = st.end();
    lst--;
    return *lst;
}

int main()
{
    int n, tmax;
    cin >> n >> tmax;
    vector<int>d(n);
    for (int i = 0;i < n;i++) {
        cin >> d[i];
    }
    int lft = 1;
    int rgt = n;
    while (rgt - lft > 1) {
        int mid = (lft + rgt) / 2;
        int t = getT(n, mid, d);
        if (t > tmax) {
            lft = mid + 1;
        }
        else {
            rgt = mid - 1;
        }
    }
    cout << lft;
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
