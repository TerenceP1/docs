// DiamondCollector.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <map>
using namespace std;

// Linked list:
struct lList {
	pair<int, long long>data;
	bool isEnd = true; // Whether to continue parsing or not
	lList* next; // Next item in linked list
};

int main()
{
	int n, k;
	cin >> n >> k;
	map<int, long long>qts; // Stores sizes of diamonds in the format {diamond size, quantity}
	// Get the sizes of the diamonds and store them in qts:
	for (int i = 0;i < n;i++) {
		int in;
		cin >> in;
		// If in is found in qts, increment quantity. Otherwise, add insert {in, 1} as there is a new size of quantity 1:
		map<int, long long>::iterator loc = qts.find(in); // Save time by finding once and keeping the iterator
		if (loc == qts.end()) {
			qts.insert({ in,1 });
		}
		else {
			loc->second++;
		}
	}
	// Get number of diamonds at most k sizes less than each diamond size
	lList* front = nullptr, * back = nullptr; // Front and back of a linked list queue containing all previous diamonds that will still add
	long long sm = 0; // Number of diamonds at most k sizes less than the current diamond size
	map<int, long long> groups; // Number of diamonds at most k sizes less than each diamond size
	bool isStart = true; // If it is the first item to be proccessed
	for (map<int, long long>::iterator it = qts.begin();it != qts.end();it++) {
		if (isStart) {
			isStart = false;
			front = new lList;
			back = front;
			front->data = *it;
			sm += it->second;
			groups.insert({ it->first,sm });
		}
		else {
			lList* nxt = new lList;
			nxt->data = *it;
			sm += it->second;
			back->isEnd = false;
			back->next = nxt;
			back = nxt;
			int mn = it->first - k;
			while (front->data.first < mn) {
				lList* nFront = front->next;
				sm -= front->data.second;
				delete front;
				front = nFront;
			}
			groups.insert({ it->first,sm });
		}
	}
	// Find max:
	long long mx = 0;
	for (map<int, long long>::iterator it = groups.begin();it != groups.end();it++) {
		for (map<int, long long>::iterator it2 = it;it2 != groups.end();it2++) {
			if (it2->first - it->first > k) {
				long long sm = it2->second + it->second;
				if (sm > mx) {
					mx = sm;
				}
			}
		}
	}
	cout << mx;
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
