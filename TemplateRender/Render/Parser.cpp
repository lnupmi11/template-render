#include "Parser.h"
#include "../BL/Constants.h"
#include "../BL/LoopStatement.h"
#include "../BL/IfStatement.h"
#include "../BL/HTML.h"
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
	if (!Parser::matchString(code, CONSTANT::VAR_REGEX))
	{
		result = code;
	}
	else
	{
		std::regex expression(CONSTANT::VAR_REGEX);
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
	std::regex expression(CONSTANT::TAG_REGEX);
	std::smatch data;
	if (std::regex_search(code.begin() + pos, code.end(), data, expression))
	{
		foundPos = data.position() + pos;
		result.before = std::string(code.begin() + pos, code.begin() + foundPos);
		std::stack<size_t> beginPositions, endPositions;
		size_t begin = 0, end = code.size();
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
		result.code += std::string(code.begin() + begin, code.begin() + end);
		foundPos = code.find("{%", end);
		if (foundPos == std::string::npos)
		{
			foundPos = code.size();
		}
		result.after += std::string(code.begin() + end, code.begin() + foundPos);
		pos = foundPos;
	}
	else
	{
		result.after = code;
		pos = code.size();
	}
	return result;
}

void Parser::findAllBlocks(std::vector<block>& blocks, const std::string& code)
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

codeType Parser::getCodeType(const std::string& code)
{
	codeType result;
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
	if (Parser::matchString(statement, CONSTANT::FOR_REGEX))
	{
		result = codeType::forLoop;
	}
	else if (Parser::matchString(statement, CONSTANT::IF_REGEX))
	{
		result = codeType::ifStatament;
	}
	else if (Parser::matchString(statement, CONSTANT::BEGIN_COMMENT_REGEX))
	{
		result = codeType::comment;
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
	std::vector<block> blocks;
	Parser::findAllBlocks(blocks, code);
	for (std::vector<block>::iterator block = blocks.begin(); block != blocks.end(); block++)
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
	switch (Parser::getCodeType(code))
	{
	case codeType::forLoop:
		body = LoopStatement::parse(code, forParameters);
		result = LoopStatement::execute(body, forParameters);
		break;
	case codeType::ifStatament:
		body = IfStatement::parse(code, ifParameters);
		result = IfStatement::execute(body, ifParameters, context);
		break;
	case codeType::comment:
		result = "";
		break;
	default:
		throw RenderError("Parser::executeCode(): incorrect type of code.", __FILE__, __LINE__);
	}
	return result;
}

std::string Parser::parseInline(const std::string& code)
{
	std::string result("");
	std::regex expression(CONSTANT::INCLUDE_TAG_REGEX);
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
			std::string inlineTag(it->str());
			size_t startOffset = inlineTag.find("\"") + 1;
			size_t endOffset = inlineTag.find("\"", startOffset);
			result += HTML::read(CONSTANT::TEMPLATE_DIR + std::string(inlineTag.begin() + startOffset, inlineTag.begin() + endOffset));
		}
		for (size_t i = pos; i < code.size(); i++)
		{
			result += code[i];
		}
	}

	return result;
}
