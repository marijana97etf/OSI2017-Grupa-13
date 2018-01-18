#include "Menu.h"


Menu::Menu(Account &account):accountP(&account)
{}

bool Menu::setOption(std::istream &input,std::ostream & output)
{
	int option;
	output << "Unos:";
	input >> option;
	currOption = option;
}

void Menu::executeOption()//pogledajte ovo
{
	if (accountP->getType == NAME_OF_ADMIN)
	{
		switch (currOption)
		{
			case 1:accountP->addAccount(); break;
			case 2:accountP->deleteAccount(); break;
			case 3:accountP->printAccounts(); break;
			case 4:accountP->changeAccount(); break;
			case 5:accountP->changeInterface(); break;
				//ostaju mi jos dva case
			case -1:accountP->exitSystem(); break;
			default: std::cout << "Greska u unosu indeksa operacije" << std::endl; break;
		}
	}
	else
	{
		switch (currOption)
		{
		case 1:accountP->inportForCustomer(); break;//Sale ako moze promijeniti fukcije da se u njima unosi korisnik ,produkt ili mjesec
		case 2:accountP->inportForProduct(); break;
		case 3:accountP->inportForMonth(); break;
		case 0:break;
		case -1:accountP->exitSystem; break;
		default: std::cout << "Greska u unosu indeksa operacije" << std::endl; break;
		}
	}
}

void Menu::printPattern(std::ostream& output)
{
	output << "Izaberite neku od opcija:" << std::endl;
	if (accountP->getType == NAME_OF_ADMIN)
		for (int i = 0; i < patterns::MAX_OPTIONS_FOR_ADMIN; i++)
			output << patterns::optionsForAdmin[i] << std::endl;
	else
		for (int i = 0; i < patterns::MAX_OPTIONS_FOR_ANALYST; i++)
			output << patterns::optionsForAnalist[i] << std::endl;
}

int Menu::getCurrOption()
{
	return currOption;
}

Menu::~Menu()
{
}

/*void Menu::setIfOptionRangeIsValid(int &option,const int limit)
{
	std::cin >> option;
	while (option < 0 || option >= limit)
	{
		std::cout << "Pogreska u unosu broja za izbor opcije" << END_OF_LINE << "Unesite ponovo:";
		std::cin >> option;
	}
}
*/