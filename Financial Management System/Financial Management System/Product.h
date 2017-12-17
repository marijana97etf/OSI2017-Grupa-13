#pragma once
#include<string>
class Product
{
	std::string sifra;
	double kolicina, cijena_po_jedinici_mjere, ukupno;
public:
	Product();
	Product(const std::string, double, double, double);
	~Product();
};

