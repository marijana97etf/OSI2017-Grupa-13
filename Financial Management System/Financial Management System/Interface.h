#pragma once
#include <windows.h>
#include <fstream>
#include <string>
#include <iostream>
#define CONFIG "Config.ini"

COLORREF WHITE = RGB(255, 255, 255);
COLORREF BLACK = RGB(0, 0, 0);
COLORREF BLUE = RGB(0, 0, 255);
COLORREF RED = RGB(255, 0, 0);
COLORREF GREEN = RGB(0, 255, 0);
COLORREF YELLOW = RGB(255, 255, 0);
COLORREF ORANGE = RGB(255, 165, 0);
COLORREF PURPLE = RGB(128, 0, 128);
COLORREF BROWN = RGB(102, 51, 0);
COLORREF SILVER = RGB(192, 192, 192);
COLORREF colors[] = { WHITE,BLACK,BLUE,RED,GREEN,YELLOW,ORANGE,PURPLE,BROWN,SILVER };
HANDLE consoleOut = GetStdHandle(STD_OUTPUT_HANDLE);

void changeBackgroundColor(short);
void changeTextColor(short);
void changeFontSize(short);

void systemConfiguration();