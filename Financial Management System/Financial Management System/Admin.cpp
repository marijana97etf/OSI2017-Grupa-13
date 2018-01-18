#include "Admin.h"

Admin::Admin() :Account::Account()
{}

Admin::Admin(const std::string &username, const std::string &pin, const std::string &type) : Account::Account(username, pin, type)
{}

void Admin::addAccount()
{
	std::string _tmpusername, _tmppin;
	char type;
	bool _isLegit;
	bool _nameExists;
	if (is_textfile_empty())
	{
		std::fstream accounts_file(ACCOUNT_FILE_NAME, std::ios_base::app);
		accounts_file << "  Username             PIN      Type    " << "\n";
		accounts_file << "  --------------------------------------" << "\n";
		accounts_file.close();
	}
	std::fstream accounts_file(ACCOUNT_FILE_NAME, std::ios_base::app);
	std::cout << "Unesite podatke o novom nalogu:\n";
	do
	{
		std::cout << "Username: "; std::cin >> _tmpusername;
		_isLegit = isLegit(_tmpusername, 'U');
		_nameExists = nameExists(_tmpusername);
	} while (isLegit(_tmpusername, 'U') || nameExists(_tmpusername));
	do
	{
		std::cout << "PIN: "; std::cin >> _tmppin;
	} while (isLegit(_tmppin, 'P'));
	do
	{
		std::cout << "Unesite tip korisnika a[D]ministrator, a[N]aliticar"; std::cin >> type;
	} while (type != 'D' && type != 'N');

	format(_tmpusername, 'U');
	format(_tmppin, 'P');
	accounts_file << _tmpusername << _tmppin << ((type == 'D') ? "admin" : "analyst") << "\n";
	accounts_file.close();
}

bool Admin::deleteAccount()
{
	std::string _tmpusername, _testline;
	std::fstream file(ACCOUNT_FILE_NAME);
	if (is_textfile_empty() || is_textfile_without_accounts()) return false;
	do
	{
		std::cout << "Unesite username naloga koji treba obrisati\n";
		std::cin >> _tmpusername;
	} while (isLegit(_tmpusername, 'U'));
	if (nameExists(_tmpusername))
	{
		std::ofstream tmp(TMP_FILE, std::ios_base::trunc);
		while (file.peek() != std::ifstream::traits_type::eof())
		{
			getline(file, _testline);
			if (_testline.find(_tmpusername, 0) == std::string::npos)
				tmp << _testline << "\n";
			_testline.clear();
		}
		file.close();
		tmp.close();
		std::remove(ACCOUNT_FILE_NAME.c_str());
		std::rename(TMP_FILE.c_str(), ACCOUNT_FILE_NAME.c_str());
		return true;
	}
	std::cout << "Ime korisnika koje ste uneli ne postoji\n";
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
	std::string _tmpusername, _textdiff;
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
			insert(pullFromText(_tmpusername), _tmpusername, _textdiff, 'P');
		}
		if (c == 'U')
		{
			std::cout << "Unesite novi username:\n";
			do
			{
				std::cin >> _textdiff;
			} while (isLegit(_textdiff, 'U'));
			insert(pullFromText(_tmpusername), _tmpusername, _textdiff, 'U');
		}
		if (c == 'T')
		{
			std::cout << "Unesite novi tip korisnika a[D]ministrator, [A]naliticar:\n";
			do
			{
				std::cin >> c;
			} while (c != 'A' && c != 'D');
			std::string type = (c == 'D') ? "admin" : "analyst";
			if (c == 'A')
				insert(pullFromText(_tmpusername), _tmpusername, type , c);
			else
				insert(pullFromText(_tmpusername), _tmpusername, type, c);

		}
		return true;
	}
	return false;
}

void Admin::changeInterface()
{
	HANDLE consoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	int option;
	std::string choose;
	bool check = false;
	do
	{
		std::cout << "Da li zelite promjeniti boju pozadine: [Da/Ne]";
		std::cin >> choose;
		if (choose == "Da" || choose == "DA" || choose == "da" || choose == "dA")
		{
			do
			{
				std::cout << "Izaberite boju pozadine." << std::endl;
				std::cout << "[1] Bijela" << std::endl;
				std::cout << "[2] Crna" << std::endl;
				std::cout << "[3] Plava" << std::endl;
				std::cout << "[4] Crvena" << std::endl;
				std::cout << "[5] Zelena" << std::endl;
				std::cout << "[6] Zuta" << std::endl;
				std::cout << "[7] Narandzasta" << std::endl;
				std::cout << "[8] Smedja" << std::endl;
				std::cout << "[9] Siva" << std::endl;
				std::cout << "Unesite broj: ";
				std::cin >> option;
			} while (option < 1 || option > 9);
			CONSOLE_SCREEN_BUFFER_INFOEX sbInfoEx;
			sbInfoEx.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);
			GetConsoleScreenBufferInfoEx(consoleOut, &sbInfoEx);
			sbInfoEx.ColorTable[0] = colors[option];
			SetConsoleScreenBufferInfoEx(consoleOut, &sbInfoEx);
			check = true;
		}
		else if (choose == "Ne" || choose == "NE" || choose == "ne" || choose == "nE")
			check = true;
	} while(check != true);
	check = false;
	do
	{
		std::cout << "Da li želite promjeniti boju teksta: [Da/Ne]";
		std::cin >> choose;
		if (choose == "Da" || choose == "DA" || choose == "da" || choose == "dA")
		{
			do
			{
				std::cout << "Izaberite boju teksta." << std::endl;
				std::cout << "[1] Bijela" << std::endl;
				std::cout << "[2] Crna" << std::endl;
				std::cout << "[3] Plava" << std::endl;
				std::cout << "[4] Crvena" << std::endl;
				std::cout << "[5] Zelena" << std::endl;
				std::cout << "[6] Zuta" << std::endl;
				std::cout << "[7] Narandzasta" << std::endl;
				std::cout << "[8] Smedja" << std::endl;
				std::cout << "[9] Siva" << std::endl;
				std::cout << "Unesite broj: ";
				std::cin >> option;
			} while (option < 1 || option > 9);
			CONSOLE_SCREEN_BUFFER_INFOEX sbInfoEx;
			sbInfoEx.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);
			GetConsoleScreenBufferInfoEx(consoleOut, &sbInfoEx);
			sbInfoEx.ColorTable[15] = colors[option];
			SetConsoleScreenBufferInfoEx(consoleOut, &sbInfoEx);
			check = true;
		}
		else if (choose == "Ne" || choose == "NE" || choose == "ne" || choose == "nE")
			check = true;
	} while (check != true);
	check = false;
	do
	{
		std::cout << "Da li zelite promjeniti velicinu fonta: [Da/Ne]";
		std::cin >> choose;
		if (choose == "Da" || choose == "DA" || choose == "da" || choose == "dA")
		{
			std::cout << "Unesite velicinu fonta (Preporuka: Izaberite velicinu fonta vecu od 14.): ";
			std::cin >> option;
			CONSOLE_FONT_INFOEX font = { sizeof(CONSOLE_FONT_INFOEX) };
			GetCurrentConsoleFontEx(consoleOut, false, &font);
			font.dwFontSize = { 6, option };
			SetCurrentConsoleFontEx(consoleOut, false, &font);
			check = true;
		}
		else if (choose == "Ne" || choose == "NE" || choose == "ne" || choose == "nE")
			check = true;
	} while (check != true);
}

bool Admin::isLegit(std::string tmp, char typeofstring)
{
	std::locale loc;
	int i = 0;
	if (typeofstring == 'P')
	{
		if (tmp.length() != LENGTH_OF_PIN || tmp.empty()) return true;
		while (i < tmp.length())
			if (!std::isalnum(tmp[i++], loc))
				return true;
		return false;
	}
	if (typeofstring == 'U')
	{
		if (tmp.length() > MAX_LENGTH_OF_NAME || tmp.empty()) return true;
		while (i < tmp.length())
			if (!std::isalpha(tmp[i++], loc))
				return true;
		return false;
	}
}

void Admin::format(std::string &tmp, char c)
{
	if (c == 'U')
	{
		while (tmp.length() < MAX_LENGTH_OF_NAME) tmp += " ";
		tmp = "  " + tmp;
	}
	if (c == 'P')
		tmp += "    ";
	tmp += SEPARATOR;
}

bool Admin::nameExists(std::string testusername)
{
	std::ifstream file(ACCOUNT_FILE_NAME);
	std::string tmpline, _tmpdummy;
	if (is_textfile_empty() || is_textfile_without_accounts())
	{
		file.close();
		return false;
	}
	getline(file, _tmpdummy);
	getline(file, _tmpdummy);
	while (file.peek() != std::ifstream::traits_type::eof())
	{
		getline(file, tmpline);
		if (tmpline.find(testusername, 0) != std::string::npos)
		{
			file.close();
			return true;
		}
		tmpline.clear();
	}
	file.close();
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

const std::vector<std::string> Admin::explode(const std::string& s, const char& c)
{
	std::string buff{ "" };
	std::vector<std::string> v;

	for (auto n : s)
	{
		if (n != c) buff += n; else
			if (n == c && buff != "") { v.push_back(buff); buff = ""; }
	}
	if (buff != "") v.push_back(buff);

	return v;
}

const std::vector<std::string> Admin::pullFromText(std::string modkey)
{
	std::fstream file(ACCOUNT_FILE_NAME);
	std::string _testline, _line;
	while (file.peek() != std::ifstream::traits_type::eof())
	{
		getline(file, _testline);
		if (_testline.find(modkey, 0) != std::string::npos)
		{
			file.close();
			return explode(_testline, SEPARATOR);
		}
	}

}

void Admin::insert(const std::vector<std::string> _modvec, std:: string &text, std::string &textdiff, char c)
{
	std::ifstream accountfile(ACCOUNT_FILE_NAME);
	std::ofstream tmp(TMP_FILE);
	std::string _currline;
	while (accountfile.peek() != std::ifstream::traits_type::eof())
	{
		getline(accountfile, _currline);
		if (_currline.find(text, 0) == std::string::npos)
			tmp << _currline << "\n";
		else
		{
			if (c == 'P')
			{
				format(textdiff, 'P');
				tmp << _modvec[0] << SEPARATOR << textdiff << _modvec[2] << "\n";
			}
			if (c == 'U')
			{
				format(textdiff, 'U');
				tmp << textdiff << _modvec[1] << SEPARATOR << _modvec[2] << "\n";
			}
			if (c == 'A' || c == 'D')
				tmp << _modvec[0] << SEPARATOR << _modvec[1] << SEPARATOR << textdiff << "\n";
		}
		_currline.clear();
	}
	accountfile.close();
	tmp.close();
	std::remove(ACCOUNT_FILE_NAME.c_str());
	std::rename(TMP_FILE.c_str(), ACCOUNT_FILE_NAME.c_str());
}

