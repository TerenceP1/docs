// ForestQueues.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;

typedef unsigned long long big;

int main()
{
	int n, q;
	cin >> n >> q;
	big** sms = new big * [n + 1];
	big tmpSm = 0;
	big* tmpIn = new big[n + 1];
	sms[0] = new big[n + 1];
	for (int i = 0;i <= n;i++) {
		sms[0][i] = 0;
	}
	char* inBuf = new char[n + 1];
	for (int i = 0;i < n;i++) {
		sms[i + 1] = new big[n + 1];
		sms[i + 1][0] = 0;
		cin >> inBuf;
		inBuf[n] = '\0';
		tmpSm = 0;
		for (int j = 0;j < n;j++) {
			sms[i + 1][j + 1] = sms[i][j + 1];
			if (inBuf[j] == '*') {
				tmpSm++;
			}
			sms[i + 1][j + 1] += tmpSm;
		}
	}
	for (int i = 0;i < q;i++) {
		int x1, x2, y1, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		cout << (sms[x2][y2] - sms[x2][y1 - 1] - sms[x1 - 1][y2] + sms[x1 - 1][y1 - 1]) << endl;
	}
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
