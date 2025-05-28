// ProcSpeedTester.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Windows.h"
using namespace std;

long long test(long long times) {
    int tmp = 0;
    DWORD64 st;
    DWORD64 end;
    DWORD64 base, add;
    st = GetTickCount64();
    for (long long i = 0;i < times;i++) {

    }
    end = GetTickCount64();
    base = end - st;
    st = GetTickCount64();
    for (long long i = 0;i < times;i++) {
        tmp++;
    }
    end = GetTickCount64();
    add = end - st;
    return add - base;
}

int main()
{
    long long tms = 2;
    long long tm = 0;
    while (tm < 1000) {
        tms *= 2;
        cout << tms << " increments test\n";
        tm = test(tms);
    }
    cout << "Speed: " << tms * 1000 / tm << " increments/sec\n";
    cout << tms << " increments in " << tm << " miliseconds\n";
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
