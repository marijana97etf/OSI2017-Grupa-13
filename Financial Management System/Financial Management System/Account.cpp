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
	char username[MAX_LENGTH_OF_NAME], pin[LENGTH_OF_PIN], type[MAX_LENGTH_OF_TYPE];

	ignoreElementsUntil(inputf, '.');
	inputf.getline(username, MAX_LENGTH_OF_NAME, ' ');

	ignoreElementsUntil(inputf, SEPARATOR);
	inputf.getline(pin, LENGTH_OF_PIN);

	ignoreElementsUntil(inputf, SEPARATOR);
	inputf.getline(type, MAX_LENGTH_OF_TYPE, ' ');

	return Account(username, pin, type);//da li podrazumijevani move konstruktor dobro kopira stringove
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

