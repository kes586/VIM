#include "TUIAdapter.h"
void TUIAdapter::init() { 
	initscr(); 
	raw();
	keypad(stdscr, true);
	noecho(); 
}
int TUIAdapter::getchar() { 
	return getch();
}
void TUIAdapter::movecursor(int x, int y){
	move(x, y);
	refresh();
}
TUIAdapter::TUIAdapter(int lines, int cols, int x, int y)
{
	window_ = newwin(lines, cols, x, y);
}
TUIAdapter::~TUIAdapter(){
	delwin(window_);
}
void TUIAdapter::print(int x, int y, MyString str)
{
	move(x, y);
	clrtoeol();
	mvprintw(x, 0, str.c_str());
}
void TUIAdapter::update(){
	refresh();
}
void TUIAdapter::Print_Status(int new_mode, int x, int y) {
	MyString status;
	switch (new_mode) {
	case 0:
		status = "Navigation_Mode";
		break;
	case 1:
		status = "Command_Mode";
		break;
	case 2:
		status = "Write_Mode";
		break;
	case 3:
		status = "Search_Mode";
	}
	status += "\t\tLine: " + to_string(x) + " Col: " + to_string(y) + "\t\t\t\t\t\t\t\t\t\t\t";
	start_color();
	init_pair(1, COLOR_RED, COLOR_GREEN);
	init_color(11, 500, 0, 500);
	attron(A_REVERSE);
	mvprintw(29, 0, status.c_str());
	clrtoeol();
	attroff(A_REVERSE);
}
void TUIAdapter::Print_Str(MyString str){
	mvaddstr(0, 0, str.c_str());
	update();
	getchar();
}
void TUIAdapter::Clear_Str(int line, int pos){
	move(line, pos);
	clrtoeol();
}
void TUIAdapter::backspace() {
	delch();
}