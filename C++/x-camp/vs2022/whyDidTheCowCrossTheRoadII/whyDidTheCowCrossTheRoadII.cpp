// whyDidTheCowCrossTheRoadII.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
using namespace std;

int main()
{
    
    int n, k, b;
    cin >> n >> k >> b;
    vector<int>org(n - k + 1, 0);
    for (int i = 0;i < b;i++) {
        int tmp;
        cin >> tmp;
        tmp--;
        if (tmp - k + 1 > -1) {
            org[tmp - k + 1]++;
        }
        else {
            org[0]++;
        }
        if (tmp < n - k + 1) {
            org[tmp]--;
        }
    }
    vector<int>psm(n - k + 1);
    int mn = INT_MAX;
    for (int i = 0;i < n - k + 1;i++) {
        if (i == 0) {
            psm[0] = org[0];
        }
        else {
            psm[i] = psm[i - 1] + org[i];
        }
        if (psm[i] < mn) {
            mn = psm[i];
        }
    }
    cout << mn;
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
