#include "Functions.h"
#include <iostream>
#include <Windows.h>
#include <fstream>
#include <direct.h>

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
	_mkdir("_cppcache_");
	std::ofstream file;
	file.open("_cppcache_/" + fileName);
	if (!file.is_open())
	{
		std::cerr << "ERROR OCCURRED: createCpp()\nFile was not opened for writting.\n";
		std::cin.get();
		return;
	}
	file << cppCode + "\n";
	file.close();
	std::cout << "File '" + fileName + "' is created.\n";
}

std::string HelperFunctions::createCompletedCppCode(const std::string& mainPartOfCppCode)
{
	std::string result = programBegin;
	result += mainPartOfCppCode;
	result += programEnd;
	return result;
}

void HelperFunctions::createBat(std::vector<std::string> filesToDelete, const std::string& fileName)
{
	std::ofstream file;
	file.open("_cppcache_/" + fileName);
	if (!file.is_open())
	{
		std::cerr << "ERROR OCCURRED: selfDestruct()\nFile was not opened for writting.\n";
		std::cin.get();
		return;
	}
	file << "cd \"_cppcache_\"\n";
	for (std::vector<std::string>::iterator i = filesToDelete.begin(); i != filesToDelete.end(); i++)
	{
		file << "del \"" + *i + "\"\n";
	}
	file << "del \"%~f0\"";
	file.close();
	std::cout << "File '" + fileName + "' for removing trash is created.\n";
}

void HelperFunctions::compile(const std::string& cppFilePath)
{
	std::string terminalPath = cppFilePath;
	terminalPath.erase(terminalPath.end() - 4, terminalPath.end());
	std::string command = "g++ _cppcache_/" + cppFilePath + " -o _cppcache_/" + terminalPath;
	system(command.c_str());
	std::cout << "File '" + cppFilePath + "' is created.\n";
}

void HelperFunctions::run(const std::string& filePath)
{
	std::cout << "Running " + filePath + "...\n";
	std::string command = ".\\" + filePath;
	ShellExecute(NULL, "open", command.c_str(), NULL, NULL, SW_SHOWDEFAULT);
}
