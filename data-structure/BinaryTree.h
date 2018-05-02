#pragma once
#include<iostream>
#include<memory>
#include "Node.h"

template<typename KeyType, typename DataType=int>
class BinaryTree : Node<KeyType, DataType> {
	typedef BinaryTree<KeyType, DataType> NodeType;
	typedef std::shared_ptr<NodeType> NodePtr;
	NodePtr parent, left, right, root, self;
	static NodeType nilNode;
	static NodePtr nil;

	static void deleteNode(NodeType *n) { return; }

	NodePtr newChild(const KeyType &key) {
		auto child = std::make_shared<NodeType>(key);
		return child;
	}

	NodePtr getNodePtr() {
		if (self == nullptr) {
			self = NodePtr(this, deleteNode);
		}
		return self;
	}

public:
	BinaryTree() :
		Node<KeyType, DataType>(),
		parent(nil), right(nil), left(nil), root(nil), self(nullptr) {}
	BinaryTree(const KeyType &key) :
		Node<KeyType, DataType>(key),
		parent(nil), right(nil), left(nil), root(nil), self(nullptr) {}
	~BinaryTree() {}

	NodePtr GetRoot() {
		if (root == nil && parent == nil) {
			root = getNodePtr();
		}
		if (root->parent != nil) {
			root = parent->GetRoot();
		}
		return root;
	}

	NodePtr GetLeftChild() const {
		return left;
	}

	NodePtr GetRightChild() const {
		return right;
	}

	NodePtr SetLeftChild(KeyType key) {
		auto child = newChild(key);
		return SetLeftChild(child);
	}

	NodePtr SetRightChild(KeyType key) {
		auto child = newChild(key);
		return SetRightChild(child);
	}

	NodePtr SetLeftChild(NodePtr child) {
		if (child->parent == nil && left == nil) {
			left = child;
			child->parent = getNodePtr();
		}
		return getNodePtr();
	}
	NodePtr SetRightChild(NodePtr child) {
		if (child->parent == nil && right == nil) {
			right = child;
			child->parent = getNodePtr();
		}
		return getNodePtr();
	}

	KeyType GetKey() const {
		return this->key;
	}

};

template<typename KeyType, typename DataType>
BinaryTree<KeyType, DataType> BinaryTree<KeyType, DataType>::nilNode;

template<typename KeyType, typename DataType>
std::shared_ptr<BinaryTree<KeyType, DataType>>
BinaryTree<KeyType, DataType>::nil = NodePtr(
	&BinaryTree<KeyType, DataType>::nilNode,
	BinaryTree<KeyType, DataType>::deleteNode
);
