#pragma once
#include "Product.h"
#include "Account.h"
#include <Windows.h>
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include<list>
#define log "Log.txt"
#define logError "logError.txt"
const int isFormat[5] = { 1,2,3,4,5 } ;

bool isProcessedBill(const std::string);
std::vector<std::string> returnVectorOfNotProcessedBills(const std::string directory);
bool checkFormat1(const std::string);

class Bill
{
	struct Date
	{
		int day, month, year;
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
	void process();//jedna od vecih funkcija koja treba da iz fajla sve podatke izdvoji u listu
	void processFormat1();
};

