#pragma once
#include "MyString_Full.h"
#include<iostream>
#include<string>
#include <cassert> 
using namespace std;
class MyString : public MyString_Full
{
	friend ostream& operator<<(ostream& out, const MyString& str);
	friend istream& operator>> (istream& in, MyString& str);
public:
	
	MyString();
	MyString(char* str);
	MyString(const char* str);
	MyString(const initializer_list<char> my_list);
	MyString(string str);
	MyString(char* str, int first_numbers);
	MyString(int count_chars, char symbol);
	MyString(const MyString& Source);
	~MyString();
	size_t length() const;
	size_t size() const;
	bool empty() const;
	int capacity() const;
	void clear();
	void shrink_to_fit();
	char* data() const;
	char* c_str();
	void erase(const int index, const int count);

	void insert(const int index, const int count, const char symbol);
	void insert(const int index, const char* str);
	void insert(const int index, const char* str, const int count);
	void insert(const int index, const string& str);
	void insert(const int index, const string& str, const int count);

	void append(const int count, const char symbol);
	void append(const char* str);
	void append(const char* str, int index, int count);
	void append(const string& str);
	void append(const string& str, int index, int count);

	void replace(const int index, const int count, const char* str);
	void replace(const int index, const int count, const string& str);

	MyString substr(const int index)const;
	MyString substr(const int index, const int count)const;

	int find(const char* str)const;
	int find(const char* str, int index)const;
	int find(const string& str)const;
	int find(const string& str, int index)const;
	int rfind(const char*, int) { return 0; };
	MyString operator+(const MyString& str);
	MyString operator+(const char* str);
	MyString operator+(const string& str);
	void operator+=(MyString& str);
	void operator+=(const char* str);
	void operator+=(const string& str);
	void operator=(const char* str);
	void operator=(const string& str);
	void operator=(const char str);
	void operator=(const MyString& str);
	const char operator[](int i)const;
	bool operator>(const MyString& tmp)const;
	bool operator<(const MyString& tmp)const;
	bool operator>=(const MyString& tmp)const;
	bool operator<=(const MyString& tmp)const;
	bool operator!=(const MyString& tmp)const;
	bool operator==(const MyString& tmp)const;
private:
	char* main_str;
	int sz;
	int cp;
};