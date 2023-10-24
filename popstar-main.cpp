/*2252712-信17-杨兆镇*/
#include"popstar.h"

char menu() {
	char m, n;
	cout << "--------------------------------------------" << endl;
	cout << "A.命令行找出可消除项并标识 " << endl;
	cout << "B.命令行完成一次消除（分步骤显示）" << endl;
	cout << "C.命令行完成一关（分步骤显示）" << endl;
	cout << "D.伪图形界面下用鼠标选择一个色块（无分割线）" << endl;
	cout << "E.伪图形界面下用鼠标选择一个色块（有分割线）" << endl;
	cout << "F.伪图形界面完成一次消除（分步骤）" << endl;
	cout << "G.伪图形界面完整版" << endl;
	cout << "Q.退出" << endl;
	cout << "--------------------------------------------" << endl;
	cout << "[请选择:]";
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
		cout << "设置为9x9有惊喜！！(小概率)" << endl;
	while (1) {
		cout << "请输入行数(8-10)：" << endl;
		cin >> a;
		if (cin.good() && a > 7 && a < 11)
			break;
		cin.clear();
		cin.ignore(1024, '\n');
	}
	cin.ignore(1024, '\n');
	while (1) {
		cout << "请输入列数(8-10)：" << endl;
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
	sss.x = &x;////整活专属
	cct_setcursor(3);//////    光标消失术！！！
	
	while (1) {
		*(sss.num) = 0;
		*(sss.t) = 0;////////是否移动
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
