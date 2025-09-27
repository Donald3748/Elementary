#pragma once
#include<stdexcept>
template<typename T>
class Vector {
private:
	T* p;
	int insize;
public:
	Vector() :p(nullptr), insize(0) {};
	~Vector() { delete[]p; };
	void push_back(const T& value);
	T pop_back();
	bool empty()const { return !insize; }
	size_t size()const { return insize; };
	Vector<T>& operator=(const Vector<T>& x);
	T& operator[](int index) {
		if (index<0 || index > insize - 1) {
			throw std::range_error("range error");
		}
		return p[index];
	}
	T& operator[](int index)const {
		if (index<0 || index > insize - 1) {
			throw std::range_error("range error");
		}
		return p[index];
	}
};

template<typename T>
void Vector<T>::push_back(const T& value) {
	insize++;
	T* np = new T[insize];
	for (int i = 0; i < insize - 1; i++)
		np[i] = p[i];
	np[insize - 1] = value;
	delete[] p;
	p = np;
	return;
}
template<typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& x) {
	if (this == &x)
		return *this;
	delete[]p;
	p = new T[x.insize];
	insize = x.insize;
	for (int i = 0; i < x.insize; i++)
		p[i] = x.p[i];
	return *this;
}
template<typename T>
T Vector<T>::pop_back() {
	if (insize == 0) {
		throw std::range_error("range error");
	}

	T temp = p[insize - 1];
	T* np = new T[insize - 1];
	for (int i = 0; i < insize - 1; i++)
		np[i] = p[i];
	insize--;
	delete[] p;
	p = np;
	return temp;
}
#include<iostream>
int main() {

	using namespace std;
	Vector<int>a;
	cout << "hello world" << endl;
	a.push_back(2);
	cout << a[0] << endl;
	a[0] = 6;
	cout << a[0] << endl;
	cout << "hello world" << endl;
	//cout << a[-1];
	return 0;
}