#include "Admin.h"

Admin::Admin():Account::Account()
{}

Admin::Admin(const std::string &username, const std::string &pin, const std::string &type):Account::Account(username, pin, type)
{}

void Admin::addAccount()
{
	std::string _tmpusername, _tmppin;
	char type;
	std::fstream accounts_file(ACCOUNT_FILE_NAME, std::fstream::app);
	if (is_textfile_empty())
	{
		accounts_file << "Username             PIN      Type    \n";
		accounts_file << "--------------------------------------\n";
	}
	std::cout << "Unesite podatke o novom nalogu:\n";
	do
	{
		std::cout << "Username: "; std::cin >> _tmpusername;
	} while (isLegit(_tmpusername, 'U') || nameExists(_tmpusername));
	do
	{
		std::cout << "PIN: "; std::cin >> _tmppin;
	} while (isLegit(_tmppin, 'P'));
	do
	{
		std::cout << "Unesite tip korisnika a[D]ministrator, a[N]aliticar"; std::cin >> type;
	} while (type != 'D' || type != 'N');
	
	format(_tmpusername);
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
	if (typeofstring == 'U')
	{
		if (tmp.length() > MAX_LENGTH_OF_NAME || tmp.empty()) return true;
		while (i++ <= tmp.length())
			if (!std::isalpha(tmp[i], loc))
				return true;
		return false;
	}
}

void Admin::format(std::string &tmp)
{
	while (tmp.length() < MAX_LENGTH_OF_NAME) tmp += " ";
}

bool Admin::nameExists(std::string testusername)
{
	std::ifstream file(ACCOUNT_FILE_NAME);
	std::string tmpusername;
	char tmp;
	if (is_textfile_empty() || is_textfile_without_accounts()) return false;
	ignoreElementsUntil(file, END_OF_LINE);
	ignoreElementsUntil(file, END_OF_LINE);
	while(file.peek() != std::ifstream::traits_type::eof())
	{
		file.get();
		file.get();
		while ((tmp = file.get()) != ' ') tmpusername += tmp;
		if (tmpusername == testusername) return true;
		tmpusername.clear();
		ignoreElementsUntil(file, END_OF_LINE);
	}
	return false;
}

bool Admin::is_textfile_empty()
{
	std::ifstream pFile(ACCOUNT_FILE_NAME);
	return pFile.peek() == std::ifstream::traits_type::eof();
}

bool Admin::is_textfile_without_accounts()
{
	std::ifstream file(ACCOUNT_FILE_NAME);
	std::string firstLine;
	getline(file, firstLine, '\n');
	if (firstLine == "Username             PIN      Type    ") return true;
	return false;
}



