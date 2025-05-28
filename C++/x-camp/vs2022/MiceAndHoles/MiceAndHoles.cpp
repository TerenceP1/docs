// MiceAndHoles.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

typedef unsigned long long big;

int main()
{
    int n, m;
    cin >> n >> m;
    vector<big>mouses(n);
    vector<big>holes(m);
    cout << "vecs\n";
    for (int i = 0;i < n;i++) {
        cin >> mouses[i];
    }
    for (int i = 0;i < m;i++) {
        cin >> holes[i];
    }
    cout << "cin\n";
    multiset<big>hls(holes.begin(), holes.end());
    big msm = 0;
    big hsm = 0;
    cout << "mset\n";
    for (int i = 0;i < n;i++) {
        auto ub = hls.upper_bound(mouses[i]);
        ub--;
        msm += mouses[i];
        hsm += *ub;
        hls.erase(ub);
    }
    cout << msm - hsm;
    return 0;
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
