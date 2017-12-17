#include "Product.h"



Product::Product():code(nullptr), quantity(0.0), pricePerUnit(0.0), total(0.0)
{
}

Product::Product(const std::string code, double quantity, double pricePerUnit, double total):code(code),quantity(quantity),pricePerUnit(pricePerUnit),total(total)
{
}


Product::~Product()
{
}
