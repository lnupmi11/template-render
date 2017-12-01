#include "Parser.h"
#include "../Utils/Constants.h"
#include <regex>
#include <string>
#include <algorithm>

bool Parser::regexCheck(const std::string& str, const std::string& regexStr)
{
	return std::regex_search(str.begin(), str.end(), std::regex(regexStr));
}

std::string Parser::parseVariables(const std::string& code, ContextBase* data)
{
	std::string result("");
	std::regex expression(CONSTANT::VAR_REGEX);
	if (!std::regex_search(code, std::smatch(), expression))
	{
		result = code;
	}
	else
	{
		std::sregex_iterator begin(code.begin(), code.end(), expression), end;
		size_t pos = 0;
		for (auto it = begin; it != end; it++)
		{
			for (size_t i = pos; i < (size_t)it->position(); i++)
			{
				result += code[i];
			}
			pos = it->position() + it->str().size();
			if (data)
			{
				result += data->getByKey(std::regex_replace(it->str(), std::regex("\\W+"), ""));
			}
			else
			{
				result += "";
			}
		}
		for (size_t i = pos; i < code.size(); i++)
		{
			result += code[i];
		}
	}
	return result;
}
