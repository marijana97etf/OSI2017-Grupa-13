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
	std::ifstream inputf(nameOfBill);
	std::string tmp;
	inputf.ignore(7);
	getline(inputf, nameOfClient);//pretpostavlja se da se ne stavljaju razmaci poslije naziva

	inputf.ignore(7);
	processDate(inputf);

	for(int i=0;i<4;i++)
	  ignoreElementsUntil(inputf, END_OF_LINE);
	
	getline(inputf,tmp);
	while (tmp[0] != '-')//radi dok se ne dodlje do linije sa -----------------------------
	{
		Product product = processData(tmp);
		auto iterator = list.begin();
		for (; iterator != list.end(); iterator++)
			if (iterator->getCode == product.getCode )
			{
				product.setQuantity(product.getQuantity + iterator->getQuantity);
				product.setTotal(product.getTotal + iterator->getTotal);
				break;
			}
		if (iterator == list.end())
			list.push_back(product);
		getline(inputf, tmp);
	}
	ignoreElementsUntil(inputf, END_OF_LINE);
	std::string totalSumOfProducts, pdv, totalSumOfBill;//maskiraju podatke clanove klase Bill

	inputf.ignore(8);
	getline(inputf, totalSumOfProducts);

	inputf.ignore(5);
	getline(inputf, pdv);

	inputf.ignore(20);
	getline(inputf,totalSumOfBill);

	this->totalSumOfProducts = std::stod(totalSumOfProducts, nullptr);
	this->pdv = std::stod(pdv, nullptr);
	this->totalSumOfBill = std::stod(totalSumOfBill, nullptr);
	inputf.close();
}

void Bill::processDate(std::ifstream &inputf)
{
	std::string day, month, year;
	for (int i = 0; i < 2; i++)
		day += inputf.get();
	inputf.get();
	for (int i = 0; i < 2; i++)
		month += inputf.get();
	inputf.get();
	for (int i = 0; i < 4; i++)
		year += inputf.get();
	inputf.get();
	date = Date::Date(std::stoi(day, nullptr, 10), std::stoi(month, nullptr, 10), std::stoi(year, nullptr, 10));
}

Product Bill::processData(std::string &tmp)
{
	std::string name;
	double quantity, pricePerUnit, total;
	double *productInfoPointers[3] = { &quantity, &pricePerUnit, &total };

	tmp += '-';//da bi bila jednolika obrada svih vrijednosti 
	int pos = tmp.find("-", 0);
	while (tmp[--pos] == ' ');//vracaj se unazad
	name = tmp.substr(0, pos + 1);

	int posOfFirstLine, posOfNextLine = tmp.find("-", 0);
	for (int i = 0; i < 3; i++)
	{
		posOfFirstLine = posOfNextLine;
		posOfNextLine = tmp.find("-", posOfNextLine+1);//uvecano za jedan jer find trazi i na poziciji posOfNextLine a tu sigurno nalazi znak -
		while (tmp[++posOfFirstLine] == ' ');
		while (tmp[--posOfNextLine] == ' ');
		std::string value = tmp.substr(posOfFirstLine, posOfNextLine - posOfFirstLine + 1);//podstring u kome se nalazi samo broj
		*productInfoPointers[i] = std::stod(value, nullptr);//std::stod - from string to doubles
	}
	return Product::Product(name, quantity, pricePerUnit, total);

}

void Bill::ignoreElementsUntil(std::ifstream &inputf, char boundary)
{
	while (inputf.get() != boundary);
}


bool Bill::Validate()
{
	if (!(checkTotalOfEveryProduct() && checkTotalofAllproducts() && checkTotalPlusPDV() && checkPDV()))
		return false;
	return true;
}

bool Bill::checkTotalOfEveryProduct()
{
	for (auto& product : list)
		if (product.getTotal() != product.getPricePerUnit() * product.getQuantity())
			return false;
	
	return true;
}

bool Bill::checkTotalofAllproducts()
{
	double total=0.0;
	for (auto& product : list)
		total += product.getTotal();

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
{}

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

void exportForCustomer(const Bill& bill)
{
	std::ofstream izlaz;
	std::string directory = "Kupac\\";
	directory += bill.nameOfClient;
	CreateDirectory("Kupac", NULL);
	izlaz.open(directory, std::ios::in);
	if (!izlaz.is_open())
	{
		izlaz.open(directory);
		izlaz << std::setw(20) << std::left << "Datum:";
		izlaz << std::setw(20) << std::left << "Sifra:";
		izlaz << std::setw(20) << std::left << "Kolicina:";
		izlaz << std::setw(20) << std::left << "Cijena:";
		izlaz << std::setw(20) << std::left << "Ukupno:" << std::endl;
		std::string tmp;
		while (tmp.length() != 87)
			tmp += "-";
		izlaz << tmp << std::endl;
		for (auto product : bill.list)
		{

			izlaz << std::setw(20) << std::left << bill.date.day << "/" << bill.date.month << "/" << bill.date.year;
			izlaz << std::setw(20) << std::left << product.getCode();
			izlaz << std::setw(20) << std::left << product.getQuantity();
			izlaz << std::setw(20) << std::left << product.getPricePerUnit();
			izlaz << std::setw(20) << std::left << product.getTotal() << std::endl;
		}
		izlaz.close();
	}
	else
	{
		izlaz.close();
		izlaz.open(directory, std::ios::app);
		for (auto product : bill.list)
		{

			izlaz << std::setw(20) << std::left << bill.date.day << "/" << bill.date.month << "/" << bill.date.year;
			izlaz << std::setw(20) << std::left << product.getCode();
			izlaz << std::setw(20) << std::left << product.getQuantity();
			izlaz << std::setw(20) << std::left << product.getPricePerUnit();
			izlaz << std::setw(20) << std::left << product.getTotal() << std::endl;
		}
		izlaz.close();
	}
	getchar();
}
