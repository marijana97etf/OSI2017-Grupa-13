#include "ErrorException.h"
#include "Account.h"


ErrorException::ErrorException(const std::string& file, const std::string& message) : file(file), message(message)
{
}

void ErrorException::processException()
{
	std::string temp = file.substr(file.length() - 4, 4);
	std::ofstream error(file.substr(0, file.length() - 4) + "_error" + temp, std::ios::app | std::ios::out);//ako se ne moze dodati onda napravi novi fajl
	error << message << std::endl;
}

ErrorException::~ErrorException()
{
}
