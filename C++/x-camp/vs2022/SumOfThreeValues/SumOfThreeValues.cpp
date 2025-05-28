// SumOfThreeValues.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <algorithm>
using namespace std;

struct itm {
    int val;
    int ind;
    bool operator<(itm a) {
        return val < a.val;
    }
};

int main()
{
    int n, x;
    cin >> n >> x;
    itm* arr = new itm[n];
    for (int i = 0;i < n;i++) {
        cin >> arr[i].val;
        arr[i].ind = i + 1;
    }
    sort(arr, arr + n);
    for (int i = 0;i < n - 2;i++) {
        int trg = x - arr[i].val;
        int first = i + 1;
        int last = n - 1;
        while (first < last) {
            if (arr[first].val + arr[last].val == trg) {
                cout << arr[first].ind << ' ' << arr[last].ind << ' ' << arr[i].ind;
                delete[] arr;
                return 0;
            }
            if (arr[first].val + arr[last].val < trg) {
                first++;
            }
            else {
                last--;
            }
        }
    }
    cout << "IMPOSSIBLE";
    delete[] arr;
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
