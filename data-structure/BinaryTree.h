#pragma once
#include<iostream>
#include<memory>
#include "Node.h"
#include "LinkQueue.h"

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

public:
	BinaryTree() :
		Node<KeyType, DataType>(),
		parent(nil), right(nil), left(nil), root(nil), self(nullptr) {}
	BinaryTree(const KeyType &key) :
		Node<KeyType, DataType>(key),
		parent(nil), right(nil), left(nil), root(nil), self(nullptr) {}
	~BinaryTree() {}

	NodePtr GetNodePtr() {
		if (self == nullptr) {
			self = NodePtr(this, deleteNode);
		}
		return self;
	}

	NodePtr GetRoot() {
		if (root == nil && parent == nil) {
			root = GetNodePtr();
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

	NodePtr GetParent() const {
		return parent;
	}

	NodePtr SetLeftChild(KeyType key) {
		auto child = newChild(key);
		return SetLeftChild(child);
	}

	NodePtr SetRightChild(KeyType key) {
		auto child = newChild(key);
		return SetRightChild(child);
	}

	NodePtr SetLeftChild(NodeType &childNode) {
		auto child = childNode.GetNodePtr();
		return SetLeftChild(child);
	}

	NodePtr SetRightChild(NodeType &childNode) {
		auto child = childNode.GetNodePtr();
		return SetRightChild(child);
	}

	NodePtr SetLeftChild(NodePtr child) {
		if (child->parent == nil && left == nil) {
			left = child;
			child->parent = GetNodePtr();
		}
		return GetNodePtr();
	}
	NodePtr SetRightChild(NodePtr child) {
		if (child->parent == nil && right == nil) {
			right = child;
			child->parent = GetNodePtr();
		}
		return GetNodePtr();
	}

	KeyType GetKey() const {
		return this->key;
	}

	void PreOrderPrint(NodePtr node = nullptr) {
		if (node == nullptr) {
			node = GetNodePtr();
		}
		if (node != nil) {
			std::cout << node->GetKey();
			PreOrderPrint(node->left);
			PreOrderPrint(node->right);
		}
	}

	void MidOrderPrint(NodePtr node = nullptr) {
		if (node == nullptr) {
			node = GetNodePtr();
		}
		if (node != nil) {
			MidOrderPrint(node->left);
			std::cout << node->GetKey();
			MidOrderPrint(node->right);
		}
	}

	void PostOrderPrint(NodePtr node = nullptr) {
		if (node == nullptr) {
			node = GetNodePtr();
		}
		if (node != nil) {
			PostOrderPrint(node->left);
			PostOrderPrint(node->right);
			std::cout << node->GetKey();
		}
	}

	void LevelOrderPrint(NodePtr node = nullptr) {
		LinkQueue<NodePtr> queue;
		if (node == nullptr) {
			node = GetNodePtr();
		}
		queue.EnQueue(node);
		while (!queue.IsEmpty()) {
			auto tmp = queue.DeQueue();
			if (tmp != nil) {
				std::cout << tmp->GetKey();
				queue.EnQueue(tmp->left);
				queue.EnQueue(tmp->right);
			}
		}
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
