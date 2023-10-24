/*2252712-信17-杨兆镇*/
#include"popstar.h"









void find_cure(struct stc sss, int c[][10], int x, int y) {
	int tmp = c[x][y];
	if (c[x][y] > 0 && c[x][y] < 10) {
		if (x != 0)
			if (c[x - 1][y] == c[x][y]) {
				c[x][y] += 10;
				find_cure(sss, c, x - 1, y);
				c[x][y] = tmp;
				*(sss.n) += 1;
			}
		if (x != sss.a - 1)
			if (c[x + 1][y] == c[x][y]) {
				c[x][y] += 10;
				find_cure(sss, c, x + 1, y);
				c[x][y] = tmp;
				*(sss.n) += 1;
			}
		if (y != 0)
			if (c[x][y - 1] == c[x][y]) {
				c[x][y] += 10;
				find_cure(sss, c, x, y - 1);
				c[x][y] = tmp;
				*(sss.n) += 1;
			}
		if (y != sss.b - 1)
			if (c[x][y + 1] == c[x][y]) {
				c[x][y] += 10;
				find_cure(sss, c, x, y + 1);
				c[x][y] = tmp;
				*(sss.n) += 1;
			}
	}
	c[x][y] += 10;
	return;
}///////////////////////////////////n为消除个数

void to_the_floor(struct stc sss, int c[][10]) {
	int tmp, t = sss.b;
	int ttmp;
	for (int j = 0; j < sss.b; j++)
		for (int i = sss.a - 1; i > 0; i--) {
			if (c[i][j] == 0 && i != 0) {
				tmp = i;
				while (c[tmp][j] == 0 && tmp > 0)
					tmp--;
				if (c[tmp][j] == 0)
					continue;
				if (sss.chc == 'D')
					for (int t = 0; t < 3 * (i - tmp); t++) {
						Sleep(1);
						starfloat(6 * j + 5, 3 * tmp + 5 + t, c[tmp][j], 0);
						cct_showch(6 * j + 4, 3 * tmp + 3 + t, ' ', 15, 15, 6);
					}
				if (sss.chc == 'E')
					for (int t = 0; t < 4 * (i - tmp); t++) {
						Sleep(1
						);
						starfloat(8 * j + 5, 4 * tmp + 5 + t, c[tmp][j], 0);
						if ((4 * tmp + 3 + t) % 4 != 2)
							cct_showch(8 * j + 4, 4 * tmp + 3 + t, ' ', 15, 15, 6);
						else {
							cct_gotoxy(8 * j + 4, 4 * tmp + 3 + t);
							cct_setcolor(15, 0);
							cout << "═══";
						}

					}
				ttmp = c[tmp][j];
				c[tmp][j] = c[i][j];
				c[i][j] = ttmp;
			}
		}


	return;
}

void darkside(struct stc sss, int c[][10]) {

	int n, t = sss.b;
	int ttmp;
	for (int j = 0; j < t; j++) {
		n = 0;
		for (int i = 0; i < sss.a; i++)
			c[i][j] == 0 ? n++ : 1;
		if (n == sss.a) {
			for (int k = j--; k < t - 1; k++)
				for (int i = sss.a - 1; i >= 0 && c[i][k + 1] != 0; i--) {
					if (sss.chc == 'D')
						for (int m = 5; m >= 0; m--) {
							Sleep(1);
							starfloat(6 * k + 5 + m, 3 * i + 4, c[i][k + 1], 0);
							cct_showch(6 * k + 10 + m, 3 * i + 3, ' ', 15, 15, 1);
							cct_showch(6 * k + 10 + m, 3 * i + 4, ' ', 15, 15, 1);
							cct_showch(6 * k + 10 + m, 3 * i + 5, ' ', 15, 15, 1);
						}
					if (sss.chc == 'E') {
						for (int m = 7; m >= 0; m--) {
							Sleep(1);
							starfloat(8 * k + 5 + m, 4 * i + 4, c[i][k + 1], 0);
							cct_showch(8 * k + 10 + m, 4 * i + 3, ' ', 15, 15, 1);
							cct_showch(8 * k + 10 + m, 4 * i + 4, ' ', 15, 15, 1);
							cct_showch(8 * k + 10 + m, 4 * i + 5, ' ', 15, 15, 1);
						}
						cct_setcolor(15, 0);
						cct_gotoxy(8 * k + 10, 4 * i + 3);
						cout << "║";
						cct_gotoxy(8 * k + 10, 4 * i + 4);
						cout << "║";
						cct_gotoxy(8 * k + 10, 4 * i + 5);
						cout << "║";
					}
					ttmp = c[i][k];
					c[i][k] = c[i][k + 1];
					c[i][k + 1] = ttmp;
				}
			t--;
		}
	}



}

void cure_cure(struct stc sss, int c[][10], int sec) {
	for (int i = 0; i < sss.a; i++)
		for (int j = 0; j < sss.b; j++)
			if (c[i][j] >= 10)
				switch (sec) {
				case 0:
					c[i][j] %= 10;//////////////////0代表恢复
					break;
				case 1:
					c[i][j] = 0;////////////////////1代表清零
					break;
				case 2:
					c[i][j] = 10;///////////////////2代表一半清零
					break;
				}
				
	return;
}///////////sce=0代表取消操作，全变为数字，sec=1代表允许清零,sec=2代表绕一圈先

int  justice(struct stc sss, int c[][10]) {
	int n = 0;
	for (int x = 0; x < sss.a; x++)
		for (int y = 0; y < sss.b; y++) {
			if (x != 0 && c[x][y] != 0)
				if (c[x - 1][y] == c[x][y]) 
					n++;
			if (x != sss.a - 1 && c[x][y] != 0)
				if (c[x + 1][y] == c[x][y])
					n++;
			if (y != 0 && c[x][y] != 0)
				if (c[x][y - 1] == c[x][y])
					n++;
			if (y != sss.b - 1 && c[x][y] != 0)
				if (c[x][y + 1] == c[x][y])
					n++;
		}

	return n;
}////////////////////0代表游戏结束,   其它正数代表尚有相邻

void to_be_continued() {
	char in[4];
	int r, c;
	cout << endl << endl << "本小题结束，请输入End继续...";
	cct_getxy(r, c);
	while (1) {
		cct_gotoxy(r, c);
		cout << "              ";
		cct_gotoxy(r, c);
		cin.clear();
		cin.getline(in, 4, '\n');
		for (int i = 0; i < 4; i++)
			in[i] > 96 ? in[i] -= 32 : 1;
		if (in[0] == 'E' && in[1] == 'N' && in[2] == 'D')
			break;
		else {
			cct_gotoxy(0, c + 1);
			cout << "输入错误，请重新输入.";
		}
	}
	return;
}

int landslide(struct stc sss, int c[][10]) {
	int s;
	if (sss.a != 9 || sss.b != 9)
		return 0;
	srand(unsigned int(time(0)));
	s = rand() % 20 + 1;
	//  1.常规输入  概率85%
	if (s < 18)
		for (int i = 0; i < sss.a; i++)
			for (int j = 0; j < sss.b; j++)
				c[i][j] = rand() % 5 + 1;

	//  2.天青色(很好看)  概率5%
	if (s == 18)
		for (int i = 0; i < sss.a; i++)
			for (int j = 0; j < sss.b; j++)
				c[i][j] = 3;
	//  3.弯曲的  概率5%
	if (s == 19)
		for (int i = 0; i < sss.a; i++) {
			for (int j = 0; j < sss.b; j++)
				c[i][j] = 4;

			if (i % 2 == 0)
				for (int j = 0; j < sss.b; j++)
					c[i][j] = 1;
			else if (i % 4 == 1)
				c[i][0] = 1;
			else if (i % 4 == 3)
				c[i][sss.b - 1] = 1;

		}

	//  4.玩原神玩的  概率5%
	if (s == 20) {
		for (int i = 0; i < sss.a; i++)
			for (int j = 0; j < sss.b; j++)
				c[i][j] = 7;
		for (int i = 2; i < 7; i++)
			c[i][0] = 6;
		for (int i = 2; i < 7; i++)
			c[i][3] = 6;
		for (int i = 2; i < 7; i++)
			c[i][5] = 6;
		for (int i = 2; i < 5; i++)
			c[i][8] = 6;
		for (int i = 1; i < 3; i++)
			c[2][i] = 6;
		for (int i = 1; i < 3; i++)
			c[6][i] = 6;
		for (int i = 6; i < 8; i++)
			c[2][i] = 6;
		for (int i = 6; i < 8; i++)
			c[2][i] = 6;
		for (int i = 6; i < 8; i++)
			c[4][i] = 6;
	}
	
	cct_setcolor(0, 7);
	return s;
}


