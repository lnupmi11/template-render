#pragma once
#include <string>
#include <list>
#include <regex>
#include "Parameters.h"
#include "../DTO/Context.h"


class HelperFunctions
{
public:

	// Info:
	// Analyzes loop's parameters and returns loop body.
	static std::string retrieveBodyForLoop(const std::string& code, forLoopParams& parameters);

	// Info:
	// Analyzes 'if' statemet's parameters and returns its body.
	static std::string retrieveBodyIf(const std::string& code, ifParams& parameters);

	// Info:
	// Analyzes condition and returns its type.
	static int getTypeOfIFCondition(const std::string& condition);

	// Info:
	// Analyzes block of code and returns its type.
	static size_t codeType(const std::string& code);

	// Info:
	// Analyzes code and returns block object.
	static block findBlock(size_t& pos, const std::string& code);

	// Info:
	// Calls findBlock(size_t, string) method while position is not equal to the end of code string.
	static void findAllBlocks(std::list<block>& blocks, const std::string& code);

	// Info:
	// According to code type executes body of specific statement.
	static std::string runCode(const std::string& code, ContextBase* context);

	// Info:
	// Parses HTML code, using recursion.
	static std::string parse(const std::string& code, ContextBase* context);

	// Info:
	// Reads template from file.
	static std::string readTemplate(const std::string& templateName);

	// Info:
	// Creates rendered HTML document.
	static void createHTML(const std::string& html, const std::string& htmlPath);

	// Info:
	// Executes 'for' loop statement.
	static std::string forLoop(const std::string& loopBody, const forLoopParams& parameters);

	// Info:
	// Executes 'if' statement.
	static std::string ifStatement(const std::string& body, const ifParams& parameters, ContextBase* context);

	// Info:
	// Looks for beginning or ending tag and writes it to block parameters.
	static void findTag(const std::string& str, blockParams& params);

	template<typename dataType>
	static bool condition(const dataType& left, const dataType& right, const ifParams& parameters, ContextBase* context)
	{
		bool result = false;
		switch (parameters.type)
		{
		case 1:
			result = (left < right);
			break;
		case 2:
			result = (left > right);
			break;
		case 3:
			result = (left <= right);
			break;
		case 4:
			result = (left >= right);
			break;
		case 5:
			result = (left == right);
			break;
		case 6:
			result = (left != right);
			break;
		case 7:
			if (std::regex_replace(context->getByKey(parameters.firstVar), std::regex("\\s+"), "") != "")
			{
				result = true;
			}
			break;
		default:
			throw RenderError("HelperFunctions::condition(): incorrect condition.", __FILE__, __LINE__);
		}
		return result;
	}

};
