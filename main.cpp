#include<iostream>
#include<memory>
#include "data-structure/Stack.h"
#include "data-structure/Queue.h"
#include "data-structure/LinkList.h"
#include "data-structure/Node.h"
#include "data-structure/LinkStack.h"
#include "data-structure/LinkQueue.h"
#include "data-structure/BinaryTree.h"

void testBinaryTree() {
	BinaryTree<int> T[11] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
	T[0].SetLeftChild(T[1])->SetRightChild(T[2]);
	T[1].SetRightChild(T[3]);
	T[2].SetLeftChild(T[4])->SetRightChild(T[5]);
	T[3].SetLeftChild(T[6])->SetRightChild(T[7]);
	T[4].SetRightChild(T[8]);
	T[5].SetLeftChild(T[9]);
	T[8].SetLeftChild(T[10]);
	T[0].PreOrderPrint();
	std::cout << std::endl;
	T[0].MidOrderPrint();
	std::cout << std::endl;
	T[0].PostOrderPrint();
	std::cout << std::endl;
	T[0].LevelOrderPrint();
	std::cout << std::endl;
}

void testQueue1() {
	Queue<int> queue(5);
	for(;;) {
		int c, data;
		std::cin >> c;
		switch (c) {
			case 0:
				return;
			case 1:
				std::cin >> data;
				queue.EnQueue(data);
				std::cout << "EnQueue: " << data << std::endl;
				break;
			case 2:
				std::cout << "DeQueue: " << queue.DeQueue() << std::endl;
				break;
			case 3:
				std::cout << "IsEmpty: " << queue.IsEmpty() << std::endl;
				break;
			case 4:
				std::cout << "IsFull: " << queue.IsFull() << std::endl;
			default:
				;
		}
	}
}

void testQueue2() {
	Queue<int> q1, q2;
	q1.EnQueue(1);
	q1.EnQueue(2);
	q2 = q1;
	Queue<int> q3(q1);
	std::cout << q2.DeQueue() << std::endl;
	std::cout << q3.DeQueue() << std::endl;
}

void testNode() {
	Node<int> n(1, 1);
	n.Print();
}

void testStack() {
	Stack<int> s;
	for(;;) {
		int c, data;
		std::cin >> c;
		switch (c) {
			case 0:
				return;
			case 1:
				std::cin >> data;
				s.Push(data);
				std::cout << "Push: " << data << std::endl;
				break;
			case 2:
				std::cout << "Pop: " << s.Pop() << std::endl;
				break;
			case 3:
				std::cout << "IsEmpty: " << s.IsEmpty() << std::endl;
				break;
			case 4:
				std::cout << "IsFull: " << s.IsFull() << std::endl;
			default:
				;
		}
	}
}

void testLinkList1() {
	LinkList<char> l;
	for(;;) {
		int c, arg1;
		char arg2;
		std::cin >> c;
		switch (c) {
			case 0:
				return;
			case 1:
				std::cin >> arg1 >> arg2;
				l.Insert(arg2, arg1);
				std::cout << "Insert: " << arg2 << " At: " << arg1 << std::endl;
				break;
			case 2:
				std::cin >> arg1;
				std::cout << "Delete: " << l.Delete(arg1) << " At: " << arg1 << std::endl;
				break;
			case 3:
				std::cout << "IsEmpty: " << l.IsEmpty() << std::endl;
				break;
			case 4:
				std::cin >> arg1;
				std::cout << "Got: " << l.Get(arg1) << " At: " << arg1 << std::endl;
				break;
			default:
				;
		}
	}
}

void testLinkList2() {
	LinkList<int> l1, l2;
	l1.Insert(1);
	l2.Insert(2);
	std::cout << l2.Get(1) << std::endl;
	l2 = l1;
	std::cout << l2.Get(1) << std::endl;
	LinkList<int> l3(l1);
	std::cout << l3.Get(1) << std::endl;
}

void testLinkStack() {
	LinkStack<int> s;
	for(;;) {
		int c, data;
		std::cin >> c;
		switch (c) {
			case 0:
				return;
			case 1:
				std::cin >> data;
				s.Push(data);
				std::cout << "Push: " << data << std::endl;
				break;
			case 2:
				std::cout << "Pop: " << s.Pop() << std::endl;
				break;
			case 3:
				std::cout << "IsEmpty: " << s.IsEmpty() << std::endl;
				break;
			case 4:
				std::cout << "Top: " << s.GetTop() << std::endl;
			default:
				;
		}
	}
}

void testLinkQueue1() {
	LinkQueue<int> queue;
	for(;;) {
		int c, data;
		std::cin >> c;
		switch (c) {
			case 0:
				return;
			case 1:
				std::cin >> data;
				queue.EnQueue(data);
				std::cout << "EnQueue: " << data << std::endl;
				break;
			case 2:
				std::cout << "DeQueue: " << queue.DeQueue() << std::endl;
				break;
			case 3:
				std::cout << "IsEmpty: " << queue.IsEmpty() << std::endl;
				break;
			case 4:
				std::cout << "Head: " << queue.GetHead() << std::endl;
			default:
				;
		}
	}
}

int main() {
	testBinaryTree();
	return 0;
}
