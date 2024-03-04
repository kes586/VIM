#pragma once
#include "curses.h"
#include "MyString.h"
using namespace std;
class TUIAdapter
{
public:
	static void init();
	static int getchar();
	static void movecursor(int x, int y);

	TUIAdapter(int lines, int cols, int x, int y);

	~TUIAdapter();

	void print(int x, int y, MyString str);

	static void update();
	static void Print_Status(int new_mode, int x, int y);
	static void backspace();
	static void Print_Str(MyString);
	static void Clear_Str(int line, int pos);
private:
	WINDOW* window_;
};

