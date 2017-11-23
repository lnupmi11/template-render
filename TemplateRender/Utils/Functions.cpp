/*
#define _CRT_SECURE_NO_WARNINGS
#include "Functions.h"
#include <fstream>
#include <iostream>
#include <Windows.h>

std::string HelperFunctions::getCppHtmlCode(const std::string& fileName)
{
	std::string result("");
	if (fileName.size() != 0)
	{
		std::ifstream file;
		file.open(fileName);

		if (file.is_open())
		{
			result.assign((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
			file.close();
		}
		else
		{
			std::cerr << "Error occurred in 'HelperFunctions::getCppHtmlCode()' function: can not open file " << fileName << '\n';
		}
	}
	else
	{
		std::cerr << "Error occurred in 'HelperFunctions::getCppHtmlCode()' function: incorrect path to html file.\n";
	}
	return result;
}

bool HelperFunctions::createHtmlPage(const std::string & htmlCode, const std::string& fileName)
{
	std::ofstream file(fileName);
	if (file.is_open())
	{
		file << htmlCode;
		file.close();
		return true;
	}
	std::cerr << "Error occurred in 'HelperFunctions::createHtmlPage()' function: can not write data to file '" << fileName << "'\n";
	return false;
}

bool HelperFunctions::createCpp(const std::string& cppCode, const std::string& fileName)
{
	if (!HelperFunctions::directoryExists(CONSTANT::TEMP_DIR))
	{
		if (!HelperFunctions::run("mkdir " + CONSTANT::TEMP_DIR))
		{
			std::cerr << "Error occurred in 'HelperFunctions::createCpp()' function: can not create folder.\n";
			return false;
		}
	}
	std::ofstream file(CONSTANT::TEMP_DIR + "\\" + fileName);
	if (file.is_open())
	{
		file << cppCode + '\n';
		file.close();
		return true;
	}
	std::cerr << "Error occurred in 'HelperFunctions::createCpp()' function: file was not opened for writting.\n";
	return false;
}

std::string HelperFunctions::createCompletedCppCode(const std::string& mainPartOfCppCode)
{
	return std::string(PROGRAM_BEGIN + mainPartOfCppCode + PROGRAM_END);
}

bool HelperFunctions::compile(const std::string& cppFilePath)
{
	if (cppFilePath.size() != 0)
	{
		std::string command(CONSTANT::MINGW_PATH + "\\g++ " + CONSTANT::TEMP_DIR + "\\" + cppFilePath +
			" -o " + CONSTANT::TEMP_DIR + "\\" + cppFilePath.substr(0, cppFilePath.size() - 4));
		if (HelperFunctions::run(command))
		{
			return true;
		}
		else
		{
			std::cerr << "Error occurred in 'HelperFunctions::compile()' function: compilation error.\n";
		}
	}
	else
	{
		std::cerr << "Error occurred in 'HelperFunctions::compile()' function: path to cpp file is none.\n";
	}
	return false;
}

bool HelperFunctions::run(const std::string& command)
{
	if (command.size() != 0 || command.find_first_not_of(' ') != std::string::npos)
	{
		STARTUPINFO startupInfo;
		PROCESS_INFORMATION processInfo;
		ZeroMemory(&startupInfo, sizeof(startupInfo));
		startupInfo.cb = sizeof(startupInfo);
		ZeroMemory(&processInfo, sizeof(processInfo));
		if (CreateProcess(NULL, const_cast<char*>(("cmd /c " + command).c_str()), NULL, NULL, FALSE, 0, NULL, NULL, &startupInfo, &processInfo))
		{
			WaitForSingleObject(processInfo.hProcess, INFINITE);
			if (CloseHandle(processInfo.hProcess))
			{
				if (CloseHandle(processInfo.hThread))
				{
					return true;
				}
				else
				{
					std::cerr << "Error occurred in 'HelperFunctions::run()' function: thread of process '" << command << 
						"' was not closed properly. Error: #" + GetLastError() + '\n';
				}
			}
			else
			{
				std::cerr << "Error occurred in 'HelperFunctions::run()' function: process '" << command <<
					"' was not closed properly. Error: #" + GetLastError() + '\n';
			}
		}
		else
		{
			std::cerr << "Error occurred in 'HelperFunctions::run()' function: process '" << command <<
				"' was not executed. Error: #" << GetLastError() << '\n';
		}
	}
	else
	{
		std::cerr << "Error occurred in 'HelperFunctions::run()' function: incorrect command.\n";
	}
	return false;
}

bool HelperFunctions::directoryExists(const std::string& directory)
{
	DWORD dirAttributes = GetFileAttributesA(directory.c_str());
	return dirAttributes != INVALID_FILE_ATTRIBUTES && dirAttributes & FILE_ATTRIBUTE_DIRECTORY;
}*/

#include <iostream>
#include <fstream>
#include <regex>
#include <algorithm>
#include <stack>
#include "Functions.h"
#include "../Render/Parser.h"
#include "RenderError.h"

std::string HelperFunctions::retrieveBodyForLoop(const std::string& code, int& numberOfIteration, bool& increment, bool& fewer)
{
	std::regex forRegex(CONSTANT::FOR_REGEX);
	std::smatch loopCondt;
	std::regex_search(code, loopCondt, forRegex);
	string loopCondition = loopCondt.str();
	int startCount = stoi(loopCondition.substr(loopCondition.find('=') + 1, loopCondition.find(';', loopCondition.find('='))));
	int endCount;
	if (loopCondition.find('<') != std::string::npos)
	{
		fewer = true;
		endCount = stoi(loopCondition.substr(loopCondition.find('<') + 1, loopCondition.find(';', loopCondition.find('<'))));
		if (loopCondition.find("++") != std::string::npos)
		{
			numberOfIteration = endCount - startCount;
			increment = true;
		}
		else
		{
			throw RenderError("HelperFunctions::retrieveBodyForLoop(): incorrect loop condition.", __FILE__, __LINE__);
		}
	}
	else if (loopCondition.find('>') != std::string::npos)
	{
		fewer = false;
		endCount = stoi(loopCondition.substr(loopCondition.find('>') + 1, loopCondition.find(';', loopCondition.find('>'))));
		if (loopCondition.find("--") != std::string::npos)
		{
			increment = false;
			numberOfIteration = startCount - endCount;
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
	//bool checkForeach = Parser::regexCheck(statement, foreachRegex);
	bool checkIf = Parser::regexCheck(statement, CONSTANT::IF_REGEX);
	if (checkFor)
	{
		result = 1;
	}
	/*else if (checkForeach)
	{
		result = 2;
	}*/
	else if (checkIf)
	{
		result = 3;
	}
	else
	{
		throw RenderError("HelperFunctions::codeType(): invalid code type.", __FILE__, __LINE__);
	}
	return result;
}

std::string HelperFunctions::runCode(const std::string& code)
{
	int numberOfIters = 0;
	bool increment, fewer;
	std::string body(""), result("");
	switch (HelperFunctions::codeType(code))
	{
	case 1:
		body = HelperFunctions::retrieveBodyForLoop(code, numberOfIters, increment, fewer);
		result = HelperFunctions::forLoop(body, numberOfIters, increment, fewer);
		break;
	case 2:
		// TODO: foreach statement
		break;
	case 3:
		// TODO: if statement
		break;
	default:
		throw RenderError("HelperFunctions::runCode(): incorrect type of code.", __FILE__, __LINE__);
		break;
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

std::string HelperFunctions::forLoop(const std::string& loopBody, const int& numberOfIteration, const bool& increment, const bool& fewer)
{
	std::string result("");
	if (increment)
	{
		if (fewer)
		{
			for (int i = 0; i < numberOfIteration; i++)
			{
				result += loopBody;
			}
		}
		else
		{
			throw RenderError("HelperFunctions::forLoop(): invalid loop condition.", __FILE__, __LINE__);
		}
	}
	if (!increment)
	{
		if (!fewer)
		{
			for (int i = numberOfIteration; i > 0; i--)
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
