#pragma once
#include "../DTO/Context.h"

class Parser
{
public:

	// Info:
	// Checks if string matches to the regular expression.
	static bool regexCheck(const std::string& str, const std::string& regexStr);

	// Info:
	// Finds declared variables and replace them with context data.
	static std::string parseVariables(const std::string& code, ContextBase* data);
};

