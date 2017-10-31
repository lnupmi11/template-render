#define _CRT_SECURE_NO_WARNINGS
#include "Functions.h"
#include <fstream>
#include <Windows.h>

#include <stdlib.h>
#include <sstream>

std::string HelperFunctions::getCppHtmlCode(const std::string& fileName)
{
	validateFileName(fileName);

	std::ifstream file;
	file.open(fileName);
	if (!file.is_open())
	{
		string exceptionMessage = "can not open file " + fileName;
		throw exception(exceptionMessage.c_str());
	}
	std::string result((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	file.close();

	return result;
}

bool HelperFunctions::createHtmlPage(const std::string & htmlCode, const std::string& fileName)
{
	validateFileName(fileName);

	std::ofstream file;
	file.open(fileName);
	if (!file.is_open())
	{
		string exceptionMessage = "can not open file " + fileName;
		throw exception(exceptionMessage.c_str());
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

void HelperFunctions::validateFileName(const std::string& fileName)
{
	if (fileName.size() == 0)
	{
		throw invalid_argument("File name is empty.");
	}
}
