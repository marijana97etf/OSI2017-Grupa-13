#pragma once
#include "Account.h"
#include "Bill.h"
class Analyst : public Account
{
public:
	Analyst();
	Analyst(const std::string&, const std::string&, const std::string&);
	bool inportForCustomer(const std::string&, std::ostream&);//vraca true ako je uspio inportovati, a false ako nije
	bool inportForProduct(const std::string&, std::ostream&);
	bool inportForMonth(const std::string&, std::ostream&);
	~Analyst();
};

