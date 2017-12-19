#pragma once
#include "Product.h"

class Bill
{
	struct Node
	{
		Product product;
		Node *next;

		Node(const Product&);
		Node();
	};
	struct Date
	{
		int day, month, year;
		Date(const int, const int, const int);
		Date() = default;
	};
	Node* head,*tail;
	std::string nameOfBill;
	double totalSumOfProducts,pdv,totalSumOfBill;
	Date date;
public:
	Bill(const std::string &);//daje se ime .txt ili .csv koji se treba obraditi
	void procces();//jedna od vecih funkcija koja treba da iz fajla sve podatke izdvoji u listu
	void Validate();//izvrsava validaciju podataka
	bool checkTotalOfEveryProduct();
	bool checkTotalofAllproducts();
	bool checkTotalPlusPDV();


	~Bill();
};

