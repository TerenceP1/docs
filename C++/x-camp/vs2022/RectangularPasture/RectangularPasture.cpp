// RectangularPasture.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

struct coords {
    int x;
    int y;
    bool operator<(coords a) {
        if (x < a.x) {
            return true;
        }
        else if (x > a.x) {
            return false;
        }
        else {
            return y < a.y;
        }
    }
};

// Less functions for sorting:

bool lessX(coords a, coords b) {
    return a.x < b.x;
}

bool lessY(coords a, coords b) {
    return a.y < b.y;
}

int main()
{
    int n;
    cin >> n;
    vector<coords>cows(n);
    for (int i = 0;i < n;i++) {
        cin >> cows[i].x >> cows[i].y;
    }
    sort(cows.begin(), cows.end(), lessX);
    int lst = -1;
    int pl = 0;
    for (int i = 0;i < n;i++) {
        cows[i].x = pl;
        if (cows[i].x != lst) {
            pl++;
        }
        lst = cows[i].x;
    }
    sort(cows.begin(), cows.end(), lessY);
    lst = -1;
    pl = 0;
    for (int i = 0;i < n;i++) {
        cows[i].y = pl;
        if (cows[i].y != lst) {
            pl++;
        }
        lst = cows[i].y;
    }
    set<pair<pair<int, int>, pair<int, int>>> rects; // {{top, bottom},{left,right}}
    for (int i = 0;i < n - 1;i++) {
        for (int j = i + 1;j < n;j++) {
            
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
