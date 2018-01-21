#pragma once
#include "Account.h"
#include "Bill.h"
#include<exception>

class Analyst : public Account
{
public:
	Analyst();
	Analyst(const std::string&, const std::string&, const std::string&);
	virtual bool inportForCustomer();//vraca true ako je uspio inportovati, a false ako nije
	virtual bool inportForProduct();
	virtual bool inportForMonth();
	~Analyst();
};

