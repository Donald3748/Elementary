#include<iostream>
#include<fstream>
#include<vector>
#include<list>
#include<deque>
#include<algorithm>
#include<functional>
using namespace std;

//ofstream outfile("payphine.txt");
void display(ostream& a = cout) {
	a << "ahead of us" << endl;
	return;
}

bool my_comp(int a, int b) { return a < b; };

class comp {
public:
	bool operator()(int val1, int val2) { cout << "the later is greater : "; return val1 < val2; }
	bool operator()(int val)const { cout << "local statistics:" << my << endl; return my < val; }
	explicit comp(const int& x) : my(x) {};
	explicit comp() { my = 0; };
	void display() {
		cout << "my data: " << my << endl;
	}
private:
	int my;
};




class FunctionObject {
private:
	int size;
public:
	FunctionObject(const int& initial) :size(initial) {}
	FunctionObject() :size(0) {}
	void display() { cout << "display size=" << size << endl; }
	bool operator()(const int& x) { return x < size; }
	bool operator()(const int& val1, const int& val2) { return val1 < val2; }
	friend FunctionObject& bind2nd(const FunctionObject&a, int val);
};
FunctionObject& bind2nd(const FunctionObject &a, int val) {
	FunctionObject F;
	F(5);
	return F;
}
template<typename T1, typename T2, typename TFO>
void find_x(T1 i1, const T2& i2, TFO F) {
	for (; i1 != i2; ++i1)
		if (F(*i1)) cout << "success! " << *i1 << endl;
}
int main() {
	typedef FunctionObject FO;
	int s[13] = { 1,2,3,4,5,6,7,8,9,10,11,12,13 };
	vector<int>a(s, s + 13);
	vector<int>::iterator it = a.begin();
	FO tmp(5);
	find_x(it, a.end(), FO(6));
	cout << "-----------------" << endl;
	find_x(it, a.end(), tmp);
	cout << "-----------------" << endl;
	find_x(it, a.end(), bind2nd(tmp, 5));
	return 0;
}
