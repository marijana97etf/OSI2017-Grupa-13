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
	inline double const getQuantity() { return quantity; }
	inline double const getPricePerUnit() { return pricePerUnit; }
	inline double const getTotal() { return total; }
	inline std::string const getCode() { return code;  }
	inline void setQuantity(double info) { quantity = info; }
	inline void setPricePerUnit(double info) { pricePerUnit = info; }
	inline void setTotal(double info) { total = info; }
	inline void setCode(std::string info) { code = info; }
};

