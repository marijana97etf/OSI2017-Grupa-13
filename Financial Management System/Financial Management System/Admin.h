#pragma once
#include "Account.h"
#include <cstdio>
#include<iostream>
#include<fstream>
#include<string>
#include <locale>
#include <cstdio>
#include <vector>

const std::string FIRST_LINE_OF_HEADER("  Username             PIN      Type    ");
const std::string SECOND_LINE_OF_HEADER("  --------------------------------------");
const std::string TMP_FILE("tmpfile.txt");


class Admin :
	public Account
{
public:
	Admin();
	Admin(const std::string&, const std::string&, const std::string&);
	virtual void addAccount();
	virtual bool deleteAccount();
	virtual void printAccounts();
	virtual bool changeAccount();
private:
	bool isNotLegit(const std::string,char);
	void format(std::string&, char);
	bool nameExists(std::string);
	bool isAccountFileEmpty();
	bool isAccountFileWithoutAccounts();
	const std::vector<std::string> pullFromText(std::string);
	const std::vector<std::string> explode(const std::string& s, const char& c);
	void insert(const std::vector<std::string>, std::string&, std::string&, char);
	bool warningFunction(int);
};

