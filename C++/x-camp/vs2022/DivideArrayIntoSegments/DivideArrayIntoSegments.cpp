// DivideArrayIntoSegments.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;
    vector<int>a(n);
    int sm = 0;
    int mx = 0;
    for (int i = 0;i < n;i++) {
        cin >> a[i];
        sm += a[i];
        if (mx < a[i]) {
            mx = a[i];
        }
    }
    int lft = mx, rgt = sm;
    while (rgt - lft >= 0) {
        int mid = (rgt + lft) / 2;
        int segs = 0;
        int cSm = 0;
        for (int i = 0;i < n;i++) {
            if (cSm + a[i] > mid) {
                segs++;
                cSm = a[i];
            }
            else {
                cSm += a[i];
            }
        }
        if (segs > m) {
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
