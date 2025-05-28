// SocialDistancing.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <map>
#include <climits>
using namespace std;

#define big long long
#define BIG_MAX LLONG_MAX

int main()
{
    int n, m;
    cin >> n >> m;
    map<big, big>grass; // {left end, right end}
    big mx = 0;
    big mn = BIG_MAX;
    for (int i = 0;i < m;i++) {
        big a, b;
        cin >> a >> b;
        grass.insert({ a,b });
        if (b > mx) {
            mx = b;
        }
        if (a < mn) {
            mn = a;
        }
    }
    big lft = 1, rgt = mx;
    while (lft <= rgt) {
        big mid = (lft + rgt) / 2;
        // Find max cows that fit with a minimum distance of mid
        big pos = mn;
        big mxCows = 1;
        while (true) {
            big nxPos = pos + mid;
            auto grs = grass.upper_bound(nxPos);
            grs--;
            if (grs->second >= nxPos) {
                pos += mid;
                mxCows++;
                continue;
            }
            grs++;
            if (grs == grass.end()) {
                break;
            }
            else {
                mxCows++;
                pos = grs->first;
            }
        }
        if (mxCows >= n) {
            lft = mid + 1;
        }
        else {
            rgt = mid - 1;
        }
    }
    cout << rgt;
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
