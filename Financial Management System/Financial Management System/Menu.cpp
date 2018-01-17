#include "Menu.h"


Menu::Menu(const std::string &pattern, const std::string &typeOfAccount):pattern(pattern),typeOfAccount(typeOfAccount)
{}

void Menu::setOption(int option)
{
	currOption = option;
}

void Menu::executeOption()
{
}

void Menu::printPattern(const std::ostream& output)
{
	
}

Menu::~Menu()
{
}
