// HPS.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
using namespace std;

int main()
{
	int n;
	cin >> n;
	vector<int>mvs(n);
	for (int i = 0;i < n;i++) {
		char in;
		cin >> in;
		switch (in) {
		case 'H':
			mvs[i] = 0;
			break;
		case 'P':
			mvs[i] = 1;
			break;
		case 'S':
			mvs[i] = 2;
			break;
		}
	}
	vector<int>* fSums = new vector<int>[3];
	fSums[0].resize(n + 1);
	fSums[1].resize(n + 1);
	fSums[2].resize(n + 1);
	for (int i = 0;i < 3;i++) {
		fSums[i][0] = 0;
		for (int j = 0;j < n;j++) {
			fSums[i][j + 1] = fSums[i][j];
			if (((mvs[j] + 1) % 3) == i) {
				fSums[i][j + 1]++;
			}
		}
	}
	vector<int>* bSums = new vector<int>[3];
	bSums[0].resize(n + 1);
	bSums[1].resize(n + 1);
	bSums[2].resize(n + 1);
	for (int i = 0;i < 3;i++) {
		bSums[i][0] = 0;
		for (int j = 0;j < n;j++) {
			bSums[i][j + 1] = bSums[i][j];
			if (((mvs[n - j - 1] + 1) % 3) == i) {
				bSums[i][j + 1]++;
			}
		}
	}
	int cMax = 0;
	// Test 0 changes
	for (int i = 0;i < 3;i++) {
		if (cMax < (fSums[i][n])) {
			cMax = fSums[i][n];
		}
	}
	// Test 1 change
	for (int i = 0;i < 3;i++) {
		for (int j = 0;j < 3;j++) {
			if (i != j) {
				for (int k = 0;k < n;k++) {
					int test = fSums[i][k + 1] + bSums[j][n - k];
					if (test > cMax) {
						cMax = test;
					}
				}
			}
		}
	}
	cout << cMax;
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
