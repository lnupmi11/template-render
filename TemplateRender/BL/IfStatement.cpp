#include "IfStatement.h"
#include "../Utils/RenderError.h"
#include "../Render/Parser.h"
#include "Constants.h"
#include <regex>
#include <queue>

std::string IfStatement::parse(const std::string& code, ifParams& parameters)
{
	std::smatch data;
	std::regex_search(code, data, std::regex(CONSTANT::IF_REGEX));
	std::string condition = data.str();
	if (std::regex_search(condition, data, std::regex(CONSTANT::COMPARISON_SYMBOL_REGEX)))
	{
		parameters.type = IfStatement::type(std::regex_replace(data.str(), std::regex("\\s+"), ""));
		size_t offset = condition.find("(") + 1;
		parameters.firstVar = std::string(condition.begin() + offset, condition.begin() + condition.find(" ", offset));
		offset = condition.find(" ", condition.find(" ", condition.find("(") + 1)) + 1;
		parameters.secondVar = std::string(condition.begin() + offset, condition.begin() + condition.find(")"));
		parameters.secondVar = std::regex_replace(parameters.secondVar, std::regex("\\W+"), "");
	}
	else
	{
		parameters.firstVar = std::string(condition.begin() + condition.find("(") + 1, condition.begin() + condition.find(")"));
		parameters.firstVar = std::regex_replace(parameters.firstVar, std::regex("\\W+"), "");
		parameters.type = conditionType::none;
	}
	size_t elsePos = 0;
	try
	{
		elsePos = Parser::findSubstringPosition(std::string(code.rbegin(), code.rend()), "%\\s*\\{", true);
	}
	catch (const std::exception&)
	{
		throw RenderError("IfStatement::parse(): invalid template syntax.", __FILE__, __LINE__);
	}
	if (std::regex_search(code, data, std::regex(CONSTANT::ELSE_REGEX)))
	{
		std::queue<std::pair<size_t, size_t>> elsePositions;
		std::queue<size_t> ifPositions;
		blockParams params(0, 0, false, false, CONSTANT::BEGIN_IF_REGEX, CONSTANT::ELSE_REGEX);
		do
		{
			Parser::findTag(code, params);
			if (params.first)
			{
				ifPositions.push(params.foundPos);
			}
			else if (params.second)
			{
				elsePositions.push(std::pair<size_t, size_t>(params.foundPos, params.offset));
			}
			if (ifPositions.size() < elsePositions.size())
			{
				std::string err(code.begin() + elsePositions.back().first, code.begin() + elsePositions.back().second);
				throw RenderError("IfStatement::parse(): invalid template syntax.", __FILE__, __LINE__, err);
			}
			if (ifPositions.size() == elsePositions.size())
			{
				elsePos = elsePositions.back().first;
				size_t end = Parser::findSubstringPosition(std::string(code.rbegin(), code.rend()), "%\\s*\\{", true);
				parameters.elseString = std::string(code.begin() + elsePos + elsePositions.back().second, code.begin() + end);
			}
			else if (params.foundPos == std::string::npos)
			{
				break;
			}
		} while (ifPositions.size() != elsePositions.size());
	}
	size_t beginPos = 0;
	try
	{
		beginPos = Parser::findSubstringPosition(code, "%\\s*\\}");
	}
	catch (const std::exception&)
	{
		throw RenderError("IfStatement::parse(): invalid template syntax.", __FILE__, __LINE__);
	}
	return std::string(code.begin() + beginPos, code.begin() + elsePos);
}

std::string IfStatement::execute(const std::string& body, const ifParams& parameters, ContextBase* context)
{
	std::string result("");
	bool check = false;
	if (context)
	{
		try
		{
			check = IfStatement::condition<double>(stod(parameters.firstVar), stod(parameters.secondVar), parameters, context);
		}
		catch (...)
		{
			check = IfStatement::condition<std::string>(context->getByKey(parameters.firstVar), context->getByKey(parameters.secondVar), parameters, context);
		}
		if (check)
		{
			result += body;
		}
		else
		{
			result += parameters.elseString;
		}
	}
	return result;
}

conditionType IfStatement::type(const std::string& condition)
{
	conditionType result;
	if (condition == "<")
	{
		result = conditionType::less;
	}
	else if (condition == ">")
	{
		result = conditionType::greater;
	}
	else if (condition == "<=")
	{
		result = conditionType::lessAndEquals;
	}
	else if (condition == ">=")
	{
		result = conditionType::greaterAndEquals;
	}
	else if (condition == "==")
	{
		result = conditionType::equals;
	}
	else if (condition == "!=")
	{
		result = conditionType::notEquals;
	}
	else
	{
		std::string err("'" + condition + "' is invalid symbol.");
		throw RenderError("IfStatement::type(): invalid template syntax.", __FILE__, __LINE__, err);
	}
	return result;
}
