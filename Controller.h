#pragma once
#include "Model.h"
#include "View.h"
#include "TUIAdapter.h"
#include "IObserver.h"
#include "MyString.h"
using namespace std;
class Controller
{
public:
	Controller();
	void Write_Navi_Loop();
	void Command_Loop();
	void Search_Loop();
	void Menu();
	
private:
	Model model;
	View view;
};

