#include "Controller.h"
Controller::Controller() {
	model.registerObserv((IObserver*)&view);
}
void Controller::Write_Navi_Loop()
{
	while (1)
	{
		int ch = TUIAdapter::getchar();
		switch (ch) {
		case 27:
			model.set_running_mode(Navigation_Mode);
			model.update_mode(Navigation_Mode);
			return;
		case 13:
			model.button_enter();
			break;
		case 8:
			model.button_backspace();
			break;
		case KEY_UP:
			model.button_key_up();
			break;
		case KEY_DOWN:
			model.button_key_down();
			break;
		case KEY_LEFT:
			model.button_key_left();
			break;
		case KEY_RIGHT:
			model.button_key_right();
			break;
		case KEY_NPAGE:
			model.button_key_page_down();
			break;
		case KEY_PPAGE:
			model.button_key_page_up();//page up в write ошибка
			break;
		default:
			if (model.get_running_mode() == Write_Mode)
				model.write(ch);
			else if (model.get_running_mode() == Navigation_Mode) {
				
				switch (ch) {
				case 'A':
					model.Erase_Line(model.getLine(), 0, model.getLines()[model.getLine()].size());
					model.set_params(model.getLine(), 0, model.getStart(), model.getEnd());
					model.set_running_mode(Write_Mode);
					break;
				case 'S':
					model.set_params(model.getLine(), model.getLines()[model.getLine()].size(),model.getStart(),model.getEnd());
					model.notifyCursorUpdated(model.getLine(), model.getCol());
					model.set_running_mode(Write_Mode);
					break;
				case 'i':
					model.set_running_mode(Write_Mode);
					break;
				case 'r':
					ch = TUIAdapter::getchar();
					model.command_r(ch);
					break;
				case 'I':
					model.set_params(model.getLine(), 0, model.getStart(), model.getEnd());
					model.set_running_mode(Write_Mode);
					break;
				case '/':
					model.set_mode_type(ch);
					model.set_running_mode(Search_Mode);
					break;
				case '?':
					model.set_mode_type(ch);
					model.set_running_mode(Search_Mode);
					break;
				case ':':
					model.set_running_mode(Command_Mode);
					break;
				}
				model.notifyTextUpdated();
				return;
			}
		}
		model.notifyTextUpdated();
	}
}

void Controller::Command_Loop()
{
	model.notifyClearScreen();
	model.notifyModeUpdated();
	model.notifyCursorUpdated(0, 0);
	
	int ch;
	MyString command;
	while (1) {
		ch = TUIAdapter::getchar();
		switch (ch) {
		case 13:
			if (command == "gg") {
				model.set_params(0, 0, 0, 28);
			}
			else if (command == "G") {
				model.set_params(model.getLines().size() - 29, 0, model.getLines().size()-29, model.getLines().size()-1);
			}
			else if (command == "n") {
				model.command_n(model.getPrevString(),model.getPrevPos()+1);
			}
			else if (command == "N") {
				model.command_N(model.getPrevString(), model.getPrevPos() - 1);
			}
			else if (command == "^") {
				model.set_params(model.getLine(), 0, model.getStart(), model.getEnd());
			}
			else if (command == "$") {
				model.set_params(model.getLine(), model.getLines()[model.getLine()].size() - 1, model.getStart(), model.getEnd());
			}
			else if (command == "w") {
				model.command_w();
			}
			else if (command == "b") {
				model.command_b();
			}
			else if (command == "x") {
				model.Erase_Line(model.getLine(), model.getCol() + 1, 1);
			}
			else if (command == "diw") {
				model.command_diw();
			}
			else if (command == "dd") {
				model.ClipBoardCopy(model.getLines()[model.getLine()]);
				model.Erase_Line(model.getLine(), 0, model.getLines()[model.getLine()].size());
			}
			else if (command == "y") {
				model.ClipBoardCopy(model.getLines()[model.getStart()]);
			}
			else if (command == "yw") {
				model.command_yw();
			}
			else if (command == "p") {
				model.command_p();
			}
			else if (command[command.size() - 1] == 'G') {
				int line = std::stoi(command.substr(0, command.size() - 1).c_str());
				if (line >= 0 && line < model.getLines().size())
					model.set_params(line, model.getCol(), model.getStart(), model.getEnd());
			}
			else if (command == "xx") {
				model.command_xx();
			}
			else if (command[0] == 'o') {
				model.command_o(command);
			}
			else if (command == "w") {
				model.WriteFile(model.getCurFile());
			}
			else if (command[0] == 'w') {
				model.WriteFile(command.substr(2));
			}
			else if (command == "q") {//в чём разница между q и wq!
				model.WriteFile(model.getCurFile());
				ExitProcess(ERROR_SUCCESS);
			}
			else if (command == "q!") {
				ExitProcess(ERROR_SUCCESS);
			}
			else if (command == "wq!") {
				model.WriteFile(model.getCurFile());
				ExitProcess(ERROR_SUCCESS);
			}
			else if (command == "h") {
				model.notifyClearScreen();
				model.notifyShowHelp();
			}
			else if(command.size()!=0){
				try {
					int line = std::stoi(command.substr(0, command.size() ).c_str());
					if (line >= 0 && line < model.getLines().size())
						model.set_params(line, model.getCol(), model.getStart(), model.getEnd());
				}
				catch (...) {

				}
			}
			model.set_running_mode(Navigation_Mode);
			model.notifyModeUpdated();
			model.notifyTextUpdated();
			command.clear();
			return;
		case 27:
			model.set_running_mode(Navigation_Mode);
			model.notifyModeUpdated();
			return;
		case 8:
			if(command.size() > 0)
				command = command.substr(0, command.size() - 1);
			break;
		default:
			if (ch > 31 && ch < 256) {
				char arr[2] = { char(ch), '\0' };
				command += arr;
			}
			
		}
		model.write_command(command);
	}
	
	
}
void Controller::Search_Loop() {
	model.notifyClearScreen();
	model.notifyModeUpdated();
	model.notifyCursorUpdated(0, 0);
	int ch;
	MyString search_str;
	while (1) {
		ch = TUIAdapter::getchar();
		if (ch == 13||ch == 27)
			break;
		if(ch == 8)
			search_str = search_str.substr(0, search_str.size() - 1);
		else if (ch > 31 && ch < 256) {
			char arr[2] = { char(ch), '\0' };
			search_str += arr;
		}
		model.write_command(search_str);
	}
	model.make_search(search_str);
	model.notifyTextUpdated();
	
}

void Controller::Menu() {
	
	while (1) {
			
		switch (model.get_running_mode()) {
		case Command_Mode:
			Command_Loop();
			break;
		case Write_Mode:
			Write_Navi_Loop();
			break;
		case Navigation_Mode:
			Write_Navi_Loop();
			break;
		case Search_Mode:
			Search_Loop();
			break;
		}

	}
}
