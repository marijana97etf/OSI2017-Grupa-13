#include "Interface.h"

COLORREF colors[] = { WHITE,BLACK,BLUE,RED,GREEN,YELLOW,ORANGE,PURPLE,BROWN,SILVER,ROSE};
HANDLE consoleOut = GetStdHandle(STD_OUTPUT_HANDLE);

void changeBackgroundColor(short index)
{
	std::ifstream input(CONFIG);
	if (input.is_open())
	{
		short value[3] = { 2, 10, 16 };
		for (int i = 0; i < 3; i++)
			input >> value[i];
		if (value[1] == index)
		{
			do
			{
				std::string choose;
				std::cout << "Unesite broj boje koja je razlicita od boje teksta: ";
				getline(std::cin, choose);
				if ((choose.length() == 2 && isdigit(choose[0]) && isdigit(choose[1])) || (choose.length() == 1 && isdigit(choose[0])))
					index = (short)std::stoi(choose);
				else
					index = value[1];
			} while (value[1] == index);
		}
		value[0] = index;
		input.close();
		std::ofstream output(CONFIG, std::ios::in);
		for (int i = 0; i < 3; i++)
			if (i != 2)
				output << value[i] << " ";
			else
				output << value[i];
		output << '\0';
		output.close();
	}
	CONSOLE_SCREEN_BUFFER_INFOEX sbInfoEx;
	sbInfoEx.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);
	GetConsoleScreenBufferInfoEx(consoleOut, &sbInfoEx);
	sbInfoEx.ColorTable[0] = colors[index - 1];
	SetConsoleScreenBufferInfoEx(consoleOut, &sbInfoEx);
	CONSOLE_SCREEN_BUFFER_INFO screen;
	GetConsoleScreenBufferInfo(consoleOut, &screen);
	screen.srWindow.Bottom = 29;
	SetConsoleWindowInfo(consoleOut, true, &screen.srWindow);
	system("COLOR 01");
}

void changeTextColor(short index)
{
	std::ifstream input(CONFIG);
	if (input.is_open())
	{
		short value[3] = { 2, 10, 16 };
		for (int i = 0; i < 3; i++)
			input >> value[i];
		if (value[0] == index)
		{
			do
			{
				std::string choose;
				std::cout << "Unesite broj boje koja je razlicita od boje pozadine: ";
				getline(std::cin, choose);
				if ((choose.length() == 2 && isdigit(choose[0]) && isdigit(choose[1])) || (choose.length() == 1 && isdigit(choose[0])))
					index = (short)std::stoi(choose);
				else
					index = value[0];
			} while (value[0] == index);
		}
		value[1] = index;
		input.close();
		std::ofstream output(CONFIG, std::ios::in);
		for (int i = 0; i < 3; i++)
			if (i != 2)
				output << value[i] << " ";
			else
				output << value[i];
		output << '\0';
		output.close();
	}
	CONSOLE_SCREEN_BUFFER_INFOEX sbInfoEx;
	sbInfoEx.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);
	GetConsoleScreenBufferInfoEx(consoleOut, &sbInfoEx);
	sbInfoEx.ColorTable[1] = colors[index - 1];
	SetConsoleScreenBufferInfoEx(consoleOut, &sbInfoEx);
	CONSOLE_SCREEN_BUFFER_INFO screen;
	GetConsoleScreenBufferInfo(consoleOut, &screen);
	screen.srWindow.Bottom = 29;
	SetConsoleWindowInfo(consoleOut, true, &screen.srWindow);
	system("COLOR 01");
}

void changeFontSize(short size)
{
	std::ifstream input(CONFIG);
	if (input.is_open())
	{
		short value[3] = { 2, 10, 16 };
		for (int i = 0; i < 3; i++)
			input >> value[i];
		value[2] = size;
		input.close();
		std::ofstream output(CONFIG, std::ios::in);
		for (int i = 0; i < 3; i++)
			if (i != 2)
				output << value[i] << " ";
			else
				output << value[i];
		output << '\0';
		output.close();
	}
	CONSOLE_FONT_INFOEX font = { sizeof(CONSOLE_FONT_INFOEX) };
	GetCurrentConsoleFontEx(consoleOut, false, &font);
	font.dwFontSize = { 6, size };
	SetCurrentConsoleFontEx(consoleOut, false, &font);
}

void systemConfiguration()
{
	SetConsoleTitle("Financial Management System");
	CreateDirectory(FILE_OF_BILLS, NULL);
	short index1, index2, index3;
	std::ifstream input(CONFIG);
	if (input.is_open())
	{
		input >> index1;
		input >> index2;
		input >> index3;
		if (index1 == index2 || (index1 < 1 || index1 > 11) || (index2 < 1 || index2 > 11) || (index3 < 5 || index3 > 72))
		{
			index1 = 2;
			index2 = 10;
			index3 = 16;
			std::ofstream output(CONFIG, std::ios::in);
			output << index1 << " " << index2 << " " << index3 << '\0';
			output.close();
		}
		changeBackgroundColor(index1);
		changeTextColor(index2);
		changeFontSize(index3);
		system("COLOR 01");
		input.close();
	}
	else
	{
		std::ofstream output(CONFIG);
		output << short(2) << " ";
		output << short(10) << " ";
		output << short(16);
		changeBackgroundColor(2);
		changeTextColor(10);
		changeFontSize(16);
		output.close();
	}
	input.close();
	std::ofstream output(ACCOUNT_FILE_NAME, std::ios::in);
	if (!output.is_open())
	{
		output.open(ACCOUNT_FILE_NAME);
		output << "  Username             PIN      Type    " << std::endl;
		output << "  --------------------------------------" << std::endl;
		output << "  Admin               |1234    |admin";
	}
	output.close();
}