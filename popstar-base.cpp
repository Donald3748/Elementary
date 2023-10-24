/*2252712-信17-杨兆镇*/
#include"popstar.h"



void inawake(struct stc sss) {
	char in[3];
	int i, j;
	while (1) {
		cout << endl << "请输入字母+数字形式[例如:c2]输入矩阵坐标：";
		for (int i = 0; i < 3; i++)
			if ((in[i] = _getche()) == '\r')
				break;
		in[0] > 96 ? in[0] -= 32 : 1;
		i = in[0] - 65;
		j = in[1] - 48;
		if (in[0] >= 'A' && in[0] <= sss.a + 64 && in[1] >= '0' && in[1] <= sss.b + 47) {
			cout << endl << "输入为" << in[0] << "行" << in[1] - 48 << "列" << endl;
			break;
		}
		else 
			cout << endl<< "输入错误，请重新输入.";
	}
	*(sss.c1) = i;
	*(sss.c2) = j;
	
	return;
}

void frameless(struct stc sss, int c[][10], int s) {
	int n = 0;
	for (int i = 0; i < sss.a; i++)
		for (int j = 0; j < sss.b; j++)
			c[i][j] >= 10 ? n++ : 1;
	for (int i = 0; i < sss.b; i++)
		cout << i << "  ";
	cout << endl;
	cout << "--+" << setw(3 * sss.b + 1) << setfill('-') << '-' << endl;
	for (int i = 0; i < sss.a; i++) {
		cout << char(i + 65) << " |";
		for (int j = 0; j < sss.b; j++) {
			cout << "  ";
			if (s == 1) {
				if ((n != 0 && c[i][j] >= 10) || (n == 0 && c[i][j] == 0))
					cct_setcolor(14, 0);
				cout << c[i][j] % 10;
				cct_setcolor(0, 7);
			}
			if (s == 0)
				cout << (c[i][j] > 10 ? '*' : '0');
		}
		cout << endl;
	}
	cout << endl;
	return;
}

void Aout(struct stc sss, int c[][10]) {
	cout << endl << "当前数组" << endl << "  |  ";
	frameless(sss, c, 1);
	int x, y;

	while (1) {
		*(sss.n) = 1;
		inawake(sss);
		x = *(sss.c1);
		y = *(sss.c2);
		find_cure(sss, c, x, y);
		if (*(sss.n) != 1)
			break;
		else
			cout << "输入的矩阵坐标处无连续相同值，请重新输入";
		c[x][y] -= 10;
	}
	cout << endl << "查找结果数组" << endl << "  |  ";
	frameless(sss, c, 0);
	cout << endl << "当前数组(不同色标识)" << endl << "  |  ";
	frameless(sss, c, 1);
	
	
	return;
}

char Bout(struct stc sss, int c[][10]) {
	char s;
	int x, y;
	Aout(sss, c);

	
	cout << endl << "请输入是否把" << char(*(sss.c1) + 65) << *(sss.c2);
	cout << "及周围的相同值消除(Y/N/Q)：";
	cct_getxy(x, y);
	while (1) {
		cct_gotoxy(x, y);
		s = _getche();
		s > 96 ? s -= 32 : 1;
		if (s == 'Y' || s == 'N' || s == 'Q')
			break;
	}
	if (s == 'Y') {
		cout << endl << "相同值归并后的数组(不同色标识):" << endl << "  |  ";
		cure_cure(sss, c, 2);//////////////////
		frameless(sss, c, 1);
		*(sss.num) += 5 * *(sss.n) * *(sss.n);
		cout << "本次得分：" << 5 * *(sss.n) * *(sss.n);
		cout << " 总得分：" << *(sss.num) << endl << endl;
		cure_cure(sss, c, 1);
		to_the_floor(sss, c);
		darkside(sss, c);
		cout << "按回车键进行数组下落操作...";
		while (_getch() != '\r');
		cout << endl << "下落后的数组:" << endl << "  |  ";
		frameless(sss, c, 1);
	}
	return s;
}

void Cout(struct stc sss, int c[][10]) {
	char s;
	while (1) {
		s = Bout(sss, c);
		if (s == 'Y') {
			cout << endl << "本次消除结束，按回车键继续新一次的消除..." << endl;
			while (_getch() != '\r');
		}
		if (s == 'N') 
			cure_cure(sss, c, 0);

		if (!justice(sss, c) || s == 'Q')
			break;
	}
	if (s != 'Q') {
		int nn = 0;
		for (int i = 0; i < sss.a; i++)
			for (int j = 0; j < sss.b; j++)
				c[i][j] != 0 ? nn++ : 1;
		cct_setcolor(0, 14);
		cout << "恭喜您！只剩" << nn << "颗★ ！本关结束！";
		cct_setcolor(0, 7);
	}
	return;
}
