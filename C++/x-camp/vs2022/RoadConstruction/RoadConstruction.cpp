// DisjointSetUnion.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <set>
using namespace std;

struct node {
    node* parent;
    bool isRoot = false;
    int size = 1;
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

/*struct nodeSzLess {
    bool operator()(node* a, node* b) const {
        return a->size < b->size;
    }
};*/

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
    int mxSz = 1;
    int cl = n;
    //cout << "Allocated!\n" << flush;
    for (int i = 0;i < n;i++) {
        nodes[i].isRoot = true;
    }
    for (int i = 0;i < m;i++) {
        int x, y;
        cin >> x >> y;
        x--;
        y--;
        node* xRoot = upProp(&(nodes[x]));
        node* yRoot = upProp(&(nodes[y]));
        if (xRoot != yRoot) {
            xRoot->isRoot = false;
            xRoot->parent = yRoot;
            nodes[x].parent = yRoot;
            cl--;
            yRoot->size += xRoot->size;
            if (yRoot->size > mxSz) {
                mxSz = yRoot->size;
            }
        }
        cout << cl << ' ' << mxSz << '\n';
    }
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
