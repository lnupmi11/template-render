#include <iostream>
#include <fstream>
#include <regex>
#include <algorithm>
#include <stack>
#include "Functions.h"
#include "../Render/Parser.h"
#include "RenderError.h"

std::string HelperFunctions::retrieveBodyForLoop(const std::string& code, forLoopParams& parameters)
{
	std::regex forRegex(CONSTANT::FOR_REGEX);
	std::smatch loopCondt;
	std::regex_search(code, loopCondt, forRegex);
	string loopCondition = loopCondt.str();
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
	return string(code.begin() + code.find("%}") + 2, code.begin() + code.rfind("{%"));
}

size_t HelperFunctions::codeType(const std::string& code)
{
	int result;
	std::string statement(code.begin(), code.begin() + code.find("%}") + 2);
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
	string firstVar;
	string secondVar;
	std::regex ifRegex(CONSTANT::IF_REGEX);
	std::smatch ifCondt;
	std::regex_search(code, ifCondt, ifRegex);
	string ifCondition = ifCondt.str();
	parameters.type = HelperFunctions::getTypeOfIFCondition(ifCondition);
	if (parameters.type < 7)
	{
		size_t offset = ifCondition.find("(") + 1;
		parameters.firstVar = std::string(ifCondition.begin() + offset, ifCondition.begin() + ifCondition.find(" ", offset));
		offset = ifCondition.find(" ", ifCondition.find(" ", ifCondition.find("(") + 1)) + 1;
		parameters.secondVar = std::string(ifCondition.begin() + offset, ifCondition.begin() + ifCondition.find(")"));
	}
	else
	{
		std::string firstVar(std::string(ifCondition.begin() + ifCondition.find("("), ifCondition.begin() + ifCondition.find(")")));
		parameters.firstVar = std::regex_replace(firstVar, std::regex("\\s+|\\(|\\)"), "");
	}
	return string(code.begin() + code.find("%}") + 2, code.begin() + code.rfind("{%"));
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

std::string HelperFunctions::runCode(const std::string& code)
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
		result = HelperFunctions::ifStatement(body, ifParameters);
		break;
	case 3:
		result = "";
		break;
	default:
		throw RenderError("HelperFunctions::runCode(): incorrect type of code.", __FILE__, __LINE__);
	}
	return result;
}

std::string HelperFunctions::parse(const std::string& code)
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
		result += HelperFunctions::parse(HelperFunctions::runCode((*block).code));
		result += (*block).after;
	}
	return result;
}

std::string HelperFunctions::readTemplate(const std::string& templateName)
{
	ifstream read(templateName);
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
				result += loopBody;
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
				result += loopBody;
			}
		}
		else
		{
			throw RenderError("HelperFunctions::forLoop(): invalid loop condition.", __FILE__, __LINE__);
		}
	}
	return result;
}

std::string HelperFunctions::ifStatement(const std::string& body, const ifParams& parameters)
{
	std::string result("");
	bool check = false;
	switch (parameters.type)
	{
	case 1: check = (parameters.firstVar < parameters.secondVar); break;
	case 2: check = (parameters.firstVar > parameters.secondVar); break;
	case 3: check = (parameters.firstVar <= parameters.secondVar); break;
	case 4: check = (parameters.firstVar >= parameters.secondVar); break;
	case 5: check = (parameters.firstVar == parameters.secondVar); break;
	case 6: check = (parameters.firstVar != parameters.secondVar); break;
	//case 7: check = (parameters.firstVar); break;
	default: break;
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
		blockParams blockParameters(foundPos, 0, false, false);
		do
		{
			HelperFunctions::findTag(code, blockParameters);
			if (blockParameters.begin)
			{
				beginPositions.push(blockParameters.foundPos);
			}
			else if (blockParameters.end)
			{
				endPositions.push(blockParameters.foundPos + blockParameters.offset);
			}
			if (beginPositions.size() < endPositions.size())
			{
				throw RenderError("HelperFunctions::findBlock(): invalid template.", __FILE__, __LINE__);
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
	std::regex expression("(" + CONSTANT::BEGIN_TAG_REGEX + ")|(" + CONSTANT::END_TAG_REGEX + ")");
	std::sregex_iterator result(str.begin() + params.foundPos + params.offset, str.end(), expression);
	if (result != std::sregex_iterator())
	{
		if (Parser::regexCheck(result->str(), CONSTANT::BEGIN_TAG_REGEX))
		{
			params.begin = true;
			params.end = false;
		}
		else if (Parser::regexCheck(result->str(), CONSTANT::END_TAG_REGEX))
		{
			params.begin = false;
			params.end = true;
		}
		else
		{
			throw RenderError("HelperFunctions::findTag(): incorrect tag.", __FILE__, __LINE__);
		}
		params.foundPos += result->position(0) + params.offset;
		params.offset = result->str().size();
	}
}
