/*2252712-信17-杨兆镇*/
#include"popstar.h"


/*fg_color：0 - 7    黑    蓝   绿   青   红  粉   黄   白
			8 - 15 亮黑 亮蓝 亮绿 亮青 亮红 亮粉 亮黄 亮白
bg_color：0 - 7    黑   蓝   绿   青   红   粉   黄   白
		  8 - 15 亮黑 亮蓝 亮绿 亮青 亮红 亮粉 亮黄 亮白

		  cct_setcolor(0, 7);表示正常显色
		  0 黑 7 白 15 亮白
*/

void starfloat(int x, int y, int bg_color, int ff) {
	cct_setcolor(bg_color + 8, ff);
	cct_gotoxy(x - 1, y - 1);
	cout << "╔═╗";
	cct_gotoxy(x - 1, y);
	cout << "║★║";
	cct_gotoxy(x - 1, y + 1);
	cout << "╚═╝";
	return;
	cct_setcolor(0, 7);///////////////////////(背景，字体)
}

void Grey(struct stc sss, int c[][10]) {
	int x = 0, y = 0;
	cct_cls();
	cct_setconsoleborder(8 * sss.b + 5, 4 * sss.a + 7, 8 * sss.b + 5, 4 * sss.a + 7);
	cout << "屏幕当前设置为" << 4 * sss.a + 7 << "行" << 8 * sss.b + 5 << "列         ";
	cct_setcolor(8, 14);
	if (*(sss.x) == 18)
		cout << "隐藏关1 ：亮青色（很好看）  (概率5%)";
	if (*(sss.x) == 19)
		cout << "隐藏关2 ：弯曲的            (概率5%)";
	if (*(sss.x) == 20)
		cout << "隐藏关3 ：玩原神玩的        (概率5%)";
	cct_setcolor(0, 7);
	cout << endl;
	for (int i = 0; i < sss.b; i++)
		cout << setfill(' ') << (i == 0 ? setw(7) : setw(8)) << i;
	cout << endl << "  ";
	cct_getxy(x, y);
	for (int i = 0; i < sss.a; i++) {
		cct_gotoxy(x - 2, y + 4 * i + 2);
		cout << char(i + 65);
	}
	cct_setcolor(15, 0);

	for (int i = 0; i <= 4 * sss.a; i++) {
		cct_gotoxy(x, y + i);
		for (int j = 0; j <= 4 * sss.b; j++) {
			if (i == 0) {
				if (j == 0)
					cout << "╔";
				if (j != 0 && j != 4 * sss.b)
					j % 4 == 0 ? cout << "╦" : cout << "═";
				if (j == 4 * sss.b)
					cout << "╗";
			}
			if (i != 0 && i != 4 * sss.a) {
				if (i % 4 == 0) {
					if (j == 0)
						cout << "╠";
					if (j != 0 && j != 4 * sss.b)
						j % 4 == 0 ? cout << "╬" : cout << "═";
					if (j == 4 * sss.b)
						cout << "╣";
				}
				else {
					if (j == 0)
						cout << "║";
					if (j != 0 && j != 4 * sss.b)
						j % 4 == 0 ? cout << "║" : cout << "  ";
					if (j == 4 * sss.b)
						cout << "║";
				}
			}
			if (i == 4 * sss.a) {
				if (j == 0)
					cout << "╚";
				if (j != 0 && j != 4 * sss.b)
					j % 4 == 0 ? cout << "╩" : cout << "═";
				if (j == 4 * sss.b)
					cout << "╝";
			}
			//Sleep(1);
			cct_gotoxy(x + 2 * j + 2, y + i);
		}
	}
	for (int i = 0; i < sss.a; i++)
		for (int j = 0; j < sss.b; j++)
			starfloat(8 * j + 5, 4 * i + 4, c[i][j], 0);//////////////////初始化完成
	return;

}

void Blue(struct stc sss, int c[][10]) {
	int x = 0, y = 0;
	cct_cls();
	cct_setconsoleborder(6 * sss.b + 7, 3 * sss.a + 8, 6 * sss.b + 7, 3 * sss.a + 8);
	cout << "屏幕当前设置为" << 3 * sss.a + 8 << "行" << 6 * sss.b + 7 << "列" << endl;
	for (int i = 0; i < sss.b; i++)
		cout << (i == 0 ? setw(7) : setw(6)) << i;
	cout << endl << "  ";
	cct_getxy(x, y);
	for (int i = 0; i < sss.a; i++) {
		cct_gotoxy(x - 2, y + 3 * i + 2);
		cout << char(i + 65);
	}
	cct_setcolor(15, 0);
	for (int i = 0; i <= 3 * sss.a + 1; i++) {
		cct_gotoxy(x, y + i);
		for (int j = 0; j <= 3 * sss.b + 1; j++) {
			if (i == 0) {
				if (j == 0)
					cout << "╔";
				if (j != 0 && j != 3 * sss.b + 1)
					cout << "═";
				if (j == 3 * sss.b + 1)
					cout << "╗";
			}
			if (i != 0 && i != 3 * sss.a + 1) {
				if (j == 0 || j == 3 * sss.b + 1)
					cout << "║";
				else
					cout << "  ";
			}
			if (i == 3 * sss.a + 1) {
				if (j == 0)
					cout << "╚";
				if (j != 0 && j != 3 * sss.b + 1)
					cout << "═";
				if (j == 3 * sss.b + 1)
					cout << "╝";
			}
			//Sleep(1);
			cct_gotoxy(x + 2 * j + 2, y + i);
		}
	}
	for (int i = 0; i < sss.a; i++)
		for (int j = 0; j < sss.b; j++)
			starfloat(6 * j + 5, 3 * i + 4, c[i][j], 0);/////////////////初始化完成
	return;
}

void Eout(struct stc sss, int c[][10]) {
	sss.chc = 'E';
	int q = 0;
	sss.q = &q;

	Grey(sss, c);




	/////////此时应该进入函数
	starfloat(5, 4, c[0][0], 7);
	c[0][0] += 20;
	cct_setcolor(0, 7);
	cct_gotoxy(0, 4 * sss.a + 3);
	cout << "箭头键/鼠标移动，回车键/单击左键选择并结束";
	cct_gotoxy(0, 4 * sss.a + 3);
	*(sss.c1) = *(sss.c2) = 0;

	Yesterday(sss, c);


	cct_setcolor(0, 7);
	cct_gotoxy(0, 4 * sss.a + 3);
	cout << "选中了" << char(*(sss.c1) + 65) << "行" << *(sss.c2) << "列";
	cct_showch(12, 4 * sss.a + 3, ' ', 0, 7, 25);


	cct_gotoxy(0, 4 * sss.a + 3);
	return;
}

void Dout(struct stc sss, int c[][10]) {
	sss.chc = 'D';
	int q = 0;
	sss.q = &q;

	Blue(sss, c);


	/////////此时应该进入函数
	starfloat(5, 4, c[0][0], 7);
	c[0][0] += 20;
	cct_setcolor(0, 7);
	cct_gotoxy(0, 3 * sss.a + 4);
	cout << "箭头键/鼠标移动，回车键/单击左键选择并结束";
	cct_gotoxy(0, 3 * sss.a + 4);
	*(sss.c1) = *(sss.c2) = 0;

	Yesterday(sss, c);
	

	cct_setcolor(0, 7);
	cct_gotoxy(0, 3 * sss.a + 4);
	cout << "  选中了" << char(*(sss.c1) + 65) << "行" << *(sss.c2) << "列";
	cct_showch(14, 3 * sss.a + 4, ' ', 0, 7, 30);

	cct_gotoxy(0, 3 * sss.a + 4);
	return;
}

void Fout(struct stc sss, int c[][10]) {
	sss.chc = 'D';
	Blue(sss, c);
	starfloat(5, 4, c[0][0], 7);
	c[0][0] += 10;
	cct_setcolor(0, 7);
	cct_gotoxy(0, 3 * sss.a + 4);
	cout << "箭头键/鼠标移动，回车键/单击左键选择并结束         " << endl;
	int p1 = 20, p2 = 20, q = 1;
	*(sss.c1) = 0;
	*(sss.c2) = 0;
	sss.q = &q;//////////////////////////m=0代表右键或者Q
	Best_star_ever(sss, p1, p2, c);
	
	if (*(sss.q) != 0)
		Bloom(sss, c);
	cct_setcolor(0, 7);

	return;
}

void GioGio(struct stc sss, int c[][10]) {

	sss.chc = 'E';
	while (1){
		*(sss.x) = landslide(sss, c);
		Grey(sss, c);
		while (1) {
			int ii = 0;
			for (ii; ii < sss.a; ii++)
				if (c[ii][0] != 0)
					break;
			starfloat(5, 4 * ii + 4, c[ii][0], 7);
			c[ii][0] += 10;
			cct_setcolor(0, 7);
			cct_gotoxy(0, 4 * sss.a + 3);
			cout << "箭头键/鼠标移动，回车键/单击左键选择并结束         " << endl;
			int p1 = 20, p2 = 20, q = 1;
			*(sss.c1) = ii;
			*(sss.c2) = 0;
			sss.q = &q;//////////////////////////m=0代表右键或者Q

			Best_star_ever(sss, p1, p2, c);

			if (*(sss.q) != 0)
				Bloom(sss, c);
			cct_setcolor(0, 7);
			if (*(sss.q) == 0)
				break;///////点了Q
			if (!justice(sss, c))
				break;
		}
		cct_gotoxy(0, 4 * sss.a + 4);
		if (*(sss.q) == 0)
			break;///////点了Q
		if (*(sss.q) != 0) {
			int nn = 0;
			for (int i = 0; i < sss.a; i++)
				for (int j = 0; j < sss.b; j++)
					c[i][j] != 0 ? nn++ : 1;
			cct_setcolor(0, 14);
			cout << "恭喜您！只剩" << nn << "颗★ ！本关结束，按回车进入下一关：";
			while (_getch() != '\r');
		}
	}
	cct_setcolor(0, 7);

	return;

}

void Best_star_ever(struct stc sss, int& p1, int& p2, int c[][10]) {
	while (1) {
		*(sss.t) = 0;//////////////确认中是否移动?   0=未移动
		if (sss.chc == 'E')
			cct_gotoxy(0, 4 * sss.a + 3);
		if (sss.chc == 'D')
			cct_gotoxy(0, 3 * sss.a + 4);
		Yesterday(sss, c);
		if (*(sss.q) == 0)
			break;///////点了Q
		else if (p1 == *(sss.c1) && p2 == *(sss.c2) && *(sss.t) == 0 && *(sss.n) != 1)////两次点击坐标相等、、未移动过鼠标、、点击处有相邻
			break;
		else {
			p1 = *(sss.c1);
			p2 = *(sss.c2);
		}
		*(sss.n) = 1;//////////////是否仅一个雷
		c[p1][p2] %= 10;
		find_cure(sss, c, p1, p2);
		for (int i = 0; i < sss.a; i++)
			for (int j = 0; j < sss.b; j++)
				if (c[i][j] > 10)
					starfloat((6 + 2 * (sss.chc - 'D')) * j + 5, (3 + sss.chc - 'D') * i + 4, c[i][j] % 10, 7);
	

		if (sss.chc == 'E')
			cct_gotoxy(0, 4 * sss.a + 3);
		if (sss.chc == 'D')
			cct_gotoxy(0, 3 * sss.a + 4);
		if (*(sss.n) != 1) {
			cct_setcolor(0, 11);
			cout << "箭头键/鼠标移动取消当前选择，回车键/单击左键合成";
			if (*(sss.n) != 1)
				starfloat((6 + 2 * (sss.chc - 'D')) * p2 + 5, (3 + sss.chc - 'D') * p1 + 4, c[p1][p2] % 10, 15);
		}
		else {
			cct_setcolor(0, 14);
			cout << " 周围无相同值   (°ー°〃)";
		}
	}

	return;
}

void Bloom(struct stc sss, int c[][10]) {

	cure_cure(sss, c, 1);
	cct_gotoxy(0, (3 + sss.chc - 'D') * sss.a + 4);
	cct_setcolor(0, 14);
	if (sss.chc == 'D') {
		cout << "合成完成，回车键/单击左键一键合成！！";
		cct_showch(37, (3 + sss.chc - 'D') * sss.a + 4, ' ', 0, 7, 20);/////////////////
		cct_showch(0, (3 + sss.chc - 'D') * sss.a + 5, ' ', 0, 7, 50);//////////////////
	}
	for (int j = 0; j < sss.b; j++)
		for (int i = sss.a - 1; i >= 0; i--)
			if (c[i][j] == 0) {
				cct_showch((6 + 2 * (sss.chc - 'D')) * j + 4, (3 + sss.chc - 'D') * i + 3, ' ', 15, 15, 6);
				cct_showch((6 + 2 * (sss.chc - 'D')) * j + 4, (3 + sss.chc - 'D') * i + 4, ' ', 15, 15, 6);
				cct_showch((6 + 2 * (sss.chc - 'D')) * j + 4, (3 + sss.chc - 'D') * i + 5, ' ', 15, 15, 6);
			}
	*(sss.num) += 5 * *(sss.n) * *(sss.n);
	cct_gotoxy(0, 0);
	cct_setcolor(0, 7);
	cout << "本次得分：" << 5 * *(sss.n) * *(sss.n);
	cout << " 总得分：" << *(sss.num);

	int X = 0, Y = 0;
	int ret, maction;
	int k1, k2;
	cct_enable_mouse();
	if (sss.chc == 'D')
		while (1) {
			ret = cct_read_keyboard_and_mouse(X, Y, maction, k1, k2);
			if (ret == CCT_MOUSE_EVENT && maction == MOUSE_LEFT_BUTTON_CLICK)
				break;
			if (ret == CCT_KEYBOARD_EVENT && k1 == 13)
				break;
		}
	to_the_floor(sss, c);
	darkside(sss, c);
	if (sss.chc == 'D') {
		cct_gotoxy(0, (3 + sss.chc - 'D') * sss.a + 4);
		cct_setcolor(0, 14);
		cout << "本次合成结束，按C/单击左键继续一次新的合成\n";
		cout << "     <(￣︶￣)↗[GO!]";
		while (1) {
			ret = cct_read_keyboard_and_mouse(X, Y, maction, k1, k2);
			if (ret == CCT_MOUSE_EVENT && maction == MOUSE_LEFT_BUTTON_CLICK)
				break;
			if (ret == CCT_KEYBOARD_EVENT && (k1 == 67 || k1 == 99))
				break;
		}
	}
	
	return;
}

void Yesterday(struct stc sss, int c[][10]) {
	int X = 0, Y = 0;
	int ret, maction;
	int k1, k2;

	int x, y, p;
	sss.p = &p;
	cct_getxy(x, y);
	cct_enable_mouse();
	
	while (1) {
		ret = cct_read_keyboard_and_mouse(X, Y, maction, k1, k2);
		if (ret == CCT_MOUSE_EVENT) {
			if (maction == MOUSE_ONLY_MOVED) 
				mice(sss, x, y, X, Y, c);
			if (maction == MOUSE_LEFT_BUTTON_CLICK && *(sss.p) == 1)
					break;
			if (maction == MOUSE_RIGHT_BUTTON_CLICK && *(sss.p) == 1) {
				*(sss.q) = 0;
				break;
			}
			
		}
		if (ret == CCT_KEYBOARD_EVENT) {
			*(sss.p) = 1;////////////肯定合法
			if (k1 == 224)
				board(sss, k2, x, y, c);
			if (k1 == 13) 	
				break;
			if (k1 == 81 || k1 == 113 ) {
				*(sss.q) = 0;
				break;
			}
		}
	}

	return;
}

void mice(struct stc sss, int x, int y, int X, int Y, int c[][10]) {
	int tmp1, tmp2;
	sss.chc == 'D' ? tmp1 = Y / 3 - 1 : tmp1 = (Y - 2) / 4;
	sss.chc == 'D' ? tmp2 = (X - 4) / 6 : tmp2 = (X - 2) / 8;
	if (*(sss.c1) != tmp1 || *(sss.c2) != tmp2)
		*(sss.t) = 1;////////////////代表已移动
	if (sss.chc == 'D' && X > 3 && X < 6 * sss.b + 4 && Y>2 && Y < 3 * sss.a + 3 && c[tmp1][tmp2] != 0)
		*(sss.p) = 1;///////////////代表位置合法
	else if (sss.chc == 'E' && X > 3 && X < 8 * sss.b + 2 && Y>2 && Y < 4 * sss.a + 2 && X % 8 != 2 && X % 8 != 3 && Y % 4 != 2 && c[tmp1][tmp2] != 0)
		*(sss.p) = 1;
	else
		*(sss.p) = 0;///////////////////位置不合法
	if (*(sss.p) == 0 || *(sss.t) == 1) {//////////////////////////////////位置非法或者已移动，就清零，变黑色
		for (int i = 0; i < sss.a; i++)
			for (int j = 0; j < sss.b; j++)
				if (c[i][j] > 10) {
					if (sss.chc == 'D')
						starfloat(6 * j + 5, 3 * i + 4, c[i][j] % 10, 0);
					if (sss.chc == 'E')
						starfloat(8 * j + 5, 4 * i + 4, c[i][j] % 10, 0);
					c[i][j] %= 10;
				}/////////////////////////把数列中大于十的变成黑色（因为新点坐标已经确定）
	}
	if (*(sss.p) == 1) {////////如果位置合法
		c[tmp1][tmp2] += 10;
		for (int i = 0; i < sss.a; i++)
			for (int j = 0; j < sss.b; j++)
				if (c[i][j] > 10) {
					if (sss.chc == 'D')
						starfloat(6 * tmp2 + 5, 3 * tmp1 + 4, c[tmp1][tmp2] % 10, 7);////////新点坐标变亮
					if (sss.chc == 'E')
						starfloat(8 * tmp2 + 5, 4 * tmp1 + 4, c[tmp1][tmp2] % 10, 7);
				}
		if (*(sss.t) == 0 && *(sss.n) != 1) {
			if (sss.chc == 'D')
				starfloat(6 * tmp2 + 5, 3 * tmp1 + 4, c[tmp1][tmp2] % 10, 15);
			if (sss.chc == 'E')
				starfloat(8 * tmp2 + 5, 4 * tmp1 + 4, c[tmp1][tmp2] % 10, 15);
		}
		cct_gotoxy(x, y);
		cct_setcolor(0, 7);
		if (*(sss.t) == 1) {/////////////////如果已经移动鼠标(且合法位置)
			cout << "[当前鼠标] " << char(tmp1 + 65) << "行" << tmp2 << "列  ";
			cct_showch(x + 17, y, ' ', 0, 7, 30);//////////////////////////////////////
		}
		cct_setcolor(0, 8);
		cout << endl << "鼠标/箭头移动 单击左键/回车键选择 单击右键/Q退出";
		*(sss.c1) = tmp1;
		*(sss.c2) = tmp2;
	}
	else 
	{
		cct_gotoxy(x, y);

		cct_setcolor(0, 7);
		cout << "[当前鼠标] " << "位置非法";
		cct_showch(x + 20, y, ' ', 0, 7, 30);///////////////////////////////////////////
	}
	return;
}

void board(struct stc sss, int k2, int x, int y, int c[][10]) {

	int a1 = *(sss.c1), b1 = *(sss.c2);
	*(sss.t) = 1;////////////肯定移动
	//*(sss.p) = 1;////////////肯定合法
	switch (k2) {
	case KB_ARROW_UP:
		do
			a1 != 0 ? a1-- : a1 = sss.a - 1;
		while (c[a1][b1] == 0);
		break;
	case KB_ARROW_DOWN:
		do
		a1 != sss.a - 1 ? a1++ : a1 = 0;
		while (c[a1][b1] == 0);
		break;
	case KB_ARROW_LEFT:
		do
		b1 != 0 ? b1-- : b1 = sss.b - 1;
		while (c[a1][b1] == 0);
		break;
	case KB_ARROW_RIGHT:
		do
		b1 != sss.b - 1 ? b1++ : b1 = 0;
		while (c[a1][b1] == 0);
		break;
	}
	for (int i = 0; i < sss.a; i++)
		for (int j = 0; j < sss.b; j++)
			if (c[i][j] > 10) {
				if (sss.chc == 'D')
					starfloat(6 * j + 5, 3 * i + 4, c[i][j] % 10, 0);
				if (sss.chc == 'E')
					starfloat(8 * j + 5, 4 * i + 4, c[i][j] % 10, 0);
				c[i][j] %= 10;
			}/////////////////////////先把数列中大于十的变成黑色（因为新点坐标已经确定）
	
	c[a1 % 10][b1 % 10] += 10;
	if (sss.chc == 'D')
		starfloat(6 * b1 + 5, 3 * a1 + 4, c[a1 % 10][b1 % 10] % 10, 7);////////新点坐标变亮
	if (sss.chc == 'E')
		starfloat(8 * b1 + 5, 4 * a1 + 4, c[a1 % 10][b1 % 10] % 10, 7);////////新点坐标变亮

	

	cct_gotoxy(x, y);
	cct_setcolor(0, 7);
	cout << "[当前键盘] " << char(a1 + 65) << "行" << b1 << "列  ";
	cct_showch(x + 17, y, ' ', 0, 7, 30);//////////////////////////////////////////////
	cct_setcolor(0, 8);
	cout << endl << "鼠标/箭头移动 单击左键/回车键选择 单击右键/Q退出";
	*(sss.c1) = a1;
	*(sss.c2) = b1;
	return;
}
