#pragma once
#include "MyString.h"
#include "Decorator.h"
#include<iostream>
class ConcreteDecorator:public Decorator
{
public:
	char* main_str;
	ConcreteDecorator(MyString* msf):Decorator(msf) {
		main_str = msf->data();
	};
	~ConcreteDecorator(){}
	int rfind(const char* search_str,int index) override {
		Decorator::rfind(search_str, index);
		int count = strlen(search_str)-1;
		for (int i = index; i >= 0; i--) {
			if (main_str[i] == search_str[count]) {
				count--;
			}
			else
				count = strlen(search_str)-1;
			if (count == 0&&strlen(search_str)!=1 || count == -1)
				return i - count - 1;
		}
		return -1;
	}
};

