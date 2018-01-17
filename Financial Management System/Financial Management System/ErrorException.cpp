#include "ErrorException.h"


ErrorException::ErrorException(const std::string& file, const std::string& message) : file(file), message(message)
{
}

void ErrorException::processException()
{
	std::ofstream error(file.substr(0, file.length() - 4) + "_error.txt");
	error << message << std::endl;
	std::ofstream logErrorOut(LOGERROR,std::ios::in);
	logErrorOut << file << std::endl;
}

ErrorException::~ErrorException()
{
}
