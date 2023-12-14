#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include <stack>
#include <map>

#include<graphics.h>
using namespace std;

#define BOARD_SIZE  12
enum { nothing, black, white };//1Ϊ���壬2Ϊ����

int board[BOARD_SIZE][BOARD_SIZE];
int my_flag;
int enemy_flag;
int status;//1ΪMy_flag��ʤ����2������
int cont;
/*���Ӹ�ʽ�������������겢�ṩһ����ֵ���أ����ڸ������Ӵ���λ��*/
struct Command {
	int x;
	int y;
	Command() :x(0), y(0) {};
	Command& operator=(pair<int, int>t) {
		x = t.first;
		y = t.second;
		return *this;
	}

};
/*������ģ�崮���������ݳ�Ա�ֱ��Ӧ��ģ�壬next����(����kmp����)����Ӧ����*/
struct Template {
	string format;
	int next[6];
	int score;
};
/*const ��ǵĴ���ģ�崮�����飬��������*/
const Template patterns[16] = {
	{"11111", {-1,-1,-1,-1,-1,0},50000},
	{"011110",{-1,0,0,0,0,-1},4320},
	{"011100",{-1,0,0,0,-1,1},720},
	{"001110",{-1,-1,1,0,0,-1},720},
	{"011010",{-1,0,0,-1,0,2},720},
	{"010110",{-1,0,-1,0,2,-1},720},
	{"01111", {-1,0,0,0,0,0},720},
	{"10111", {-1,0,-1,1,1,0},720},
	{"11011", {-1,-1,1,-1,-1,0},720},
	{"11101", {-1,-1,-1,2,-1,0},720},
	{"11110", {-1,-1,-1,-1,3,0},720},
	{"001100",{-1,-1,1,0,-1,-1},120},
	{"001010",{-1,-1,1,-1,1,-1},120},
	{"010100",{-1,0,-1,0,-1,3},120},
	{"000100",{-1,-1,-1,2,-1,-1},20},
	{"001000",{-1,-1,1,-1,-1,2},20},
};


bool kmp_search(const string&, const string&, const int next[]);
// ���峣��
const int CELL_SIZE = 40;
// ��������������
void draw_board() {
	// ��ʼ����ͼ����
	
	initgraph(CELL_SIZE * (BOARD_SIZE + 2), CELL_SIZE * (BOARD_SIZE + 4));
	setfillcolor(BROWN);
	fillrectangle(CELL_SIZE, 3 * CELL_SIZE, 13 * CELL_SIZE, 15 * CELL_SIZE);
	// ������������
	setbkcolor(WHITE);
	setlinestyle(PS_SOLID, 1);
	setlinecolor(WHITE);
	for (int i = 0; i <= BOARD_SIZE; ++i) {
		line(CELL_SIZE, (i + 3) * CELL_SIZE, CELL_SIZE * (BOARD_SIZE + 1), (i + 3) * CELL_SIZE);
		//line(CELL_SIZE, (i + 1) * CELL_SIZE, CELL_SIZE * (BOARD_SIZE - 1), (i + 1) * CELL_SIZE);
		line((i + 1) * CELL_SIZE, 3 * CELL_SIZE, (i + 1) * CELL_SIZE, CELL_SIZE * (BOARD_SIZE + 3));
	}
}
// ����ӵķ�����x��y�ֱ��ʾ���ӵ�����
void put_black(int x, int y) {
	// ���ƺ���
	setfillcolor(BLACK);
	fillcircle(int((x + 1.5) * CELL_SIZE), int((y + 0.5) * CELL_SIZE), CELL_SIZE / 2);
}
// ����ӵķ�����x��y�ֱ��ʾ���ӵ�����
void put_white(int x, int y) {
	// ���ư���
	setfillcolor(WHITE);
	fillcircle(int((x + 1.5) * CELL_SIZE), int((y + 0.5) * CELL_SIZE), CELL_SIZE / 2);
}
char change(int i) {
	if (i < 10) return char(i + 48);
	else  return char(i + 55);
}
// ���ѡ����ɫ
inline void indicate(int f, int s) {
	settextstyle(int(0.5 * CELL_SIZE), 0, _T("����"));
	setbkcolor(BLACK);
	settextcolor(WHITE);
	for (int i = 0; i < BOARD_SIZE; i++) {
		outtextxy((i + 1) * CELL_SIZE + CELL_SIZE / 3, int(2.5 * CELL_SIZE), change(i));
		outtextxy(CELL_SIZE - CELL_SIZE / 3, (i + 3) * CELL_SIZE + CELL_SIZE / 3, change(i));
	}
	if (s == 2) {
		setbkcolor(WHITE);
		settextcolor(BLACK);
	}
	if (f == 1) {
		outtextxy(3 * CELL_SIZE, 1 * CELL_SIZE, _T("        "));
		outtextxy(3 * CELL_SIZE, int(1.5 * CELL_SIZE), _T("  ����  "));
		outtextxy(3 * CELL_SIZE, 2 * CELL_SIZE, _T("        "));
	}
	if (f == 2) {
		outtextxy(9 * CELL_SIZE, 1 * CELL_SIZE, _T("        "));
		outtextxy(9 * CELL_SIZE, int(1.5 * CELL_SIZE), _T("  ����  "));
		outtextxy(9 * CELL_SIZE, 2 * CELL_SIZE, _T("        "));
	}
}
void pre_prepare() {
	// �������
	indicate(1, 1);
	indicate(2, 1);
	ExMessage msg;
	while (1) {
		msg = getmessage(EX_MOUSE);
		if (3 * CELL_SIZE < msg.x && msg.x < 5 * CELL_SIZE && 1 * CELL_SIZE < msg.y && msg.y < 2.5 * CELL_SIZE) {
			indicate(1, 2);
			if (msg.message == WM_LBUTTONDOWN) {
				my_flag = white;
				break;
			}
		}
		else(indicate(1, 1));
		if (9 * CELL_SIZE < msg.x && msg.x < 11 * CELL_SIZE && 1 * CELL_SIZE < msg.y && msg.y < 2.5 * CELL_SIZE) {
			indicate(2, 2);
			if (msg.message == WM_LBUTTONDOWN) {
				my_flag = black;
				break;
			}
		}
		else(indicate(2, 1));
	}
	setbkcolor(BLACK);
	settextcolor(BLACK);
	outtextxy(3 * CELL_SIZE, 1 * CELL_SIZE, _T("        "));
	outtextxy(3 * CELL_SIZE, int(1.5 * CELL_SIZE), _T("        "));
	outtextxy(3 * CELL_SIZE, 2 * CELL_SIZE, _T("        "));
	outtextxy(9 * CELL_SIZE, 1 * CELL_SIZE, _T("        "));
	outtextxy(9 * CELL_SIZE, int(1.5 * CELL_SIZE), _T("        "));
	outtextxy(9 * CELL_SIZE, 2 * CELL_SIZE, _T("        "));
	settextcolor(WHITE);
	if (my_flag == white)
		outtextxy(6 * CELL_SIZE, 2 * CELL_SIZE, _T("��ִ����"));
	if (my_flag == black)
		outtextxy(6 * CELL_SIZE, 2 * CELL_SIZE, _T("��ִ����"));
}
// �ж϶Ծ��Ƿ����
bool is_over() {
	string lines[54];
	for (int i = 0; i < BOARD_SIZE; i++)
		for (int j = 0; j < BOARD_SIZE; j++)
			lines[i].push_back(board[i][j] == my_flag ? '1' : board[i][j] == 0 ? '0' : '2');//"--"
	for (int i = 0; i < BOARD_SIZE; i++)
		for (int j = 0; j < BOARD_SIZE; j++)
			lines[i + BOARD_SIZE].push_back(board[j][i] == my_flag ? '1' : board[j][i] == 0 ? '0' : '2');//"|"
	for (int i = 4; i < 12; i++)//  "/"
		for (int j = 0; j < 12 - abs(11 - i); j++)
			lines[i + 2 * BOARD_SIZE - 4].push_back(board[j][i - j] == my_flag ? '1' : board[j][i - j] == 0 ? '0' : '2');
	for (int i = 12; i < 19; i++)
		for (int j = 0; j < 12 - abs(11 - i); j++)
			lines[i + 2 * BOARD_SIZE - 4].push_back(board[j + i % 11][11 - j] == my_flag ? '1' : board[j + i % 11][11 - j] == 0 ? '0' : '2');
	for (int i = 4; i < 12; i++)//  "\"
		for (int j = 0; j < 12 - abs(11 - i); j++)
			lines[i + 2 * BOARD_SIZE + 11].push_back(board[11 - i + j][j] == my_flag ? '1' : board[11 - i + j][j] == 0 ? '0' : '2');// "\"
	for (int i = 12; i < 19; i++)
		for (int j = 0; j < 12 - abs(11 - i); j++)
			lines[i + 2 * BOARD_SIZE + 11].push_back(board[j][i - 11 + j] == my_flag ? '1' : board[j][i - 11 + j] == 0 ? '0' : '2');
	for (int i = 0; i < 54; i++) {
		if (kmp_search(lines[i], patterns[0].format, patterns[0].next)) {
			status = 1;
			return true;
		}
		if (kmp_search(lines[i], "22222", patterns[0].next)) {
			status = 2;
			return true;
		}
	}
	return false;
}
void show_answer() {
	outtextxy(6 * CELL_SIZE, 2 * CELL_SIZE, _T("        "));
	setbkcolor(WHITE);
	settextcolor(BLACK);
	outtextxy(6 * CELL_SIZE, int(0.5 * CELL_SIZE), _T("        "));
	if (status == 1)
		outtextxy(6 * CELL_SIZE, 1 * CELL_SIZE, _T(" ������ "));
	if (status == 2)
		outtextxy(6 * CELL_SIZE, 1 * CELL_SIZE, _T(" ��Ӯ�� "));
	outtextxy(6 * CELL_SIZE, int(1.5 * CELL_SIZE), _T("        "));
} 
//test
bool cccontinue() {
	if (status == 1) {
		setbkcolor(BLACK);
		settextcolor(WHITE);
		outtextxy(CELL_SIZE, int(15.1 * CELL_SIZE), _T("��ϲ�㣡�����ݺݱ�ɴ������ֻ����"));
		outtextxy(9 * CELL_SIZE, int(15.1 * CELL_SIZE), char(cont / 10 + 48));
		outtextxy(int(9.25 * CELL_SIZE), int(15.1 * CELL_SIZE), char(cont % 10 + 48));
		outtextxy(int(9.5 * CELL_SIZE), int(15.1 * CELL_SIZE), _T("��"));
	}
	if (status == 2) {
		setbkcolor(BLACK);
		settextcolor(WHITE);
		outtextxy(CELL_SIZE, int(2.5 * CELL_SIZE), _T("�ɶ񣡾�Ȼ����Ӯ��"));
	}
	outtextxy(9 * CELL_SIZE, CELL_SIZE, _T("        "));
	outtextxy(9 * CELL_SIZE, int(1.5 * CELL_SIZE), _T("�����˳�"));
	outtextxy(9 * CELL_SIZE, 2 * CELL_SIZE, _T("        "));
	outtextxy(3 * CELL_SIZE, CELL_SIZE, _T("        "));
	outtextxy(3 * CELL_SIZE, int(1.5 * CELL_SIZE), _T("������Ϸ"));
	outtextxy(3 * CELL_SIZE, 2 * CELL_SIZE, _T("        "));
	ExMessage msg;
	while (1) {
		msg = getmessage(EX_MOUSE);
		if (9 * CELL_SIZE < msg.x && msg.x < 11 * CELL_SIZE && 1 * CELL_SIZE < msg.y && msg.y < 2.5 * CELL_SIZE) {
			setbkcolor(WHITE);
			settextcolor(BLACK);
			outtextxy(9 * CELL_SIZE, CELL_SIZE, _T("        "));
			outtextxy(9 * CELL_SIZE, int(1.5 * CELL_SIZE), _T("�����˳�"));
			outtextxy(9 * CELL_SIZE, 2 * CELL_SIZE, _T("        "));
			if (msg.message == WM_LBUTTONDOWN)
				return 0;

		}
		else {
			setbkcolor(BLACK);
			settextcolor(WHITE);
			outtextxy(9 * CELL_SIZE, CELL_SIZE, _T("        "));
			outtextxy(9 * CELL_SIZE, int(1.5 * CELL_SIZE), _T("�����˳�"));
			outtextxy(9 * CELL_SIZE, 2 * CELL_SIZE, _T("        "));
		}
		if (3 * CELL_SIZE < msg.x && msg.x < 5 * CELL_SIZE && 1 * CELL_SIZE < msg.y && msg.y < 2.5 * CELL_SIZE) {
			setbkcolor(WHITE);
			settextcolor(BLACK);
			outtextxy(3 * CELL_SIZE, CELL_SIZE, _T("        "));
			outtextxy(3 * CELL_SIZE, int(1.5 * CELL_SIZE), _T("������Ϸ"));
			outtextxy(3 * CELL_SIZE, 2 * CELL_SIZE, _T("        "));
			if (msg.message == WM_LBUTTONDOWN) {
				return 1;
			}
		}
		else {
			setbkcolor(BLACK);
			settextcolor(WHITE);
			outtextxy(3 * CELL_SIZE, CELL_SIZE, _T("        "));
			outtextxy(3 * CELL_SIZE, int(1.5 * CELL_SIZE), _T("������Ϸ"));
			outtextxy(3 * CELL_SIZE, 2 * CELL_SIZE, _T("        "));
		}
	}
}



/*kmp������Ч�ʸ���*/
bool kmp_search(const string& s, const string& p, const int next[]) {
	int i = 0;
	int j = 0;
	int s_size = s.size();
	int p_size = p.size();
	while (i < s_size && j < p_size) {
		/*���j == -1�����ߵ�ǰ�ַ�ƥ��ɹ�����s[i] == p[j]��������i++��j++*/
		if (j == -1 || s[i] == p[j]) {
			i++;
			j++;
		}
		else {
			/*���j != -1���ҵ�ǰ�ַ�ƥ��ʧ�ܣ���s[i] != p[j]�������� i ���䣬j = next[j]*/
			j = next[j];
		}
	}
	if (j == p_size)
		return true;
	return false;//û�ҵ�����false
}
/*��һ��Ĺ�ֵ����������Ч��δ���ӵ�*/
int evaluate_point(Command& p) {
	int result = 0;//���շ���
	int i;//ѭ����׼
	int role = my_flag;

	string my_lines[4];
	string enemy_lines[4];
	//��ǰ����ռ䣬���ڲ���ʱ���Ч��
	for (auto& line : my_lines) {
		line.reserve(15);
	}
	for (auto& line : enemy_lines) {
		line.reserve(15);
	}
	//  "|"�Ĳ���
	int bottom = max(0, p.x - 5);
	int roof = min(BOARD_SIZE - 1, p.x + 5);
	for (i = bottom; i <= roof; i++) {
		if (i != p.x) {
			my_lines[0].push_back(board[i][p.y] == role ? '1' : board[i][p.y] == 0 ? '0' : '2');
			enemy_lines[0].push_back(board[i][p.y] == role ? '2' : board[i][p.y] == 0 ? '0' : '1');
		}
		else {
			my_lines[0].push_back('1');
			enemy_lines[0].push_back('1');
		}
	}
	//  "--"�Ĳ���
	bottom = max(0, p.y - 5);
	roof = min(BOARD_SIZE - 1, p.y + 5);
	for (i = bottom; i <= roof; i++) {
		if (i != p.y) {
			my_lines[1].push_back(board[p.x][i] == role ? '1' : board[p.x][i] == 0 ? '0' : '2');
			enemy_lines[1].push_back(board[p.x][i] == role ? '2' : board[p.x][i] == 0 ? '0' : '1');
		}
		else {
			my_lines[1].push_back('1');
			enemy_lines[1].push_back('1');
		}
	}
	//  "\"�Ĳ���
	bottom = -min(min(p.x, p.y), 5);
	roof = min(min(BOARD_SIZE - 1 - p.x, BOARD_SIZE - 1 - p.y), 5);
	for (i = bottom; i <= roof; i++) {
		if (i) {
			my_lines[2].push_back(board[p.x + i][p.y + i] == role ? '1' : board[p.x + i][p.y + i] == 0 ? '0' : '2');
			enemy_lines[2].push_back(board[p.x + i][p.y + i] == role ? '2' : board[p.x + i][p.y + i] == 0 ? '0' : '1');
		}
		else {
			my_lines[2].push_back('1');
			enemy_lines[2].push_back('1');
		}
	}
	//  "/"�Ĳ���
	bottom = -min(min(BOARD_SIZE - 1 - p.x, p.y), 5);
	roof = min(min(p.x, BOARD_SIZE - 1 - p.y), 5);
	for (i = bottom; i <= roof; i++) {
		if (i) {
			my_lines[3].push_back(board[p.x - i][p.y + i] == role ? '1' : board[p.x - i][p.y + i] == 0 ? '0' : '2');
			enemy_lines[3].push_back(board[p.x - i][p.y + i] == role ? '2' : board[p.x - i][p.y + i] == 0 ? '0' : '1');
		}
		else {
			my_lines[3].push_back('1');
			enemy_lines[3].push_back('1');
		}
	}

	/*��������, ���ĸ������ϵ�ɨ�贮������ģ�崮�������ɹ������Ӧ�ķ���*/
	for (i = 0; i < 4; i++)
		for (int j = 0; j < 16; j++) {
			if (kmp_search(my_lines[i], patterns[j].format, patterns[j].next))
				result += (patterns[j].score + patterns[j].score / 10);//�Լ��������ľ���ӷָ��࣬ռ����Ȩ��
			if (kmp_search(enemy_lines[i], patterns[j].format, patterns[j].next))
				result += patterns[j].score;
		}
	return result;
	/*���ط����ǶԼ���������Եз�����֮�ͣ��Լ��������ľ���ͶԶԷ������ľ��涼��Ҫ�������Լ��ķ�������Ҫ�����Ȩ�ظ���*/
}
/*�ж�һ��δ���ӵ���Χ�˸��Ϸ����Ƿ��Ѿ�������*/
inline bool is_around(int i, int j) {
	if (i > 0) if (board[i - 1][j]) return true;//up
	if (j > 0) if (board[i][j - 1]) return true;//left
	if (i < BOARD_SIZE - 1) if (board[i + 1][j]) return true;//down
	if (j < BOARD_SIZE - 1) if (board[i][j + 1]) return true;//right
	if (i > 0 && j > 0) if (board[i - 1][j - 1]) return true;//up,left
	if (i > 0 && j < BOARD_SIZE - 1) if (board[i - 1][j + 1]) return true;//up,right
	if (i < BOARD_SIZE - 1 && j > 0) if (board[i + 1][j - 1]) return true;//down,left
	if (i < BOARD_SIZE - 1 && j < BOARD_SIZE - 1) if (board[i + 1][j + 1]) return true;//down,right
	return false;
}
/*�ҳ����ܵ����ӵ㣬���ط�����ߵ�ǰ���*/
multimap<int, Command, greater<int>> generate_possible_moves() {
	Command possible_move;
	stack<Command>possible_moves;//������ܵ��ƶ�
	multimap<int, Command, greater<int>> ordered_possible_moves;//����multimap�������ڷ����Ľ�������multimap��ԭ�����п����ж���������ͬ��
	for (int i = 0; i < BOARD_SIZE; i++)
		for (int j = 0; j < BOARD_SIZE; j++)
			if (board[i][j] == 0 && is_around(i, j)) {
				possible_move = { i,j };
				possible_moves.push(possible_move);
			}//����ǿյ������Χ�˸��������ӣ�������Ϊ���ܵ��ƶ���ջ
	Command next_move;
	while (!possible_moves.empty()) {//ɨ��ջ��ÿһ�����ܵ����ӵ㣬�������������multimap��
		next_move = possible_moves.top();
		int point_score = evaluate_point(next_move);
		ordered_possible_moves.insert(pair<int, Command>(point_score, next_move));
		possible_moves.pop();
	}
	multimap<int, Command, greater<int>> ans;
	auto best_move = ordered_possible_moves.begin();
	for (int i = 0; i < 5 && best_move != ordered_possible_moves.end(); i++) {//����ǰ����㣬���ش������ǵİ������������е�multimap
		ans.insert(*best_move);
		best_move++;
	}
	return ans;
}
/*ֻ��һ�㣬�ҳ��������ӵ��з�����ߵĲ���������*/
Command single_max() {
	Command choice = generate_possible_moves().begin()->second;
	return choice;
}
/*�з�����*/
void place(Command cmd) {
	board[cmd.x][cmd.y] = enemy_flag;
}
/*��ʼ������*/
void start() {
	cont = 0;
	memset(board, 0, sizeof(board));
	board[5][5] = white;
	board[6][6] = white;
	board[5][6] = black;
	board[6][5] = black;
	put_black(6, 8);
	put_black(5, 9);
	put_white(5, 8);
	put_white(6, 9);
	enemy_flag = 3 - my_flag;
}
/*�ü����ж������ú��������ѵ�λ������*/
void turn() {
	Command my_move = single_max();
	int x = my_move.x, y = my_move.y;
	board[x][y] = my_flag;
	

	outtextxy(0, CELL_SIZE / 2, _T("�ҵ����ӵ�λ:"));
	outtextxy(int(3.25 * CELL_SIZE), CELL_SIZE / 2, change(x));
	outtextxy(int(3.75 * CELL_SIZE), CELL_SIZE / 2, change(y));

	string result = "PLACE ";
	if (x < 10) result += change(x);
	if (x < 10) result += " ";
	if (x == 10) result += "10 ";
	if (x == 11) result += "11 ";

	if (y < 10) result += change(y);
	if (y < 10) result += " TURN";
	if (y == 10) result += "10 TURN";
	if (y == 11) result += "11 TURN";
	
	if (OpenClipboard(NULL)) {
		// ��ռ��а�����
		EmptyClipboard();

		// ����ȫ���ڴ棬�������ݸ��ƽ�ȥ
		HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, result.size() + 1);
		if (hMem != NULL) {
			LPVOID pData = GlobalLock(hMem);
			if (pData != NULL) {
				memcpy(pData, result.c_str(), result.size() + 1);
				GlobalUnlock(hMem);

				// ���������õ����а�
				SetClipboardData(CF_TEXT, hMem);
			}
		}

		// �رռ��а�
		CloseClipboard();
	}
	if (my_flag == black)
		put_black(y, x + 3);
	if (my_flag == white)
		put_white(y, x + 3);
	cont++;
}

/*����ָ����ú��ʵĺ���*/
void loop() {
	setbkcolor(BLACK);
	settextcolor(WHITE);
	outtextxy(9 * CELL_SIZE, CELL_SIZE, _T("        "));
	outtextxy(9 * CELL_SIZE, int(1.5 * CELL_SIZE), _T("��������"));
	outtextxy(9 * CELL_SIZE, 2 * CELL_SIZE, _T("        "));
	ExMessage msg;
	while (1) {
		msg = getmessage(EX_MOUSE);
		if (CELL_SIZE < msg.x && msg.x < 13 * CELL_SIZE && 3 * CELL_SIZE < msg.y && msg.y < 15 * CELL_SIZE) {
			if (msg.message == WM_LBUTTONDOWN) {
				//�����ӣ�ģ��з���
				int x = msg.x / CELL_SIZE - 1;
				int y = msg.y / CELL_SIZE;
				if (board[y - 3][x] != nothing) {
					status = 1;
					break;
				}
				board[y - 3][x] = enemy_flag;
				if (enemy_flag == black)
					put_black(x, y);
				if (enemy_flag == white)
					put_white(x, y);
				if (is_over()) break;
				turn();
				if (is_over()) break;
			}
			FlushMouseMsgBuffer();
		}
		else if (9 * CELL_SIZE < msg.x && msg.x < 11 * CELL_SIZE && 1 * CELL_SIZE < msg.y && msg.y < 2.5 * CELL_SIZE) {
			setbkcolor(WHITE);
			settextcolor(BLACK);
			outtextxy(9 * CELL_SIZE, CELL_SIZE, _T("        "));
			outtextxy(9 * CELL_SIZE, int(1.5 * CELL_SIZE), _T("��������"));
			outtextxy(9 * CELL_SIZE, 2 * CELL_SIZE, _T("        "));
			if (msg.message == WM_LBUTTONDOWN) {
				status = 1;
				setbkcolor(BLACK);
				outtextxy(9 * CELL_SIZE, 2 * CELL_SIZE, _T("        "));
				break;
			}
		}
		else {
			setbkcolor(BLACK);
			settextcolor(WHITE);
			outtextxy(9 * CELL_SIZE, CELL_SIZE, _T("        "));
			outtextxy(9 * CELL_SIZE, int(1.5 * CELL_SIZE), _T("��������"));
			outtextxy(9 * CELL_SIZE, 2 * CELL_SIZE, _T("        "));
		}
	}
}

/*main����*/
int main(int argc, char* argv[]) {
	while (1) {
		draw_board();
		pre_prepare();
		start();
		if (my_flag == black)
			turn();
		loop();
		show_answer();
		if (!cccontinue())
			break;
		cleardevice();
	}
	return 0;
}