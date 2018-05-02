#pragma once
#include<iostream>
#include<memory>
#include "Node.h"
#include "LinkQueue.h"

template<typename KeyType, typename DataType>
struct BinaryTreeNode : Node<KeyType, DataType> {
	typedef std::shared_ptr<BinaryTreeNode<KeyType, DataType>> NodePtr;
	NodePtr parent, left, right, root;
	BinaryTreeNode() :
		Node<KeyType, DataType>(),
		parent(nullptr),
		left(nullptr),
		right(nullptr),
		root(nullptr) {}
	BinaryTreeNode(const KeyType &key) :
		Node<KeyType, DataType>(key),
		BinaryTreeNode() {}
	BinaryTreeNode(const BinaryTreeNode<KeyType, DataType> &rhs) :
		Node<KeyType, DataType>(rhs),
		parent(rhs.parent),
		left(rhs.left),
		right(rhs.right),
		root(rhs.root) {}

	BinaryTreeNode<KeyType, DataType>&
	operator=(const BinaryTreeNode<KeyType, DataType> &rhs) {
		this->key = rhs.key;
		this->data = rhs.data;
		parent = rhs.parent;
		left = rhs.left;
		right = rhs.right;
		root = rhs.root;

		return *this;
	}

	void Bind(NodePtr p=nullptr, NodePtr l=nullptr, NodePtr r=nullptr, NodePtr rt=nullptr) {
		parent = p;
		left = l;
		right = r;
		root = rt;
	}
};

template<KeyType, DataType=int>
class BinaryTree {
	typedef BinaryTreeNode<KeyType, DataType> BinaryTreeNode;
	typedef std::shared_ptr<BinaryTreeNode> NodeType;
	NodeType node;
	static NodeType nil=nullptr;
	void initNil() {
		if (!nil) {
			nil = std::make_shared<BinaryTreeNode>();
			nil->Bind(nil, nil, nil, nil);
		}
	}

public:
	BinaryTree() {
		initNil();
		node = std::make_shared<BinaryTreeNode>();
		node->Bind(nil, nil, nil, node);
	}
	BinaryTree(const KeyType &key) {
		initNil();
		node = std::make_shared<BinaryTreeNode>(key);
		node->Bind(nil, nil, nil, node);
	}
	BinaryTree&
	SetLeftChild(const BinaryTree &child) {
		if (node->left == nil && child.node->parent == nil) {
			node->left = child.node;
			child.node->parent = node;
			child.node->root = node->root;
		}
		return *this;
	}
	BinaryTree&
	SetRightChild(const BinaryTree &child) {
		if (node->right == nil && child.node->parent == nil) {
			node->right = child.node;
			child.node->parent = node;
			child.node->root = node->root;
		}
		return *this;
	}
	BinaryTree&
	GetLeftChild() {
		return
	}

};
