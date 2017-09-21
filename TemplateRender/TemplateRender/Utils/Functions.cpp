#include "Functions.h"
#include <iostream>
#include <Windows.h>
#include <fstream>

void createCpp(const std::string& cppCode, const std::string& fileName)
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
void createBat(std::vector<std::string> filesToDelete, const std::string& fileName)
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
void compile(const std::string& cppFilePath)
{
	std::string command = "g++ " + cppFilePath;
	system(command.c_str());
}
void run(const std::string& filePath)
{
	ShellExecute(NULL, NULL, filePath.c_str(), NULL, NULL, SW_SHOWDEFAULT);
}
