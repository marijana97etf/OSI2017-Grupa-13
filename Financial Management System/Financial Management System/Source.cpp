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
		std::cout << "                LOGIN                 " << std::endl;
		std::string name, pin;
		std::cout << "Unesite ime: ";
		std::cin >> name;
		std::cout << "Unesite pin: ";
		std::cin >> pin;
		while ( Admin::isNotLegit(pin,'P') )
		{
			std::cout << "Nedozvoljen format pin-a" << std::endl;
			std::cout << "Unesite novi pin : ";
			std::cin >> pin;
		}
		Account acc(name, pin);
		if ( acc.checkTypeOfUser() == IS_ADMIN)
		{
			std::cout << "Prijavljeni ste kao: " << "Administrator"<<std::endl;
			Sleep(1000);
			Admin ad(name, pin, NAME_OF_ADMIN);
			Menu menu(ad);
			while (1)
			{
				menu.printPattern(std::cout);
				menu.setOption(std::cin, std::cout);
				menu.executeOption();
				if ( menu.getCurrOption() == 0)
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
	getchar();
	getchar();
	return 0;
}
