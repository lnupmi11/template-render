#include <fstream>
#include <algorithm>
#include <stack>
#include "Functions.h"
#include "../Render/Parser.h"
#include "Constants.h"

std::string HelperFunctions::retrieveBodyForLoop(const std::string& code, forLoopParams& parameters)
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
			throw RenderError("HelperFunctions::retrieveBodyForLoop(): incorrect loop condition.", __FILE__, __LINE__);
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
			throw  RenderError("HelperFunctions::retrieveBodyForLoop(): incorrect loop condition.", __FILE__, __LINE__);
		}
	}
	else
	{
		throw  RenderError("HelperFunctions::retrieveBodyForLoop(): incorrect loop condition.", __FILE__, __LINE__);
	}
	size_t beginPos = 0, endPos = 0;
	try
	{
		beginPos = HelperFunctions::findSubstringPosition(code, "%\\s*\\}");
		endPos = HelperFunctions::findSubstringPosition(std::string(code.rbegin(), code.rend()), "%\\s*\\{", true);
	}
	catch (const std::exception&)
	{
		throw RenderError("HelperFunctions::retrieveBodyForLoop(): invalid template syntax.", __FILE__, __LINE__);
	}
	return std::string(code.begin() + beginPos, code.begin() + endPos);
}

size_t HelperFunctions::codeType(const std::string& code)
{
	int result;
	size_t endPos = 0;
	try
	{
		endPos = HelperFunctions::findSubstringPosition(code, "%\\s*\\}");
	}
	catch (const std::exception&)
	{
		throw RenderError("HelperFunctions::codeType(): invalid template syntax.", __FILE__, __LINE__);
	}
	std::string statement(code.begin(), code.begin() + endPos);
	bool checkFor = Parser::regexCheck(statement, CONSTANT::FOR_REGEX);
	bool checkIf = Parser::regexCheck(statement, CONSTANT::IF_REGEX);
	bool checkComment = Parser::regexCheck(statement, CONSTANT::BEGIN_COMMENT_REGEX);
	if (checkFor)
	{
		result = 1;
	}
	else if (checkIf)
	{
		result = 2;
	}
	else if (checkComment)
	{
		result = 3;
	}
	else
	{
		throw RenderError("HelperFunctions::codeType(): invalid code type.", __FILE__, __LINE__);
	}
	return result;
}

std::string HelperFunctions::retrieveBodyIf(const std::string& code, ifParams& parameters)
{
	std::smatch data;
	std::regex_search(code, data, std::regex(CONSTANT::IF_REGEX));
	std::string condition = data.str();
	parameters.type = HelperFunctions::getTypeOfIFCondition(condition);
	if (parameters.type < CONSTANT::MAX_IF_TYPE)
	{
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
	}
	size_t elsePos = 0;
	try
	{
		elsePos = HelperFunctions::findSubstringPosition(std::string(code.rbegin(), code.rend()), "%\\s*\\{", true);
	}
	catch (const std::exception&)
	{
		throw RenderError("HelperFunctions::retrieveBodyIf(): invalid template syntax.", __FILE__, __LINE__);
	}
	if (std::regex_search(code, data, std::regex(CONSTANT::ELSE_REGEX)))
	{
		std::stack<std::pair<size_t, size_t>> elsePositions;
		std::stack<size_t> ifPositions;
		blockParams params(0, 0, false, false, CONSTANT::BEGIN_IF_REGEX, CONSTANT::ELSE_REGEX);
		do
		{
			HelperFunctions::findTag(code, params);
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
				throw RenderError("HelperFunctions::retrieveBodyIf(): invalid template syntax.", __FILE__, __LINE__);
			}
			if (ifPositions.size() == elsePositions.size())
			{
				elsePos = elsePositions.top().first;
				parameters.elseString = std::string(code.begin() + elsePos + elsePositions.top().second, code.begin() + code.rfind("{%"));
				while (!ifPositions.empty())
				{
					ifPositions.pop();
				}
			}
			else if (params.foundPos == std::string::npos)
			{
				break;
			}
		} while (ifPositions.size() != 0);
	}
	size_t beginPos = 0;
	try
	{
		beginPos = HelperFunctions::findSubstringPosition(code, "%\\s*\\}");
	}
	catch (const std::exception&)
	{
		throw RenderError("HelperFunctions::retrieveBodyIf(): invalid template syntax.", __FILE__, __LINE__);
	}
	return std::string(code.begin() + beginPos, code.begin() + elsePos);
}

int HelperFunctions::getTypeOfIFCondition(const std::string& condition)
{
	int result;
	if (condition.find("<") != std::string::npos)
	{
		result = 1;
	}
	else if (condition.find(">") != std::string::npos)
	{
		result = 2;
	}
	else if (condition.find("<=") != std::string::npos)
	{
		result = 3;
	}
	else if (condition.find(">=") != std::string::npos)
	{
		result = 4;
	}
	else if (condition.find("==") != std::string::npos)
	{
		result = 5;
	}
	else if (condition.find("!=") != std::string::npos)
	{
		result = 6;
	}
	else
	{
		result = 7;
	}
	return result;
}

std::string HelperFunctions::runCode(const std::string& code, ContextBase* context)
{
	forLoopParams forParameters;
	ifParams ifParameters;
	std::string body(""), result("");
	switch (HelperFunctions::codeType(code))
	{
	case 1:
		body = HelperFunctions::retrieveBodyForLoop(code, forParameters);
		result = HelperFunctions::forLoop(body, forParameters);
		break;
	case 2:
		body = HelperFunctions::retrieveBodyIf(code, ifParameters);
		result = HelperFunctions::ifStatement(body, ifParameters, context);
		break;
	case 3:
		result = "";
		break;
	default:
		throw RenderError("HelperFunctions::runCode(): incorrect type of code.", __FILE__, __LINE__);
	}
	return result;
}

std::string HelperFunctions::parse(const std::string& code, ContextBase* context)
{
	std::string result("");
	std::list<block> blocks;
	HelperFunctions::findAllBlocks(blocks, code);
	for (std::list<block>::iterator block = blocks.begin(); block != blocks.end(); block++)
	{
		if ((*block).before.size() == 0 && (*block).code.size() == 0)
		{
			result += (*block).after;
			return result;
		}
		result += (*block).before;
		result += HelperFunctions::parse(HelperFunctions::runCode((*block).code, context), context);
		result += (*block).after;
	}
	return result;
}

std::string HelperFunctions::readTemplate(const std::string& templateName)
{
	std::ifstream read(templateName);
	std::string result("");
	if (read.is_open())
	{
		result.assign((std::istreambuf_iterator<char>(read)), std::istreambuf_iterator<char>());
		read.close();
	}
	else
	{
		throw RenderError("HelperFunctions::readTemplate(): template '" + templateName + "' does not exist.", __FILE__, __LINE__);
	}
	return result;
}

void HelperFunctions::createHTML(const std::string& html, const std::string& htmlPath)
{
	std::ofstream file(htmlPath);
	if (file.is_open())
	{
		file << html;
		file.close();
	}
	else
	{
		throw RenderError("HelperFunctions::createHTML(): can not open file '" + htmlPath + "' for writting.", __FILE__, __LINE__);
	}
}

std::string HelperFunctions::forLoop(const std::string& loopBody, const forLoopParams& parameters)
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
			throw RenderError("HelperFunctions::forLoop(): invalid loop condition.", __FILE__, __LINE__);
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
			throw RenderError("HelperFunctions::forLoop(): invalid loop condition.", __FILE__, __LINE__);
		}
	}
	return result;
}

std::string HelperFunctions::ifStatement(const std::string& body, const ifParams& parameters, ContextBase* context)
{
	std::string result("");
	bool check = false;
	if (context)
	{
		try
		{
			check = HelperFunctions::condition<double>(stod(parameters.firstVar), stod(parameters.secondVar), parameters, context);
		}
		catch (...)
		{
			check = HelperFunctions::condition<std::string>(context->getByKey(parameters.firstVar), context->getByKey(parameters.secondVar), parameters, context);
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

block HelperFunctions::findBlock(size_t& pos, const std::string& code)
{
	size_t foundPos = 0;
	block result;
	foundPos = code.find("{%", pos);
	if (foundPos == std::string::npos)
	{
		result.after = code;
		pos = code.size();
	}
	else
	{
		for (size_t i = pos; i < foundPos; i++)
		{
			result.before += code[i];
		}
		std::stack<size_t> beginPositions;
		std::stack<size_t> endPositions;
		size_t begin = 0;
		size_t end = code.size();
		blockParams blockParameters(foundPos, 0, false, false, CONSTANT::BEGIN_TAG_REGEX, CONSTANT::END_TAG_REGEX);
		do
		{
			HelperFunctions::findTag(code, blockParameters);
			if (blockParameters.first)
			{
				beginPositions.push(blockParameters.foundPos);
			}
			else if (blockParameters.second)
			{
				endPositions.push(blockParameters.foundPos + blockParameters.offset);
			}
			if (beginPositions.size() < endPositions.size())
			{
				throw RenderError("HelperFunctions::findBlock(): invalid template syntax.", __FILE__, __LINE__);
			}
			if (beginPositions.size() == endPositions.size())
			{
				while (beginPositions.size() > 1)
				{
					beginPositions.pop();
				}
				begin = beginPositions.top();
				beginPositions.pop();
				end = endPositions.top();
			}
		} while (beginPositions.size() != 0);
		result.code += code.substr(begin, end - begin);
		foundPos = code.find("{%", end);
		if (foundPos == std::string::npos)
		{
			foundPos = code.size();
		}
		for (size_t i = end; i < foundPos; i++)
		{
			result.after += code[i];
		}
		pos = foundPos;
	}
	return result;
}

void HelperFunctions::findAllBlocks(std::list<block>& blocks, const std::string& code)
{
	size_t pos = 0;
	while (pos < code.size())
	{
		blocks.push_back(HelperFunctions::findBlock(pos, code));
	}
}

void HelperFunctions::findTag(const std::string& str, blockParams& params)
{
	std::regex expression("(" + params.regexFirst + ")|(" + params.regexSecond + ")");
	std::smatch data;
	if (std::regex_search(str.begin() + params.foundPos + params.offset, str.end(), data, expression))
	{
		if (Parser::regexCheck(data.str(), params.regexFirst))
		{
			params.first = true;
			params.second = false;
		}
		else if (Parser::regexCheck(data.str(), params.regexSecond))
		{
			params.first = false;
			params.second = true;
		}
		else
		{
			throw RenderError("HelperFunctions::findTag(): incorrect tag.", __FILE__, __LINE__);
		}
		params.foundPos += data.position() + params.offset;
		params.offset = data.str().size();
	}
}

size_t HelperFunctions::findSubstringPosition(const std::string& str, const std::string& regex, bool reverse)
{
	size_t result = 0;
	std::smatch data;
	if (std::regex_search(str, data, std::regex(regex)))
	{
		if (reverse)
		{
			result = std::abs((int)(data.position() - str.size())) - data.str().size();
		}
		else
		{
			result = data.position() + data.str().size();
		}
	}
	else
	{
		throw std::exception();
	}
	return result;
}
