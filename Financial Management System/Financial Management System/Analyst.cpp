#include "Analyst.h"



Analyst::Analyst() : Account::Account()
{
}

Analyst::Analyst(const std::string& username, const std::string& pin, const std::string& type) : Account::Account(username,pin,type)
{
	if (this->checkTypeOfUser() == IS_ANALYST)
	{
		std::vector<std::string> vec = returnVectorOfNotProcessedBills("*");
		for (int i = 0; i < vec.size(); i++)
		{
			int formatCode;
			std::ofstream logOut(LOG, std::ios::in);
			if (checkFormat1(vec[i]))
			{
				formatCode = 1;
				Bill bill(vec[i], formatCode);
				try
				{
					bill.Validate();//dodao sam ovde da bi se bacao izuzetak o gresci
					bill.process();
					bill.exportForCustomer();
					bill.exportForMonth();
					bill.exportForProduct();
					logOut << vec[i] << std::endl;
				}
				catch (ErrorException& ex)
				{
					ex.processException();
				}
			}
			else if (checkFormat2(vec[i]))
			{
				formatCode = 2;
				Bill bill(vec[i], formatCode);
				try
				{
					bill.Validate();
					bill.process();
					bill.exportForCustomer();
					bill.exportForMonth();
					bill.exportForProduct();
					logOut << vec[i] << std::endl;
				}
				catch (ErrorException& ex)
				{
					ex.processException();
				}
			}
			else if (checkFormat3(vec[i]))
			{
				formatCode = 3;
				Bill bill(vec[i], formatCode);
				try
				{
					bill.Validate();
					bill.process();
					bill.exportForCustomer();
					bill.exportForMonth();
					bill.exportForProduct();
					logOut << vec[i] << std::endl;
				}
				catch (ErrorException& ex)
				{
					ex.processException();
				}
			}
			else if (checkFormat4(vec[i]))
			{
				formatCode = 4;
				Bill bill(vec[i], formatCode);
				try
				{
					bill.Validate();
					bill.process();
					bill.exportForCustomer();
					bill.exportForMonth();
					bill.exportForProduct();
					logOut << vec[i] << std::endl;
				}
				catch (ErrorException& ex)
				{
					ex.processException();
				}
			}
			else if (checkFormat5(vec[i]))
			{
				formatCode = 5;
				Bill bill(vec[i], formatCode);
				try
				{
					bill.Validate();
					bill.process();
					bill.exportForCustomer();
					bill.exportForMonth();
					bill.exportForProduct();
					logOut << vec[i] << std::endl;
				}
				catch (ErrorException& ex)
				{
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

bool Analyst::inportForCustomer(const std::string& customer, std::ostream& out)
{
	std::ifstream in;
	in.open("Kupac\\" + customer + ".txt", std::ios::in);
	//trebalo bi ispisati nekakvu poruku da li ima ili nema kupca i tako za sve ove importe
	if (in.is_open())
	{
		std::string temp;
		while (!in.eof())
		{
			getline(in, temp);
			out << temp;
		}
		return true;
	}
	else
		return false;
}

bool Analyst::inportForProduct(const std::string& product, std::ostream& out)
{
	std::ifstream in;
	in.open("Proizvod\\" + product + ".txt", std::ios::in);
	if (in.is_open())
	{
		std::string temp;
		while (!in.eof())
		{
			getline(in, temp);
			out << temp;
		}
		return true;
	}
	else
		return false;
}

bool Analyst::inportForMonth(const std::string& month, std::ostream& out)
{
	std::ifstream in;
	in.open("Mjesec\\" + month + ".txt", std::ios::in); //month je oblika "Januar 2017"
	if (in.is_open())
	{
		std::string temp;
		while (!in.eof())
		{
			getline(in, temp);
			out << temp;
		}
		return true;
	}
	else
		return false;
}


Analyst::~Analyst()
{
}
