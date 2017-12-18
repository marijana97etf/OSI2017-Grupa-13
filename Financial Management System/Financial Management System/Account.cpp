#include "Account.h"



Account::Account():username(nullptr),pin(nullptr),type(nullptr)
{}


Account::Account(const std::string &username, const std::string &pin, const std::string &type):username(username),pin(pin),type(type)
{}

Account Account::getNextUser(std::ifstream &inputf)
{
	int start = inputf.tellg();
	if (start == 0)//provjeriti da li je ova linija korektna
	{
		ignoreElementsUntil(inputf, END_OF_LINE);
		ignoreElementsUntil(inputf, END_OF_LINE);
	}

	ignoreElementsUntil(inputf, '.');
	getline(inputf,username,' ');

	ignoreElementsUntil(inputf, SEPARATOR);
	getline(inputf,pin,' ');

	ignoreElementsUntil(inputf, SEPARATOR);
	getline(inputf,type, ' ');


	return *this;
}

int Account::checkTypeOfUser()
{
	std::ifstream inputf(ACCOUNT_FILE_NAME);
	while (!inputf.eof())
	{
		Account next = getNextUser(inputf);
		if (next.username == username && next.pin == pin)
			return next.type == NAME_OF_ADMIN ? IS_ADMIN : IS_ANALYST;

	}
	return ERROR;
}

void Account::ignoreElementsUntil(std::ifstream& inputf, char boundary)
{
	char tmp;
	while ((tmp = inputf.get()) != boundary);
	return;
}

std::ostream & operator<<(std::ostream &output,const Account &other)
{
	return output << other.username << " " << other.pin << " " << other.type << std::endl;
}

std::istream & operator>>(std::istream &input, Account &other)
{
	return input >> other.username >> other.pin >> other.type;
}
