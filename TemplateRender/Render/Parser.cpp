#include "Parser.h"
#include "../Utils/Constants.h"
#include <regex>
#include <string>
#include <algorithm>

bool Parser::regexCheck(const std::string& str, const std::string& regexStr)
{
	return regex_search(str.begin(), str.end(), std::regex(regexStr));
}

std::string Parser::parseVariables(const std::string& code, ContextBase* data)
{
	std::string result("");
	if (code.find("{{") == std::string::npos)
	{
		result = code;
	}
	else
	{
		std::regex expression(CONSTANT::VAR_REGEX);
		std::sregex_iterator begin(code.begin(), code.end(), expression), end;
		size_t pos = 0;
		for (auto it = begin; it != end; it++)
		{
			for (size_t i = pos; i < (size_t)it->position(); i++)
			{
				result += code[i];
			}
			pos = it->position() + it->str().size();
			result += data->getByKey(std::regex_replace(it->str(), std::regex("\\s+|\\{|\\}"), ""));
		}
		for (size_t i = pos; i < code.size(); i++)
		{
			result += code[i];
		}
	}
	return result;
}
