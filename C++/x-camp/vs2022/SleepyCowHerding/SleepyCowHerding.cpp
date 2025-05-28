// SleepyCowHerding.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

/*
The Strategy:

Min moves:
1. Find a window size n with the most cows in it as possible fully contained within the outermost cows (if it is n cows, you are done. It would be 0) using the strategy described later.
If there are n-1 cows and the spot with the missing cow is on the edge of the window, the answer is 1 if the missing cow is 1 away from the gap and 2 otherwise.
If not, the answer will be n minus the number of cows in the window

To find the window with the most cows:
1. List all windows size n starting or ending with a cow
2. Filter windows that are out of bounds
3. Scan through the valid windows to find the one with the most cows

Max moves:
1. Choose the side where its edge cow's distance from it's nearest cow is lesser
Let the distance between the chosen side's edge cow and it's nearest cow be 'a'
Let the distance between the edgemost cows be 'b'
The answer is always b-n-a+2
*/

#include <iostream>
#include <algorithm>
#include <cmath>
#include <climits>
#include <set>
using namespace std;

class tree {
private:
	int cMin;
	bool isLeaf;
	int val;
	int index;
	tree* lNxt;
	bool hasRB;
	tree* rNxt;
	void mkTr(int* arr, int lft, int rgt, int splitLen) {
		if (splitLen == 0) {
			isLeaf = true;
			hasRB = false;
			val = arr[lft];
			cMin = val;
			index = lft;
		}
		else {
			cMin = arr[lft];
			isLeaf = false;
			if (rgt - lft <= splitLen) {
				hasRB = false;
				lNxt = new tree;
				lNxt->mkTr(arr, lft, rgt, splitLen / 2);
			}
			else {
				hasRB = true;
				lNxt = new tree;
				lNxt->mkTr(arr, lft, lft + splitLen, splitLen / 2);
				rNxt = new tree;
				rNxt->mkTr(arr, lft + splitLen, rgt, splitLen / 2);
			}
		}
	}
public:
	tree() {}
	~tree() {
		if (!isLeaf) {
			if (hasRB) {
				delete rNxt;
			}
			delete lNxt;
		}
	}
	void initTree(int* arr, int sz) {
		int splitLen = pow(2, (int)log2(sz));
		mkTr(arr, 0, sz, splitLen);
	}
	pair<int, int> find(int a) {
		if (isLeaf) {
			return make_pair(index, val);
		}
		else {
			if (hasRB) {
				if (a >= rNxt->cMin) {
					return rNxt->find(a);
				}
				else {
					return lNxt->find(a);
				}
			}
			else {
				return lNxt->find(a);
			}
		}
	}
};

int main()
{
	int n;
	cin >> n;
	int* arr = new int[n];
	for (int i = 0;i < n;i++) {
		cin >> arr[i];
	}
	sort(arr, arr + n);
	// Min:
	set<int>itms;
	itms.insert(arr, arr + n);
	tree tr;
	tr.initTree(arr, n);
	int mx = INT_MIN;
	for (int i = 0;i < n;i++) {
		if (arr[i] + n - 1 <= arr[n - 1]) {
			pair<int, int>tst = tr.find(arr[i] + n - 1);
			int nms = tst.first - i + 1;
			if (nms == n - 1) {
				if (itms.find(arr[i] + n - 1) == itms.end()) {
					nms--;
				}
			}
			if (nms > mx) {
				mx = nms;
			}
		}
	}
	cout << n - mx << endl;
	// Max:
	int ls = arr[1] - arr[0];
	int rs = arr[n - 1] - arr[n - 2];
	int mn;
	if (ls > rs) {
		mn = rs;
	}
	else {
		mn = ls;
	}
	int dst = arr[n - 1] - arr[0];
	cout << dst - n - mn + 2;
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
