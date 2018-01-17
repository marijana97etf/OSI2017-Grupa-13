#pragma once
#include<iostream>
#include<string>
#include<exception>
#include<fstream>
#define LOG "Log.txt"
#define LOGERROR "LogError.txt"
class ErrorException : public std::exception
{
	std::string file;
	std::string message;
public:
	ErrorException(const std::string&, const std::string&);
	void processException();
	~ErrorException();
};

