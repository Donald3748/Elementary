#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stack>
#include <map>
// ADD: Grafical interface
#include<graphics.h>

#define BOARD_SIZE  12
// enum:1 for black , 2 for white
enum { nothing, black, white };
// define the size of the graphic unit
const int CELL_SIZE = 40;
// template strings for kmp search
struct Template {
	std::string format;
	int next[6];
	int score;
};
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
// the position of the chess
struct Command {
	int x;
	int y;
	Command() :x(0), y(0) {};
	Command& operator=(std::pair<int, int>t) {
		x = t.first;
		y = t.second;
		return *this;
	}
};
using namespace std;

int board[BOARD_SIZE][BOARD_SIZE];
int my_flag;
int enemy_flag;
int status;

bool kmpSearch(const string&, const string&, const int next[]);
inline char intToChar(int i);
// draw the chess board
void drawChessBoard()
{
	// initialize the graphic interface
	initgraph(CELL_SIZE * (BOARD_SIZE + 2), CELL_SIZE * (BOARD_SIZE + 4));

	setfillcolor(CYAN);
	fillrectangle(CELL_SIZE, 3 * CELL_SIZE, 13 * CELL_SIZE, 15 * CELL_SIZE);

	setlinestyle(PS_SOLID, 1);
	setlinecolor(WHITE);
	// draw lines
	for (int i = 0; i <= BOARD_SIZE; ++i)
	{
		line(CELL_SIZE, (i + 3) * CELL_SIZE, CELL_SIZE * (BOARD_SIZE + 1), (i + 3) * CELL_SIZE);
		line((i + 1) * CELL_SIZE, 3 * CELL_SIZE, (i + 1) * CELL_SIZE, CELL_SIZE * (BOARD_SIZE + 3));
	}
	// set text style
	settextstyle(int(0.5 * CELL_SIZE), 0, _T("宋体"));
	// draw the border
	for (int i = 0; i < BOARD_SIZE; i++) {
		outtextxy((i + 1) * CELL_SIZE + CELL_SIZE / 3, int(2.5 * CELL_SIZE), intToChar(i));
		outtextxy(CELL_SIZE - CELL_SIZE / 3, (i + 3) * CELL_SIZE + CELL_SIZE / 3, intToChar(i));
	}
}
// place black pawn
void putBlackPawn(int x, int y)
{
	setfillcolor(BLACK);
	fillcircle(int((x + 1.5) * CELL_SIZE), int((y + 0.5) * CELL_SIZE), CELL_SIZE / 2);
}
// place white pawn
void putWhitePawn(int x, int y)
{
	setfillcolor(WHITE);
	fillcircle(int((x + 1.5) * CELL_SIZE), int((y + 0.5) * CELL_SIZE), CELL_SIZE / 2);
}
// change integer to char
inline char intToChar(int i)
{
	if (i < 10) return char(i + 48);
	else  return char(i + 55);
}
// output colored text on specific point
void outColoredText(double a, double b, string f, int bkcolor, int textcolor)
{
	setbkcolor(bkcolor);
	settextcolor(textcolor);
	outtextxy(static_cast<int>(a * CELL_SIZE), static_cast<int>(b * CELL_SIZE), _T("        "));
	outtextxy(static_cast<int>(a * CELL_SIZE), static_cast<int>((b + 0.5) * CELL_SIZE), f.c_str());
	outtextxy(static_cast<int>(a * CELL_SIZE), static_cast<int>((b + 1) * CELL_SIZE), _T("        "));
}

void chooseBeginner() {
	outColoredText(3, 1, "  人先  ", BLACK, WHITE);
	outColoredText(9, 1, "  AI先  ", BLACK, WHITE);
	ExMessage msg;
	while (1) {
		msg = getmessage(EX_MOUSE);
		if (3 * CELL_SIZE < msg.x && msg.x < 5 * CELL_SIZE && 1 * CELL_SIZE < msg.y && msg.y < 2.5 * CELL_SIZE) {
			outColoredText(3, 1, "  人先  ", WHITE, BLACK);
			if (msg.message == WM_LBUTTONDOWN) {
				my_flag = white;
				break;
			}
		}
		else
			outColoredText(3, 1, "  人先  ", BLACK, WHITE);
		if (9 * CELL_SIZE < msg.x && msg.x < 11 * CELL_SIZE && 1 * CELL_SIZE < msg.y && msg.y < 2.5 * CELL_SIZE) {
			outColoredText(9, 1, "  AI先  ", WHITE, BLACK);
			if (msg.message == WM_LBUTTONDOWN) {
				my_flag = black;
				break;
			}
		}
		else
			outColoredText(9, 1, "  AI先  ", BLACK, WHITE);
	}
	outColoredText(3, 1, "        ", BLACK, WHITE);
	outColoredText(9, 1, "        ", BLACK, WHITE);
	if (my_flag == white)
		outtextxy(6 * CELL_SIZE, 2 * CELL_SIZE, _T("您执黑棋"));
	if (my_flag == black)
		outtextxy(6 * CELL_SIZE, 2 * CELL_SIZE, _T("您执白棋"));
}
// judge whether the game is over
bool isOver() {
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
		if (kmpSearch(lines[i], patterns[0].format, patterns[0].next)) {
			status = 1;
			return true;
		}
		if (kmpSearch(lines[i], "22222", patterns[0].next)) {
			status = 2;
			return true;
		}
	}
	return false;
}
void showResult() {
	outtextxy(6 * CELL_SIZE, 2 * CELL_SIZE, _T("        "));
	if (status == 1)
		outColoredText(6, 0.5, " 您输了 ", WHITE, BLACK);
	if (status == 2)
		outColoredText(6, 0.5, " 您赢了 ", WHITE, BLACK);
}

bool isToContinue() {
	ExMessage msg;
	while (1) {
		msg = getmessage(EX_MOUSE);
		if (9 * CELL_SIZE < msg.x && msg.x < 11 * CELL_SIZE && 1 * CELL_SIZE < msg.y && msg.y < 2.5 * CELL_SIZE) {
			outColoredText(9, 1, "点我退出", WHITE, BLACK);
			if (msg.message == WM_LBUTTONDOWN)
				return 0;
		}
		else {
			outColoredText(9, 1, "点我退出", BLACK, WHITE);
		}
		if (3 * CELL_SIZE < msg.x && msg.x < 5 * CELL_SIZE && 1 * CELL_SIZE < msg.y && msg.y < 2.5 * CELL_SIZE) {
			outColoredText(3, 1, "继续游戏", WHITE, BLACK);
			if (msg.message == WM_LBUTTONDOWN) {
				return 1;
			}
		}
		else {
			outColoredText(3, 1, "继续游戏", BLACK, WHITE);
		}
	}
}

bool kmpSearch(const string& s, const string& p, const int next[]) {
	int i = 0;
	int j = 0;
	int s_size = s.size();
	int p_size = p.size();
	while (i < s_size && j < p_size) {
		if (j == -1 || s[i] == p[j]) {
			i++;
			j++;
		}
		else {
			j = next[j];
		}
	}
	if (j == p_size)
		return true;
	return false;
}

int evaluatePoint(Command& p) {
	int result = 0;
	int i;
	int role = my_flag;

	string my_lines[4];
	string enemy_lines[4];
	for (auto& line : my_lines) {
		line.reserve(15);
	}
	for (auto& line : enemy_lines) {
		line.reserve(15);
	}
	//  "|"
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
	//  "--"
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
	//  "\"
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
	//  "/"
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

	for (i = 0; i < 4; i++)
		for (int j = 0; j < 16; j++) {
			if (kmpSearch(my_lines[i], patterns[j].format, patterns[j].next))
				result += (patterns[j].score + patterns[j].score / 10);
			if (kmpSearch(enemy_lines[i], patterns[j].format, patterns[j].next))
				result += patterns[j].score;
		}
	return result;
}

inline bool isAround(int i, int j) {
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

multimap<int, Command, greater<int>> generatePossibleMoves() {
	Command possible_move;
	stack<Command>possible_moves;
	multimap<int, Command, greater<int>> ordered_possible_moves;
	for (int i = 0; i < BOARD_SIZE; i++)
		for (int j = 0; j < BOARD_SIZE; j++)
			if (board[i][j] == 0 && isAround(i, j)) {
				possible_move = make_pair(i, j);
				possible_moves.push(possible_move);
			}
	Command next_move;
	while (!possible_moves.empty()) {
		next_move = possible_moves.top();
		int point_score = evaluatePoint(next_move);
		ordered_possible_moves.insert(pair<int, Command>(point_score, next_move));
		possible_moves.pop();
	}
	multimap<int, Command, greater<int>> ans;
	auto best_move = ordered_possible_moves.begin();
	for (int i = 0; i < 5 && best_move != ordered_possible_moves.end(); i++) {
		ans.insert(*best_move);
		best_move++;
	}
	return ans;
}

Command singleMoveForecast() {
	Command choice = generatePossibleMoves().begin()->second;
	return choice;
}

void initialize() {
	memset(board, 0, sizeof(board));
	board[5][5] = white;
	board[6][6] = white;
	board[5][6] = black;
	board[6][5] = black;
	putBlackPawn(6, 8);
	putBlackPawn(5, 9);
	putWhitePawn(5, 8);
	putWhitePawn(6, 9);
	enemy_flag = 3 - my_flag;
}

void turn() {
	Command my_move = singleMoveForecast();
	int x = my_move.x, y = my_move.y;
	board[x][y] = my_flag;
	//setbkcolor(BLACK);
	//outtextxy(0, CELL_SIZE / 2, _T("AI落子位置为："));
	//outtextxy(int(3.25 * CELL_SIZE), CELL_SIZE / 2, change(x));
	//outtextxy(int(3.75 * CELL_SIZE), CELL_SIZE / 2, change(y));
	//string result = "PLACE ";
	//if (x < 10) result += change(x);
	//if (x < 10) result += " ";
	//if (x == 10) result += "10 ";
	//if (x == 11) result += "11 ";
	//if (y < 10) result += change(y);
	//if (y < 10) result += " TURN";
	//if (y == 10) result += "10 TURN";
	//if (y == 11) result += "11 TURN";
	//if (OpenClipboard(NULL)) {
	//	EmptyClipboard();
	//	HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, result.size() + 1);
	//	if (hMem != NULL) {
	//		LPVOID pData = GlobalLock(hMem);
	//		if (pData != NULL) {
	//			memcpy(pData, result.c_str(), result.size() + 1);
	//			GlobalUnlock(hMem);
	//			SetClipboardData(CF_TEXT, hMem);
	//		}
	//	}
	//	CloseClipboard();
	//}
	if (my_flag == black)
		putBlackPawn(y, x + 3);
	if (my_flag == white)
		putWhitePawn(y, x + 3);
}

void loop() {
	ExMessage msg;
	while (1)
	{
		msg = getmessage(EX_MOUSE);
		if (CELL_SIZE < msg.x && msg.x < 13 * CELL_SIZE && 3 * CELL_SIZE < msg.y && msg.y < 15 * CELL_SIZE)
		{
			if (msg.message == WM_LBUTTONDOWN)
			{
				int x = msg.x / CELL_SIZE - 1;
				int y = msg.y / CELL_SIZE;
				if (board[y - 3][x] != nothing)
				{
					status = 1;
					break;
				}
				board[y - 3][x] = enemy_flag;
				if (enemy_flag == black)
					putBlackPawn(x, y);
				if (enemy_flag == white)
					putWhitePawn(x, y);
				if (isOver()) break;
				turn();
				if (isOver()) break;
			}
			FlushMouseMsgBuffer();
		}
		else if (9 * CELL_SIZE < msg.x && msg.x < 11 * CELL_SIZE && 1 * CELL_SIZE < msg.y && msg.y < 2.5 * CELL_SIZE) 
		{
			outColoredText(9, 1, "布响丸辣", WHITE, BLACK);
			if (msg.message == WM_LBUTTONDOWN) {
				status = 1;
				setbkcolor(BLACK);
				outtextxy(9 * CELL_SIZE, 2 * CELL_SIZE, _T("        "));
				break;
			}
		}
		else {
			outColoredText(9, 1, "布响丸辣", BLACK, WHITE);
		}
	}
}

int main() {
	while (1) {
		drawChessBoard();
		chooseBeginner();
		initialize();
		if (my_flag == black)
			turn();
		loop();
		showResult();
		if (!isToContinue())
			break;
		cleardevice();
	}
	return 0;
}