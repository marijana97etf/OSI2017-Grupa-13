#pragma once
#include<iostream>
#include<fstream>
#include<exception>
#include<Windows.h>
#include"Account.h"
#include"Pattern.h"

class Menu
{
	Account* accountP;
	int currOption;
public:
	Menu(Account&);
	void setOption(std::istream &,std::ostream &);
	void executeOption();
	void printPattern(std::ostream&);
	int getCurrOption();
	~Menu();
};

