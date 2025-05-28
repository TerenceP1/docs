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