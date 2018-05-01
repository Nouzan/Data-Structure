#pragma once
#include<memory>
#include "Node.h"

template<typename T>
class Stack {
	typedef Node<T> Node;
	const static int MAX_SIZE = 10000;
	std::unique_ptr<Node[]> array;
	int top;

public:
	Stack() {
		top = -1;
		array.reset(new Node[MAX_SIZE]);
	}

	~Stack() {
		array.release();
	}

	bool Push(T data) {
		if (IsFull())
			return false;
		else {
			array[++top] = data;
			return true;
		}
	}

	bool IsEmpty() const {
		return top == -1;
	}

	bool IsFull() const {
		return top + 1 == MAX_SIZE;
	}

	T Pop() {
		if (!IsEmpty())
			return array[top--].data;
		else
			throw "Stack::栈空";
	}

	T GetTop() const {
		if (!IsEmpty())
			return array[top].data;
		else
			throw "Stack::栈空";
	}

	Stack(const Stack<T> &rhs) {
		top = -1;
		array.reset(new Node[MAX_SIZE]);
		for (int i = 0; i <= rhs.top; i ++) {
			Push(rhs.array[i].data);
		}
	}

	Stack<T>& operator=(const Stack& rhs) {
		top = -1;
		for (int i = 0; i <= rhs.top; i ++) {
			Push(rhs.array[i].data);
		}
		return *this;
	}

	Stack(T *data_list, int size): Stack() {
		for (int i = 0; i < size; i ++) {
			Push(data_list[i]);
		}
	}
};
