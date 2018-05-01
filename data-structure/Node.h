#pragma once
#include<iostream>
#include<memory>

template<typename DataType, typename KeyType=int>
struct Node {
	KeyType key;
	DataType data;

	Node()=default;
	Node(const KeyType &k, const DataType &d) : key(k), data(d) {}
	Node(const Node<DataType, KeyType> &rhs) {
		key = rhs.key;
		data = rhs.data;
	}
	Node(const DataType &d) : data(d) {}
	Node<DataType, KeyType>& operator=(const Node<DataType, KeyType> &rhs) {
		key = rhs.key;
		data = rhs.data;
		return *this;
	}
	Node<DataType, KeyType>& operator=(const DataType &d) {
		data = d;
		return *this;
	}
	void Print() {
		std::cout << "Node<" << key << ", " << data << '>' << std::endl;
	}
};
