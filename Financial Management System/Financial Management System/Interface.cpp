#include "Interface.h"

COLORREF colors[] = { WHITE,BLACK,BLUE,RED,GREEN,YELLOW,ORANGE,PURPLE,BROWN,SILVER };
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
				std::cout << "Unesite broj boje koja je razlicita od boje teksta: ";
				std::cin >> index;
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
				std::cout << "Unesite broj boje koja je razlicita od boje pozadine: ";
				std::cin >> index;
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
	short index1, index2;
	std::ifstream input(CONFIG);
	if (input.is_open())
	{
		input >> index1;
		input >> index2;
		if (index1 == index2 || (index1 < 1 || index1 > 10) || (index2 < 1 || index2 > 10))
		{
			index1 = 2;
			index2 = 10;
		}
		changeBackgroundColor(index1);
		changeTextColor(index2);
		input >> index1;
		changeFontSize(index1);
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
}