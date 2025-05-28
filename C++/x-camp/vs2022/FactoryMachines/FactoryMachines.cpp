// FactoryMachines.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
using namespace std;

typedef long long big;

int main()
{
    big n, t;
    cin >> n >> t;
    vector<big>vec(n);
    big mn = -1;
    for (big i = 0;i < n;i++) {
        cin >> vec[i];
        if (mn == -1) {
            mn = vec[i];
        }
        else if (vec[i] < mn) {
            mn = vec[i];
        }
    }
    big lft = 0;
    big rgt = mn * t;
    while (rgt - lft > 1) {
        big md = (lft + rgt) / 2;
        big prod = 0;
        for (big i = 0;i < n;i++) {
            prod += md / vec[i];
        }
        if (prod >= t) {
            rgt = md;
        }
        else {
            lft = md;
        }
    }
    cout << rgt;
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
