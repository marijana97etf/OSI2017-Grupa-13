#pragma once
#include "Product.h"
#include <Windows.h>
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#define log "Log.txt"
#define logError "logError.txt"

bool isProcessedBill(const std::string);
std::vector<std::string> returnVectorOfNotProcessedBills(const std::string directory);
bool checkFormat1(const std::string);

class Bill
{
	struct Node
	{
		Product product;
		Node *next;

		Node(const Product&);
	};
	struct Date
	{
		int day, month, year;
		Date(const int, const int, const int);
	};
	Node* head,*tail;
	std::string nameOfBill;
	Date date;
public:
	Bill();
	Bill(const std::string &);//daje se ime .txt ili .csv koji se treba obraditi
	void procces();//jedna od vecih funkcija koja treba da iz fajla sve podatke izdvoji u listu
	void Validate();//izvrsava validaciju podataka
	bool checkTotalOfEveryProduct();
	bool checkTotalofAllproducts();
	bool checkTotalPlusPDV();
	~Bill();
};

