#include<iostream>
#include"Menu.h"
#include"ErrorException.h"
#include"Account.h"
#include"Admin.h"
#include"Analyst.h"
#include"Bill.h"


int main()
{
	std::cout << "Dobrodosli :D " << std::endl;
	while (1)
	{
		std::string name, pin;
		std::cout << "Unesite ime" << std::endl;
		std::cin >> name;//treba izvrsiti provjeru imena
		std::cout << "Unesite pin" << std::endl;
		std::cin >> pin;
		Account acc(name, pin);
		if (acc.checkTypeOfUser == NAME_OF_ADMIN)
		{
			Admin ad(name, pin, NAME_OF_ADMIN);//treba izmanipulisati destruktorima da se pravilno oslobodi memorija kod polimorfizma
			Menu menu(ad);
			while (1)
			{
				menu.printPattern(std::cout);
				menu.setOption(std::cin, std::cout);
				menu.executeOption();
				if (menu.getCurrOption == 0)
					break;
			}
		}
		else
			if (acc.checkTypeOfUser == NAME_OF_ANALYST)
			{
				Analyst an(name, pin, NAME_OF_ANALYST);
				Menu menu(an);
				while (1)
				{
					menu.printPattern(std::cout);
					menu.setOption(std::cin, std::cout);//Treba jos vidjeti sta cemo sa ispisom kod analiticara kod funkcija koje on odabir
					menu.executeOption();               //Mislim da se moze otvoriti noi prozor konzole za to da se ne guzva
					if (menu.getCurrOption == 0)        //I jos bi trebali tu par informacija ispisati
						break;                          //I JOS DESTRUKTOR
				}                                       //jos treba namjestiti da se bacaju izuzetci u validaciji i da se hvataju
			}                                           
	}
	getchar();
	getchar();
	return 0;
}
