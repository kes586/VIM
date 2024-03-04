#pragma once
#include "MyString_Full.h"
#include "MyString.h"
class Decorator : public MyString_Full
{
public:
	Decorator(MyString* tmp): msf(tmp){}
	virtual int rfind(const char* search_str, int index) = 0;
protected:
	MyString_Full* msf;
};

