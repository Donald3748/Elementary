/*2252712-��17-������*/
#include"popstar.h"


/*fg_color��0 - 7    ��    ��   ��   ��   ��  ��   ��   ��
			8 - 15 ���� ���� ���� ���� ���� ���� ���� ����
bg_color��0 - 7    ��   ��   ��   ��   ��   ��   ��   ��
		  8 - 15 ���� ���� ���� ���� ���� ���� ���� ����

		  cct_setcolor(0, 7);��ʾ������ɫ
		  0 �� 7 �� 15 ����
*/

void starfloat(int x, int y, int bg_color, int ff) {
	cct_setcolor(bg_color + 8, ff);
	cct_gotoxy(x - 1, y - 1);
	cout << "�X�T�[";
	cct_gotoxy(x - 1, y);
	cout << "�U��U";
	cct_gotoxy(x - 1, y + 1);
	cout << "�^�T�a";
	return;
	cct_setcolor(0, 7);///////////////////////(����������)
}

void Grey(struct stc sss, int c[][10]) {
	int x = 0, y = 0;
	cct_cls();
	cct_setconsoleborder(8 * sss.b + 5, 4 * sss.a + 7, 8 * sss.b + 5, 4 * sss.a + 7);
	cout << "��Ļ��ǰ����Ϊ" << 4 * sss.a + 7 << "��" << 8 * sss.b + 5 << "��         ";
	cct_setcolor(8, 14);
	if (*(sss.x) == 18)
		cout << "���ع�1 ������ɫ���ܺÿ���  (����5%)";
	if (*(sss.x) == 19)
		cout << "���ع�2 ��������            (����5%)";
	if (*(sss.x) == 20)
		cout << "���ع�3 ����ԭ�����        (����5%)";
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
					cout << "�X";
				if (j != 0 && j != 4 * sss.b)
					j % 4 == 0 ? cout << "�j" : cout << "�T";
				if (j == 4 * sss.b)
					cout << "�[";
			}
			if (i != 0 && i != 4 * sss.a) {
				if (i % 4 == 0) {
					if (j == 0)
						cout << "�d";
					if (j != 0 && j != 4 * sss.b)
						j % 4 == 0 ? cout << "�p" : cout << "�T";
					if (j == 4 * sss.b)
						cout << "�g";
				}
				else {
					if (j == 0)
						cout << "�U";
					if (j != 0 && j != 4 * sss.b)
						j % 4 == 0 ? cout << "�U" : cout << "  ";
					if (j == 4 * sss.b)
						cout << "�U";
				}
			}
			if (i == 4 * sss.a) {
				if (j == 0)
					cout << "�^";
				if (j != 0 && j != 4 * sss.b)
					j % 4 == 0 ? cout << "�m" : cout << "�T";
				if (j == 4 * sss.b)
					cout << "�a";
			}
			//Sleep(1);
			cct_gotoxy(x + 2 * j + 2, y + i);
		}
	}
	for (int i = 0; i < sss.a; i++)
		for (int j = 0; j < sss.b; j++)
			starfloat(8 * j + 5, 4 * i + 4, c[i][j], 0);//////////////////��ʼ�����
	return;

}

void Blue(struct stc sss, int c[][10]) {
	int x = 0, y = 0;
	cct_cls();
	cct_setconsoleborder(6 * sss.b + 7, 3 * sss.a + 8, 6 * sss.b + 7, 3 * sss.a + 8);
	cout << "��Ļ��ǰ����Ϊ" << 3 * sss.a + 8 << "��" << 6 * sss.b + 7 << "��" << endl;
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
					cout << "�X";
				if (j != 0 && j != 3 * sss.b + 1)
					cout << "�T";
				if (j == 3 * sss.b + 1)
					cout << "�[";
			}
			if (i != 0 && i != 3 * sss.a + 1) {
				if (j == 0 || j == 3 * sss.b + 1)
					cout << "�U";
				else
					cout << "  ";
			}
			if (i == 3 * sss.a + 1) {
				if (j == 0)
					cout << "�^";
				if (j != 0 && j != 3 * sss.b + 1)
					cout << "�T";
				if (j == 3 * sss.b + 1)
					cout << "�a";
			}
			//Sleep(1);
			cct_gotoxy(x + 2 * j + 2, y + i);
		}
	}
	for (int i = 0; i < sss.a; i++)
		for (int j = 0; j < sss.b; j++)
			starfloat(6 * j + 5, 3 * i + 4, c[i][j], 0);/////////////////��ʼ�����
	return;
}

void Eout(struct stc sss, int c[][10]) {
	sss.chc = 'E';
	int q = 0;
	sss.q = &q;

	Grey(sss, c);




	/////////��ʱӦ�ý��뺯��
	starfloat(5, 4, c[0][0], 7);
	c[0][0] += 20;
	cct_setcolor(0, 7);
	cct_gotoxy(0, 4 * sss.a + 3);
	cout << "��ͷ��/����ƶ����س���/�������ѡ�񲢽���";
	cct_gotoxy(0, 4 * sss.a + 3);
	*(sss.c1) = *(sss.c2) = 0;

	Yesterday(sss, c);


	cct_setcolor(0, 7);
	cct_gotoxy(0, 4 * sss.a + 3);
	cout << "ѡ����" << char(*(sss.c1) + 65) << "��" << *(sss.c2) << "��";
	cct_showch(12, 4 * sss.a + 3, ' ', 0, 7, 25);


	cct_gotoxy(0, 4 * sss.a + 3);
	return;
}

void Dout(struct stc sss, int c[][10]) {
	sss.chc = 'D';
	int q = 0;
	sss.q = &q;

	Blue(sss, c);


	/////////��ʱӦ�ý��뺯��
	starfloat(5, 4, c[0][0], 7);
	c[0][0] += 20;
	cct_setcolor(0, 7);
	cct_gotoxy(0, 3 * sss.a + 4);
	cout << "��ͷ��/����ƶ����س���/�������ѡ�񲢽���";
	cct_gotoxy(0, 3 * sss.a + 4);
	*(sss.c1) = *(sss.c2) = 0;

	Yesterday(sss, c);
	

	cct_setcolor(0, 7);
	cct_gotoxy(0, 3 * sss.a + 4);
	cout << "  ѡ����" << char(*(sss.c1) + 65) << "��" << *(sss.c2) << "��";
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
	cout << "��ͷ��/����ƶ����س���/�������ѡ�񲢽���         " << endl;
	int p1 = 20, p2 = 20, q = 1;
	*(sss.c1) = 0;
	*(sss.c2) = 0;
	sss.q = &q;//////////////////////////m=0�����Ҽ�����Q
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
			cout << "��ͷ��/����ƶ����س���/�������ѡ�񲢽���         " << endl;
			int p1 = 20, p2 = 20, q = 1;
			*(sss.c1) = ii;
			*(sss.c2) = 0;
			sss.q = &q;//////////////////////////m=0�����Ҽ�����Q

			Best_star_ever(sss, p1, p2, c);

			if (*(sss.q) != 0)
				Bloom(sss, c);
			cct_setcolor(0, 7);
			if (*(sss.q) == 0)
				break;///////����Q
			if (!justice(sss, c))
				break;
		}
		cct_gotoxy(0, 4 * sss.a + 4);
		if (*(sss.q) == 0)
			break;///////����Q
		if (*(sss.q) != 0) {
			int nn = 0;
			for (int i = 0; i < sss.a; i++)
				for (int j = 0; j < sss.b; j++)
					c[i][j] != 0 ? nn++ : 1;
			cct_setcolor(0, 14);
			cout << "��ϲ����ֻʣ" << nn << "�š� �����ؽ��������س�������һ�أ�";
			while (_getch() != '\r');
		}
	}
	cct_setcolor(0, 7);

	return;

}

void Best_star_ever(struct stc sss, int& p1, int& p2, int c[][10]) {
	while (1) {
		*(sss.t) = 0;//////////////ȷ�����Ƿ��ƶ�?   0=δ�ƶ�
		if (sss.chc == 'E')
			cct_gotoxy(0, 4 * sss.a + 3);
		if (sss.chc == 'D')
			cct_gotoxy(0, 3 * sss.a + 4);
		Yesterday(sss, c);
		if (*(sss.q) == 0)
			break;///////����Q
		else if (p1 == *(sss.c1) && p2 == *(sss.c2) && *(sss.t) == 0 && *(sss.n) != 1)////���ε��������ȡ���δ�ƶ�����ꡢ�������������
			break;
		else {
			p1 = *(sss.c1);
			p2 = *(sss.c2);
		}
		*(sss.n) = 1;//////////////�Ƿ��һ����
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
			cout << "��ͷ��/����ƶ�ȡ����ǰѡ�񣬻س���/��������ϳ�";
			if (*(sss.n) != 1)
				starfloat((6 + 2 * (sss.chc - 'D')) * p2 + 5, (3 + sss.chc - 'D') * p1 + 4, c[p1][p2] % 10, 15);
		}
		else {
			cct_setcolor(0, 14);
			cout << " ��Χ����ֵͬ   (��`�㡨)";
		}
	}

	return;
}

void Bloom(struct stc sss, int c[][10]) {

	cure_cure(sss, c, 1);
	cct_gotoxy(0, (3 + sss.chc - 'D') * sss.a + 4);
	cct_setcolor(0, 14);
	if (sss.chc == 'D') {
		cout << "�ϳ���ɣ��س���/�������һ���ϳɣ���";
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
	cout << "���ε÷֣�" << 5 * *(sss.n) * *(sss.n);
	cout << " �ܵ÷֣�" << *(sss.num);

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
		cout << "���κϳɽ�������C/�����������һ���µĺϳ�\n";
		cout << "     <(�����)�J[GO!]";
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
			*(sss.p) = 1;////////////�϶��Ϸ�
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
		*(sss.t) = 1;////////////////�������ƶ�
	if (sss.chc == 'D' && X > 3 && X < 6 * sss.b + 4 && Y>2 && Y < 3 * sss.a + 3 && c[tmp1][tmp2] != 0)
		*(sss.p) = 1;///////////////����λ�úϷ�
	else if (sss.chc == 'E' && X > 3 && X < 8 * sss.b + 2 && Y>2 && Y < 4 * sss.a + 2 && X % 8 != 2 && X % 8 != 3 && Y % 4 != 2 && c[tmp1][tmp2] != 0)
		*(sss.p) = 1;
	else
		*(sss.p) = 0;///////////////////λ�ò��Ϸ�
	if (*(sss.p) == 0 || *(sss.t) == 1) {//////////////////////////////////λ�÷Ƿ��������ƶ��������㣬���ɫ
		for (int i = 0; i < sss.a; i++)
			for (int j = 0; j < sss.b; j++)
				if (c[i][j] > 10) {
					if (sss.chc == 'D')
						starfloat(6 * j + 5, 3 * i + 4, c[i][j] % 10, 0);
					if (sss.chc == 'E')
						starfloat(8 * j + 5, 4 * i + 4, c[i][j] % 10, 0);
					c[i][j] %= 10;
				}/////////////////////////�������д���ʮ�ı�ɺ�ɫ����Ϊ�µ������Ѿ�ȷ����
	}
	if (*(sss.p) == 1) {////////���λ�úϷ�
		c[tmp1][tmp2] += 10;
		for (int i = 0; i < sss.a; i++)
			for (int j = 0; j < sss.b; j++)
				if (c[i][j] > 10) {
					if (sss.chc == 'D')
						starfloat(6 * tmp2 + 5, 3 * tmp1 + 4, c[tmp1][tmp2] % 10, 7);////////�µ��������
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
		if (*(sss.t) == 1) {/////////////////����Ѿ��ƶ����(�ҺϷ�λ��)
			cout << "[��ǰ���] " << char(tmp1 + 65) << "��" << tmp2 << "��  ";
			cct_showch(x + 17, y, ' ', 0, 7, 30);//////////////////////////////////////
		}
		cct_setcolor(0, 8);
		cout << endl << "���/��ͷ�ƶ� �������/�س���ѡ�� �����Ҽ�/Q�˳�";
		*(sss.c1) = tmp1;
		*(sss.c2) = tmp2;
	}
	else 
	{
		cct_gotoxy(x, y);

		cct_setcolor(0, 7);
		cout << "[��ǰ���] " << "λ�÷Ƿ�";
		cct_showch(x + 20, y, ' ', 0, 7, 30);///////////////////////////////////////////
	}
	return;
}

void board(struct stc sss, int k2, int x, int y, int c[][10]) {

	int a1 = *(sss.c1), b1 = *(sss.c2);
	*(sss.t) = 1;////////////�϶��ƶ�
	//*(sss.p) = 1;////////////�϶��Ϸ�
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
			}/////////////////////////�Ȱ������д���ʮ�ı�ɺ�ɫ����Ϊ�µ������Ѿ�ȷ����
	
	c[a1 % 10][b1 % 10] += 10;
	if (sss.chc == 'D')
		starfloat(6 * b1 + 5, 3 * a1 + 4, c[a1 % 10][b1 % 10] % 10, 7);////////�µ��������
	if (sss.chc == 'E')
		starfloat(8 * b1 + 5, 4 * a1 + 4, c[a1 % 10][b1 % 10] % 10, 7);////////�µ��������

	

	cct_gotoxy(x, y);
	cct_setcolor(0, 7);
	cout << "[��ǰ����] " << char(a1 + 65) << "��" << b1 << "��  ";
	cct_showch(x + 17, y, ' ', 0, 7, 30);//////////////////////////////////////////////
	cct_setcolor(0, 8);
	cout << endl << "���/��ͷ�ƶ� �������/�س���ѡ�� �����Ҽ�/Q�˳�";
	*(sss.c1) = a1;
	*(sss.c2) = b1;
	return;
}
