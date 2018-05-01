#include<iostream>
#include<memory>
#include"data-structure/Stack.h"
#include "data-structure/Queue.h"

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

int main(){
	testQueue1();
	return 0;
}
