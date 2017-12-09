#include "LoopStatement.h"
#include "Constants.h"
#include "../Utils/RenderError.h"
#include "../Render/Parser.h"
#include <regex>

std::string LoopStatement::TEMPLATE = "";

std::string LoopStatement::parse(const std::string& code, forLoopParams& parameters)
{
	std::smatch data;
	std::regex_search(code, data, std::regex(CONSTANT::FOR_REGEX));
	std::string loopCondition = data.str();
	std::regex_search(code, data, std::regex("\\w+(\\+\\+|\\-\\-)"));
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
			std::string err(LoopStatement::getError(loopCondition));
			throw RenderError("LoopStatement::parse(): incorrect loop condition.", __FILE__, __LINE__, err);
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
			std::string err(LoopStatement::getError(loopCondition));
			throw  RenderError("LoopStatement::parse(): incorrect loop condition.", __FILE__, __LINE__, err);
		}
	}
	else
	{
		throw  RenderError("LoopStatement::parse(): incorrect loop condition.", __FILE__, __LINE__);
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
	return std::string(code.begin() + beginPos, code.begin() + endPos);
}

std::string LoopStatement::execute(const std::string& loopBody, const forLoopParams& parameters)
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

std::string LoopStatement::getError(const std::string loop)
{
	std::string result("");
	if (LoopStatement::TEMPLATE.size() > 0)
	{
		size_t errPos = LoopStatement::TEMPLATE.find(loop);
		if (errPos != std::string::npos)
		{
			size_t errLine = 0;
			std::string::iterator begin = LoopStatement::TEMPLATE.begin(), end = LoopStatement::TEMPLATE.begin() + errPos;
			for (std::string::iterator it = begin; it != end; it++)
			{
				if (*it == '\n')
				{
					errLine++;
				}
			}
			result = "loop '" + loop + "' is invalid, line " + std::to_string(errLine + 1);
		}
	}
	return result;
}
