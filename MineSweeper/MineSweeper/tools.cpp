#include"needings.h"

/*得到各个参数*/
void mine_sweeper::get_mode_and_initialize() {
	initgraph(500, 400);
	settextstyle(int(CELL_SIZE) - 1, 0, _T("宋体"));
	/*待定*/
	//outtextxy(2 * CELL_SIZE, 11 * CELL_SIZE, _T("Customize"));
	/*待定*/
	enum { _OUT, _EASY, _MEDIUM, _EXPERT };
	int pos = _OUT;
	int u_pos = _OUT;
	setfillcolor(BLACK);
	setbkcolor(BLACK);
	settextcolor(WHITE);
	fillrectangle(2 * CELL_SIZE, 1 * CELL_SIZE, 10 * CELL_SIZE, 4 * CELL_SIZE);
	outtextxy(3 * CELL_SIZE, 2 * CELL_SIZE, _T("Easy    9x9 "));//10
	fillrectangle(2 * CELL_SIZE, 5 * CELL_SIZE, 10 * CELL_SIZE, 8 * CELL_SIZE);
	outtextxy(3 * CELL_SIZE, 6 * CELL_SIZE, _T("Medium 16x16"));//40
	fillrectangle(2 * CELL_SIZE, 9 * CELL_SIZE, 10 * CELL_SIZE, 12 * CELL_SIZE);
	outtextxy(3 * CELL_SIZE, 10 * CELL_SIZE, _T("Expert 30x16"));//99
	ExMessage msg;
	while (1) {
		msg = getmessage(EX_MOUSE);
		int x = msg.x / CELL_SIZE;
		int y = msg.y / CELL_SIZE;
		if (1 < x && x < 10 && 0 < y && y < 4) pos = _EASY;
		else if (1 < x && x < 10 && 4 < y && y < 8) pos = _MEDIUM;
		else if (1 < x && x < 10 && 8 < y && y < 12) pos = _EXPERT;
		else pos = _OUT;
		if (msg.message == WM_MOUSEMOVE)
			if (u_pos != pos) {
				setfillcolor(BLACK);
				setbkcolor(BLACK);
				settextcolor(WHITE);
				switch (u_pos) {
				case _EASY:
					fillrectangle(2 * CELL_SIZE, 1 * CELL_SIZE, 10 * CELL_SIZE, 4 * CELL_SIZE);
					outtextxy(3 * CELL_SIZE, 2 * CELL_SIZE, _T("Easy    9x9 "));//10
					break;
				case _MEDIUM:
					fillrectangle(2 * CELL_SIZE, 5 * CELL_SIZE, 10 * CELL_SIZE, 8 * CELL_SIZE);
					outtextxy(3 * CELL_SIZE, 6 * CELL_SIZE, _T("Medium 16x16"));//40
					break;
				case _EXPERT:
					fillrectangle(2 * CELL_SIZE, 9 * CELL_SIZE, 10 * CELL_SIZE, 12 * CELL_SIZE);
					outtextxy(3 * CELL_SIZE, 10 * CELL_SIZE, _T("Expert 16x30"));//99
					break;
				}
				setfillcolor(WHITE);
				setbkcolor(WHITE);
				settextcolor(BLACK);
				switch (pos) {
				case _EASY:
					fillrectangle(2 * CELL_SIZE, 1 * CELL_SIZE, 10 * CELL_SIZE, 4 * CELL_SIZE);
					outtextxy(3 * CELL_SIZE, 2 * CELL_SIZE, _T("Easy    9x9 "));//10
					break;
				case _MEDIUM:
					fillrectangle(2 * CELL_SIZE, 5 * CELL_SIZE, 10 * CELL_SIZE, 8 * CELL_SIZE);
					outtextxy(3 * CELL_SIZE, 6 * CELL_SIZE, _T("Medium 16x16"));//40
					break;
				case _EXPERT:
					fillrectangle(2 * CELL_SIZE, 9 * CELL_SIZE, 10 * CELL_SIZE, 12 * CELL_SIZE);
					outtextxy(3 * CELL_SIZE, 10 * CELL_SIZE, _T("Expert 16x30"));//99
					break;
				}
				u_pos = pos;
			}
		if (msg.message == WM_LBUTTONDOWN)
			if (pos != _OUT) {
				switch (pos) {
				case _EASY:
					board_x = board_y = 9;
					mines_num = 10;
					break;
				case _MEDIUM:
					board_x = board_y = 16;
					mines_num = 40;
					break;
				case _EXPERT:
					board_x = 16;
					board_y = 30;
					mines_num = 99;
					break;
				}
				break;
			}
	}
	closegraph();
	board.resize(board_x, vector<int>(board_y));
	status.resize(board_x, vector<int>(board_y));
}

/*随机生成雷的位置，保证点击位置周围一定无雷，一定无位置重复的雷*/
void mine_sweeper::random_form() {
	vector<pair<int, int>>mines;
	srand(unsigned(time(0)));
	int tmp_y, tmp_x;
	int x = stay_y / CELL_SIZE - 2;
	int y = stay_x / CELL_SIZE - 1;
	for (int i = 0; i < mines_num; i++) {
		tmp_x = rand() % board_x;
		tmp_y = rand() % board_y;
		if (abs(x - tmp_x) < 2 && abs(y - tmp_y) < 2) {
			i--;
			continue;
		}
		bool is_unique = true;
		for (int j = 0; j < i - 1; j++)
			if (mines[j] == pair<int, int>(tmp_x, tmp_y)) {
				is_unique = false;
				break;
			}
		if (is_unique) mines.push_back(pair<int, int>(tmp_x, tmp_y));
		else i--;
	}
	for (auto& x : board)
		for (auto& y : x)
			y = 0;
	for (int i = 0; i < mines_num; i++)
		board[mines[i].first][mines[i].second] = 9;
	/*格点为9代表此点为雷*/
	for (int i = 0; i < mines_num; i++) {
		int x = mines[i].first;
		int y = mines[i].second;
		if (x < board_x - 1)
			board[x + 1][y]++;
		if (x > 0)
			board[x - 1][y]++;
		if (y < board_y - 1)
			board[x][y + 1]++;
		if (y > 0)
			board[x][y - 1]++;
		if (x < board_x - 1 && y < board_y - 1)
			board[x + 1][y + 1]++;
		if (x < board_x - 1 && y > 0)
			board[x + 1][y - 1]++;
		if (x > 0 && y < board_y - 1)
			board[x - 1][y + 1]++;
		if (x > 0 && y > 0)
			board[x - 1][y - 1]++;
	}
	for (auto& i : board)
		for (auto& j : i)
			j > 9 ? j = 9 : j;
}

/*打印出带颜色的雷区*/
void mine_sweeper::print_frame() {

	initgraph((board_y + 6) * CELL_SIZE, (board_x + 5) * CELL_SIZE);
	setlinestyle(PS_SOLID, 1);
	setlinecolor(WHITE);
	/*绘制横线*/
	for (int i = 0; i <= board_x; ++i)
		line(CELL_SIZE, (i + 2) * CELL_SIZE, CELL_SIZE * (board_y + 1), (i + 2) * CELL_SIZE);
	/*绘制竖线*/
	for (int i = 0; i <= board_y; ++i)
		line((i + 1) * CELL_SIZE, CELL_SIZE * 2, (i + 1) * CELL_SIZE, CELL_SIZE * (board_x + 2));
	/*我来调色！*/
	COLORREF ORANGE = HSVtoRGB(40, 1, 1);
	for (int x = 0; x < board_x; x++)
		for (int y = 0; y < board_y; y++) {
			if ((x + y) % 2)
				setfillcolor(COLOR_1);
			else
				setfillcolor(COLOR_2);
			fillrectangle((y + 1) * CELL_SIZE, (x + 2) * CELL_SIZE, (y + 2) * CELL_SIZE, (x + 3) * CELL_SIZE);
		}
	show_notice();
}

/*管理每一次的鼠标事件*/
void mine_sweeper::control_by_mouse() {
	/*设置大小为CELL_SIZE-1*/
	settextstyle(int(CELL_SIZE) - 1, 0, _T("宋体"));
	ExMessage msg;
	while (1) {
		msg = getmessage(EX_MOUSE);
		stay_x = msg.x;
		stay_y = msg.y;

		if (msg.message == WM_MOUSEMOVE)
			move();

		else if (msg.message == WM_LBUTTONDOWN) {
			if (is_first_click) {
				random_form();
				is_first_click = false;
			}
			click();
		}
		else if (msg.message == WM_RBUTTONDOWN) 
			flag();
		justice();
		if (is_over)
			break;
	}
	end_manage();
}

/*鼠标移动？在这里！*/
void mine_sweeper::move() {
	/*在左空一列，在上空两行*/

	/*以下x与y表示以竖直方向为x，水平方向为y*/
	int x = stay_y / CELL_SIZE - 2;
	int y = stay_x / CELL_SIZE - 1;
	/*与刚才不相同，表明移动了鼠标的位置*/
	/*且上一次移动位置必须处于正常状态*/
	if ((x != just_moved_x || y != just_moved_y) && status[just_moved_x][just_moved_y] == normal) {
		COLORREF ORANGE = HSVtoRGB(40, 1, 1);
		if ((just_moved_x + just_moved_y) % 2)
			setfillcolor(COLOR_1);
		else
			setfillcolor(COLOR_2);
		fillrectangle((just_moved_y + 1) * CELL_SIZE, (just_moved_x + 2) * CELL_SIZE, (just_moved_y + 2) * CELL_SIZE, (just_moved_x + 3) * CELL_SIZE);
	}
	/*鼠标当前位置变白*/
	if (0 <= x && x < board_x && 0 <= y && y < board_y && status[x][y] == normal) {
		setfillcolor(WHITE);
		fillrectangle((y + 1) * CELL_SIZE, (x + 2) * CELL_SIZE, (y + 2) * CELL_SIZE, (x + 3) * CELL_SIZE);
	}

	setbkcolor(BLACK);
	settextcolor(WHITE);
	if (x < 0 || x >= board_x || y < 0 || y >= board_y)
		outtextxy(CELL_SIZE, int((board_x + 2.25) * CELL_SIZE), _T("[当前位置]: 非法    "));
	else {
		if (status[x][y] == normal)
			outtextxy(CELL_SIZE, int((board_x + 2.25) * CELL_SIZE), _T("[当前位置]: 合法    "));
		if (status[x][y] == cleared)
			outtextxy(CELL_SIZE, int((board_x + 2.25) * CELL_SIZE), _T("[当前位置]: 已清除"));
		if (status[x][y] == marked)
			outtextxy(CELL_SIZE, int((board_x + 2.25) * CELL_SIZE), _T("[当前位置]: 已标记"));
		just_moved_x = x;
		just_moved_y = y;
	}
}

/*单击右键以标记地雷*/
void mine_sweeper::flag() {
	int x = stay_y / CELL_SIZE - 2;
	int y = stay_x / CELL_SIZE - 1;
	if (0 > x || x >= board_x || 0 > y || y >= board_y) return;
	if (board[x][y] == cleared) return;
	if ((x + y) % 2)
		setbkcolor(COLOR_1);
	else
		setbkcolor(COLOR_2);
	settextcolor(BLUE);
	if (status[x][y] == normal) {
		outtextxy((y + 1) * CELL_SIZE + 1, (x + 2) * CELL_SIZE + 1, _T("★"));
		setbkcolor(BLACK);
		settextcolor(WHITE);
		outtextxy(CELL_SIZE, int((board_x + 2.25) * CELL_SIZE), _T("[当前位置]: 已标记"));
		status[x][y] = marked;
		picked_num++;
		show_notice();
	}
	else if (status[x][y] == marked) {
		outtextxy((y + 1) * CELL_SIZE + 1, (x + 2) * CELL_SIZE + 1, _T("  "));
		setbkcolor(BLACK);
		settextcolor(WHITE);
		outtextxy(CELL_SIZE, int((board_x + 2.25) * CELL_SIZE), _T("[当前位置]: 合法  "));
		status[x][y] = normal;
		picked_num--;
		show_notice();
	}
}

/*单击左键以排雷*/
void mine_sweeper::click() {
	int x = stay_y / CELL_SIZE - 2;
	int y = stay_x / CELL_SIZE - 1;
	if (0 > x || x >= board_x || 0 > y || y >= board_y) return;
	if (status[x][y] != normal) return;
	/*扫雷失败*/
	if (board[x][y] == 9) 
		is_over = true;
	/*点击点四周有雷*/
	else if (board[x][y] != 0) {
		setfillcolor(BLACK);
		fillrectangle((y + 1) * CELL_SIZE, (x + 2) * CELL_SIZE, (y + 2) * CELL_SIZE, (x + 3) * CELL_SIZE);
		outtextxy(int((y + 1.25) * CELL_SIZE), (x + 2) * CELL_SIZE + 1, char(board[x][y] + 48));
		status[x][y] = cleared;
	}
	/*点击处四周无雷*/
	else {
		get_empty_cleared(x, y);
	}
	return;
}

/*连续消消消*/
void mine_sweeper::get_empty_cleared(int x, int y) {
	if (status[x][y] != normal) return;
	if (board[x][y] == 0) {
		setfillcolor(BLACK);
		fillrectangle((y + 1) * CELL_SIZE, (x + 2) * CELL_SIZE, (y + 2) * CELL_SIZE, (x + 3) * CELL_SIZE);
		status[x][y] = cleared;
		if (x < board_x - 1)
			get_empty_cleared(x + 1, y);
		if (x > 0)
			get_empty_cleared(x - 1, y);
		if (y < board_y - 1)
			get_empty_cleared(x, y + 1);
		if (y > 0)
			get_empty_cleared(x, y - 1);
		if (x < board_x - 1 && y < board_y - 1)
			get_empty_cleared(x + 1, y + 1);
		if (x < board_x - 1 && y > 0)
			get_empty_cleared(x + 1, y - 1);
		if (x > 0 && y < board_y - 1)
			get_empty_cleared(x - 1, y + 1);
		if (x > 0 && y > 0)
			get_empty_cleared(x - 1, y - 1);
	}
	else if (board[x][y] < 9) {
		setfillcolor(BLACK);
		fillrectangle((y + 1) * CELL_SIZE, (x + 2) * CELL_SIZE, (y + 2) * CELL_SIZE, (x + 3) * CELL_SIZE);
		outtextxy(int((y + 1.25) * CELL_SIZE), (x + 2) * CELL_SIZE + 1, char(board[x][y] + 48));
		status[x][y] = cleared;
	}
	return;
}

/*打印提示信息（好麻烦）*/
void mine_sweeper::show_notice() {
	float i = 0;
	settextstyle(int(CELL_SIZE) - 1, 0, _T("宋体"));
	outtextxy(int((i / 2 + 1) * CELL_SIZE), CELL_SIZE, _T("一共"));
	i += 4;
	string num = to_string(mines_num);
	for (size_t j = 0; j < num.size(); j++, i++)
		outtextxy(int((i / 2 + 1) * CELL_SIZE), CELL_SIZE, num[j]);
	outtextxy(int((i / 2 + 1) * CELL_SIZE), CELL_SIZE, _T("个雷，剩余"));
	i += 10;
	num = to_string(mines_num - picked_num);
	for (size_t j = 0; j < num.size(); j++, i++)
		outtextxy(int((i / 2 + 1) * CELL_SIZE), CELL_SIZE, num[j]);
	outtextxy(int((i / 2 + 1) * CELL_SIZE), CELL_SIZE, _T("个    "));
	i += 6;
}

/*判断雷局，游戏是否结束*/
void mine_sweeper::justice() {
	for (int x = 0; x < board_x; x++)
		for (int y = 0; y < board_y; y++)
			if (board[x][y] < 9)
				if (status[x][y] != cleared) return;

	is_win = true;
	is_over = true;
}

/*display answer after the end of the game*/
void mine_sweeper::end_manage() {
	setbkcolor(BLACK);
	int x = stay_y / CELL_SIZE - 2;
	int y = stay_x / CELL_SIZE - 1;
	if (is_win == true)
		outtextxy(CELL_SIZE, int((board_x + 2.25) * CELL_SIZE), _T("恭喜您！完胜！      "));
	else {
		outtextxy(CELL_SIZE, int((board_x + 2.25) * CELL_SIZE), _T("好可惜，您踩雷了 "));
		for (int i = 0; i < board_x; i++)
			for (int j = 0; j < board_y; j++) {
				if (status[i][j] == cleared) {
					setfillcolor(BLACK);
					setbkcolor(BLACK);
					settextcolor(WHITE);
				}
				else if ((i + j) % 2) {
					setfillcolor(COLOR_1);
					setbkcolor(COLOR_1);
					settextcolor(BLACK);
				}
				else {
					setfillcolor(COLOR_2);
					setbkcolor(COLOR_2);
					settextcolor(BLACK);
				}
				fillrectangle((j + 1) * CELL_SIZE, (i + 2) * CELL_SIZE, (j + 2) * CELL_SIZE, (i + 3) * CELL_SIZE);
				if (board[i][j] == 0);
				else if (board[i][j] == 9)
					outtextxy(int((j + 1.25) * CELL_SIZE), (i + 2) * CELL_SIZE + 1, '*');
				else
					outtextxy(int((j + 1.25) * CELL_SIZE), (i + 2) * CELL_SIZE + 1, char(board[i][j] + 48));
			}
		setfillcolor(RED);
		fillrectangle(int((y + 1) * CELL_SIZE), (x + 2) * CELL_SIZE, (y + 2) * CELL_SIZE, (x + 3) * CELL_SIZE);
		setbkcolor(RED);
		outtextxy(int((y + 1.25) * CELL_SIZE), (x + 2) * CELL_SIZE + 1, '*');
	}
}

/*已经结束了，你是否要继续？*/
bool mine_sweeper::is_to_continue() {
	ExMessage msg;
	setbkcolor(BLACK);
	settextcolor(WHITE);
	outtextxy(int((board_y + 2) * CELL_SIZE), (board_x - 4) * CELL_SIZE, _T("结束吧"));
	outtextxy(int((board_y + 2) * CELL_SIZE), (board_x)*CELL_SIZE, _T("想继续"));
	while (1) {
		msg = getmessage(EX_MOUSE);
		int x = msg.x / CELL_SIZE;
		int y = msg.y / CELL_SIZE;
		if (msg.message == WM_MOUSEMOVE) {
			if (board_y + 1 < x && x < board_y + 5 && board_x - 5 < y && y < board_x - 3) {
				setbkcolor(WHITE);
				settextcolor(BLACK);
				outtextxy((board_y + 2) * CELL_SIZE, (board_x - 4) * CELL_SIZE, _T("结束吧"));
			}
			else {
				setbkcolor(BLACK);
				settextcolor(WHITE);
				outtextxy((board_y + 2) * CELL_SIZE, (board_x - 4) * CELL_SIZE, _T("结束吧"));
			}
			if (board_y + 1 < x && x < board_y + 5 && board_x - 1 < y && y < board_x + 1) {
				setbkcolor(WHITE);
				settextcolor(BLACK);
				outtextxy((board_y + 2) * CELL_SIZE, board_x * CELL_SIZE, _T("想继续"));
			}
			else {
				setbkcolor(BLACK);
				settextcolor(WHITE);
				outtextxy((board_y + 2) * CELL_SIZE, board_x * CELL_SIZE, _T("想继续"));
			}
		}
		if (msg.message == WM_LBUTTONDOWN) {
			if (board_y + 1 < x && x < board_y + 5 && board_x - 5 < y && y < board_x - 3) return false;
			if (board_y + 1 < x && x < board_y + 5 && board_x - 1 < y && y < board_x + 1) return true;
		}

	}
}

/*清除状态，重复进行游戏*/
void mine_sweeper::clear() {
	stay_x = -7;
	stay_y = -7;//生
	just_moved_x = 0;
	just_moved_y = 0;
	is_over = false;
	is_win = false;
	is_first_click = true;
	mines_num = 0;
	picked_num = 0;
	board_x = 0;
	board_y = 0;
	board.resize(0);
	status.resize(0);
}

