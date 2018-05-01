#pragma once
#include<iostream>
#include<memory>

template<typename KeyType, typename DataType=int>
struct Node {
	KeyType key;
	DataType data;

	Node()=default;
	Node(const KeyType &k, const DataType &d) : key(k), data(d) {}
	Node(const Node<KeyType, DataType> &rhs) {
		key = rhs.key;
		data = rhs.data;
	}
	Node(const KeyType &k) : key(k) {}
	Node<KeyType, DataType>& operator=(const Node<KeyType, DataType> &rhs) {
		key = rhs.key;
		data = rhs.data;
		return *this;
	}
	Node<KeyType, DataType>& operator=(const KeyType &k) {
		key = k;
		return *this;
	}
	void Print() {
		std::cout << "Node<" << key << ", " << data << '>' << std::endl;
	}
};
