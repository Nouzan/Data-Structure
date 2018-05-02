#pragma once
#include<iostream>
#include<memory>
#include "Node.h"

template<typename KeyType, typename DataType=int>
struct BinaryTreeNode : Node<KeyType, DataType> {
	typedef std::shared_ptr<BinaryTreeNode<KeyType, DataType>> NodePtr;
	std::shared_ptr<BinaryTreeNode<KeyType, DataType>> left, right, parent;
	BinaryTreeNode(const KeyType &k) : Node<KeyType, DataType>(k), parent(nullptr), left(nullptr), right(nullptr) {}
	BinaryTreeNode(const BinaryTreeNode<KeyType, DataType> &rhs) : Node<KeyType, DataType>(rhs), parent(rhs.parent), left(rhs.parent), right(rhs.parent) {}
	BinaryTreeNode(
		std::shared_ptr<BinaryTreeNode<KeyType, DataType>> p = nullptr,
		std::shared_ptr<BinaryTreeNode<KeyType, DataType>> l = nullptr,
		std::shared_ptr<BinaryTreeNode<KeyType, DataType>> r = nullptr
	) : Node<KeyType, DataType>(), parent(p), left(l), right(r) {}
	BinaryTreeNode<KeyType, DataType>&
	operator=(const BinaryTreeNode<KeyType, DataType> &rhs) {
		this->data = rhs.data;
		this->key = rhs.key;
		parent = rhs.parent;
		left = rhs.left;
		right = rhs.right;
		return *this;
	}

	//绑定parent, left, right
	BinaryTreeNode<KeyType, DataType>&
	Bind(
		std::shared_ptr<BinaryTreeNode<KeyType, DataType>> p = nullptr,
		std::shared_ptr<BinaryTreeNode<KeyType, DataType>> l = nullptr,
		std::shared_ptr<BinaryTreeNode<KeyType, DataType>> r = nullptr
	) {
		parent = p;
		left = l;
		right = r;
		return *this;
	}

	NodePtr SetLeftChild(NodePtr l) {
		left = l;
		if (l != nil)
			l->parent = node;
		return node;
	}

	NodePtr SetRightChild(NodePtr node, NodePtr right) {
		node->right = right;
		if (right != nil)
			right->parent = node;
		return node;
	}
}


template<typename KeyType>
class BinaryTree {
	typedef BinaryTreeNode<KeyType> Node;
	typedef std::shared_ptr<Node> NodePtr;
	std::shared_ptr<Node> nil;  //哨兵
	std::shared_ptr<Node> root;  //根结点

	//摧毁树
	void destoryTree(std::shared_ptr<Node> rt) {
		if (rt != nil) {
			auto left = rt->left;
			auto right = rt->right;
			rt.reset();
			destoryTree(left);
			destoryTree(right);
		}
	}

	//寻找结点
	std::shared_ptr<Node> get const (const KeyType &key, std::shared_ptr<Node> rt = root) {
		if (rt == nil) {
			return nil;
		}
		if (rt->key == key) {
			return rt;
		} else {
			auto left = get(key, rt->left);
			if (left != nil) {
				return left;
			}
			auto right = get(key, rt->right);
			if(right != nil) {
				return right;
			}
		}
	}


public:
	BinaryTree() {
		nil = std::make_shared<Node>();
		nil->Bind(nil, nil, nil);
		root = nil;
	}

	BinaryTree(const KeyType &k) : BinaryTree() {
		root = NewNode(k);
	}

	std::shared_ptr<Node> SetRoot(NodePtr node) {

	}

	std::shared_ptr<Node> NewNode(
		const KeyType &key,
		std::shared_ptr<Node> p = nil,
		std::shared_ptr<Node> l = nil,
		std::shared_ptr<Node> r = nil
	) {
		auto node = std::make_shared<Node>(p, l, r);
		node->key = key;
		return node;
	}

	~BinaryTree() {
		destoryTree(root);
	}

};
