#pragma once
#include "Account.h"
#include "Bill.h"
class Analyst : public Account
{
public:
	Analyst();
	Analyst(const std::string&, const std::string&, const std::string&);
	virtual bool inportForCustomer(const std::string&, std::ostream&);//vraca true ako je uspio inportovati, a false ako nije
	virtual bool inportForProduct(const std::string&, std::ostream&);
	virtual bool inportForMonth(const std::string&, std::ostream&);
	~Analyst();
};

