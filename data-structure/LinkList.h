#pragma once
#include<iostream>
#include<memory>
#include "Node.h"

template<typename DataType, typename KeyType=int>
struct LinkListNode : Node<DataType, KeyType> {
	std::shared_ptr<LinkListNode<DataType, KeyType>> next;
	std::shared_ptr<LinkListNode<DataType, KeyType>> prev;

	LinkListNode() : next(nullptr), prev(nullptr) {}

	LinkListNode(const DataType &data) : Node<DataType, KeyType>(data), next(nullptr), prev(nullptr) {
		//std::cout << data << std::endl;
	}

	LinkListNode(const LinkListNode<DataType, KeyType> &rhs) : Node<DataType, KeyType>(rhs), next(rhs.next), prev(rhs.prev) {
	}

	LinkListNode<DataType, KeyType>& operator=(const LinkListNode<DataType, KeyType> &rhs) {
		this->key = rhs.key;
		this->data = rhs.data;
		next = rhs.next;
		prev = rhs.prev;
		return *this;
	}
};

template<typename DataType>
class LinkList {
	typedef LinkListNode<DataType> Node;
	std::shared_ptr<Node> nil;

	std::shared_ptr<Node> get(int index) const {
		auto p = nil;
		int count = 0;
		while (p->next != nil && count != index) {
			p = p->next;
			count ++;
		}
		if (count == index) {
			//std::cout << "Got" << p->data << std::endl;
			return p;
		} else if (count < index) {
			std::cerr << "LinkList: 下标越界" << std::endl;
			return nullptr;
		} else {
			std::cerr << "LinkList: 链表连接错误" << std::endl;
			return nullptr;
		}
	}

public:
	LinkList() {
		nil = std::make_shared<Node>();
		nil->next = nil;
		nil->prev = nil;
	}

	~LinkList() {
		auto head = nil->next;
		while (head != nil) {
			auto tmp = head;
			head = head->next;
			tmp.reset();
		}
		nil.reset();
	}

	bool IsEmpty() const {
		return nil->next == nil;
	}

	void Insert(const DataType &data, int index = 0) {
		auto p = get(index);
		if (p) {
			auto q = std::make_shared<Node>(data);
			q->prev = p->prev;
			p->prev->next = q;
			p->prev = q;
			q->next = p;
		}
	}

	DataType Delete(int index) {
		auto p = get(index);
		if (p && p != nil) {
			p->prev->next = p->next;
			p->next->prev = p->prev;
			return p->data;
		}
		throw "error";
	}

	DataType Get(int index) {
		auto p = get(index);
		if (p)
			return p->data;
		else
			throw "error";
	}
};
