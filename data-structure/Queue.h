#pragma once
#include<iostream>
#include<memory>
#include "Node.h"

template<typename T>
class Queue {
	typedef Node<T> Node;
	int head, tail;
	const int QUEUE_SIZE;
	std::unique_ptr<Node[]> array;

	int inc(int &index) {
		int old_index = index++;
		index %= QUEUE_SIZE;
		return old_index;
	}

	int getInc(int index) const {
		return ++index % QUEUE_SIZE;
	}

public:
	Queue(int queue_size = 10000): QUEUE_SIZE(queue_size + 1) {
		head = tail = 0;
		array.reset(new Node[QUEUE_SIZE]);
	}

	Queue(const Queue<T> &rhs): Queue(rhs.QUEUE_SIZE) {
		head = rhs.head;
		tail = rhs.tail;
		for(int i = rhs.head; i != rhs.tail; inc(i)) {
			array[i] = rhs.array[i];
		}
	}

	Queue<T>& operator=(const Queue<T> &rhs) {
		head = tail = 0;
		for(int i = rhs.head; i != rhs.tail; inc(i)) {
			EnQueue(rhs.array[i].key);
		}
		return *this;
	}

	~Queue() {
		array.release();
	}

	bool EnQueue(T data) {
		if (IsFull()) {
			std::cerr << "Queue: 队满" << std::endl;
			return false;
		}

		array[inc(tail)] = data;
		return true;
	}

	T DeQueue() {
		if (IsEmpty()) {
			std::cerr << "Queue: 队空" << std::endl;
			throw "error";
		}

		return array[inc(head)].key;
	}

	T GetHead() const {
		return array[head].key;
	}

	bool IsEmpty() const {
		return head == tail;
	}

	bool IsFull() const {
		return getInc(tail) == head;
	}

};
