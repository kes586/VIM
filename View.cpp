#include "View.h"
#include "MyString.h"
View::View() : textwin(cTextWindowLines, cTextWindowCols, 0, 0)
{
}

void View::updateText(const std::vector<MyString> lines, int line, int col,int start_print,int end_print, mode cur_mode)
{
	int cntLine = 0;
	int start = start_print;
	int end = end_print;
	while (start <= end) {
		textwin.print(cntLine, 0, lines[start]);
		++cntLine;
		++start;
	}
	updateMode(cur_mode, line, col,start_print);	
}

void View::updateMode(mode new_mode, int line, int col,int start_print)
{
	TUIAdapter::Print_Status(new_mode, line, col);
	TUIAdapter::movecursor(line-start_print, col);
}
void View::clearScreen() {
	for (int i = 0; i < 28; i++) {
		TUIAdapter::Clear_Str(i, 0);
	}
	TUIAdapter::update();
}

void View::updateBackSpace()
{
	TUIAdapter::backspace();
}

void View::updateCursor(int line, int pos)
{
	TUIAdapter::movecursor(line, pos);
}

void View::updateCommand(MyString command){
	textwin.print(0, 0, command);
}

void View::ShowHelp(MyString help_string){
	TUIAdapter::Print_Str(help_string);
}


