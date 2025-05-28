// HeapViewer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <sstream>
using namespace std;

typedef unsigned char byte;

int main()
{
    int sz;
    cout << "Bytes to allocate: ";
    cin >> sz;
    cout << "Offset: ";
    long long ofst;
    cin >> ofst;
    cout << hex;
    byte* bt = new byte[sz]();
    byte* cpy = bt;
    for (byte* i = bt + ofst;i <= (&(bt[sz - 1]));i++) {
        if (i == (&(bt[0]))) {
            cout << "array contents:\n";
        }
        cout << "0x" << (void*)(i);
        cout << ": ";
        string vl;
        stringstream tmp;
        tmp << hex << (unsigned int)(*i);
        vl = tmp.str();
        if (vl.length() == 1) {
            vl = "0" + vl;
        }
        cout << vl << endl;
    }
    delete[] bt;
    bt = cpy;
    cout << "deleted buffer:\n";
    for (byte* i = bt + ofst;i <= (&(bt[sz - 1]));i++) {
        if (i == (&(bt[0]))) {
            cout << "array contents:\n";
        }
        cout << "0x" << (void*)(i);
        cout << ": ";
        string vl;
        stringstream tmp;
        tmp << hex << (unsigned int)(*i);
        vl = tmp.str();
        if (vl.length() == 1) {
            vl = "0" + vl;
        }
        cout << vl << endl;
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
