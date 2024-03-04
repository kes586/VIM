#include "Model.h"

Model::Model()
{
	lines.resize(29);
	help_string = "i - Enter text before the cursor\n" + (string)"I - Go to the beginning of the line and start entering text\n" +
		"S - Go to the end of the line and start typing\n" + "A - Delete the contents of the row and start typing\n" +
		"r - Replace one character under the cursor\n" + ": - Activating the command input mode\n" +
		"/ - Activates search mode until the end of the document\n" + "? - Activates search mode until the start of the document\n" +
		"gg - Moves the cursor to the first page of the text\n" + "G - Moves the cursor to the last page of the text\n" +
		"^ - Moves the cursor to the start of the line\n" + "$ - Moves the cursor to the end of the line\n" +
		"w - Move the cursor to the end of a word to the right of the cursor\n" + "b - Move the cursor to the beginning of the word to the left of the cursor\n" +
		"x - Delete the character after the cursor\n" + "diw - Delete the word under the cursor, including one space on the right\n" +
		"dd - Cut (copy and delete) the current line\n" + "y - Copy the current line\n" +
		"yw - Copy the word under the cursor\n" + "p - Insert after the cursor\n" +
		"NG - Go to the line with the number N\n" + "/<text> - Search for the <text> string from the cursor to the end of the file\n" +
		"?<text> - Search for the <text> string from the cursor to the beginning of the file\n" + "n - Repeat search forward\n" +
		"N - Repeat search back\n" + "o <filename> - Open the file <filename>\n" +
		"x - Write to the current file and close it\n" + "w - Write to the current file\n" +
		"w <filename> - Write to file <filename>\n" + "q - Exit program\n" +
		"wq! - Write to the current file and close it\n" + "num	- Go to the line with the number <num>\n";
}

void Model::registerObserv(IObserver* observer)
{
	observers_.push_back(observer);
}

void Model::notifyTextUpdated()
{
	for (auto observer : observers_)
		observer->updateText(lines, line_pos, col_pos,start_print,end_print,running_mode);
}


void Model::notifyModeUpdated(){
	
	for (auto observer : observers_)
		observer->updateMode(running_mode,line_pos,col_pos,start_print);
	
}

void Model::set_params(int line, int pos, int start, int end)
{
	line_pos = line;
	col_pos = pos;
	start_print = start;
	end_print = end;
	notifyTextUpdated();
}

void Model::notifyClearScreen(){
	for (auto observer : observers_)
		observer->clearScreen();
}
void Model::notifyupdateBackSpace() {
	for (auto observer : observers_)
		observer->updateBackSpace();
}
void Model::notifyCursorUpdated(int line,int pos){
	for (auto observer : observers_)
		observer->updateCursor(line,pos);
}
void Model::notifyCommandUpdated(MyString command) {
	for (auto observer : observers_)
 		observer->updateCommand(command);
}
void Model::notifyShowHelp(){
	for (auto observer : observers_)
		observer->ShowHelp(help_string);
}
const std::vector<MyString>& Model::getLines() const{
	return lines;
}
int Model::getLine() const {
	return line_pos;
}

int Model::getCol() const {
	return col_pos;
}
int Model::getStart() const {
	return start_print;
}
int Model::getEnd() const {
	return end_print;
}
MyString Model::getCurFile()const
{
	return current_file;
}
MyString Model::getPrevString()const {
	return prev_search_string;
}
int Model::getPrevPos()const {
	return prev_pos;
}
void Model::Erase_Line(int line, int index, int count) {
	lines[line].erase(index, count);
}
void Model::button_enter(){
	if (running_mode == Navigation_Mode)
		return;
	if (line_pos == end_print) {
		if (running_mode != Write_Mode && line_pos == lines.size() - 1)
			return;
		lines.resize(lines.size() + 29);
		start_print++;
		end_print++;
	}
	for (int i = lines.size() - 2; i > line_pos; i--) {
		lines[i + 1] = lines[i];
	}
	if (line_pos % 29 == 0 && line_pos != 0)
		lines.resize(lines.size() + 29);
	lines[line_pos + 1].clear();
	lines[line_pos + 1] = lines[line_pos].substr(col_pos);
	lines[line_pos] = lines[line_pos].substr(0, col_pos);
	notifyTextUpdated();
}

void Model::write(int ch){
	MyString& cur_line = lines[line_pos];
	cur_line.insert(col_pos, 1, ch);
	col_pos++;
	
	if (lines[line_pos].size() == 121) {
		if(prev_line_perenos !=line_pos){
			for (int i = lines.size() - 2; i >= line_pos; i--) {
				lines[i + 1] = lines[i];
			}
			lines[line_pos + 1].clear();
			prev_line_perenos = line_pos;
		}
		lines[line_pos+1].insert(0,1,lines[line_pos][120]);
		lines[line_pos] = lines[line_pos].substr(0, 120);
	}
	if (col_pos == 120) {
		col_pos = 0;
		line_pos++;
	}
}

void Model::write_command(MyString command) {
	notifyCommandUpdated(command);
}
void Model::button_key_up(){
	if (line_pos == start_print && start_print != 0) {
		start_print--;
		end_print--;
	}
	if (line_pos != 0)
		line_pos--;
	if (lines[line_pos].size() < lines[line_pos + 1].size())
		col_pos = lines[line_pos].size();
}
void Model::button_key_down(){
	if (line_pos + 1 == lines.size() && running_mode == Navigation_Mode)
		return;
	if (line_pos == end_print) {
		start_print++;
		end_print++;
		if (running_mode == Write_Mode)
			lines.resize(lines.size() + 29);
	}
	line_pos++;
	if (lines[line_pos].size() < lines[line_pos - 1].size())
		col_pos = lines[line_pos].size();
}
void Model::update_mode(mode new_mode) {
	running_mode = new_mode;
	notifyModeUpdated();
}

void Model::button_key_left(){
	if (col_pos == 0 && line_pos != 0) {
		line_pos--;
		col_pos = lines[line_pos].size();
	}
	else {
		col_pos--;
		if (col_pos < 0)
			col_pos = 0;
	}
}
void Model::button_key_right() {
	if (col_pos < 119)
		col_pos++;
	else {
		if (line_pos == end_print) {
			start_print++;
			end_print++;
			if (running_mode == Write_Mode)
				lines.resize(lines.size() + 29);
		}
		line_pos++;
		col_pos = 0;
	}
}
void Model::button_key_page_down() {
	if (lines.size() <= line_pos + 29 && running_mode == Write_Mode)
		lines.resize(lines.size() + 29);
	notifyClearScreen();
	start_print += 28;
	end_print += 28;
	if (end_print > lines.size()) {
		end_print = lines.size() - 1;
		start_print = end_print - 28;
	}
	line_pos = start_print;
	col_pos = 0;
}
void Model::button_key_page_up() {
	notifyClearScreen();
	start_print -= 28;
	end_print -= 28;
	if (start_print < 0) {
		start_print = 0;
		end_print = 28;
	}
	line_pos = start_print;
	col_pos = 0;
}
void Model::set_mode_type(int ch)
{
	mode_type = ch;
}
void Model::make_search(MyString command){
	if (command != prev_search_string) {
		prev_search_string = command.c_str();
		prev_line = line_pos;
		prev_pos = col_pos;
	}
	
	if (mode_type == '?') 
		command_N(command, col_pos);
	else if (mode_type == '/')
		command_n(command, col_pos);
}



mode Model::get_running_mode() const {
	return running_mode;
}
void Model::set_running_mode(mode new_mode) {
	running_mode = new_mode;
}
void Model::command_o(MyString command) {
	ifstream infile(command.substr(2).c_str());
	if (!infile.is_open())
		return;
	current_file = command.substr(2).c_str();
	lines.clear();
	lines.resize(29);
	int i = 0;
	MyString tmp_line;
	char ch;
	for (; infile;)
	{
		infile.get(ch);
		if (infile.eof()) break;
		char arr[2] = { char(ch), '\0' };
		tmp_line += arr;
		if (ch == '\n') {
			if (tmp_line.size() < 119)
				lines[i++] = tmp_line;
			else {
				for (int j = 0; j < tmp_line.size(); j++) {
					char arr[2] = { char(tmp_line[j]), '\0' };
					lines[i] += arr;
					if (j % 119 == 0 && j != 0) {
						i++;
						if (i % 29 == 0)
							lines.resize(lines.size() + 29);
					}
				}
				i++;
			}
			if (i % 29 == 0)
				lines.resize(lines.size() + 29);
			tmp_line.clear();
		}
	}
	set_params(0, 0, 0, 28);
	set_running_mode(Navigation_Mode);
	infile.close();
	notifyTextUpdated();
}
void Model::command_p() {
	MyString to_paste = ClipBoardPaste();
	if (to_paste.size() + lines[line_pos].size() < 120) {
		if (col_pos != lines[line_pos].size())
			col_pos++;
		lines[line_pos].insert(col_pos, to_paste.c_str());
	}
	else {//some algorithm for moving
		for (int i = lines.size() - 2; i >= line_pos; i--) {
			lines[i + 1] = lines[i];
		}
		
		lines[line_pos + 1].clear();
		lines[line_pos].insert(col_pos, to_paste.c_str());
		lines[line_pos + 1].insert(0,lines[line_pos].substr(120).c_str());
		lines[line_pos] = lines[line_pos].substr(0, 120);
	}
	notifyTextUpdated();
}
void Model::command_xx() {
	WriteFile(getCurFile());
	lines.clear();
	lines.resize(29);
	set_params(0, 0, 0, 28);
	current_file.clear();
	set_running_mode(Navigation_Mode);
	notifyTextUpdated();
}
void Model::command_r(int ch)
{
	char arr[2] = { char(ch),'\0' };
	lines[line_pos].replace(col_pos, 1, arr);
}
void Model::command_yw() {
	MyString_Full* decor = new ConcreteDecorator(&lines[line_pos]);
	int start_ind = decor->rfind(" ",col_pos);
	int end_ind = lines[line_pos].find(" ", col_pos);
	if (start_ind == -1)
		start_ind = 0;
	else
		start_ind++;
	if (end_ind == -1)
		end_ind = lines[line_pos].size();
	else
		end_ind++;
	MyString tmp = lines[line_pos].substr(start_ind, end_ind - start_ind);
	ClipBoardCopy(tmp);
}
void Model::command_w() {
	int pos = lines[line_pos].find(" ", col_pos);
	if (col_pos == pos - 1)
		pos = lines[line_pos].find(" ", pos + 1);
	if (pos != -1)
		col_pos = pos - 1;
	else if (col_pos != lines[line_pos].size() - 1)
		col_pos = lines[line_pos].size() - 1;
	else {
		line_pos++;
		col_pos = 1;
		command_w();
	}
}
void Model::command_b() {
	MyString_Full* decor = new ConcreteDecorator(&lines[line_pos]);
	int pos = decor->rfind(" ", col_pos-2);
	if (col_pos == pos + 1&&pos!=-1)
		pos = decor->rfind(" ", col_pos);
	if (pos != -1)
		col_pos = pos + 1;
	else if (col_pos != 0)
		col_pos = 0;
	else {
		line_pos--;
		if (line_pos < 0)
			line_pos = 0;
		col_pos = lines[line_pos].size()-1;
		command_b();
	}
}
void Model::command_n(MyString string_for_search,int position){
	int i, j = 0, pos = position;
	for (i = prev_line; i < lines.size(); i++) {
		j = lines[i].find(string_for_search.c_str(), pos);
		if (j != -1)
			break;
		pos = 0;
	}
	if (i == lines.size() && j == -1) {
		running_mode = Navigation_Mode;
		return;
	}
	line_pos = prev_line = i;
	if (line_pos > end_print) {
		end_print = line_pos;
		start_print = end_print - 28;
	}
	col_pos = j;
	prev_pos = j + command.size();
	notifyCursorUpdated(i, j);
	running_mode = Navigation_Mode;
}
void Model::command_N(MyString string_for_search, int position){
	int i, j = 0, pos = position;
	for (i = line_pos; i >= 0; i--) {
		MyString_Full* decor = new ConcreteDecorator(&lines[i]);
		j = decor->rfind(string_for_search.c_str(), pos);
		if (j != -1)
			break;
		if (i != 0)
			pos = lines[i - 1].size()-1;
	}
	if (i == -1 && j == -1) {
		running_mode = Navigation_Mode;
		return;
	}
	line_pos = prev_line = i;
	if (line_pos < start_print) {
		start_print = line_pos;
		end_print = start_print + 28;
	}
	col_pos = j;
	prev_pos = j - command.size();
	notifyCursorUpdated(i, j);
	running_mode = Navigation_Mode;
}
void Model::command_diw() {
	MyString_Full* decor = new ConcreteDecorator(&lines[line_pos]);
	int start_ind = decor->rfind(" ", col_pos);
	int end_ind = lines[line_pos].find(" ", col_pos);
	if (start_ind == -1)
		start_ind = 0;
	else
		start_ind++;
	if (end_ind == -1) {
		end_ind = lines[line_pos].size();
		col_pos = start_ind - 2;
	}
	else
		end_ind++;
	lines[line_pos].erase(start_ind, end_ind - start_ind);
	notifyTextUpdated();
}

void Model::button_backspace()
{
	if (running_mode == Navigation_Mode)
		return;
	if (col_pos == 0 && line_pos != 0) {
		if (lines[line_pos-1].size() == 0) {
			lines.erase(lines.begin() + line_pos - 1);
			lines.push_back("");
			line_pos--;
			col_pos = 0;
		}
		else if(lines[line_pos].size() == 0){
			lines.erase(lines.begin() + line_pos);
			lines.push_back("");
		}
		else {
			line_pos--;
			col_pos = lines[line_pos].size();
		}
		notifyTextUpdated();
	}
	if (col_pos > 0) {
		//lines[line_pos].erase(col_pos - 1, (col_pos));
		lines[line_pos].replace(col_pos - 1,1, "");
		col_pos--;
		notifyupdateBackSpace();
	}
}
void Model::ClipBoardCopy(MyString str)
{
	if (OpenClipboard(0)) {
		EmptyClipboard();
		HGLOBAL hClipboardData;
		hClipboardData = GlobalAlloc(GMEM_DDESHARE, str.size()+1);
		char* pszBuffer = (char*)GlobalLock(hClipboardData);
		strcpy_s(pszBuffer, str.size()+1, str.c_str());
		GlobalUnlock(hClipboardData);
		SetClipboardData(CF_TEXT, hClipboardData);
		CloseClipboard();
	}
}
MyString Model::ClipBoardPaste() {
	if (!OpenClipboard(0)) {
		return "";
	}
	HANDLE hData = GetClipboardData(CF_TEXT);
	char* pszText = static_cast<char*>(GlobalLock(hData));
	
	MyString tmp(pszText);

	GlobalUnlock(hData);
	CloseClipboard();
	return tmp;
}



void Model::WriteFile(MyString file){
	ofstream outfile(file.c_str(), ofstream::trunc);
	if (!outfile.is_open())
		return;
	for (const auto& x : lines)
		outfile << x << endl;
	outfile.close();
}
