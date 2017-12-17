#pragma once
#include "Product.h"
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
	~Bill();
};

