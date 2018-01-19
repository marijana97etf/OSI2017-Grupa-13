#pragma once
#include "Account.h"
#include <cstdio>
#include<iostream>
#include<fstream>
#include<string>
#include <locale>
#include <cstdio>
#include <vector>
#include <windows.h>

COLORREF WHITE = RGB(255, 255, 255);
COLORREF BLACK = RGB(0, 0, 0);
COLORREF BLUE = RGB(0, 0, 255);
COLORREF RED = RGB(255, 0, 0);
COLORREF GREEN = RGB(0, 255, 0);
COLORREF YELLOW = RGB(255, 255, 0);
COLORREF ORANGE = RGB(255, 165, 0);
COLORREF PURPLE = RGB(128, 0, 128);
COLORREF BROWN = RGB(102, 51, 0);
COLORREF SILVER = RGB(192, 192, 192);

COLORREF colors[] = { WHITE,BLACK,BLUE,RED,GREEN,YELLOW,ORANGE,PURPLE,BROWN,SILVER };
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
	virtual void changeInterface();
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

