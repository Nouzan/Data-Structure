#include<memory>

template<typename T>
class Stack {
	const static int MAX_SIZE = 10000;
	std::unique_ptr<T[]> array;
	int top;

public:
	Stack() {
		top = -1;
		array.reset(new T[MAX_SIZE]);
	}

	~Stack() {
		array.release();
	}

	bool Push(T data) {
		if (top + 1 >= MAX_SIZE)
			return false;
		else {
			array[++top] = data;
			return true;
		}
	}

	bool IsEmpty() const {
		return top == -1;
	}

	T Pop() {
		if (!IsEmpty())
			return array[top--];
		else
			throw "Stack::栈空";
	}

	T GetTop() const {
		if (!IsEmpty())
			return array[top];
		else
			throw "Stack::栈空";
	}

	Stack(const Stack<T> &rhs) {
		top = -1;
		array.reset(new T[MAX_SIZE]);
		for (int i = 0; i <= rhs.top; i ++) {
			Push(rhs.array[i]);
		}
	}

	Stack<T>& operator=(const Stack& rhs) {
		top = -1;
		for (int i = 0; i <= rhs.top; i ++) {
			Push(rhs.array[i]);
		}
		return *this;
	}

	Stack(T *data_list, int size): Stack() {
		for (int i = 0; i < size; i ++) {
			Push(data_list[i]);
		}
	}
};
