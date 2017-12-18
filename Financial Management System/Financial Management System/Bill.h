#pragma once
#include "Product.h"
#include <Windows.h>
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#define log "Log.txt"
#define logError "logError.txt"

bool isProcessed(std::string);
std::vector<std::string> returnVectorOfNotProcessedBills(std::string directory);

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

