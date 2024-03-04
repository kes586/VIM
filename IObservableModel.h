#pragma once
#include "IObserver.h"
#include "MyString.h"
class IObservableModel
{
public:
	virtual void registerObserv(IObserver* observer) = 0;
	virtual void notifyTextUpdated() = 0;
	virtual void notifyModeUpdated() = 0;
	virtual void notifyClearScreen() = 0;
	virtual void notifyupdateBackSpace() = 0;
	virtual void notifyCursorUpdated(int line, int pos) = 0;
	virtual void notifyCommandUpdated(MyString command) = 0;
	virtual void notifyShowHelp() = 0;
};

