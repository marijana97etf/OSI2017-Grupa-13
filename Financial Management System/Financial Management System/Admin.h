#pragma once
#include "Account.h"
#include<iostream>
#include<fstream>
#include<string>
#include <locale>

const int LENGHT_OF_HEADER = 38;
class Admin :
	public Account
{
public:
	Admin();
	Admin(const std::string&, const std::string&, const std::string&);
	void addAccount();
	bool deleteAccount();
	void printAccounts();
	bool changeAccount();
private:
	bool isLegit(const std::string,char);
	void format(std::string&);
	bool nameExists(std::string);
	bool is_textfile_empty();
	bool is_textfile_without_accounts();
};

