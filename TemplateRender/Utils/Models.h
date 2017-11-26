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
	bool begin;
	bool end;

	blockParams(size_t foundPos, size_t offset, bool begin, bool end);
};

struct forLoopParams
{
	int numberOfIteration;
	bool increment;
	bool fewer;

	forLoopParams();
};
