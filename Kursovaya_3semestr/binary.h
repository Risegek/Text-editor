#pragma once

#include <string>
#include <fstream>
#include <iostream>
class binary : public std::fstream
{
private: 
	char* binary_name;
	char* name_text;

	void addElem(int _pos, int num);
	void resizeArr();
public:
	binary(const char* name_fail);
	~binary() { close(); delete[] binary_name; delete[] name_text; };

	void binaryToText(const char* nameText);
	void TextToBinary(const char* nameText);
	

	char* getFile() { return name_text; }

	void deleteStr(int num);
	void printFile();
	void changeStr(int num, const char* str);
	void addStr(int num,const char* str);
	bool is_empty();

};

