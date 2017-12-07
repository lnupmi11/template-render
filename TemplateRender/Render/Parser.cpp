#include "Parser.h"
#include "../Utils/Constants.h"
#include "../Utils/LoopStatement.h"
#include "../Utils/IfStatement.h"
#include <regex>
#include <algorithm>
#include <stack>

bool Parser::matchString(const std::string& str, const std::string& regexStr)
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

size_t Parser::findSubstringPosition(const std::string& str, const std::string& regex, bool reverse)
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

block Parser::findBlock(size_t& pos, const std::string& code)
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
			Parser::findTag(code, blockParameters);
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
				throw RenderError("Parser::findBlock(): invalid template syntax.", __FILE__, __LINE__);
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

void Parser::findAllBlocks(std::list<block>& blocks, const std::string& code)
{
	size_t pos = 0;
	while (pos < code.size())
	{
		blocks.push_back(Parser::findBlock(pos, code));
	}
}

void Parser::findTag(const std::string& str, blockParams& params)
{
	std::regex expression("(" + params.regexFirst + ")|(" + params.regexSecond + ")");
	std::smatch data;
	if (std::regex_search(str.begin() + params.foundPos + params.offset, str.end(), data, expression))
	{
		if (Parser::matchString(data.str(), params.regexFirst))
		{
			params.first = true;
			params.second = false;
		}
		else if (Parser::matchString(data.str(), params.regexSecond))
		{
			params.first = false;
			params.second = true;
		}
		else
		{
			throw RenderError("Parser::findTag(): incorrect tag.", __FILE__, __LINE__);
		}
		params.foundPos += data.position() + params.offset;
		params.offset = data.str().size();
	}
}

size_t Parser::codeType(const std::string& code)
{
	int result;
	size_t endPos = 0;
	try
	{
		endPos = Parser::findSubstringPosition(code, "%\\s*\\}");
	}
	catch (const std::exception&)
	{
		throw RenderError("Parser::codeType(): invalid template syntax.", __FILE__, __LINE__);
	}
	std::string statement(code.begin(), code.begin() + endPos);
	bool checkFor = Parser::matchString(statement, CONSTANT::FOR_REGEX);
	bool checkIf = Parser::matchString(statement, CONSTANT::IF_REGEX);
	bool checkComment = Parser::matchString(statement, CONSTANT::BEGIN_COMMENT_REGEX);
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
		throw RenderError("Parser::codeType(): invalid code type.", __FILE__, __LINE__);
	}
	return result;
}

std::string Parser::parseTemplate(const std::string& code, ContextBase* context)
{
	std::string result("");
	std::list<block> blocks;
	Parser::findAllBlocks(blocks, code);
	for (std::list<block>::iterator block = blocks.begin(); block != blocks.end(); block++)
	{
		if ((*block).before.size() == 0 && (*block).code.size() == 0)
		{
			result += (*block).after;
			return result;
		}
		result += (*block).before;
		result += Parser::parseTemplate(Parser::executeCode((*block).code, context), context);
		result += (*block).after;
	}
	return result;
}

std::string Parser::executeCode(const std::string& code, ContextBase* context)
{
	forLoopParams forParameters;
	ifParams ifParameters;
	std::string body(""), result("");
	switch (Parser::codeType(code))
	{
	case 1:
		body = LoopStatement::parse(code, forParameters);
		result = LoopStatement::execute(body, forParameters);
		break;
	case 2:
		body = IfStatement::parse(code, ifParameters);
		result = IfStatement::execute(body, ifParameters, context);
		break;
	case 3:
		result = "";
		break;
	default:
		throw RenderError("Parser::executeCode(): incorrect type of code.", __FILE__, __LINE__);
	}
	return result;
}
