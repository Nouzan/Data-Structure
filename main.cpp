#include<iostream>
#include<memory>
#include"data-structure/Stack.h"

int main(){
	Stack<int> s1, s2;
	s1.Push(1);
	s1.Push(2);
	s2 = s1;
	std::cout << s2.Pop() << std::endl;
	std::cout << s2.Pop() << std::endl;
	std::cout << s1.GetTop() << std::endl;
	return 0;
}
