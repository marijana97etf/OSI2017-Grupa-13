#include "Bill.h"
#include "Account.h"


Bill::Bill(): nameOfBill(nullptr), date(Date(0,0,0))
{}

void Bill::process()
{
	if (formatCode == isFormat[1])
		processFormat1();
}

void Bill::processFormat1()
{
	std::ifstream inputfile(inputf);
	inputfile.ignore(7);
	inputfile.get()

}

bool Bill::Validate()
{
	if (!(checkTotalOfEveryProduct() && checkTotalofAllproducts() && checkTotalPlusPDV() && checkPDV()))
		return false;
	return true;
}

bool Bill::checkTotalOfEveryProduct()
{
	for (Node *p = head; p != nullptr; p = p->next)
		if (p->product.getTotal() != p->product.getPricePerUnit() * p->product.getQuantity()) 
			return false;
	return true;
}

bool Bill::checkTotalofAllproducts()
{
	double total=0.0;
	for (Node *p = head; p != nullptr; p = p->next)
		total += p->product.getTotal();
	if (total==totalSumOfProducts)
		return true;
	return false;
}

bool Bill::checkTotalPlusPDV()
{
	if (totalSumOfProducts + pdv != totalSumOfBill)
		return false;
	return true;
}

bool Bill::checkPDV()
{
	if(pdv==totalSumOfProducts*17/100)
		return true;
	return false;
}




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

Bill::Date::Date(const int day, const int month, const int year): day(day), month(month), year(year)
{}

bool isProcessedBill(const std::string file)
{
	std::ifstream inputFileLog(log);//konstante se pretezno pisu velikim slovima
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
		{
			inputFile.close();
			return false;
		}
		getline(inputFile, tmp);
		if (tmp.substr(0, 6) != "Datum:")
		{
			inputFile.close();
			return false;
		}
		getline(inputFile, tmp);
		inputFile >> tmp;
		if (tmp.substr(0, 5) != "Racun")
		{
			inputFile.close();
			return false;
		}
		getline(inputFile, tmp);
		getline(inputFile, tmp);
		inputFile >> tmp;
		if (tmp != "Proizvod")
		{
			inputFile.close();
			return false;
		}
		inputFile >> tmp;
		if (tmp != "-")
		{
			inputFile.close();
			return false;
		}
		inputFile >> tmp;
		if (tmp != "kolicina")
		{
			inputFile.close();
			return false;
		}
		inputFile >> tmp;
		if (tmp != "-")
		{
			inputFile.close();
			return false;
		}
		inputFile >> tmp;
		if (tmp != "cijena")
		{
			inputFile.close();
			return false;
		}
		inputFile >> tmp;
		if (tmp != "-")
		{
			inputFile.close();
			return false;
		}
		inputFile >> tmp;
		if (tmp != "ukupno")
		{
			inputFile.close();
			return false;
		}
		inputFile >> tmp;
		int size = tmp.length();
		std::string tmp1 = "";
		for (int i = 0; i < size; i++, tmp1 += '-');
		if (tmp == tmp1)
		{
			inputFile.close();
			return false;
		}
		inputFile.close();
		return true;
	}
	return false;
}