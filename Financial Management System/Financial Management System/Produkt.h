#pragma once
#include<string>
class Produkt
{
	std::string sifra;
	double kolicina, cijena_po_jedinici_mjere, ukupno;
public:
	Produkt();
	Produkt(const std::string, double, double, double);
	~Produkt();
};

