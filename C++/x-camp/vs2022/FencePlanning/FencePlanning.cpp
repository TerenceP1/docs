// DisjointSetUnion.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <climits>
using namespace std;

struct node {
	node* parent;
	bool isRoot = false;
	int xMin, xMax, yMin, yMax;
};

node* upProp(node* nd) {
	//cout << "upProp begin\n";
	node* upP = nd;
	while (!upP->isRoot) {
		upP = upP->parent;
		//cout << "upProp to " << upP << endl;
		//cout << "upP is { parent = " << upP->parent << ", isRoot = " << upP->isRoot << "}\n" << flush;
	}
	//cout << "upProp end\n";

	if ((!nd->isRoot)) {
		if (!nd->parent->isRoot) {
			nd->parent = upP;
		}
	}

	return upP;
}

inline void combine(node* nodes, int a, int b) {
	node* xRoot = upProp(&(nodes[a]));
	node* yRoot = upProp(&(nodes[b]));
	if (xRoot != yRoot) {
		xRoot->isRoot = false;
		xRoot->parent = yRoot;
		nodes[a].parent = yRoot;
		if (xRoot->xMin < yRoot->xMin) {
			yRoot->xMin = xRoot->xMin;
		}
		if (xRoot->yMin < yRoot->yMin) {
			yRoot->yMin = xRoot->yMin;
		}
		if (xRoot->xMax > yRoot->xMax) {
			yRoot->xMax = xRoot->xMax;
		}
		if (xRoot->yMax > yRoot->yMax) {
			yRoot->yMax = xRoot->yMax;
		}
	}
}

int main()
{
	//cout << "Startup\n" << flush;
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	//cout << "Desync\n" << flush;
	int n, m;
	cin >> n >> m;
	//cout << "Allocating...\n" << flush;
	node* nodes = new node[n];
	//cout << "Allocated!\n" << flush;
	for (int i = 0;i < n;i++) {
		nodes[i].isRoot = true;
		int x, y;
		cin >> x >> y;
		nodes[i].xMax = x;
		nodes[i].yMax = y;
		nodes[i].xMin = x;
		nodes[i].yMin = y;
	}
	for (int i = 0;i < m;i++) {
		int a, b;
		cin >> a >> b;
		a--;
		b--;
		combine(nodes, a, b);
	}
	long long mn = LLONG_MAX;
	for (int i = 0;i < n;i++) {
		if (nodes[i].isRoot) {
			long long prod = ((long long)(nodes[i].xMax - nodes[i].xMin + 1)) * ((long long)(nodes[i].yMax - nodes[i].yMin + 1));
			if (prod < mn) {
				mn = prod;
			}
		}
	}
	cout << mn;
	cout << flush;
	//cout << "Deallocating memory...\n";
	delete[] nodes;
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
