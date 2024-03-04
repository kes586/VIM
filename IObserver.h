#pragma once
#include <vector>
#include "MyString.h"
enum mode {
	Navigation_Mode,
	Command_Mode,
	Write_Mode,
	Search_Mode
};
class IObserver
{
public:
	virtual void updateText(const std::vector<MyString> lines, int line, int col, int start_print, int end_print, mode cur_mode) = 0;
	virtual void updateMode(mode new_mode, int line, int col,int start_print) = 0;
	virtual void clearScreen() = 0;
	virtual void updateBackSpace() = 0;
	virtual void updateCursor(int line,int pos) = 0;
	virtual void updateCommand(MyString command) = 0;
	virtual void ShowHelp(MyString) = 0;
};

