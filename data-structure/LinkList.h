#pragma once
#include<iostream>
#include<memory>
#include "Node.h"

template<typename KeyType, typename DataType=int>
struct LinkListNode : Node<KeyType, DataType> {
	std::shared_ptr<LinkListNode<KeyType, DataType>> next;
	std::shared_ptr<LinkListNode<KeyType, DataType>> prev;

	LinkListNode() : next(nullptr), prev(nullptr) {}

	LinkListNode(const KeyType &k) : Node<KeyType, DataType>(k), next(nullptr), prev(nullptr) {
		//std::cout << data << std::endl;
	}

	LinkListNode(const LinkListNode<KeyType, DataType> &rhs) : Node<KeyType, DataType>(rhs), next(rhs.next), prev(rhs.prev) {
	}

	LinkListNode<KeyType, DataType>& operator=(const LinkListNode<KeyType, DataType> &rhs) {
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
	int length;
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
	LinkList() : length(0) {
		nil = std::make_shared<Node>();
		nil->next = nil;
		nil->prev = nil;
	}

	LinkList(const LinkList<DataType> &rhs) : LinkList() {
		auto head = rhs.nil->next;
		while (head != rhs.nil) {
			Insert(head->key);
			head = head->next;
		}
	}

	LinkList<DataType>& operator=(const LinkList<DataType> &rhs) {
		auto head = nil->next;
		while (head != nil) {
			Delete(1);
			head = head->next;
		}
		head = rhs.nil->next;
		while (head != rhs.nil) {
			Insert(head->key);
			head = head->next;
		}
		return *this;
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

	void Insert(const DataType &data, std::shared_ptr<Node> p) {
		if (p) {
			auto q = std::make_shared<Node>(data);
			q->prev = p->prev;
			p->prev->next = q;
			p->prev = q;
			q->next = p;
			length ++;
		}
	}

	void Insert(const DataType &data, int index = 0) {
		auto p = get(index);
		Insert(data, p);
	}

	DataType Delete(std::shared_ptr<Node> p) {
		if (p && p != nil) {
			p->prev->next = p->next;
			p->next->prev = p->prev;
			length --;
			return p->key;
		}
		throw "error";
	}

	DataType Delete(int index) {
		auto p = get(index);
		return Delete(p);
	}


	DataType Get(int index) {
		auto p = get(index);
		if (p)
			return p->key;
		else
			throw "error";
	}

	std::shared_ptr<Node> GetHead() const {
		return nil->next;
	}

	std::shared_ptr<Node> GetTail() const {
		return nil->prev;
	}

	int Length() const {
		return length;
	}
};
