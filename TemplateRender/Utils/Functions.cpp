#define _CRT_SECURE_NO_WARNINGS
#include "Functions.h"
#include <fstream>
#include <Windows.h>

#include <stdlib.h>
#include <sstream>

std::string HelperFunctions::getCppHtmlCode(const std::string& fileName)
{
	if (fileName.size() == 0)
	{
		std::cerr << "Error occurred in 'HelperFunctions::getCppHtmlCode()' function: incorrect path to html file.\n";
		return "";
	}
	std::ifstream file;
	file.open(fileName);

	if (!file.is_open())
	{
		std::cerr << "Error occurred in 'HelperFunctions::getCppHtmlCode()' function: can not open file " << fileName << "\n";
		return "";
	}
	std::string result((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	file.close();
	return result;
}

bool HelperFunctions::createHtmlPage(const std::string & htmlCode, const std::string& fileName)
{
	std::ofstream file;
	file.open(fileName);
	if (!file.is_open())
	{
		std::cerr << "Error occurred in 'HelperFunctions::createHtmlPage()' function: can not write data to file '" << fileName << "'\n";
		return false;
	}
	file << htmlCode;
	file.close();
	return true;
}


std::string HelperFunctions::createCompletedCppCode(const std::string& mainPartOfCppCode)
{
	std::string result = programBegin;
	result += mainPartOfCppCode;
	result += programEnd;
	return result;
}
