#pragma once
#include<iostream>
using namespace std;

template<typename T>
class FindSet {
private:
	FindSet<T> *p;
	int rank;
	T value;

public:
	FindSet() {
		rank = 0;
		p = this;
	}

	FindSet(T v) {
		rank = 0;
		p = this;
		value = v;
	}

	void Set(T v) {
		value = v;
	}

	T Get() {
		return value;
	}

	void Link(FindSet<T> &other) {
		if (rank > other.rank) {
			other.p = this;
		} else {
			p = &other;
			if (rank == other.rank) {
				other.rank ++;
			}
		}
	}

	FindSet<T> &Find() {
		if (p == this) {
			return *p;
		} else {
			p = &(p->Find());
		}
		return *p;
	}

	void Union(FindSet<T> &other) {
		Find().Link(other.Find());
	}
};
