#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<cstdlib>

const int MAX_LENGTH_OF_NAME = 20,LENGTH_OF_PIN = 4, MAX_LENGTH_OF_TYPE('10');
const int MAX_LENGTH_OF_ROW = 100;
const std::string ACCOUNT_FILE_NAME("accountfile.txt");
const std::string NAME_OF_ADMIN("admin"),NAME_OF_ANALYST("analyst");
const char END_OF_LINE('\n'),SEPARATOR('|');
const int ERRORFLAG = -1;
const int IS_ADMIN = 0, IS_ANALYST = 1;

class Account
{
protected:
	std::string username, pin, type;
	void ignoreElementsUntil(std::ifstream &, char);
public:
	Account();
	Account(const std::string&, const std::string&, const std::string& = "");//mijenjao sam ovu liniju

	Account getNextUser(std::ifstream &);		
	int checkTypeOfUser();
	std::string getType();

	void exitSystem();//ostalo je da se ovo napise

	virtual void addAccount() {};
	virtual bool deleteAccount() { return false;  };
	virtual void printAccounts() {};
	virtual bool changeAccount() { return false;  };
	virtual void changeInterface() {};
	virtual void getSystemCurrency() {};

	virtual bool inportForCustomer() { return false; };//vraca true ako je uspio inportovati, a false ako nije
	virtual bool inportForProduct() { return false;  };
	virtual bool inportForMonth() { return false; };
	//VIdi sta ces sa destruktorom

private:
	friend std::ostream& operator<<(std::ostream&, const Account&);
	friend std::istream& operator>>(std::istream&, Account&);

};

