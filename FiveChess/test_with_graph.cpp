#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include <stack>
#include <map>

#include<graphics.h>
using namespace std;

#define BOARD_SIZE  12
enum { nothing, black, white };//1为黑棋，2为白棋

int board[BOARD_SIZE][BOARD_SIZE];
int my_flag;
int enemy_flag;
int status;//1为My_flag的胜利，2就输了
int cont;
/*棋子格式，储存棋子坐标并提供一个赋值重载，便于更改棋子储存位置*/
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
/*搜索的模板串，三个数据成员分别对应串模板，next数组(便于kmp搜索)，相应分数*/
struct Template {
	string format;
	int next[6];
	int score;
};
/*const 标记的储存模板串的数组，便于搜索*/
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
// 定义常量
const int CELL_SIZE = 40;
// 绘制五子棋棋盘
void draw_board() {
	// 初始化绘图窗口
	
	initgraph(CELL_SIZE * (BOARD_SIZE + 2), CELL_SIZE * (BOARD_SIZE + 4));
	setfillcolor(BROWN);
	fillrectangle(CELL_SIZE, 3 * CELL_SIZE, 13 * CELL_SIZE, 15 * CELL_SIZE);
	// 绘制棋盘网格
	setbkcolor(WHITE);
	setlinestyle(PS_SOLID, 1);
	setlinecolor(WHITE);
	for (int i = 0; i <= BOARD_SIZE; ++i) {
		line(CELL_SIZE, (i + 3) * CELL_SIZE, CELL_SIZE * (BOARD_SIZE + 1), (i + 3) * CELL_SIZE);
		//line(CELL_SIZE, (i + 1) * CELL_SIZE, CELL_SIZE * (BOARD_SIZE - 1), (i + 1) * CELL_SIZE);
		line((i + 1) * CELL_SIZE, 3 * CELL_SIZE, (i + 1) * CELL_SIZE, CELL_SIZE * (BOARD_SIZE + 3));
	}
}
// 落黑子的方法，x和y分别表示落子的坐标
void put_black(int x, int y) {
	// 绘制黑子
	setfillcolor(BLACK);
	fillcircle(int((x + 1.5) * CELL_SIZE), int((y + 0.5) * CELL_SIZE), CELL_SIZE / 2);
}
// 落白子的方法，x和y分别表示落子的坐标
void put_white(int x, int y) {
	// 绘制白子
	setfillcolor(WHITE);
	fillcircle(int((x + 1.5) * CELL_SIZE), int((y + 0.5) * CELL_SIZE), CELL_SIZE / 2);
}
char change(int i) {
	if (i < 10) return char(i + 48);
	else  return char(i + 55);
}
// 鼠标选择棋色
inline void indicate(int f, int s) {
	settextstyle(int(0.5 * CELL_SIZE), 0, _T("宋体"));
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
		outtextxy(3 * CELL_SIZE, int(1.5 * CELL_SIZE), _T("  我先  "));
		outtextxy(3 * CELL_SIZE, 2 * CELL_SIZE, _T("        "));
	}
	if (f == 2) {
		outtextxy(9 * CELL_SIZE, 1 * CELL_SIZE, _T("        "));
		outtextxy(9 * CELL_SIZE, int(1.5 * CELL_SIZE), _T("  你先  "));
		outtextxy(9 * CELL_SIZE, 2 * CELL_SIZE, _T("        "));
	}
}
void pre_prepare() {
	// 输出汉字
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
		outtextxy(6 * CELL_SIZE, 2 * CELL_SIZE, _T("您执黑棋"));
	if (my_flag == black)
		outtextxy(6 * CELL_SIZE, 2 * CELL_SIZE, _T("您执白棋"));
}
// 判断对局是否结束
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
		outtextxy(6 * CELL_SIZE, 1 * CELL_SIZE, _T(" 您输了 "));
	if (status == 2)
		outtextxy(6 * CELL_SIZE, 1 * CELL_SIZE, _T(" 您赢了 "));
	outtextxy(6 * CELL_SIZE, int(1.5 * CELL_SIZE), _T("        "));
} 
bool cccontinue() {
	if (status == 1) {
		setbkcolor(BLACK);
		settextcolor(WHITE);
		outtextxy(CELL_SIZE, int(15.1 * CELL_SIZE), _T("恭喜你！您被狠狠薄纱！而我只用了"));
		outtextxy(9 * CELL_SIZE, int(15.1 * CELL_SIZE), char(cont / 10 + 48));
		outtextxy(int(9.25 * CELL_SIZE), int(15.1 * CELL_SIZE), char(cont % 10 + 48));
		outtextxy(int(9.5 * CELL_SIZE), int(15.1 * CELL_SIZE), _T("步"));
	}
	if (status == 2) {
		setbkcolor(BLACK);
		settextcolor(WHITE);
		outtextxy(CELL_SIZE, int(2.5 * CELL_SIZE), _T("可恶！竟然被你赢了"));
	}
	outtextxy(9 * CELL_SIZE, CELL_SIZE, _T("        "));
	outtextxy(9 * CELL_SIZE, int(1.5 * CELL_SIZE), _T("点我退出"));
	outtextxy(9 * CELL_SIZE, 2 * CELL_SIZE, _T("        "));
	outtextxy(3 * CELL_SIZE, CELL_SIZE, _T("        "));
	outtextxy(3 * CELL_SIZE, int(1.5 * CELL_SIZE), _T("继续游戏"));
	outtextxy(3 * CELL_SIZE, 2 * CELL_SIZE, _T("        "));
	ExMessage msg;
	while (1) {
		msg = getmessage(EX_MOUSE);
		if (9 * CELL_SIZE < msg.x && msg.x < 11 * CELL_SIZE && 1 * CELL_SIZE < msg.y && msg.y < 2.5 * CELL_SIZE) {
			setbkcolor(WHITE);
			settextcolor(BLACK);
			outtextxy(9 * CELL_SIZE, CELL_SIZE, _T("        "));
			outtextxy(9 * CELL_SIZE, int(1.5 * CELL_SIZE), _T("点我退出"));
			outtextxy(9 * CELL_SIZE, 2 * CELL_SIZE, _T("        "));
			if (msg.message == WM_LBUTTONDOWN)
				return 0;

		}
		else {
			setbkcolor(BLACK);
			settextcolor(WHITE);
			outtextxy(9 * CELL_SIZE, CELL_SIZE, _T("        "));
			outtextxy(9 * CELL_SIZE, int(1.5 * CELL_SIZE), _T("点我退出"));
			outtextxy(9 * CELL_SIZE, 2 * CELL_SIZE, _T("        "));
		}
		if (3 * CELL_SIZE < msg.x && msg.x < 5 * CELL_SIZE && 1 * CELL_SIZE < msg.y && msg.y < 2.5 * CELL_SIZE) {
			setbkcolor(WHITE);
			settextcolor(BLACK);
			outtextxy(3 * CELL_SIZE, CELL_SIZE, _T("        "));
			outtextxy(3 * CELL_SIZE, int(1.5 * CELL_SIZE), _T("继续游戏"));
			outtextxy(3 * CELL_SIZE, 2 * CELL_SIZE, _T("        "));
			if (msg.message == WM_LBUTTONDOWN) {
				return 1;
			}
		}
		else {
			setbkcolor(BLACK);
			settextcolor(WHITE);
			outtextxy(3 * CELL_SIZE, CELL_SIZE, _T("        "));
			outtextxy(3 * CELL_SIZE, int(1.5 * CELL_SIZE), _T("继续游戏"));
			outtextxy(3 * CELL_SIZE, 2 * CELL_SIZE, _T("        "));
		}
	}
}



/*kmp搜索，效率更高*/
bool kmp_search(const string& s, const string& p, const int next[]) {
	int i = 0;
	int j = 0;
	int s_size = s.size();
	int p_size = p.size();
	while (i < s_size && j < p_size) {
		/*如果j == -1，或者当前字符匹配成功（即s[i] == p[j]），都令i++，j++*/
		if (j == -1 || s[i] == p[j]) {
			i++;
			j++;
		}
		else {
			/*如果j != -1，且当前字符匹配失败（即s[i] != p[j]），则令 i 不变，j = next[j]*/
			j = next[j];
		}
	}
	if (j == p_size)
		return true;
	return false;//没找到返回false
}
/*对一点的估值函数，仅生效于未落子点*/
int evaluate_point(Command& p) {
	int result = 0;//最终分数
	int i;//循环基准
	int role = my_flag;

	string my_lines[4];
	string enemy_lines[4];
	//提前分配空间，便于插入时提高效率
	for (auto& line : my_lines) {
		line.reserve(15);
	}
	for (auto& line : enemy_lines) {
		line.reserve(15);
	}
	//  "|"的部分
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
	//  "--"的部分
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
	//  "\"的部分
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
	//  "/"的部分
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

	/*搜索部分, 在四个方向上的扫描串中搜索模板串，搜索成功便加相应的分数*/
	for (i = 0; i < 4; i++)
		for (int j = 0; j < 16; j++) {
			if (kmp_search(my_lines[i], patterns[j].format, patterns[j].next))
				result += (patterns[j].score + patterns[j].score / 10);//对己方有利的局面加分更多，占更大权重
			if (kmp_search(enemy_lines[i], patterns[j].format, patterns[j].next))
				result += patterns[j].score;
		}
	return result;
	/*返回分数是对己方分数与对敌方分数之和（对己方有利的局面和对对方有利的局面都重要，但是自己的分数更重要，因此权重更大）*/
}
/*判断一个未落子点周围八个合法点是否已经有落子*/
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
/*找出可能的落子点，返回分数最高的前五个*/
multimap<int, Command, greater<int>> generate_possible_moves() {
	Command possible_move;
	stack<Command>possible_moves;//储存可能的移动
	multimap<int, Command, greater<int>> ordered_possible_moves;//利用multimap建立关于分数的降序排序（multimap的原因是有可能有多个点分数相同）
	for (int i = 0; i < BOARD_SIZE; i++)
		for (int j = 0; j < BOARD_SIZE; j++)
			if (board[i][j] == 0 && is_around(i, j)) {
				possible_move = { i,j };
				possible_moves.push(possible_move);
			}//如果是空点而且周围八格内有落子，将其作为可能的移动入栈
	Command next_move;
	while (!possible_moves.empty()) {//扫描栈中每一个可能的落子点，求其分数并插入multimap中
		next_move = possible_moves.top();
		int point_score = evaluate_point(next_move);
		ordered_possible_moves.insert(pair<int, Command>(point_score, next_move));
		possible_moves.pop();
	}
	multimap<int, Command, greater<int>> ans;
	auto best_move = ordered_possible_moves.begin();
	for (int i = 0; i < 5 && best_move != ordered_possible_moves.end(); i++) {//遍历前五个点，返回储存他们的按分数降序排列的multimap
		ans.insert(*best_move);
		best_move++;
	}
	return ans;
}
/*只搜一层，找出可能落子点中分数最高的并将它返回*/
Command single_max() {
	Command choice = generate_possible_moves().begin()->second;
	return choice;
}
/*敌方落子*/
void place(Command cmd) {
	board[cmd.x][cmd.y] = enemy_flag;
}
/*初始化工作*/
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
/*该己方行动，调用函数求出最佳点位并落子*/
void turn() {
	Command my_move = single_max();
	int x = my_move.x, y = my_move.y;
	board[x][y] = my_flag;
	

	outtextxy(0, CELL_SIZE / 2, _T("我的落子点位:"));
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
		// 清空剪切板内容
		EmptyClipboard();

		// 分配全局内存，并将数据复制进去
		HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, result.size() + 1);
		if (hMem != NULL) {
			LPVOID pData = GlobalLock(hMem);
			if (pData != NULL) {
				memcpy(pData, result.c_str(), result.size() + 1);
				GlobalUnlock(hMem);

				// 将数据设置到剪切板
				SetClipboardData(CF_TEXT, hMem);
			}
		}

		// 关闭剪切板
		CloseClipboard();
	}
	if (my_flag == black)
		put_black(y, x + 3);
	if (my_flag == white)
		put_white(y, x + 3);
	cont++;
}

/*根据指令调用合适的函数*/
void loop() {
	setbkcolor(BLACK);
	settextcolor(WHITE);
	outtextxy(9 * CELL_SIZE, CELL_SIZE, _T("        "));
	outtextxy(9 * CELL_SIZE, int(1.5 * CELL_SIZE), _T("部响丸辣"));
	outtextxy(9 * CELL_SIZE, 2 * CELL_SIZE, _T("        "));
	ExMessage msg;
	while (1) {
		msg = getmessage(EX_MOUSE);
		if (CELL_SIZE < msg.x && msg.x < 13 * CELL_SIZE && 3 * CELL_SIZE < msg.y && msg.y < 15 * CELL_SIZE) {
			if (msg.message == WM_LBUTTONDOWN) {
				//人落子（模拟敌方）
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
			outtextxy(9 * CELL_SIZE, int(1.5 * CELL_SIZE), _T("部响丸辣"));
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
			outtextxy(9 * CELL_SIZE, int(1.5 * CELL_SIZE), _T("部响丸辣"));
			outtextxy(9 * CELL_SIZE, 2 * CELL_SIZE, _T("        "));
		}
	}
}

/*main函数*/
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