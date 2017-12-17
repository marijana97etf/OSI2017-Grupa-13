#include "Product.h"



Product::Product():code(nullptr), quantity(0.0), price_per_unit(0.0), total(0.0)
{
}

Product::Product(const std::string code, double quantity, double price_per_unit, double total):code(code),quantity(quantity),price_per_unit(price_per_unit),total(total)
{
}


Product::~Product()
{
}
