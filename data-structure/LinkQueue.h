#pragma once
#include<iostream>
#include<memory>
#include "LinkList.h"

template<typename T>
class LinkQueue {
	std::shared_ptr<LinkListNode<T> > head, tail;
	LinkList<T> linkList;

	void updateHeadTail() {
		head = linkList.GetTail();
		tail = linkList.GetHead();
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

	void EnQueue(T data) {
		linkList.Insert(data, tail);
		updateHeadTail();
	}

	T DeQueue() {
		if (IsEmpty()) {
			std::cerr << "Queue: 队空" << std::endl;
			throw "error";
		}

		T data = head->key;
		linkList.Delete(head);
		updateHeadTail();
		return data;
	}

	T GetHead() const {
		return head->key;
	}

	bool IsEmpty() const {
		return linkList.IsEmpty();
	}

};
