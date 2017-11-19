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

#include <fstream>
#include <iostream>
#include <regex>
#include<algorithm>
#include "Functions.h"
#include "../Render/Parser.h"

std::string HelperFunctions::retrieveCode(const std::string& code)
{

}

size_t HelperFunctions::codeType(const std::string& code)
{
	int result;
	const std::string forRegex = "\\s*for\\s*\\(\\s*auto | \\s*size_t |\\s*int \\s*[a-z]{1,}\\s*=\\s*\\d{1,}\\s*;\\s*[a-z]{1,}\\s*<\\s*\\d{1,}\\s*;\\s*[a-z]{1,}\\+\\+\\s*\\)";
	//const std::string foreachRegex = "\\s*for\\s*\\(\\s*auto\\s*[a-z]{1,}\\s*\\:\\s*[a-z]{1,}\\s*\\)";
	const std::string ifRegex = "\\s*if\\s*\\(\\s*[a-z]{1,}\\s*< |\\s*> \\s*[a-z]{1,}\\s*\\)";

	bool checkFor = Parser::regexCheck(code, forRegex);
	//bool checkForeach = Parser::regexCheck(code, foreachRegex);
	bool checkIf = Parser::regexCheck(code, ifRegex);
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
	return result;
}

std::string HelperFunctions::runCode(const std::string& code)
{

}

std::string HelperFunctions::parse(const std::string& code)
{

}

std::string HelperFunctions::readTemplate(const std::string& templateName)
{
	
	ifstream read;
	read.open(templateName);
	std::string result="";
	if (read.is_open())
	{
		result.assign((std::istreambuf_iterator<char>(read)),
			std::istreambuf_iterator<char>());
		read.close();
		
	}
	else
	{
		throw  std::exception("File not found");
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
		throw std::exception(("Can not open file '" + htmlPath + "' for writting.").c_str());
	}
}

void HelperFunctions::render(const std::string& templatePath, const std::string& htmlPath)
{
	std::string html = HelperFunctions::readTemplate(templatePath);
	std::string htmlCode = HelperFunctions::parse(html);
	HelperFunctions::createHTML(htmlCode, htmlPath);
}
