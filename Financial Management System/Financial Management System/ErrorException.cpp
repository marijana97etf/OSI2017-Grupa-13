#include "ErrorException.h"
#include "Account.h"


ErrorException::ErrorException(const std::string& file, const std::string& message,bool toOpen ) : file(file), message(message),toOpen(toOpen)
{
}

void ErrorException::processException()
{
		std::ofstream error(file.substr(0, file.length() - 4) + "_error.txt", std::ios::app | std::ios::out);//ako se ne moze dodati onda napravi novi fajl
		error << message << std::endl;
		std::ofstream logErrorOut(LOGERROR, std::ios::app | std::ios::out );
		logErrorOut << file << std::endl;
}

ErrorException::~ErrorException()
{
}
