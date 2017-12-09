#pragma once
#include "../DTO/Context.h"
#include "../BL/Parameters.h"
#include <list>

class Parser
{
public:

	// Info:
	// Checks if string matches to the regular expression.
	static bool matchString(const std::string& str, const std::string& regexStr);

	// Info:
	// Finds declared variables and replace them with context data.
	static std::string parseInline(const std::string& code, ContextBase* context);

	// Info:
	// Finds substring position using regular expression.
	static size_t findSubstringPosition(const std::string& str, const std::string& regex, bool reverse = false);

	// Info:
	// Analyzes code and returns block object.
	static block findBlock(size_t& pos, const std::string& code);

	// Info:
	// Calls findBlock(size_t, string) method while position is not equal to the end of code string.
	static void findAllBlocks(std::vector<block>& blocks, const std::string& code);

	// Info:
	// Looks for beginning or ending tag and writes it to block parameters.
	static void findTag(const std::string& str, blockParams& params);

	// Info:
	// Analyzes block of code and returns its type.
	static codeType getCodeType(const std::string& code);

	// Info:
	// Parses HTML code, using recursion.
	static std::string parseTemplate(const std::string& code, ContextBase* context);

	// Info:
	// According to code type executes body of specific statement.
	static std::string executeCode(const std::string& code, ContextBase* context);
};

