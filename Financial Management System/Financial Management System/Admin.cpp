#include "Admin.h"

Admin::Admin():Account::Account()
{}

Admin::Admin(const std::string &username, const std::string &pin, const std::string &type):Account::Account(username, pin, type)
{}

void Admin::addAccount()
{
	std::string _tmpusername, _tmppin;
	char type;
	std::fstream accounts_file(ACCOUNT_FILE_NAME);
	if (accounts_file.peek() == 'NUL')
	{
		accounts_file << "Username             PIN      Type    \n";
		accounts_file << "--------------------------------------\n";
	}
	accounts_file.seekp(std::ios_base::end);
	std::cout << "Unesite podatke o novom nalogu:\n";
	do
	{
		std::cout << "Username: "; std::cin >> _tmpusername;
	} while (isLegit(_tmpusername, 'U'));
	do
	{
		std::cout << "PIN: "; std::cin >> _tmppin;
	} while (isLegit(_tmppin, 'P'));
	do
	{
		std::cout << "Unesite tip korisnika a[D]ministrator, a[N]aliticar"; std::cin >> type;
	} while (type != 'D' || type != 'N');
	while (_tmpusername.length() < MAX_LENGTH_OF_NAME) _tmpusername += " ";
	accounts_file << _tmpusername << SEPARATOR << _tmppin << SEPARATOR << "    " << ((type = 'D') ? "admin" : "analyst")<<"\n";
}

void Admin::printAccounts()
{
	std::ifstream acccouts_file(ACCOUNT_FILE_NAME);
	std::cout << acccouts_file.rdbuf();
}

bool Admin::isLegit(std::string tmp, char typeofstring)
{
	std::locale loc;
	int i = 0;
	if (typeofstring == 'P')
	{
		if (tmp.length() > LENGTH_OF_PIN || tmp.empty()) return true;
		while (i++ <= tmp.length())
			if (!std::isalnum(tmp[i], loc)) 
				return true;
		return false;
	}
	if (typeofstring == 'P')
	{
		if (tmp.length() > LENGTH_OF_PIN || tmp.empty()) return true;
		while (i++ <= tmp.length())
			if (!std::isalpha(tmp[i], loc))
				return true;
		return false;
	}
}



