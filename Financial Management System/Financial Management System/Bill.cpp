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

bool isProcessed(std::string file)
{
	std::ifstream inputFileLog(log);
	std::ifstream inputFileLogError(logError);
	if (inputFileLog.is_open())
	{
		std::string bill;
		while (!inputFileLog.eof())
		{
			inputFileLog >> bill;
			if (bill == file)
			{
				inputFileLog.close();
				return true;
			}
		}
		inputFileLog.close();
	}
	if (inputFileLogError.is_open())
	{
		std::string bill;
		while (!inputFileLogError.eof())
		{
			inputFileLogError >> bill;
			if (bill == file)
			{
				inputFileLogError.close();
				return true;
			}
		}
		inputFileLogError.close();
	}
	return false;
}

std::vector<std::string> returnVectorOfNotProcessedBills(std::string directory)
{
	std::vector<std::string> files;
	WIN32_FIND_DATA fileData;
	HANDLE hFind;

	if (!((hFind = FindFirstFile(directory.c_str(), &fileData)) == INVALID_HANDLE_VALUE)) {
		while (FindNextFile(hFind, &fileData)) 
		{
			std::string file = fileData.cFileName;
			if (file.length() > 4 && (file.substr(file.length() - 4, 4) == ".txt" || file.substr(file.length() - 4, 4) == ".csv"))
			{
				if (file != log && file != logError && isProcessed(file) == false)
					files.push_back(file);
			}
		}
	}
	FindClose(hFind);
	return files;
}
