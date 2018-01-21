#include<iostream>
#include<cstdlib>
#include<Windows.h>
#include"Menu.h"
#include"ErrorException.h"
#include "Interface.h"
#include"Account.h"
#include"Admin.h"
#include"Analyst.h"
#include"Bill.h"

int main()
{
	systemConfiguration();
	while (1)
	{
		system("CLS");
		std::cout << "  ____        _                     _           _ _ " << std::endl;
		std::cout << " |  _ \\  ___ | |__  _ __ ___     __| | ___  ___| (_)" << std::endl;
		std::cout << " | | | |/ _ \\| '_ \\| '__/ _ \\   / _` |/ _ \\/ __| | |" << std::endl;
		std::cout << " | |_| | (_) | |_) | | | (_) | | (_| | (_) \\__ \\ | |" << std::endl;
		std::cout << " |____/ \\___/|_.__/|_|  \\___/   \\__,_|\\___/|___/_|_|" << std::endl;
		std::cout << "----------------------------------------------------" << std::endl;
		std::cout << "                       LOGIN                        " << std::endl;
		std::string name, pin;
		std::cout << "Unesite ime: ";
		getline(std::cin, name);
		std::cout << "Unesite pin: ";
		getline(std::cin, pin);
		if (Admin::isNotLegit(pin, 'P'))
		{
			std::cout << "Nedozvoljen format PIN-a" << std::endl;
			Sleep(1000);
		}
		else
		{
			Account acc(name, pin);
			if (acc.checkTypeOfUser() == IS_ADMIN)
			{
				std::cout << "Prijavljeni ste kao: " << "Administrator" << std::endl;
				Sleep(1000);
				Admin ad(name, pin, NAME_OF_ADMIN);
				Menu menu(ad);
				while (1)
				{
					menu.printPattern(std::cout);
					try
					{
						menu.setOption(std::cin, std::cout);
						menu.executeOption();
					}
					catch (std::invalid_argument &ex)
					{
						std::cout << "Greska u unosu." << std::endl << "Potrebno je unijeti jednu od cifara u [] zagradama za odabir odgovarajuce opcije ." << std::endl;
						Sleep(2000);
					}
					if (menu.getCurrOption() == 0)
						break;
				}
			}
			else
				if (acc.checkTypeOfUser() == IS_ANALYST)
				{
					std::cout << "Prijavljeni ste kao: " << "Analiticar" << std::endl;
					Sleep(1000);
					Analyst an(name, pin, NAME_OF_ANALYST);
					Menu menu(an);
					while (1)
					{
						menu.printPattern(std::cout);
						try
						{
							menu.setOption(std::cin, std::cout);
							menu.executeOption();
						}
						catch (std::invalid_argument &ex)
						{
							std::cout << "Greska u unosu." << std::endl << "Potrebno je unijeti jednu od cifara u [] zagradama za odabir odgovarajuce opcije ." << std::endl;
							Sleep(2000);
						}
						if (menu.getCurrOption() == 0)
							break;
					}
				}
				else
				{
					std::cout << "Korisnik sa unesenim imenom i pinom ne postoji na sistemu." << std::endl;
					std::cout << "Prijavite se ponovo." << std::endl << "Nova prijava zapocinje uskoro" << std::endl;
					Sleep(3000);
				}
		}
	}
	getchar();
	getchar();
	return 0;
}
