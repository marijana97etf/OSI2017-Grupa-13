#include "Bill.h"



Bill::Bill(): head(nullptr), tail(nullptr), nameOfBill(nullptr), date(Date(0,0,0))
{}

Bill::~Bill()
{
	if (head != nullptr)
	{
		Node *del = head;
		for (Node *temp = head->next; temp; temp = temp->next)
		{
			delete del;
			del = temp;
		}
		delete del;
		head = tail = nullptr;
	}
	else
		tail = nullptr;
}

Bill::Node::Node(const Product& product): product(product), next(nullptr)
{}

Bill::Date::Date(const int day, const int month, const int year): day(day), month(month), year(year)
{}
