#pragma once
#include<string>

class Account
{
protected:
	std::string username, pin, type;
public:
	Account();
	Account(const std::string&, const std::string&, const std::string&);
};

