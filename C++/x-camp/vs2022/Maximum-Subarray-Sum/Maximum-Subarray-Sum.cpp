// Maximum-Subarray-Sum.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<int>x(n);
    for (int i = 0;i < n;i++) {
        cin >> x[i];
    }
    if (n == 1) {
        cout << x[0];
        return 0;
    }
    int gMax = x[0];
    int cMax = x[0];
    for (int i = 1;i < n;i++) {
        if (cMax < 0) {
            cMax = x[i];
        }
        else {
            cMax += x[i];
        }
        if (cMax > gMax) {
            gMax = cMax;
        }
    }
    cout << gMax;
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
