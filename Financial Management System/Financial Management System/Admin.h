#pragma once
#include "Account.h"
#include <locale>
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
};

