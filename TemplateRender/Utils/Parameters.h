#pragma once
#include <string>

struct block
{
	std::string	code;
	std::string before;
	std::string after;

	block();
	block(const std::string& code, const std::string& before, const std::string& after);
};

struct blockParams
{
	size_t foundPos;
	size_t offset;
	bool first;
	bool second;
	std::string regexFirst;
	std::string regexSecond;

	blockParams(size_t foundPos, size_t offset, bool first, bool second, std::string regexFirst, std::string regexSecond);
};

struct forLoopParams
{
	int numberOfIteration;
	bool increment;
	bool fewer;
	std::string iteratorName;

	forLoopParams();
};

struct ifParams
{
	int type;
	std::string firstVar;
	std::string secondVar;
	std::string elseString;

	ifParams();
};
