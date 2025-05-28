// BinarySearch.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
using namespace std;
int binary_search(vector<int> vec, int n, int target) {
    int searchLen = 0;
    int inc = 1;
    int pos = 0;
    while (inc <= n) {
        inc <<= 1;
        searchLen++;
    }
    inc >>= 1;
    searchLen--;
    for (int i = -1;i < searchLen;i++) {
        if (pos + inc < n) {
            int tst = vec[pos + inc];
            if (tst <= target) {
                pos += inc;
            }
        }
        inc >>= 1;
    }
    if (vec[pos] == target) {
        int bLen = 0;
        int dec = 1;
        while (dec <= pos) {
            dec <<= 1;
            bLen++;
        }
        dec >>= 1;
        bLen--;
        for (int i = -1;i < bLen;i++) {
            if (vec[pos - dec] == target) {
                pos -= dec;
            }
            dec >>= 1;
        }
        return pos + 1;
    }
    return 0;
}
int main() {
    int n;
    cin >> n;
    vector<int> vec(n);
    for (int i = 0;i < n;i++) {
        cin >> vec[i];
    }
    int tst;
    bool bgn = true;
    int nm = 0;
    while (cin >> tst) {
        if (!bgn) { cout << ' '; }
        if (bgn) { bgn = false; }
        cout << binary_search(vec, n, tst);
        nm++;
    }
    cout << endl << nm;
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
