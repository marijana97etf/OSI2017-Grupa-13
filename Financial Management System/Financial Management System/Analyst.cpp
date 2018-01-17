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
			if (checkFormat1(vec[i]))
			{
				formatCode = 1;
				Bill bill(vec[i], formatCode);
				//fali export podataka sa racuna u fajlove
			}
			else if (checkFormat2(vec[i]))
			{
				formatCode = 2;
				Bill bill(vec[i], formatCode);
			}
			else if (checkFormat3(vec[i]))
			{
				formatCode = 3;
				Bill bill(vec[i], formatCode);
			}
			else if (checkFormat4(vec[i]))
			{
				formatCode = 4;
				Bill bill(vec[i], formatCode);
			}
			else if (checkFormat5(vec[i]))
			{
				formatCode = 5;
				Bill bill(vec[i], formatCode);
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
