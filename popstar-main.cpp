/*2252712-��17-������*/
#include"popstar.h"

char menu() {
	char m, n;
	cout << "--------------------------------------------" << endl;
	cout << "A.�������ҳ����������ʶ " << endl;
	cout << "B.���������һ���������ֲ�����ʾ��" << endl;
	cout << "C.���������һ�أ��ֲ�����ʾ��" << endl;
	cout << "D.αͼ�ν����������ѡ��һ��ɫ�飨�޷ָ��ߣ�" << endl;
	cout << "E.αͼ�ν����������ѡ��һ��ɫ�飨�зָ��ߣ�" << endl;
	cout << "F.αͼ�ν������һ���������ֲ��裩" << endl;
	cout << "G.αͼ�ν���������" << endl;
	cout << "Q.�˳�" << endl;
	cout << "--------------------------------------------" << endl;
	cout << "[��ѡ��:]";
	while (1) {
		n = _getch();
		n > 96 ? m = n - 32 : m = n;
		if (m >= 'A' && m <= 'G' || m == 'Q')
			break;
	}
	cout << ' ' << n << endl << endl << endl;
	return m;
}

void input(int& a, int& b, int chc,int c[][10]) {
	srand(unsigned int(time(0)));
	if (chc == 'G')
		cout << "����Ϊ9x9�о�ϲ����(С����)" << endl;
	while (1) {
		cout << "����������(8-10)��" << endl;
		cin >> a;
		if (cin.good() && a > 7 && a < 11)
			break;
		cin.clear();
		cin.ignore(1024, '\n');
	}
	cin.ignore(1024, '\n');
	while (1) {
		cout << "����������(8-10)��" << endl;
		cin >> b;
		if (cin.good() && b > 7 && b < 11)
			break;
		cin.clear();
		cin.ignore(1024, '\n');
	}
	cin.ignore(1024, '\n');

	for (int i = 0; i < a; i++)
		for (int j = 0; j < b; j++)
			c[i][j] = rand() % 5 + 1;
	return;
}

int main()
{
	struct stc sss;
	int c1, c2, x, n = 0, num = 0, t = 0;
	int c[10][10];
	sss.c1 = &c1;
	sss.c2 = &c2;
	sss.n = &n;
	sss.num = &num;
	sss.t = &t;
	sss.x = &x;////����ר��
	cct_setcursor(3);//////    �����ʧ��������
	
	while (1) {
		*(sss.num) = 0;
		*(sss.t) = 0;////////�Ƿ��ƶ�
		sss.chc = menu();
		if (sss.chc != 'Q') {
			cct_cls();
			input(sss.a, sss.b, sss.chc, c);
		}
		for (int i = 0; i < sss.a; i++)
			for (int j = 0; j < sss.b; j++)
				c[i][j] = 3;
		switch (sss.chc) {
		case 'A':
			Aout(sss, c);
			break;
		case'B':
			Bout(sss, c);
			break;
		case'C':
			Cout(sss, c);
			break;
		case 'D':
			Dout(sss, c);
			break;
		case 'E':
			Eout(sss, c);
			break;
		case 'F':
			Fout(sss, c);
			break;
		case 'G':
			GioGio(sss, c);
			break;
		}
		to_be_continued();
		cct_cls();
		if (sss.chc == 'Q')
			break;
	}
	

  
	return 0;
}
