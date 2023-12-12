#include"needings.h"

int main() {
	mine_sweeper circle;

	main_body:
	circle.get_mode_and_initialize();
	circle.print_frame();
	circle.control_by_mouse();
	
	if (circle.is_to_continue()){
		circle.clear();
		goto main_body;
	}
	
	return 0;
}