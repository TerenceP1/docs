// PaintingTheBarn.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;

typedef long long big;

int main()
{
    int n, k;
    cin >> n >> k;
    big* chArr = new big[1002001]();
    for (int i = 0;i < n;i++) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        chArr[x1 * 1001 + y1]++;
        chArr[x1 * 1001 + y2]--;
        chArr[x2 * 1001 + y1]--;
        chArr[x2 * 1001 + y2]++;
    }
    big* pSums = new big[1002001];
    big cSm = 0;
    int res = 0;
    for (int i = 0;i < 1001;i++) {
        for (int j = 0;j < 1001;j++) {
            cSm += chArr[i * 1001 + j];
            if (i == 0) {
                pSums[j] = cSm;
                if (cSm == k) {
                    res++;
                }
            }
            else {
                pSums[i * 1001 + j] = pSums[(i - 1) * 1001 + j] + cSm;
                if (pSums[i * 1001 + j] == k) {
                    res++;
                }
            }
        }
    }
    cout << res;
    delete[] pSums;
    delete[] chArr;
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
