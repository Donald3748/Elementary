#pragma once
template<typename T>
class List;
template<typename T>
class List_iterator;

/*类模板定义：ListNode*/
template<typename T>
class ListNode {
	friend class List<T>;
	friend class List_iterator<T>;
private:
	T data;
	ListNode<T>* link;
public:
	ListNode() :data(), link(nullptr) {};
	ListNode(T input, ListNode<T>* p) :data(input), link(p) {};
	ListNode(const ListNode<T>* a) :data(a->data), link(a->link) {};
};
/*类模板定义：链表迭代器*/
template<typename T>
class List_iterator {
	friend class List<T>;
private:
	ListNode<T>* p;
	const List<T>& l;
	List_iterator(ListNode<T>* a, const List<T>& p) :p(a), l(p) {};
public:
	List_iterator(const List_iterator<T>& a) :p(a.p), l(a.l) {};
	List_iterator<T> operator ++(int) { List_iterator next_p(*this); p = p->link; return next_p; }
	List_iterator<T>& operator ++() { p = p->link; return *this; }
	T operator *() const { return p->data; }
	bool operator == (const List_iterator<T>& a)const { return p == a.p; }
	bool operator != (const List_iterator<T>& a)const { return p != a.p; }
	List_iterator<T>& operator = (const List_iterator<T>& a) { if (l.first != a.l.first) throw("error"); p = a.p; return *this; }
};
/*类模板定义：List*/
/*修正：带尾节点版*/
template<typename T>
class List {
	friend class List_iterator<T>;
private:
	ListNode<T>* first;
	ListNode<T>* last;
public:
	using iterator = List_iterator<T>;
	List() { last = new ListNode<T>(); first = last; }
	~List() {
		while (first != last) {
			auto p = first;
			first = first->link;
			delete p;
		}
		delete first;
	}
	iterator insert(iterator pos, const T& input);
	iterator erase(iterator pos);
	void push_back(const T&);
	iterator begin()const { iterator a(first, *this); return a; }
	iterator end()const { iterator a(last, *this); return a; }
	int size() const;
};
/*子函数：取得当前List大小*/
template<typename T>
int List<T>::size()const {
	int a = 0;
	auto t = first;
	while (t != last) { t = t->link; a++; }
	return a;
}
/*子函数：在特定位置插入数值*/
/*在iterator pos之前插入新元素*/
template<typename T>
List_iterator<T> List<T>::insert(iterator pos, const T& x) {
	auto t = first;
	if (pos.p == first) {
		ListNode<T>* np = new ListNode<T>();
		np->data = x;
		np->link = first;
		first = np;
		return this->begin();
	}
	while (t->link != pos.p) t = t->link;
	ListNode<T>* np = new ListNode<T>();
	np->data = x;
	np->link = t->link;
	t->link = np;
	iterator it(np, pos.l);
	return it;
}
/*子函数：在特定位置删除元素*/
/*记位置pos是删除的第pos个结点，pos>0*/
template<typename T>
List_iterator<T> List<T>::erase(iterator pos) {
	if (first == last) //空列表，无法
		throw("error");
	if (pos == this->end()) //企图删除尾节点？
		throw("error");
	ListNode<T>* sp = first;
	if (first == pos.p) {
		//删除头节点
		first = first->link;
		delete sp;
		return this->begin();
	}
	while (sp->link != pos.p) sp = sp->link;
	sp->link = pos.p->link;
	delete pos.p;
	iterator it(sp->link, *this);
	return it;//返回删除位置现在的元素
}
/*子函数：在最后插入单个数值*/
template<typename T>
void List<T>::push_back(const T& x) {
	if (first == last) {
		ListNode<T>* np = new ListNode<T>();
		np->data = x;
		np->link = last;
		first = np;
		return;
	}
	ListNode<T>* np = new ListNode<T>();
	last->link = np;
	np->link = last->link;
	np->data = last->data;
	last->data = x;
	last = np;
	return;
}
#include<iostream>
#include<list>
using namespace std;
int main() {
	List<int> a;
	a.push_back(1);
	a.push_back(2);
	a.push_back(3);
	a.push_back(4);
	auto it = a.begin();
	it++;

	auto t = a.erase(it);
	cout << *t << endl;

	for (auto e : a)
		cout << e << endl;

	return 0;
}