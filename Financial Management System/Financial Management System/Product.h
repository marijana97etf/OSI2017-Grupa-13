#pragma once
#include<string>
class Product
{
	std::string code;
	double quantity, pricePerUnit, total;
public:
	Product();
	Product(const std::string, double, double, double);
	~Product();
};

