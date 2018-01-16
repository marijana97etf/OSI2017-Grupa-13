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
bool checkFormat2(const std::string);
bool checkFormat3(const std::string);
bool checkFormat4(const std::string);
bool checkFormat5(const std::string);

class Bill
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
	Bill();
	Bill(const std::string &,int);//daje se ime .txt ili .csv koji se treba obraditi
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
	void processFormat2();
	void processFormat3();
	void processFormat4();
	void processFormat5();
	void processDate(std::ifstream &);
	Product processDataForFormat124(std::string &);
	Product processDataForFormat3(std::string &);
	void processDataForFormat5(std::string &);
	void putNewProductInList(const Product&);
	void ignoreElementsUntil(std::ifstream &, char);
};

