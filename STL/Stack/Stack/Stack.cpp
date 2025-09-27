#pragma once

#include<iostream>

template<typename T>
class StackNode {
	template<typename T>
	friend class Stack;
private:
	T data;
	StackNode<T>* link;
};
/*带底(尾)节点版*/
template<typename T>
class Stack {
private:
	StackNode<T>* top_;
	StackNode<T>* end;
public:
	Stack() { top_ = end = new StackNode<T>(); }
	~Stack();
	void push(T x);
	void pop();
	T top();
	void display() {
		StackNode<T>* p = top_; while (p != end) { std::cout << p->data << ' ';  p = p->link; }
	}
	bool empty() { return top_ == end; }
};
template<typename T>
Stack<T>::~Stack() {
	while (!(this->empty())) {
		this->pop();
	}
	delete top_;
}
/*子函数1：push*/
template<typename T>
void Stack<T>::push(T x) {
	StackNode<T>* p = new StackNode<T>();
	p->data = x;
	p->link = top_;
	top_ = p;
}
template <typename T>
void Stack<T>::pop() {
	if (top_ == end) {
		std::cerr << "error,current stack is empty";
		return;
	}
	StackNode<T>* q = top_;
	top_ = top_->link;
	delete q;
	return;
}
template<typename T>
T Stack<T>::top() {
	
	if (top_ == end)
		throw("error");
	
	return top_->data;
}

int main() {

	try {
		Stack<int>a;
		std::cout << a.top() << std::endl;
		a.push(2);
	}
	catch (...) {
		std::cout << "world" << std::endl;
	}
	
}