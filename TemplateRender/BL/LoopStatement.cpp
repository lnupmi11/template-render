#include "LoopStatement.h"
#include "Regex.h"
#include "../Utils/RenderError.h"
#include "Parser.h"
#include <regex>

#include <iostream>

std::string LoopStatement::parseForLoop(const std::string& code, forLoopParams& parameters)
{
	std::smatch data;
	std::regex_search(code, data, std::regex(REGEX::FOR_REGEX));
	std::string loopCondition = data.str();
	if (!std::regex_search(loopCondition, data, std::regex("\\w+(\\+\\+|\\-\\-?)")))
	{
		throw RenderError("Parser::parseInline(): invalid template syntax.", __FILE__, __LINE__, loopCondition);
	}
	parameters.iteratorName = std::regex_replace(data.str(), std::regex("\\W+"), "");
	int startCount = stoi(loopCondition.substr(loopCondition.find('=') + 1, loopCondition.find(';', loopCondition.find('='))));
	int endCount;
	if (loopCondition.find('<') != std::string::npos)
	{
		parameters.fewer = true;
		endCount = stoi(loopCondition.substr(loopCondition.find('<') + 1, loopCondition.find(';', loopCondition.find('<'))));
		if (loopCondition.find("++") != std::string::npos)
		{
			parameters.numberOfIteration = endCount - startCount;
			parameters.increment = true;
		}
		else
		{
			throw RenderError("LoopStatement::parse(): incorrect loop condition.", __FILE__, __LINE__, loopCondition);
		}
	}
	else if (loopCondition.find('>') != std::string::npos)
	{
		parameters.fewer = false;
		endCount = stoi(loopCondition.substr(loopCondition.find('>') + 1, loopCondition.find(';', loopCondition.find('>'))));
		if (loopCondition.find("--") != std::string::npos)
		{
			parameters.increment = false;
			parameters.numberOfIteration = startCount - endCount;
		}
		else
		{
			throw  RenderError("LoopStatement::parse(): incorrect loop condition.", __FILE__, __LINE__, loopCondition);
		}
	}
	else
	{
		throw  RenderError("LoopStatement::parse(): incorrect loop condition.", __FILE__, __LINE__, loopCondition);
	}
	size_t beginPos = 0, endPos = 0;
	try
	{
		beginPos = Parser::findSubstringPosition(code, "%\\s*\\}");
		endPos = Parser::findSubstringPosition(std::string(code.rbegin(), code.rend()), "%\\s*\\{", true);
	}
	catch (const std::exception&)
	{
		throw RenderError("LoopStatement::parse(): invalid template syntax.", __FILE__, __LINE__);
	}
	std::string result;
	try
	{
		result = std::string(code.begin() + beginPos, code.begin() + endPos);
	}
	catch (...)
	{
		throw RenderError("LoopStatement::parse(): invalid template syntax, end tag was missed of incorrect.", __FILE__, __LINE__);
	}
	return result;
}

std::string LoopStatement::executeForLoop(const std::string& loopBody, const forLoopParams& parameters)
{
	std::string result("");
	if (parameters.increment)
	{
		if (parameters.fewer)
		{
			for (int i = 0; i < parameters.numberOfIteration; i++)
			{
				result += std::regex_replace(loopBody, std::regex("\\{\\{\\s*" + parameters.iteratorName + "\\s*\\}\\}"), std::to_string(i));
			}
		}
		else
		{
			throw RenderError("LoopStatement::execute(): invalid loop condition.", __FILE__, __LINE__);
		}
	}
	if (!parameters.increment)
	{
		if (!parameters.fewer)
		{
			for (int i = parameters.numberOfIteration; i > 0; i--)
			{
				result += std::regex_replace(loopBody, std::regex("\\{\\{\\s*" + parameters.iteratorName + "\\s*\\}\\}"), std::to_string(i));
			}
		}
		else
		{
			throw RenderError("LoopStatement::execute(): invalid loop condition.", __FILE__, __LINE__);
		}
	}
	return result;
}

std::string LoopStatement::parseForeachLoop(const std::string& code, foreachLoopParams& parameters)
{
	std::string result("");
	std::smatch data;
	std::regex_search(code, data, std::regex(REGEX::FOREACH_REGEX));
	std::string loopStatement(data.str());
	size_t beginPos = loopStatement.find("auto");
	if (beginPos != std::string::npos)
	{
		beginPos = loopStatement.find(' ', beginPos);
		size_t endPos = loopStatement.find(':', beginPos);
		if (endPos != std::string::npos)
		{
			std::string var(loopStatement.begin() + beginPos, loopStatement.begin() + endPos);
			parameters.varName = std::regex_replace(var, std::regex("\\s+"), "");
			beginPos = loopStatement.find(')', endPos);
			var = std::string(loopStatement.begin() + endPos + 1, loopStatement.begin() + beginPos);
			parameters.containerName = std::regex_replace(var, std::regex("\\s+"), "");
			result = std::string(code.begin() + code.find('}', beginPos) + 1, code.begin() + code.rfind('{'));
		}
		else
		{
			throw RenderError("LoopStatement::parseForeachLoop(): invalid loop statement.", __FILE__, __LINE__, loopStatement);
		}
	}
	else
	{
		std::string errMessage("type of variable is missing or incorrect.");
		throw RenderError("LoopStatement::parseForeachLoop(): invalid loop statement.", __FILE__, __LINE__, loopStatement, errMessage);
	}
	return result;
}

std::string LoopStatement::executeForeachLoop(const std::string& loopBody, const foreachLoopParams& parameters, Context* context)
{
	std::string result("");
	if (context)
	{
		std::string collectionName = context->getByKey(parameters.containerName);
		if (collectionName.size() > 0)
		{
			std::vector<std::string> collection = Parser::parseCollection(collectionName);
			for (const auto& var : collection)
			{
				std::string temp(std::regex_replace(loopBody, std::regex("\\{\\{\\s*" + parameters.varName + "\\s*\\}\\}"), var));
				result += temp;
			}
		}
		else
		{
			throw RenderError("LoopStatement::executeForeachLoop(): collection '" + parameters.containerName + "' does not exist.", __FILE__, __LINE__);
		}
	}
	return result;
}
