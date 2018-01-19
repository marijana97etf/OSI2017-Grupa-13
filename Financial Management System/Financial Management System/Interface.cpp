#include "Interface.h"

COLORREF colors[] = { WHITE,BLACK,BLUE,RED,GREEN,YELLOW,ORANGE,PURPLE,BROWN,SILVER };
HANDLE consoleOut = GetStdHandle(STD_OUTPUT_HANDLE);

void changeBackgroundColor(short index)
{
	std::ifstream input("Config.ini");
	if (input.is_open())
	{
		short value[3];
		for (int i = 0; i < 3; i++)
			input >> value[i];
		value[0] = index;
		input.close();
		std::ofstream output("Config.ini", std::ios::in);
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
	std::ifstream input("Config.ini");
	if (input.is_open())
	{
		short value[3];
		for (int i = 0; i < 3; i++)
			input >> value[i];
		value[1] = index;
		input.close();
		std::ofstream output("Config.ini", std::ios::in);
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
	std::ifstream input("Config.ini");
	if (input.is_open())
	{
		short value[3];
		for (int i = 0; i < 3; i++)
			input >> value[i];
		value[2] = size;
		input.close();
		std::ofstream output("Config.ini", std::ios::in);
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
	short index;
	std::ifstream input(CONFIG);
	if (input.is_open())
	{
		input >> index;
		changeBackgroundColor(index);
		input >> index;
		changeTextColor(index);
		input >> index;
		changeFontSize(index);
		system("COLOR 01");
		input.close();
	}
	else
	{
		std::ofstream output(CONFIG);
		output << short(2) << " ";
		output << short(10) << " ";
		output << short(16);
		output.close();
	}
}