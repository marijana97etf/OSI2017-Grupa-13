#include "Product.h"



Product::Product():sifra(nullptr),cijena_po_jedinici_mjere(0.0),kolicina(0.0),ukupno(0.0)
{
}

Product::Product(const std::string sifra, double kolicina, double cijena_po_jedinici_mjere, double ukupno):sifra(sifra),kolicina(kolicina),cijena_po_jedinici_mjere(cijena_po_jedinici_mjere),ukupno(ukupno)
{
}


Product::~Product()
{
}
