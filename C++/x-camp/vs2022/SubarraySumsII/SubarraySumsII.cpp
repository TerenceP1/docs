// SubarraySumsII.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <map>
using namespace std;

int main()
{
	long long n, x;
	cin >> n >> x;
	vector<long long>a(n);
	vector<long long>sums(n + 1);
	sums[0] = 0;
	for (long long i = 0;i < n;i++) {
		cin >> a[i];
		sums[i + 1] = sums[i] + a[i];
	}
	map<long long, long long>cNums;
	map<long long, long long>::iterator frst = cNums.begin();
	cNums.insert(frst, { 0, 1 });
	long long res = 0;
	for (long long i = 1;i <= n;i++) {
		map<long long, long long>::iterator tst = cNums.find(sums[i] - x);
		if (tst != cNums.end()) {
			res += tst->second;
		}
		map<long long, long long>::iterator inc = cNums.find(sums[i]);
		if (inc == cNums.end()) {
			cNums.insert(frst, { sums[i],1 });
		}
		else {
			inc->second++;
		}
	}
	cout << res;
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
