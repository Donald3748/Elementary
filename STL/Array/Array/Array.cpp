#include<iostream>
using namespace std;

template<typename T>
class Array {
private :
	int Arraysize;
	T* p;
	void get_Array();
public:
	Array() :Arraysize(0), p(new T[0]) {};
	Array(int size);
	Array(const Array<T>& x);
	~Array() { delete[]p; };
	Array<T>& operator=(const Array<T>& x);////?
	T& operator[](int i);
	int length() { return Arraysize; };
};

template<typename T>
void Array<T>::get_Array() {
	p = new T[Arraysize];
	if (p == 0) {
		Arraysize = 0;
		cerr << "Memory allocation failure!" << endl;
	}
	return;
}

template<typename T>
 Array<T>::Array(int size) {
	 if (size <= 0) {
		 cout << "input failure" << endl;
		 Arraysize = 0;
		 p = NULL;
		 return;
	}
	
	 Arraysize = size;
	 get_Array();
	 return;

}

 template<typename T>
 Array<T>::Array(const Array<T>& x) {
	 if (x.Arraysize <= 0) {
		 cerr << "failure!" << endl;
		 return;
	 }
	 int n = Arraysize = x.Arraysize;
	 get_Array();
	 T* p1 = p;
	 T* p2 = x.p;
	 while (n--) *(p1++) = *(p2)++;
 }

 template<typename T>
 Array<T>& Array<T>::operator=(const Array<T>& x) {
	 if (x.Arraysize < 0) {
		 cerr << "failure! index size zero" << endl;
		 return *this;
	 }
	 int n = Arraysize = x.Arraysize;
	 T* p1 = p;
	 T* p2 = x.p;
	 get_Array();
	 while (n--) *(p1++) = *(p2++);
	 return *this;
 }


 template<typename T>
 T& Array<T>::operator[](int i) {
	 if (i > Arraysize - 1 || i < 0) {
		 cerr << "range error! too wide or minus" << endl;
		return;
	 }
	 return p[i];
 }

 int main() {
	 Array<int>a(3);
	 Array<int>x(a);
	 Array<int>s;
	 s = a;
	 cout << s.length() << endl;
	 return 0;
 }