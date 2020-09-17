#pragma once
#include <iostream>
class Error
{
private:
	char* str_error;
public:
	Error(const char* str) {
		str_error = new char[strlen(str) + 1];
		print_error(str);
	};

	void print_error(const char* str) {
		for (int i = 0; str[i] != 0; i++) {
			std::cout << str[i];
		}
		std::cout << std::endl;
	}
	~Error() { delete[] str_error; };
};

class file_open_error :Error
{
public:
	file_open_error(const char* str) :Error(str) {};

};

class file_write_error :Error
{
public:
	file_write_error(const char* str) :Error(str) {};

};

class empty_error :Error
{
public:
	empty_error(const char* str) :Error(str) {};

};

class stringToInt :Error
{
public:
	stringToInt(const char* str) :Error(str) {};

};



