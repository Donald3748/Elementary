#include<iostream>
using std::istream;
using std::ostream;

class String {
private:
	friend istream& operator>>(istream& in, String& a);
	char* p;
	int insize;
public:
	String() :p(nullptr), insize(0) { };
	String(const char* s);
	~String() { delete[] p; }
	int size()const { return insize; };
	String& operator+=(char a);
	String& operator+=(const char* s);
	String& operator+=(const String& a);
	String& operator=(const char* s);
	String& operator=(const String& a);
	bool operator==(const String& s)const;
	bool operator!=(const String& s)const { return !(*this == s); };
	char& operator[](int i) { return p[i]; };
	char& operator[](int i)const { return p[i]; };
};
String::String(const char* s) {
	insize = int(strlen(s));
	char* np = new char[insize + 1];
	strcpy(np, s);
	delete[]p;
	p = np;
}
String& String::operator+=(const char* s) {
	String tmp(s);
	(*this) += tmp;
	return *this;
}
String& String::operator+=(const String& a) {
	insize += a.size();
	char* np = new char[insize + 1];
	if (p != nullptr)
		strcpy_s(np, insize + 1, p);
	strcat_s(np, insize + strlen(a.p) + 2, a.p);

	delete[]p;
	p = np;
	return *this;
}
String& String::operator+=(char a) {
	insize += 1;
	char* np = new char[insize + 1];
	if (p != nullptr)
		strcpy_s(np, insize + 1, p);
	np[insize - 1] = a;
	np[insize] = '\0';
	if (p != nullptr)
		delete[]p;
	p = np;
	return *this;
}
String& String::operator=(const char* s) {
	String tmp(s);
	*this = tmp;
	return(*this);
}
String& String::operator=(const String& a) {
	char* t = p;
	insize = a.insize;
	p = new char[a.insize + 1];
	for (int i = 0; i < insize; i++)
		p[i] = a[i];
	delete[]t;
	return(*this);
}
bool String:: operator==(const String& s) const {
	if (this->size() != s.size()) return false;
	for (int i = 0; i < s.size(); i++)
		if (s[i] != p[i]) return false;
	return true;
}
ostream& operator<<(ostream& out, const String& a) {
	for (int i = 0; i < a.size(); i++)
		out << a[i];
	return out;
}
istream& operator>>(istream& in, String& a) {
	char t = 's';
	a.~String();
	while (1) {
		t = getchar();
		if (t == '\n') break;
		a += t;
	}
	return in;
}

int main() {
	using namespace std;
	String a;
	String b;
	cin >> a;
	cin >> b;
	cout << a << endl;
	a += b;
	cout << a;
	return 0;
}