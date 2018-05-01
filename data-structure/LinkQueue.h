#pragma once
#include<iostream>
#include<memory>
#include "LinkList.h"

template<typename T>
class LinkQueue {
	std::shared_ptr<LinkListNode<T>> head, tail;
	LinkList<T> linkList;

	void updateHeadTail() {
		head = linkList.GetHead();
		tail = linkList.GetTail();
	}

public:
	LinkQueue() {
		updateHeadTail();
	}

	~LinkQueue() {}

	LinkQueue(const LinkQueue<T> &rhs): LinkQueue() {
		linkList = rhs.linkList;
		updateHeadTail();
	}

	LinkQueue<T>& operator=(const LinkQueue<T> &rhs) {
		linkList = rhs.linkList;
		updateHeadTail();
		return *this;
	}

	bool EnQueue(T data) {
		linkList.Insert(data);
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
