#pragma once
#include<memory>
#include "LinkList.h"

template<typename DataType>
class LinkStack {
	typedef LinkList<DataType> StorageType;
	StorageType linkList;
	std::shared_ptr<LinkListNode<DataType>> top;

public:
	LinkStack() {
		top = linkList.GetHead();
	}

	~LinkStack() {}

	void Push(DataType data) {
		linkList.Insert(data);
		top = linkList.GetHead();
	}

	bool IsEmpty() const {
		return linkList.IsEmpty();
	}

	DataType Pop() {
		if (!IsEmpty()) {
			DataType data = top->data;
			linkList.Delete(1);
			top = linkList.GetHead();
			return data;
		}
		else
			throw "Stack::栈空";
	}

	DataType GetTop() const {
		if (!IsEmpty())
			return top->data;
		else
			throw "Stack::栈空";
	}

	LinkStack(const LinkStack<DataType> &rhs) : linkList(rhs.linkList) {
		top = linkList.GetHead();
	}

	LinkStack<DataType>& operator=(const LinkStack<DataType>& rhs) {
		linkList = rhs.linkList;
		top = linkList.GetHead();
		return *this;
	}

	LinkStack(DataType *data_list, int size): LinkStack() {
		for (int i = 0; i < size; i ++) {
			Push(data_list[i]);
		}
	}
};