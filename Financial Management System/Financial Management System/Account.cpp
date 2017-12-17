#include "Account.h"



Account::Account():username(nullptr),pin(nullptr),type(nullptr)
{}


Account::Account(const std::string &username, const std::string &pin, const std::string &type):username(username),pin(pin),type(type)
{}

