#pragma once
#include "Product.h"
#include "Account.h"
#include <Windows.h>
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include<list>
#include<iomanip>
#define LOG "Log.txt"
#define LOGERROR "LogError.txt"

const int isFormat[5] = { 1,2,3,4,5 } ;
const std::string month[12] = { "Januar","Februar","Mart","April","Maj","Jun","Jul","Avgust","Septembar","Oktobar","Novembar","Decembar" };

bool isProcessedBill(const std::string);
std::vector<std::string> returnVectorOfNotProcessedBills(const std::string directory);
bool checkFormat1(const std::string);

class Bill
{
	struct Date
	{
		int day, month, year;
	public:
		Date(const int, const int, const int);
	};
	std::list <Product> list;
	std::string nameOfBill,nameOfClient;
	double totalSumOfProducts, pdv, totalSumOfBill;
	int formatCode;
	Date date;
public:
	Bill();
	Bill(const std::string &);//daje se ime .txt ili .csv koji se treba obraditi
	bool Validate();//izvrsava validaciju podataka
	  bool checkTotalOfEveryProduct();
	  bool checkTotalofAllproducts();
	  bool checkTotalPlusPDV();
	  bool checkPDV();
	~Bill();
private:
	friend void exportForCustomer(const Bill&);
	friend void exportForProduct(const Bill&);
	friend void exportForMonth(const Bill&);
	void process();//jedna od vecih funkcija koja treba da iz fajla sve podatke izdvoji u listu
	void processFormat1();
	void processDate(std::ifstream &);
	Product processData(std::string &);
	void ignoreElementsUntil(std::ifstream &, char);
};

