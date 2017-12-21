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
		accounts_file << FIRST_LINE_OF_HEADER << "\n";
		accounts_file << SECOND_LINE_OF_HEADER << "\n";
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
	
	accounts_file << _tmpusername;
	format(_tmpusername);
	accounts_file << SEPARATOR << _tmppin << SEPARATOR << "    " << SEPARATOR << ((type = 'D') ? "admin" : "analyst")<<"\n";

	accounts_file.close();
}

bool Admin::deleteAccount()
{
	std::string _tmpusername, _testline;
	std::fstream file(ACCOUNT_FILE_NAME);
	char tmp;
	if (is_textfile_empty() || is_textfile_without_accounts()) return false;
	do
	{
		std::cout << "Unesite username naloga koji treba obrisati\n";
		std::cin >> _tmpusername;
	} while (isLegit(_tmpusername, 'U'));
	if (nameExists(_tmpusername))
	{
		std::fstream tmp(TMP_FILE, std::fstream::trunc);
		while (getline(file, _testline))
		{
			if (_testline.find(_tmpusername, 0) == -1)
				tmp << _testline << "\n";
		}
		file = std::move(tmp);
		file.close();
		tmp.close();
		return true;
	}
	return false;
}

	void Admin::printAccounts()
	{
		std::ifstream acccouts_file(ACCOUNT_FILE_NAME);
		std::cout << acccouts_file.rdbuf();
		acccouts_file.close();
	}

	bool Admin::changeAccount()
	{
		std::string _tmpusername, _testline, _textdiff;
		char c;
		do
		{
			std::cout << "Unesite username naloga koji treba promjeniti\n";
			std::cin >> _tmpusername;
		} while (isLegit(_tmpusername, 'U'));
		if (nameExists(_tmpusername))
		{
			std::cout << "Unesite sta zelite izmjeniti: [U]sername, [P]IN, [T]ip korisnika\n";
			do
			{
				std::cin >> c;
			} while (c != 'P' && c != 'U' && c != 'T');
			if (c == 'P')
			{
				std::cout << "Unesite novi PIN:\n";
				do
				{
					std::cin >> _textdiff;
				} while (isLegit(_textdiff, 'P'));
				modify(_testline, _tmpusername);
				std::vector < std::string > _modvector = explode(_testline, SEPARATOR);//sta ovo radi
				std::ofstream accounts(ACCOUNT_FILE_NAME, std::ofstream::app);
				accounts << _modvector[0] << SEPARATOR << _textdiff << "    " << SEPARATOR << _modvector[2] << "\n";//???
			}
			if (c == 'U')
			{
				std::cout << "Unesite novi username:\n";
				do
				{
					std::cin >> _textdiff;
				} while (isLegit(_textdiff, 'U'));
				modify(_testline, _tmpusername);
				std::vector < std::string > _modvector = explode(_testline, SEPARATOR);
				std::ofstream accounts(ACCOUNT_FILE_NAME, std::ofstream::app);
				accounts << _textdiff << SEPARATOR << _modvector[1] << "    " << SEPARATOR << _modvector[2] << "\n";
			}
			if (c == 'T')
			{
				std::cout << "Unesite novi tip korisnika a[D]ministrator, [A]naliticar:\n";
				do
				{
					std::cin >> c;
				} while (c != 'A' && c != 'D');
				modify(_testline, _tmpusername);
				std::vector < std::string > _modvector = explode(_testline, SEPARATOR);
				std::ofstream accounts(ACCOUNT_FILE_NAME, std::ofstream::app);
				accounts << _modvector[0] << SEPARATOR << _modvector[1] << "    " << SEPARATOR << ((c == 'A') ? "analyst" : "admin") << "\n";
			}
			return true;
		}
		return false;
	}

	bool Admin::isLegit(std::string tmp, char typeofstring)
{
		std::locale loc;
	int i = 0;
	if (typeofstring == 'P')
	{
		if (tmp.length() != LENGTH_OF_PIN || tmp.empty()) return true;//pin mora biti tacno duzine cetiri a ne samo vece
		while (i++ <= tmp.length())                                  //malo nema smisla slati true ako je nesto netacno jer je funkcija isLegit
			if (!std::isalnum(tmp[i], loc))							 // cela funkcija ima obruntu logiku
				return true;									     //vraca true ako je nesto nelegitimno
		return false;											     //aha vidim u cemu je greska
	}																 //sada je dobro?
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
	if (is_textfile_empty() || is_textfile_without_accounts())
	{
		file.close();
		return false;
	}
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
		file.close();
	}
	return false;
}

bool Admin::is_textfile_empty()
{
	std::ifstream pFile(ACCOUNT_FILE_NAME);
	return pFile.peek() == std::ifstream::traits_type::eof();
	pFile.close();
}

bool Admin::is_textfile_without_accounts()
{
	std::ifstream file(ACCOUNT_FILE_NAME);
	std::string firstLine, secondLine;
	getline(file, firstLine);
	getline(file, secondLine);
	if (firstLine == FIRST_LINE_OF_HEADER && secondLine == SECOND_LINE_OF_HEADER && file.peek() == std::ifstream::traits_type::eof())
	{
		file.close();
		return true;
	}
	file.close();
	return false;
}

void Admin::modify(std::string &moddedline, std::string modkey)
{
	std::fstream file(ACCOUNT_FILE_NAME);
	std::fstream tmp(TMP_FILE, std::fstream::trunc);
	std::string _testline;
	while (getline(file, _testline))
	{
		if (_testline.find(modkey, 0) == -1)
			tmp << _testline << "\n";
		else
			moddedline = _testline;
	}
	file.swap(tmp);
	file.close();
	tmp.close();



