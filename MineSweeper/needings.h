#include<iostream>
#include<graphics.h>
#include<string>
#include<vector>
using namespace std;
const int CELL_SIZE = 20;
enum { normal, cleared, marked };
const COLORREF COLOR_1 = LIGHTBLUE;

const COLORREF COLOR_2 = HSVtoRGB(40, 1, 1);

class mine_sweeper {
private:
	/* 0-8 指该块周围雷数、9表示该块为雷*/
	vector<vector<int>> board;
	vector<vector<int>> status;
	int stay_x = -7;
	int stay_y = -7;//生
	int just_moved_x = 0;
	int just_moved_y = 0;
	bool is_over = false;
	bool is_win = false;
	bool is_first_click = true;
public:
	int mines_num = 0;
	int picked_num = 0;
	int board_x = 0;
	int board_y = 0;
	void get_mode_and_initialize();
	void random_form();
	void print_frame();
	void control_by_mouse();
	void move();
	void click();
	void flag();
	void get_empty_cleared(int x, int y);
	void show_notice();
	void justice();
	bool is_to_continue();
	void clear();
	void end_manage();
};
