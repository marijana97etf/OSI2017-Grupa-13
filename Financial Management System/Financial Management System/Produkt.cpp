#include "Produkt.h"



Produkt::Produkt():sifra(nullptr),cijena_po_jedinici_mjere(0.0),kolicina(0.0),ukupno(0.0)
{
}

Produkt::Produkt(const std::string sifra, double kolicina, double cijena_po_jedinici_mjere, double ukupno):sifra(sifra),kolicina(kolicina),cijena_po_jedinici_mjere(cijena_po_jedinici_mjere),ukupno(ukupno)
{
}


Produkt::~Produkt()
{
}
