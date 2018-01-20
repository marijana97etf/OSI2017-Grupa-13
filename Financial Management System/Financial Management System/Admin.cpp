#include "Admin.h"

std::string currencies[] = { "BAM","EUR","USD","RSD","HRK" };

Admin::Admin() :Account::Account()
{}

Admin::Admin(const std::string &username, const std::string &pin, const std::string &type) : Account::Account(username, pin, type)
{
	std::string temp;
	std::ifstream input(CONFIG);
	getline(input, temp);
	getline(input, currency);
	input.close();
	input.open(CONFIG);
	getline(input, temp);
	if (input.eof())
	{
		input.close();
		std::ofstream output(CONFIG);
		output << temp << std::endl;
		short choose;
		do
		{
			system("CLS");
			std::cout << "Izaberite valutu sistema: " << std::endl;
			std::cout << "[1] (BAM) Konvertibilna marka" << std::endl;
			std::cout << "[2] (EUR) Euro" << std::endl;
			std::cout << "[3] (USD) Americki dolar" << std::endl;
			std::cout << "[4] (RSD) Srpski dinar" << std::endl;
			std::cout << "[5] (HRK) Hrvatska kuna" << std::endl;
			std::cout << "Unesite broj: ";
			std::cin >> choose;
		} while (choose < 1 || choose > 5);
		output << currencies[choose - 1];
		output.close();
	}
}

void Admin::addAccount()
{
	system("CLS");
	std::string tmpusername, tmp_pin;
	char type;
	int count = 0;
	char c;
	if (isAccountFileEmpty())
	{
		std::fstream account_file(ACCOUNT_FILE_NAME, std::ios_base::app);
		account_file << "  Username             PIN      Type    " << "\n";
		account_file << "  --------------------------------------" << "\n";
		account_file.close();
	}
	std::fstream account_file(ACCOUNT_FILE_NAME, std::ios_base::app);
	std::cout << "Unesite podatke o novom nalogu:\n";
	do
	{
		if (warningFunction(count++))
			return;
		std::cout << "Username: "; std::cin >> tmpusername;
	} while (isNotLegit(tmpusername, 'U') || nameExists(tmpusername));
	count = 0;
	do
	{
		if (warningFunction(count++))
			return;
		std::cout << "PIN: "; std::cin >> tmp_pin;
	} while (isNotLegit(tmp_pin, 'P'));
	count = 0;
	do
	{
		if (warningFunction(count++))
			return;
		std::cout << "Unesite tip korisnika a[D]ministrator, a[N]aliticar "; std::cin >> type;
	} while (type != 'D' && type != 'N');

	format(tmpusername, 'U');
	format(tmp_pin, 'P');
	account_file << tmpusername << tmp_pin << ((type == 'D') ? "admin" : "analyst") << "\n";
	account_file.close();
	std::cout << "Nalog je uspjesno dodan." << std::endl;
	Sleep(1000);
}

bool Admin::deleteAccount()
{
	system("CLS");
	if (isAccountFileEmpty() || isAccountFileWithoutAccounts()) return false;
	std::string username, testline;
	std::fstream account_file(ACCOUNT_FILE_NAME);
	int count = 0;
	char c = 'X';
	std::string temp;
	do
	{
		std::cout << "Unesite username naloga koji treba obrisati\n";
		do
		{
			if (warningFunction(count++))
				return false;
			std::cin >> username;
		} while (isNotLegit(username, 'U'));
		if (nameExists(username))
		{
			std::ofstream tmpfile(TMP_FILE, std::ios_base::trunc);
			while (account_file.peek() != std::ifstream::traits_type::eof())
			{
				getline(account_file, testline);
				if (testline.substr(2, testline.find_first_of(' ', 2) - 2) != username)
					tmpfile << testline << "\n";
				testline.clear();
			}
			account_file.close();
			tmpfile.close();
			std::remove(ACCOUNT_FILE_NAME.c_str());
			std::rename(TMP_FILE.c_str(), ACCOUNT_FILE_NAME.c_str());
			std::cout << "Nalog je uspjesno obrisan." << std::endl;
			Sleep(1000);
			return true;
		}
		std::cout << " Ime korisnika koje ste uneli ne postoji\n";
		std::cout << " Da li zelite unesete ponovo : [D]a, [N]e.\n UPOZORENJE!\n Unosenje bilo kog karaktera osim navedih ce se protumaciti\n kao komanda za izlazak\n iz procesa unosenja naloga!: ";
		std::cin >> temp;
		if (temp == "D")
			system("CLS");
	} while (temp == "D");
	return false;
}

void Admin::printAccounts()
{
	system("CLS");
	std::ifstream accountsfile(ACCOUNT_FILE_NAME);
	std::cout << accountsfile.rdbuf();
	accountsfile.close();
	getchar();
	std::cout << "Pritisni ENTER za povratak.";
	std::string temp;
	getline(std::cin, temp);
}

bool Admin::changeAccount()
{
	system("CLS");
	if (isAccountFileEmpty() || isAccountFileWithoutAccounts()) return false;
	std::string username, textdiff;
	int count = 0;
	char c = 'X';
	std::string temp;
	do
	{
		std::cout << "Unesite username naloga koji treba promjeniti\n";
		do
		{
			if (warningFunction(count++))
				return false;
			std::cin >> username;
		} while (isNotLegit(username, 'U'));
		count = 0;
		if (nameExists(username))
		{
			std::cout << "Unesite sta zelite izmjeniti: [U]sername, [P]IN, [T]ip korisnika\n";
			do
			{
				if (warningFunction(count++))
					return false;
				std::cin >> c;
			} while (c != 'P' && c != 'U' && c != 'T');
			if (c == 'P')
			{
				std::cout << "Unesite novi PIN:\n";
				do
				{
					if (warningFunction(count++))
						return false;
					std::cin >> textdiff;
				} while (isNotLegit(textdiff, 'P'));
				insert(pullFromText(username), username, textdiff, 'P');
			}
			if (c == 'U')
			{
				std::cout << "Unesite novi username:\n";
				do
				{
					if (warningFunction(count++))
						return false;
					std::cin >> textdiff;
				} while (isNotLegit(textdiff, 'U'));
				insert(pullFromText(username), username, textdiff, 'U');
			}
			if (c == 'T')
			{
				std::cout << "Unesite novi tip korisnika a[D]ministrator, [A]naliticar:\n";
				do
				{
					if (warningFunction(count++))
						return false;
					std::cin >> c;
				} while (c != 'A' && c != 'D');
				std::string type = (c == 'D') ? "admin" : "analyst";
				if (c == 'A')
					insert(pullFromText(username), username, type, c);
				else
					insert(pullFromText(username), username, type, c);

			}
			return true;
		}
		std::cout << " Ime korisnika koje ste uneli ne postoji\n";
		std::cout << " Da li zelite unesete ponovo : [D]a, [N]e.\n UPOZORENJE!\n Unosenje bilo kog karaktera osim navedih ce se protumaciti kao komanda za\n izlazak iz procesa izmjene naloga!: ";
		std::cin >> temp;
		if (temp == "D")
			system("CLS");
	} while (temp == "D");
	return false;
}

void Admin::changeInterface()
{
	HANDLE consoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	short option;
	std::string choose;
	bool check = false;
	do
	{
		system("CLS");
		std::cout << "Da li zelite promjeniti boju pozadine: [Da/Ne]";
		std::cin >> choose;
		if (choose == "Da" || choose == "DA" || choose == "da" || choose == "dA")
		{
			do
			{
				system("CLS");
				std::cout << "Izaberite boju pozadine." << std::endl;
				std::cout << "[1] Bijela" << std::endl;
				std::cout << "[2] Crna" << std::endl;
				std::cout << "[3] Plava" << std::endl;
				std::cout << "[4] Crvena" << std::endl;
				std::cout << "[5] Zelena" << std::endl;
				std::cout << "[6] Zuta" << std::endl;
				std::cout << "[7] Narandzasta" << std::endl;
				std::cout << "[8] Ljubicasta" << std::endl;
				std::cout << "[9] Smedja" << std::endl;
				std::cout << "[10] Siva" << std::endl;
				std::cout << "Unesite broj: ";
				std::cin >> option;
			} while (option < 1 || option > 10);
			changeBackgroundColor(option);
			check = true;
		}
		else if (choose == "Ne" || choose == "NE" || choose == "ne" || choose == "nE")
			check = true;
	} while (check != true);
	check = false;
	do
	{
		system("CLS");
		std::cout << "Da li zelite promjeniti boju teksta: [Da/Ne]";
		std::cin >> choose;
		if (choose == "Da" || choose == "DA" || choose == "da" || choose == "dA")
		{
			do
			{
				system("CLS");
				std::cout << "Izaberite boju pozadine." << std::endl;
				std::cout << "[1] Bijela" << std::endl;
				std::cout << "[2] Crna" << std::endl;
				std::cout << "[3] Plava" << std::endl;
				std::cout << "[4] Crvena" << std::endl;
				std::cout << "[5] Zelena" << std::endl;
				std::cout << "[6] Zuta" << std::endl;
				std::cout << "[7] Narandzasta" << std::endl;
				std::cout << "[8] Ljubicasta" << std::endl;
				std::cout << "[9] Smedja" << std::endl;
				std::cout << "[10] Siva" << std::endl;
				std::cout << "Unesite broj: ";
				std::cin >> option;
			} while (option < 1 || option > 10);
			changeTextColor(option);
			check = true;
		}
		else if (choose == "Ne" || choose == "NE" || choose == "ne" || choose == "nE")
			check = true;
	} while (check != true);
	check = false;
	do
	{
		system("CLS");
		std::cout << "Da li zelite promjeniti velicinu fonta: [Da/Ne]";
		std::cin >> choose;
		if (choose == "Da" || choose == "DA" || choose == "da" || choose == "dA")
		{
			do
			{
				system("CLS");
				std::cout << "Unesite velicinu fonta (Preporuka: Izaberite velicinu fonta vecu od 14.): ";
				std::cin >> option;
				changeFontSize(option);
				check = true;
			} while (option < 5 || option > 72);
		}
		else if (choose == "Ne" || choose == "NE" || choose == "ne" || choose == "nE")
			check = true;
	} while (check != true);
}

void Admin::getSystemCurrency()
{
	system("CLS");
	getchar();
	std::cout << "Valuta sistema je " << currency << std::endl;
	std::string temp;
	std::cout << "Pritisnite ENTER za povratak u meni.";
	getline(std::cin, temp);
}


bool Admin::isNotLegit(std::string string, char typeofstring)
{
	std::locale loc;
	int i = 0;
	if (typeofstring == 'P')
	{
		if (string.length() != LENGTH_OF_PIN || string.empty()) return true;
		while (i < string.length())
			if (!std::isalnum(string[i++], loc))
				return true;
		return false;
	}
	if (typeofstring == 'U')
	{
		if (string.length() > MAX_LENGTH_OF_NAME || string.empty()) return true;
		while (i < string.length())
			if (!std::isalpha(string[i++], loc))
				return true;
		return false;
	}
}

void Admin::format(std::string &string, char c)
{
	if (c == 'U')
	{
		while (string.length() < MAX_LENGTH_OF_NAME) string += " ";
		string = "  " + string;
	}
	if (c == 'P')
		string += "    ";
	string += SEPARATOR;
}

bool Admin::nameExists(std::string testusername)
{
	std::ifstream file(ACCOUNT_FILE_NAME);
	std::string tmpline, dummystring;
	if (isAccountFileEmpty() || isAccountFileWithoutAccounts())
	{
		file.close();
		return false;
	}
	getline(file, dummystring);
	getline(file, dummystring);
	while (file.peek() != std::ifstream::traits_type::eof())
	{
		getline(file, tmpline);
		if (tmpline.substr(2, tmpline.find_first_of(' ', 2) - 2) == testusername)
		{
			file.close();
			return true;
		}
		tmpline.clear();
	}
	file.close();
	return false;
}

bool Admin::isAccountFileEmpty()
{
	std::ifstream pfile(ACCOUNT_FILE_NAME);
	return pfile.peek() == std::ifstream::traits_type::eof();
}

bool Admin::isAccountFileWithoutAccounts()
{
	std::ifstream file(ACCOUNT_FILE_NAME);
	std::string firstline, secondline;
	getline(file, firstline);
	getline(file, secondline);
	if (firstline == FIRST_LINE_OF_HEADER && secondline == SECOND_LINE_OF_HEADER && file.peek() == std::ifstream::traits_type::eof())
	{
		file.close();
		return true;
	}
	file.close();
	return false;
}

const std::vector<std::string> Admin::explode(const std::string& string, const char& c)
{
	std::string buff{ "" };
	std::vector<std::string> v;

	for (auto n : string)
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
	std::string testline, line;
	while (file.peek() != std::ifstream::traits_type::eof())
	{
		getline(file, testline);
		if (testline.substr(2, testline.find_first_of(' ', 2) - 2) == modkey)
		{
			file.close();
			return explode(testline, SEPARATOR);
		}
	}

}

void Admin::insert(const std::vector<std::string> modvec, std:: string &text, std::string &textdiff, char c)
{
	std::ifstream accountfile(ACCOUNT_FILE_NAME);
	std::ofstream tmpfile(TMP_FILE);
	std::string currline;
	while (accountfile.peek() != std::ifstream::traits_type::eof())
	{
		getline(accountfile, currline);
		if (currline.substr(2, currline.find_first_of(' ', 2) - 2) != text)
			tmpfile << currline << "\n";
		else
		{
			if (c == 'P')
			{
				format(textdiff, 'P');
				tmpfile << modvec[0] << SEPARATOR << textdiff << modvec[2] << "\n";
			}
			if (c == 'U')
			{
				format(textdiff, 'U');
				tmpfile << textdiff << modvec[1] << SEPARATOR << modvec[2] << "\n";
			}
			if (c == 'A' || c == 'D')
				tmpfile << modvec[0] << SEPARATOR << modvec[1] << SEPARATOR << textdiff << "\n";
		}
		currline.clear();
	}
	accountfile.close();
	tmpfile.close();
	std::remove(ACCOUNT_FILE_NAME.c_str());
	std::rename(TMP_FILE.c_str(), ACCOUNT_FILE_NAME.c_str());
}

bool Admin::warningFunction(int count)
{
	char c = 'X';
	if (count > 3)
	{
		std::cout << " Uneli ste netacnu informaciju vise puta.\n Da li zelite da nastavite sa procesom: [D]a, [N]e?\n";
		std::cout << " UPOZORENJE!\n Unosenje bilo kog karaktera\n osim navedenih ce se protumaciti kao komanda za izlazak iz procesa: ";
		std::cin >> c;
		if (c != 'D' && c != 'N')
			return true;
		if (c == 'D')
			return false;
		return true;
	}
	return false;
}

