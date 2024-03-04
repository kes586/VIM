#pragma once
#include <vector>
#include "IObservableModel.h"
#include "IObserver.h"
#include "curses.h"
#include <Windows.h>
#include <fstream>
#include "MyString.h"
#include "ConcreteDecorator.h"
using namespace std;
class Model : IObservableModel
{
public:
	const std::vector<MyString>& getLines() const;
	std::vector<IObserver*> observers_;

	Model();
	int getLine() const;
	int getCol() const;
	int getStart() const;
	int getEnd() const;
	int getPrevPos()const;
	MyString getPrevString()const;
	MyString getCurFile()const;
	mode get_running_mode() const;
	void set_running_mode(mode new_mode);
	void set_mode_type(int ch);
	void button_enter();
	void button_backspace();
	void button_key_up();
	void button_key_down();
	void button_key_left();
	void button_key_right();
	void button_key_page_down();
	void button_key_page_up();
	void write(int ch);
	void write_command(MyString);
	void set_params(int line, int pos, int start, int end);
	void make_search(MyString);
	void update_mode(mode new_mode);
	void ClipBoardCopy(MyString);
	void Erase_Line(int line,int idndex,int count);
	MyString ClipBoardPaste();
	void WriteFile(MyString);
	void command_w();
	void command_b();
	void command_n(MyString string_for_search, int position);
	void command_N(MyString string_for_search, int position);
	void command_diw();
	void command_o(MyString);
	void command_yw();
	void command_p();
	void command_xx();
	void command_r(int ch);
	virtual void registerObserv(IObserver* observer) override;
	virtual void notifyTextUpdated() override;
	virtual void notifyModeUpdated() override;
	virtual void notifyClearScreen() override;
	virtual void notifyupdateBackSpace() override;
	virtual void notifyCursorUpdated(int line, int pos) override;
	virtual void notifyCommandUpdated(MyString command) override;
	virtual void notifyShowHelp() override;
private:
	
	MyString help_string;
	vector<MyString> lines;
	MyString command;
	int line_pos = 0, col_pos = 0;
	int start_print = 0, end_print = 28;
	mode running_mode;
	MyString current_file;
	char mode_type;
	int prev_line = 0, prev_pos = 0;
	MyString prev_search_string = "";
	int prev_line_perenos = -1;
};