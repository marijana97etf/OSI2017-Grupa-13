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
	inline double const getQuantity() { return quantity; } const
	inline double const getPricePerUnit() { return pricePerUnit; } const
	inline double const getTotal() { return total; } const
};

