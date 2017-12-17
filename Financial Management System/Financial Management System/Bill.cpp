#include "Bill.h"



Bill::Bill(): head(nullptr), tail(nullptr), nameOfBill(nullptr), date(Date(0,0,0))
{}

Bill::~Bill()
{}

Bill::Node::Node(const Product& product): product(product), next(nullptr)
{}

Bill::Date::Date(const int day, const int month, const int year): day(day), month(month), year(year)
{}
