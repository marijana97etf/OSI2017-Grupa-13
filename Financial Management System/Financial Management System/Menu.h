#pragma once
#include<iostream>
#include<fstream>
#include"Account.h"
#include"Pattern.h"

class Menu
{
	Account* accountP;
	int currOption;
public:
	Menu(Account&);//metode u adminu bi trebale biti const
	bool setOption(std::istream &,std::ostream &);
	void executeOption();
	void printPattern(std::ostream&);
	int getCurrOption();
	~Menu();
private:
	/*void setIfOptionRangeIsValid(int&,const int);*/
};

