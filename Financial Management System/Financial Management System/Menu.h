#pragma once
#include<iostream>
#include<fstream>
#include"Account.h"
#include"Pattern.h"

class Menu
{
	std::string pattern;
	std::string typeOfAccount;
	Account* accountP;
	int currOption;
public:
	Menu(const std::string&,const std::string&);
	void setOption(int);
	void executeOption();
	void printPattern(const std::ostream&);
	~Menu();
};

