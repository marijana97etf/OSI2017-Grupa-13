#include "Analyst.h"
#include "Interface.h"


Analyst::Analyst() : Account::Account()
{
}

Analyst::Analyst(const std::string& username, const std::string& pin, const std::string& type) : Account::Account(username,pin,type)
{
	if (this->checkTypeOfUser() == IS_ANALYST)
	{
		std::string file = FILE_OF_BILLS;
		file += "\\*";
		std::vector<std::string> vec = returnVectorOfNotProcessedBills(file);
		for (int i = 0; i < vec.size(); i++)
		{
			bool format[5] = {};
			std::ofstream logOut(LOG,std::ios::app | std::ios::out);
			if ((format[0] = checkFormat1(vec[i])) || (format[1] = checkFormat2(vec[i])) || (format[2] = checkFormat3(vec[i])) || (format[3] = checkFormat4(vec[i])) || (format[4] = checkFormat5(vec[i])))
			{
				try
				{
					int j;
					for (j = 0; !format[j]; j++);
					Bill bill(vec[i], j + 1);
					if (!bill.Validate())//dodao sam ovde da bi se bacao izuzetak o gresci
						continue;
					bill.exportForCustomer();
					bill.exportForMonth();
					bill.exportForProduct();
					logOut << vec[i] << std::endl;
				}
				catch (std::invalid_argument &in)
				{
					ErrorException ex(vec[i], "U racunu se nalazi neodgovarajuci tip podatka.");
					ex.processException();
				}
			}
			else
			{
				ErrorException ex(vec[i], "Neodgovarajuci format.");
				ex.processException();
			}
		}
	}
}

bool Analyst::inportForCustomer()
{
	system("CLS");
	std::string customer;
	std::cout << "Unesite kupca: ";
	getline(std::cin, customer);
	std::ifstream in;
	in.open("Kupac\\" + customer + ".txt", std::ios::in);
	if (in.is_open())
	{
		std::string temp;
		while (!in.eof())
		{
			getline(in, temp);
			std::cout << temp << std::endl;
		}
		std::cout << "Pritisnite ENTER za povratak u meni." << std::endl;
		getline(std::cin, temp);
		return true;
	}
	else
	{
		std::cout << "Nema podataka za unesenog kupca." << std::endl;
		Sleep(1000);
		return false;
	}
}

bool Analyst::inportForProduct()
{
	system("CLS");
	std::string product;
	std::cout << "Unesite proizvod: ";
	getline(std::cin, product);
	std::ifstream in;
	in.open("Proizvod\\" + product + ".txt", std::ios::in);
	if (in.is_open())
	{
		std::string temp;
		while (!in.eof())
		{
			getline(in, temp);
			std::cout << temp << std::endl;
		}
		std::cout << "Pritisnite ENTER za povratak u meni." << std::endl;
		getline(std::cin, temp);
		return true;
	}
	else
	{
		std::cout << "Nema podataka za uneseni proizvod." << std::endl;
		Sleep(1000);
		return false;
	}
}

bool Analyst::inportForMonth()
{
	system("CLS");
	std::string date;
	std::cout << "Unesite mjesec i godinu (npr: Januar 2017): ";
	getline(std::cin, date);
	std::ifstream in;
	in.open("Mjesec\\" + date + ".txt", std::ios::in); //month je oblika "Januar 2017"
	if (in.is_open())
	{
		std::string temp;
		while (!in.eof())
		{
			getline(in, temp);
			std::cout << temp << std::endl;
		}
		std::cout << "Pritisnite ENTER za povratak u meni." << std::endl;
		getline(std::cin, temp);
		return true;
	}
	else
	{
		std::cout << "Nema podataka za uneseni datum." << std::endl;
		Sleep(1000);
		return false;
	}
}


Analyst::~Analyst()
{
}
