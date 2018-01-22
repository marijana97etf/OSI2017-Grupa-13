#pragma once
#include "Account.h"
#include "Interface.h"
#include <cstdio>
#include<iostream>
#include<fstream>
#include<string>
#include <locale>
#include <cstdio>
#include <vector>
#include <windows.h>

const std::string FIRST_LINE_OF_HEADER("  Username             PIN      Type    ");
const std::string SECOND_LINE_OF_HEADER("  --------------------------------------");
const std::string TMP_FILE("tmpfile.txt");


class Admin : public Account
{
	std::string currency;
public:
	Admin();
	Admin(const std::string&, const std::string&, const std::string&);
	virtual void addAccount();//funkcija koja omogucava da se doda korisnicki nalog sa adekvatnim informacijama
	virtual bool deleteAccount();//funkcija koja omogucava brisanje naloga cije ime i prezime postoje
	virtual void printAccounts();// funcija za ispis svih naloga 
	virtual bool changeAccount();//funkcija za izmjenu vec postojecih naloga. Omogucava izmjenu imena, prezimena, pina i tipa naloga
	virtual void changeInterface();//funkcija za izmjenu korisnickog interfejsa. Omogucava izmjenu velicine fonta, boje pozadine i boje teksta
	virtual void getSystemCurrency();// funckija za ispis valute sistema
    static bool isNotLegit(const std::string, char);//funckija koja provjerava da li je uneseno ime, prezime ili pin u odgovarajucem formatu
private:
	void format(std::string&, char);// funckija za formatiranje imena prezimena i pina
	bool nameExists(std::string);// funkcija koja provjerava da li uneseni korisnicki nalog postoji
	bool isAccountFileEmpty();//provjerava da li je fajl sa korisinickim nalozima prazan
	bool isAccountFileWithoutAccounts();// provjerava da li je fajl sa korisnickim nalogom bez ijednog naloga
	const std::vector<std::string> pullFromText(std::string);// funkija koja pronalazi nalog u fajlu sa k.nalozima i vraca njegove podatke u vidu vektora stringova
	const std::vector<std::string> explode(const std::string& s, const char& c);//funkicja koja razbija string u vektor stringova
	void insert(const std::vector<std::string>, std::string&, std::string&, char);//funkcija koja umece zeljenu izmjenu korisnickog naloga u fajl sa korisnickim nalozima
	bool warningFunction(int);// funkcija za ispis upozorenja tokom unosenja podataka
};

