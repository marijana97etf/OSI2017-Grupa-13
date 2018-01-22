#pragma once
#include "Product.h"
#include "Account.h"
#include "ErrorException.h"
#include <Windows.h>
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include<list>
#include<iomanip>
#include<cctype>
#include<cmath>

const int isFormat[5] = { 1,2,3,4,5 } ;
const std::string month[12] = { "Januar","Februar","Mart","April","Maj","Jun","Jul","Avgust","Septembar","Oktobar","Novembar","Decembar" };
const double EPS = 0.5;

bool isProcessedBill(const std::string);      //	funkcija koja provjerava da li je račun procesiran
std::vector<std::string> returnVectorOfNotProcessedBills(const std::string directory); //   funkcija koja vraća niz računa koji nisu procesirani
bool checkFormat1(const std::string);         //
bool checkFormat2(const std::string);		  //
bool checkFormat3(const std::string);		  //    funkcije za procesiranje svih 5 formata računa
bool checkFormat4(const std::string);		  //
bool checkFormat5(const std::string);         //

class Bill			// Klasa "Račun"
{
	struct Date
	{
		int day, month, year;
	public:
		Date() = default;
		Date(const int, const int, const int);
	};
	std::list <Product> list;         
	std::string nameOfBill,nameOfClient;
	double totalSumOfProducts, pdv, totalSumOfBill;
	int formatCode;
	Date date;
public:
	Bill();											 // podrazumjevani konstruktor
	Bill(const std::string &,int);					 // konstruktor
	void process();									 // procesiranje računa
	bool Validate();								 // validacija računa
	void exportForCustomer();						 // izvoz podataka za kupca
	void exportForProduct();					   	 // izvoz podataka za proizvod
	void exportForMonth();		              	     // izvoz podataka za mjesec
	~Bill();
private:
	bool checkTotalOfEveryProduct();	  		     // metoda za provjeru ukupne cijene svakog proizvoda
	bool checkTotalofAllproducts();				     // metoda za provjeru ukupne cijene svih proizvoda
	bool checkTotalPlusPDV();					     // metoda za provjeru ispravnosti konačne cijene (Ukupno+PDV)
	void processFormat1();							 // metoda za provjeru formata prvog tipa računa
	void processFormat2();							 // metoda za provjeru drugog tipa računa
	void processFormat3();							 // metoda za provjeru treceg tipa računa
	void processFormat4();							 // metoda za provjeru četvrtog tipa računa
	void processFormat5();							 // metoda za provjeru petog tipa računa
	void processDate(std::ifstream &);				 // metoda za procesiranje datuma
	Product processDataForFormat124(std::string &);  // metoda za procesiranje podataka za formate računa 1, 2 i 4
	Product processDataForFormat3(std::string &);    // metoda za procesiranje podataka za račun sa trećim formatom računa
	void putNewProductInList(const Product&);        // metoda za dodavanje proizvoda u listu
	void ignoreElementsUntil(std::ifstream &, char); // metoda za ignorisanje karaktera 
	int numberOfDigits(double);						 // metoda koja vraća broj cifara broja
};

