#include"MyString.h"

MyString::MyString() :MyString((char*)"")
{

}

MyString::MyString(char* str) :MyString(str, strlen(str))
{

}

MyString::MyString(const char* str) :MyString((char*)str, strlen(str))
{

}

MyString::MyString(initializer_list<char> my_list):MyString(string(my_list.begin(),my_list.end()))//Can I use such constructor for string class?
{
	
}

MyString::MyString(string str):MyString((char*)str.c_str(), str.size())//Can I use c_str for string in constructor?
{

}

MyString::MyString(char* str, int first_numbers)
{
	sz = first_numbers;
	cp = sz + 1;
	main_str = new char[cp];
	memcpy(main_str, str, first_numbers);
	main_str[sz] = '\0';
}

MyString::MyString(int count_chars, char symbol):MyString(string(count_chars,symbol))//Can I use such constructor for string class?
{

}

MyString::MyString(const MyString& Source):MyString(Source.main_str)
{

}

MyString::~MyString()
{
	delete[]main_str;
}

size_t MyString::length()const {
	return size();
}

size_t MyString::size()const {
	return sz;
}

bool MyString::empty()const {
	if (sz)
		return false;
	return true;
}

int MyString::capacity()const {
	return cp;
}

void MyString::clear() {
	memset(main_str, 0, sz);
	sz = 0;
}

void MyString::shrink_to_fit() {
	MyString* tmp_str = new MyString(main_str);
	delete[]main_str;
	main_str = new char[tmp_str->cp];
	memcpy(main_str, tmp_str->c_str(), tmp_str->sz);
	main_str[sz] = '\0';
	cp = tmp_str->cp;
	sz = tmp_str->sz;
	delete tmp_str;
}

char* MyString::data()const {
	return main_str;
}

char* MyString::c_str() {
	main_str[sz] = '\0';
	return main_str;
}
void MyString::erase(int index, int count) {
	assert(("Wrong index in erase method call", index >= 0 && index <=sz));
	assert(("Wrong count in erase method call", count >= 0 && count <= sz));
	assert(("Wrong index or count in erase method call", index+count <= sz));
	memcpy((char*)(main_str + index), (char*)(main_str + index + count), sz - index - count);
	sz -= count;
	main_str[sz] = '\0';
}

void MyString::insert(int index, int count, char symbol) {
	char* str = new char[count+1];
	memset(str, symbol, count);
	str[count] = '\0';
	insert(index, str, count);
	delete[]str;
}

void MyString::insert(const int index, const char* str) {
	MyString* tmp = new MyString(str);
	insert(index, str, tmp->size());
	delete tmp;
}

void MyString::insert(const int index, const char* str, const int count) {
	assert(("Wrong count in insert method call", count >= 0 && count <= strlen(str)));
	assert(("Wrong index in insert method call", index >= 0 && index <= sz));
	assert(("NULL pointer to str in insert method call", str != NULL));
	char* tmp_str = new char[sz];
	memcpy(tmp_str, main_str, sz);
	if (sz + count + 1 > cp) {
		delete[] main_str;
		cp = sz + +count+1;
		main_str = new char[cp];
	}
	memcpy(main_str, tmp_str, index);
	memcpy((char*)(main_str + index), str, count);
	memcpy((char*)(main_str + index + count), (char*)(tmp_str + index), sz - index);
	delete[]tmp_str;
	sz += count;
	main_str[sz] = '\0';
	
}
void MyString::insert(const int index, const string& str) {
	insert(index, str, str.size());
}
void MyString::insert(const int index, const string& str, const int count) {
	MyString* tmp = new MyString(str);
	insert(index, tmp->main_str, count);
	delete tmp;
}

void MyString::append(const int count, const char symbol) {
	char* str = new char[count];
	memset(str, symbol, count);
	append(str, 0, count);
	delete[]str;
}
void MyString::append(const char* str) {
	append(str, 0, strlen(str));
}
void MyString::append(const char* str, const int index, const int count) {
	assert(("Wrong count in append method call", count >= 0 && count <=strlen(str) ));
	assert(("Wrong index in append method call", index >= 0 && index <= strlen(str)));
	assert(("Wrong index or count in append method call", index+count <= strlen(str)));
	assert(("NULL pointer to str in append method call", str != NULL));
	char* tmp_str = new char[count];
	memcpy(tmp_str, (char*)(str + index), count);
	insert(sz, tmp_str, count);
	delete[]tmp_str;
}
void MyString::append(const string& str) {
	MyString* tmp = new MyString(str);
	append(tmp->main_str);
	delete tmp;
}
void MyString::append(const string& str, const int index, const int count) {
	MyString* tmp = new MyString(str);
	append(tmp->main_str, index, count);
	delete tmp;
}

void MyString::replace(const int index, const int count, const char* str) {
	assert(("Wrong count in replace method call", count >= 0 && index + count <= sz));
	assert(("Wrong index in replace method call", index >= 0 && index < sz));
	assert(("NULL pointer to str in replace method call", str!=NULL));
	erase(index, count);
	insert(index, str);
}
void MyString::replace(const int index, const int count, const  string& str) {
	MyString* tmp = new MyString(str);
	replace(index, count, tmp->main_str);
	delete tmp;
}

MyString MyString::substr(const int index)const {
	assert(("Wrong index in substr method call", index >= 0 && index <= sz));
	MyString tmp(main_str);
	tmp.erase(0, index);
	return tmp;
}
MyString MyString::substr(const int index, const int count)const {
	MyString tmp = substr(index);
	assert(("Wrong count in substr method call", count >= 0 && index+count <= sz));
	tmp.erase(count, sz - count - index);
	return tmp;
}

int MyString::find(const char* str)const {
	return find(str, 0);
}
int MyString::find(const char* str, int index)const {
	assert(("NULL pointer to str in find method call",str!=NULL));
	assert(("Wrong index in find method call",index>=0 && index<=sz));
	int count = 0;
	for (int i = index; i < strlen(main_str); i++) {
		if (main_str[i] == str[count]) {
			count++;
		}
		else
			count = 0;
		if (count == strlen(str))
			return i - count + 1;
	}
	return -1;
}
int MyString::find(const string& str)const {
	return find(str, 0);
}
int MyString::find(const string& str, const int index)const {
	MyString* tmp = new MyString(str);
	int res = find(tmp->main_str, index);
	delete tmp;
	return res;
}

MyString MyString::operator+(const MyString& str) {
	return *this + str.main_str;
}
MyString MyString::operator+(const char* str) {
	MyString tmp(main_str);
	tmp.append(str);
	return tmp;
}
MyString MyString::operator+(const string& str) {
	MyString tmp(str);
	return operator+(tmp.c_str());
	/*MyString tmp(str);
	return *this + tmp;*/
}
void MyString::operator+=(MyString& str) {
	return *this += str.main_str;
}
void MyString::operator+=(const char* str) {
	this->append(str);
}
void MyString::operator+=(const string& str) {
	MyString tmp(str);
	return *this += tmp;
}
void MyString::operator=(const char* str) {
	clear();
	append(str);
}
void MyString::operator=(const string& str) {
	MyString tmp(str);
	return *this = tmp.main_str;
}
void MyString::operator=(char str) {
	MyString tmp(1, str);
	return *this = tmp.main_str;
}
void MyString::operator=(const MyString& str) {
	MyString tmp(str);
	return *this = tmp.main_str;
}
const char MyString::operator[](const int i)const {
	return main_str[i];
}
bool MyString::operator>(const MyString& tmp)const {
	if (sz == tmp.sz) {
		if (memcmp(main_str, tmp.main_str, sz) > 0)
			return 1;
		else
			return 0;
	}
	else if (sz > tmp.sz) {
		if (memcmp(main_str, tmp.main_str, tmp.sz) >= 0)
			return 1;
		else
			return 0;
	}
	else {
		if (memcmp(main_str, tmp.main_str, sz) > 0)
			return 1;
		else
			return 0;
	}
}
bool MyString::operator<(const MyString& tmp)const {
	if (sz == tmp.sz) {
		if (memcmp(main_str, tmp.main_str, sz) < 0)
			return 1;
		else
			return 0;
	}
	else if (sz > tmp.sz) {
		if (memcmp(main_str, tmp.main_str, tmp.sz) < 0)
			return 1;
		else
			return 0;
	}
	else {
		if (memcmp(main_str, tmp.main_str, sz) <= 0)
			return 1;
		else
			return 0;
	}
}
bool MyString::operator>=(const MyString& tmp)const {
	return !(bool)operator>(tmp);
}
bool MyString::operator<=(const MyString& tmp)const {
	return !(bool)operator<(tmp);
}
bool MyString::operator!=(const MyString& tmp)const {
	if (sz != tmp.sz)
		return 1;
	if (memcmp(main_str, tmp.main_str, sz))
		return 1;
	return 0;
}
bool MyString::operator==(const MyString& tmp)const {
	return !(bool)operator!=(tmp);
}

ostream& operator<<(ostream& out, const MyString& str)
{
	out << str.main_str;
	return out;
}
istream& operator>> (istream& in, MyString& str) {
	str.clear();
	char sym;
	while (in && (sym = in.get()) != '\n')
		str.append(1, sym);
	return in;
}