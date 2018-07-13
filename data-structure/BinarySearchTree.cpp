#pragma once
#include <iostream>

using namespace std;

template<typename T>
class BSTree {
private:
	T value;
	BSTree *left;
	BSTree *right;
	BSTree *parent;
	int height;
	static bool cmp(const T& a, const T& b) {
		return a < b;
	}
	BSTree *successor() {
		if(right != NULL) {
			BSTree *y = this;
			BSTree *x = right;
			while (x != NULL) {
				x = x->left;
				y = x;
			}
			return y;
		} else {
			BSTree *x = this;
			BSTree *y = parent;
			while (y != NULL && x == y->right) {
				x = y;
				y = y->parent;
			}
			return y;
		}

	}

	void calcHeight() {
		if (parent) {
			height = parent->height + 1;
		} else {
			height = 0;
		}
		if (left) {
			left->calcHeight();
		}
		if (right) {
			right->calcHeight();
		}
	}

public:
	BSTree() : height(0), left(NULL), right(NULL), parent(NULL) {
	}
	BSTree(T v) : height(0), value(v), left(NULL), right(NULL), parent(NULL) {
	}
	BSTree(T *A, int num, bool (*cp)(const T&, const T&) = cmp) : BSTree(A[0]) {
		for (int i = 1; i < num; i ++) {
			BSTree<T> *x = new BSTree<T>(A[i]);
			Insert(x, cp);
		}
	}
	~BSTree() {
		if (left) {
			delete left;
		}
		if (right) {
			delete right;
		}
	}
	void Insert(BSTree *t, bool (*cp)(const T&, const T&) = cmp) {
		if (cmp(t->value, value)) {
			if (left == NULL) {
				left = t;
				t->parent = this;
				t->calcHeight();
			} else {
				left->Insert(t, cp);
			}
		} else {
			if (right == NULL) {
				right = t;
				t->parent = this;
				t->calcHeight();
			} else {
				right->Insert(t, cp);
			}
		}
	}
	T Delete(BSTree *t) {
		if (t->left == NULL && t->right == NULL) {
			if (t->parent) {
				if (t->parent->left == t) {
					t->parent->left = NULL;
				} else {
					t->parent->right = NULL;
				}
			}
			t->parent = NULL;
			t->calcHeight();
			return t->value;
		}

		if (t->left != NULL && t->right != NULL) {
			T tmp = Delete(t->successor());
			T result = t->value;
			t->value = tmp;
			return result;
		}

		if (t->left != NULL) {
			t->left->parent = t->parent;
			t->left->calcHeight();
			if (t->parent) {
				if (t->parent->left == t) {
					t->parent->left = t->left;

				} else {
					t->parent->right = t->left;
				}
			}
			t->left = NULL;
		} else {
			t->right->parent = t->parent;
			t->right->calcHeight();
			if (t->parent) {
				if (t->parent->left == t) {
					t->parent->left = t->right;
				} else {
					t->parent->right = t->right;
				}
			}

			t->right = NULL;
		}
		t->parent = NULL;
		t->calcHeight();
		return t->value;
	}

	void MinOrderPrint() {
		if (left) {
			left->MinOrderPrint();
		}
		cout << "<" << value << ", " << height << ">" << " ";
		if (right) {
			right->MinOrderPrint();
		}
	}

	BSTree *GetLeft() {
		return left;
	}

	BSTree *GetRight() {
		return right;
	}
};

int main() {
	int A[5] = {25, 11, 24, 12};
	BSTree<int> bst(A, 4);
	bst.MinOrderPrint();
	cout << endl;
	BSTree<int> *l = bst.GetLeft();
	bst.Delete(l);
	bst.MinOrderPrint();
	cout << endl;
	bst.Delete(&bst);
	bst.MinOrderPrint();
	cout << endl;

}
