#pragma once
#include<iostream>
#include<fstream>
#include<string>

const int MAX_LENGTH_OF_NAME = 20,LENGTH_OF_PIN = 4, MAX_LENGTH_OF_TYPE('10');
const int MAX_LENGTH_OF_ROW = 100;
const std::string ACCOUNT_FILE_NAME("accountfile");
const std::string NAME_OF_ADMIN("admin"),NAME_OF_ANALYST("analyst");
const char END_OF_LINE('\n'),SEPARATOR('|');
const int ERROR = -1;
const int IS_ADMIN = 0, IS_ANALYST = 1;

class Account
{
protected:
	std::string username, pin, type;
	void ignoreElementsUntil(std::ifstream &, char);
public:
	Account();
	Account(const std::string&, const std::string&, const std::string&);

	Account getNextUser(std::ifstream &);		
	int checkTypeOfUser();

private:
	friend std::ostream& operator<<(std::ostream&, const Account&);
	friend std::istream& operator>>(std::istream&, Account&);

};

