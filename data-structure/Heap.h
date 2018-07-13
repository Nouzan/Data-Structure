#pragma once

#include<iostream>
using namespace std;

template<typename T>
class Heap {
private:
	const static int maxSize = 100000;
	T array[maxSize];
	int n;
	bool (*cmp)(const T&, const T&);
	static bool defaultCmp(const T& a, const T& b) {
		return a < b;
	}

	bool isSmaller(int i, int j) {
		return cmp(array[i], array[j]);
	}

	int left(int r) {
		return 2 * (r + 1) - 1;
	}
	int right(int r) {
		return 2 * (r + 1);
	}
	int parent(int r) {
		if (r == 0)
			return 0;
		return (r + 1) / 2 - 1;
	}
	void swap(int i, int j) {
		if (i != j) {
			T tmp = array[i];
			array[i] = array[j];
			array[j] = tmp;
		}
	}
	void heapify(int root) {
		int smallest = root;
		if (left(root) < n && isSmaller(left(root), root)) {
			smallest = left(root);
			swap(left(root), root);
		}
		if (right(root) < n && isSmaller(right(root), root)) {
			smallest = right(root);
			swap(right(root), root);
		}

		if (smallest != root) {
			heapify(smallest);
		}
	}
public:
	Heap(bool (*cp)(const T&, const T&) = defaultCmp) {
		n = 0;
		cmp = cp;
	}
	Heap(T *A, int num, bool (*cp)(const T&, const T&) = defaultCmp) {
		n = num;
		cmp = cp;

		for (int i = 0; i < n; i ++) {
			 array[i] = A[i];
		}

		int m = n / 2 - 1;
		for(int i = m; i >= 0; i --) {
			heapify(i);
		}
	}
	void Insert(T x) {
		array[n ++] = x;
		for (int i = n - 1; isSmaller(i, parent(i)); i = parent(i)) {
			swap(i, parent(i));
		}
	}
	T Extract() {
		swap(0, --n);
		heapify(0);
		return array[n];
	}
	bool IsEmpty() const {
		return n == 0;
	}
	void GetSorted(T *A) {
		for(int i = 0; n != 0; i ++) {
			A[i] = Extract();
		}
	}
};

// int main() {
// 	int A[5] = {3, 8, 2, 7, 1};
// 	Heap<int> mh(A, 3);
// 	//mh.GetSorted(A);
// 	for(int i = 0; i < 2; i ++) {
// 		mh.Insert(A[i + 3]);
// 		cout << mh.Extract() << " ";
// 	}
// 	cout << endl;
// 	return 0;
// }
