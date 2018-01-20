#include "Menu.h"


Menu::Menu(Account &account):accountP(&account),currOption(DEFAULT_OPTION)
{}

void Menu::setOption(std::istream &input,std::ostream & output)
{
	std::string option;
	output << "Unos:";
	input >> option;
	try
	{
		currOption = std::stoi(option, nullptr, 10);
	}
	catch (std::invalid_argument &ex)
	{
		output << "Greska u unosu." << std::endl << "Potrebno je unijeti jednu od cifara u [] zagradama za odabir odgovarajuce opcije ." << std::endl;
		Sleep(2000);
	}
}

void Menu::executeOption()
{
	if ( accountP->getType() == NAME_OF_ADMIN)
	{
		switch (currOption)
		{
			case 1:accountP->addAccount(); break;
			case 2:accountP->deleteAccount(); break;
			case 3:accountP->printAccounts(); break;
			case 4:accountP->changeAccount(); break;
			case 5:accountP->changeInterface(); break;
			case 6:accountP->getSystemCurrency(); break;
			case 0: break;
			case -1:accountP->exitSystem(); break;
			default: std::cout<< "Greska u unosu." << std::endl << "Potrebno je unijeti jednu od cifara u [] zagradama za odabir odgovarajuce opcije ." << std::endl; break;
		}
	}
	else
	{
		switch (currOption)
		{
		case 1:accountP->inportForCustomer(); break;
		case 2:accountP->inportForProduct(); break;
		case 3:accountP->inportForMonth(); break;
		case 0:break;
		case -1:accountP->exitSystem(); break;
		default: std::cout << "Greska u unosu indeksa operacije" << std::endl; break;
		}
	}
}

void Menu::printPattern(std::ostream& output)
{
	system("CLS");
	output << "Izaberite neku od opcija:" << std::endl;
	if (accountP->getType() == NAME_OF_ADMIN)
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
	accountP = nullptr;
}