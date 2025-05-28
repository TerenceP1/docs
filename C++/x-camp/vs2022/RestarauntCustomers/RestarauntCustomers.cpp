// RestarauntCustomers.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct action {
	int time;
	bool state; // 0 if coming and 1 if leaving
	bool operator<(action a) {
		return time < a.time;
	}
};

int main()
{
	int n;
	cin >> n;
	vector<action>sortedEvents;
	for (int i = 0;i < n;i++) {
		action first{ 0,0 }, last{ 0,1 };
		cin >> first.time >> last.time;
		sortedEvents.push_back(first);
		sortedEvents.push_back(last);
	}
	sort(sortedEvents.begin(), sortedEvents.end());
	int cMax = 0;
	int cNum = 0;
	for (action i : sortedEvents) {
		if (i.state) {
			cNum--;
		}
		else {
			cNum++;
			if (cNum > cMax) {
				cMax = cNum;
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
