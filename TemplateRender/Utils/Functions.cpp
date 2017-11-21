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
#include "Constants.h"
#include "../Render/Parser.h"

std::string HelperFunctions::retrieveBodyForLoop(const std::string& code, int& numberOfIteration, bool& increment, bool& fewer)
{
	string result = "";
	std::regex forRegex(CONSTANT::FOR_REGEX);
	std::smatch loopCondt;
	std::regex_search(code, loopCondt, forRegex);
	string loopCondition = loopCondt.str();
	int startCount = stoi(loopCondition.substr(loopCondition.find('=')+1, loopCondition.find(';', loopCondition.find('='))));
	int endCount;
	if (loopCondition.find('<') != std::string::npos)
	{
		fewer = true;
		endCount = stoi(loopCondition.substr(loopCondition.find('<')+1, loopCondition.find(';', loopCondition.find('<'))));
		if (loopCondition.find("++") != std::string::npos)
		{
			numberOfIteration = endCount - startCount;
			increment = true;
		}
		else
		{
			throw  std::exception("Exception in 'HelperFunctions::retrieveBodyForLoop()': Incorrect loop condition");
		}
	}
	else if(loopCondition.find('>') != std::string::npos)
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
			throw  std::exception("Exception in 'HelperFunctions::retrieveBodyForLoop()': Incorrect loop condition");
		}
	}
	else
	{
		throw  std::exception("Exception in 'HelperFunctions::retrieveBodyForLoop()': Incorrect loop condition");
	}
//	std::copy(code.begin() + loopCondition.length(), code.end() - 1, result);
	result = string(code.begin() + loopCondition.size(), code.end() - 12);
	return result;
}

size_t HelperFunctions::codeType(const std::string& code)
{
	int result;
	
	std::string codeTemp(code.begin(), code.begin() + code.find("%}") + 2);
	std::cout << codeTemp << endl << endl;

	bool checkFor = Parser::regexCheck(code, CONSTANT::FOR_REGEX);
	//bool checkForeach = Parser::regexCheck(code, foreachRegex);
	bool checkIf = Parser::regexCheck(code, CONSTANT::IF_REGEX);
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
		throw exception("Exception in 'HelperFunctions::codeType()': Invalid code type");
	}
	return result;
}

std::string HelperFunctions::runCode(const std::string& code)
{
	int numberOfIters = 0;
	bool increment, fewer;
	std::string body;
	std::string result("");
	switch (HelperFunctions::codeType(code))
	{
	case 1:
		body = HelperFunctions::retrieveBodyForLoop(code, numberOfIters, increment, fewer);
		result = HelperFunctions::forLoop(body, numberOfIters, increment, fewer);
		break;
	case 2:
		// TODO: foreach statement (result += ...)
		break;
	case 3:
		// TODO: if statement (result += ...)
		break;
	default:
		throw exception("Exception in 'HelperFunctions::runCode()': Incorrect type of code");
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
	ifstream read;
	read.open(templateName);
	std::string result("");
	if (read.is_open())
	{
		result.assign((std::istreambuf_iterator<char>(read)), std::istreambuf_iterator<char>());
		read.close();
	}
	else
	{
		throw  std::exception(("Exception in 'HelperFunctions::readTemplate()': File '" + templateName + "' not found").c_str());
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
		throw std::exception(("Exception in 'HelperFunctions::createHTML()': Can not open file '" + htmlPath + "' for writting.").c_str());
	}
}

void HelperFunctions::render(const std::string& templatePath, const std::string& htmlPath)
{
	try
	{
		std::string templateHTML = HelperFunctions::readTemplate(CONSTANT::TEMPLATE_DIR + templatePath);
		std::string completedHTML = HelperFunctions::parse(templateHTML);
		HelperFunctions::createHTML(completedHTML, CONSTANT::ENDPOINT_DIR + htmlPath);
	}
	catch (const std::exception& exc)
	{
		std::cerr << exc.what();
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
			throw  std::exception("Exception in 'HelperFunctions::forLoop()': Invalid loop condition");
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
			throw  std::exception("Exception in 'HelperFunctions::forLoop()': Invalid loop condition");
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
		for (size_t i = 0; i < foundPos; i++)
		{
			result.before += code[i];
		}
		std::stack<size_t> beginPositions;
		std::stack<size_t> endPositions;
		size_t begin = 0;
		size_t end = code.size();
		std::string temp1(code);
		std::string temp2(code);
		do
		{
			// TODO: search for "{% for" or "for %}"
			//
			//		 if ("{% for" is found)
			//		 {
			//			beginPositions.push(foundPos);
			//		 }
			//		 else if ("for %}" is found)
			//		 {
			//			endPositions.push(foundPos);
			//			if (beginPositions.size() < 2)
			//			{
			//				begin = beginPositions.top();
			//				end = endPositions.top();
			//			}
			//			beginPositions.pop();
			//		 }
			//

			
			if (HelperFunctions::findTag(temp1, CONSTANT::BEGIN_TAG_REGEX, foundPos))
			{
				beginPositions.push(foundPos);
			}
			else if (HelperFunctions::findTag(temp2, CONSTANT::END_TAG_REGEX, foundPos))
			{
				endPositions.push(foundPos);
				if (beginPositions.size() == 1)
				{
					begin = beginPositions.top();
					end = endPositions.top();
				}
				beginPositions.pop();
			}
		} while (beginPositions.size() != 0 || foundPos != std::string::npos);

		end += 12;	// 6 -- size of "{% endfor %}"
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

bool HelperFunctions::findTag(std::string& str, const std::string& regexStr, size_t& position)
{
	std::regex expression(regexStr);
	std::smatch data;
	bool result = std::regex_search(str, data, expression);
	if (result)
	{
		position = data.position(0);
		str.erase(str.begin(), str.begin() + position + data[0].str().size());
	}
	else
	{
		position = std::string::npos;
	}
	return result;
}
