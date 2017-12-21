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
	void skip(std::fstream&, char);
	void modify(std::string&, std::string);
	const std::vector<std::string> explode(const std::string&, const char&)
};

