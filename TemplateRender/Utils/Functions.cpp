#include "Functions.h"
#include <iostream>
#include <Windows.h>
#include <fstream>

std::string HelperFunctions::getCppHtmlCode(const std::string& fileName)
{
	std::ifstream file;
	file.open(fileName);
	
	if (!file.is_open())
	{
		std::cout << "can not open file " << fileName << "\n";
	}
	std::string result((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	file.close();
	return result;
}

void HelperFunctions::createHtmlPage(const std::string & htmlCode, const std::string& fileName)
{
	std::ofstream file;
	file.open(fileName);
	if (!file.is_open())
	{
		std::cout << "can not write data in file ..." << fileName << "\n";
	}
	file << htmlCode;
	file.close();
}


void HelperFunctions::createCpp(const std::string& cppCode, const std::string& fileName)
{
	std::ofstream file;
	file.open(fileName);
	if (!file.is_open())
	{
		std::cerr << "ERROR OCCURRED: createCpp()\nFile was not opened for writting.\n";
		std::cin.get();
		return;
	}
	file << cppCode + "\n";
	file.close();
}
void HelperFunctions::createBat(std::vector<std::string> filesToDelete, const std::string& fileName)
{
	std::ofstream file;
	file.open(fileName);
	if (!file.is_open())
	{
		std::cerr << "ERROR OCCURRED: selfDestruct()\nFile was not opened for writting.\n";
		std::cin.get();
		return;
	}
	for (std::vector<std::string>::iterator i = filesToDelete.begin(); i != filesToDelete.end(); i++)
	{
		file << "del \"" + *i + "\"\n";
	}
	file << "del \"%~f0\"";
	file.close();
}
void HelperFunctions::compile(const std::string& cppFilePath)
{
	std::string command = "g++ " + cppFilePath;
	system(command.c_str());
}
void HelperFunctions::run(const std::string& filePath)
{
	ShellExecute(NULL, NULL, filePath.c_str(), NULL, NULL, SW_SHOWDEFAULT);
}
