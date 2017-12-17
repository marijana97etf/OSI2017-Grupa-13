#pragma once
#include<string>
class Product
{
	std::string code;
	double quantity, price_per_unit, total;
public:
	Product();
	Product(const std::string, double, double, double);
	~Product();
};

