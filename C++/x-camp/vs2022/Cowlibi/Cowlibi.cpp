// Cowlibi.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <fstream>
using namespace std;

typedef long long big;

// location and time
struct gr {
	big x;
	big y;
	big t;
	bool operator<(gr &a) {
		return t < a.t;
	}
};
bool operator<(gr& a, big t) {
	return a.t < t;
}
bool operator<(big t, gr& a) {
	return t < a.t;
}

bool tmComp(const gr a, const gr b) {
	return a.t < b.t;
}

less<gr> lessTest;

ifstream in("C:\\Users\\teren\\Documents\\Programming\\C++\\x-camp\\vs2022\\Cowlibi\\x64\\Debug\\uoj2.in");

int main()
{
	big n, g;
	in >> g >> n;
	vector<gr>grs(g);
	vector<gr>alibi(n);
	for (big i = 0;i < g;i++) {
		big x, y, t;
		in >> x >> y >> t;
		grs[i] = { x,y,t };
	}
	for (big i = 0;i < n;i++) {
		big x, y, t;
		in >> x >> y >> t;
		alibi[i] = { x,y,t };
	}
	sort(grs.begin(), grs.end());
	sort(alibi.begin(), alibi.end());
	/*vector<double>dff(g - 1);
	double dffSm = 0;
	for (int i = 0;i < g - 1;i++) {
		dff[i] = sqrt((double)((grs[i].x - grs[i + 1].x) * (grs[i].x - grs[i + 1].x) + (grs[i].y - grs[i + 1].y) * (grs[i].y - grs[i + 1].y)));
		dffSm += dff[i];
	}*/
	big res = 0;
	for (big i = 0;i < n;i++) {
		auto lb = upper_bound(grs.begin(), grs.end(), alibi[i].t);
		if (lb != grs.begin()) {
			lb--;
			if (lb->t == alibi[i].t) {
				if (lb != grs.begin()) {
					lb--;
					cout << i << "-th alibi found an equal!\n";
					double frm = sqrt((double)((lb->x - alibi[i].x) * (lb->x - alibi[i].x) +
						(lb->y - alibi[i].y) * (lb->y - alibi[i].y)));
					if ((frm > (alibi[i].t - lb->t))) {
						res++;
						cout << "Incremented!\n";
						continue;
					}
					lb++;
				}
			}
			double from = sqrt((double)((lb->x - alibi[i].x) * (lb->x - alibi[i].x) +
				(lb->y - alibi[i].y) * (lb->y - alibi[i].y)));
			cout << i << "-th alibi is centered!\n";
			if ((from > (alibi[i].t - lb->t))) {
				res++;
				cout << i << "-th alibi cant reach left\n";
			}
			else {
				lb++;
				cout << i << "-th alibi can reach left\n";
				if (lb!=grs.end()){
					double to = sqrt((double)((lb->x - alibi[i].x) * (lb->x - alibi[i].x) +
						(lb->y - alibi[i].y) * (lb->y - alibi[i].y)));
					if (to > (lb->t - alibi[i].t)) {
						res++;
						cout << i << "-th alibi cant reach right\n";
					}
				}
			}
		}
		else {
			if (lb != grs.end()) {
				cout << i << "-th alibi all on left\n";
				double to = sqrt((double)((lb->x - alibi[i].x) * (lb->x - alibi[i].x) +
					(lb->y - alibi[i].y) * (lb->y - alibi[i].y)));
				if (to > (lb->t - alibi[i].t)) {
					res++;
				}
			}
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
