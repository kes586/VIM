#pragma once
#include "TUIAdapter.h"
#include "Model.h"
#include "IObserver.h"

class View : IObserver
{
public:
	View();

	// Inherited via IObserver
	virtual void updateText(const std::vector<MyString> lines, int line, int col, int start_print, int end_print, mode cur_mode) override;
	virtual void updateMode(mode new_mode, int line, int col,int start_print) override;
	virtual void clearScreen() override;
	virtual void updateBackSpace() override;
	virtual void updateCursor(int line, int pos) override;
	virtual void updateCommand(MyString) override;
	virtual void ShowHelp(MyString) override;
private:
	static const int cTextWindowLines = 30;
	static const int cTextWindowCols = 120;
	TUIAdapter textwin;
};

