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

bool isProcessedBill(const std::string file)
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

std::vector<std::string> returnVectorOfNotProcessedBills(const std::string directory)
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
				if (file != log && file != logError && isProcessedBill(file) == false)
					files.push_back(file);
			}
		}
	}
	FindClose(hFind);
	return files;
}

bool checkFormat1(const std::string file)
{
	std::ifstream inputFile(file);
	if (inputFile.is_open())
	{
		std::string tmp;
		getline(inputFile, tmp);
		if (tmp.substr(0, 6) != "Kupac:")
			return false;
		getline(inputFile, tmp);
		if (tmp.substr(0, 6) != "Datum:")
			return false;
		getline(inputFile, tmp);
		inputFile >> tmp;
		if (tmp.substr(0, 5) != "Racun")
			return false;
		getline(inputFile, tmp);
		getline(inputFile, tmp);
		inputFile >> tmp;
		if (tmp != "Proizvod")
			return false;
		inputFile >> tmp;
		if (tmp != "-")
			return false;
		inputFile >> tmp;
		if (tmp != "kolicina")
			return false;
		inputFile >> tmp;
		if (tmp != "-")
			return false;
		inputFile >> tmp;
		if (tmp != "cijena")
			return false;
		inputFile >> tmp;
		if (tmp != "-")
			return false;
		inputFile >> tmp;
		if (tmp != "ukupno")
			return false;
		inputFile >> tmp;
		int size = tmp.length();
		std::string tmp1 = "";
		for (int i = 0; i < size; i++, tmp1 += '-');
		if (tmp == tmp1)
			return false;
		return true;
	}
	return false;
}