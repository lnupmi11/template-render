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
