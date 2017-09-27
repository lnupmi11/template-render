#include "Functions.h"
#include "../Header.h"
#include <Windows.h>
#include <fstream>
#include <direct.h>

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

bool HelperFunctions::createCpp(const std::string& cppCode, const std::string& fileName)
{
	_mkdir("_cppcache_");
	std::ofstream file;
	file.open("_cppcache_/" + fileName);
	if (!file.is_open())
	{
		std::cerr << "Error occurred in 'HelperFunctions::createCpp()' function: file was not opened for writting.\n";
		return false;
	}
	file << cppCode + "\n";
	file.close();
	std::cout << "File '" + fileName + "' is created.\n";
	return true;
}

std::string HelperFunctions::createCompletedCppCode(const std::string& mainPartOfCppCode)
{
	std::string result = programBegin;
	result += mainPartOfCppCode;
	result += programEnd;
	return result;
}

bool HelperFunctions::createBat(std::vector<std::string> filesToDelete, const std::string& fileName)
{
	_mkdir("_cppcache_");
	std::ofstream file;
	file.open("_cppcache_/" + fileName);
	if (!file.is_open())
	{
		std::cerr << "Error occurred in 'HelperFunctions::createBat()' function: file was not opened for writting.\n";
		return false;
	}
	file << "cd \"_cppcache_\"\n";
	if (filesToDelete.size() != 0)
	{
		for (std::vector<std::string>::iterator i = filesToDelete.begin(); i != filesToDelete.end(); i++)
		{
			file << "del \"" + *i + "\"\n";
		}
	}
	file << "del \"%~f0\"";
	file.close();
	std::cout << "File '" + fileName + "' for removing trash is created.\n";
	return true;
}

bool HelperFunctions::compile(const std::string& cppFilePath)
{
	if (cppFilePath.size() == 0)
	{
		std::cerr << "Error occurred in 'HelperFunctions::compile()' function: path to cpp file is none.\n";
		return false;
	}
	std::string command = "g++ _cppcache_/" + cppFilePath + " -o _cppcache_/" + cppFilePath.substr(0, cppFilePath.size() - 4);
	size_t status = system(command.c_str());
	if (status != CMD_EXECUTE_SUCCESS)
	{
		std::cerr << "Error occurred in 'HelperFunctions::compile()' function: compilation error.\n";
		return false;
	}
	std::cout << "File '" + cppFilePath + "' is created.\n";
	return true;
}

bool HelperFunctions::run(const std::string& filePath, const int& windowState)
{
	if (filePath.size() == 0)
	{
		std::cerr << "Error occurred in 'HelperFunctions::run()' function: path to executable file is none.\n";
		return false;
	}
	std::cout << "Running " + filePath + "...\n";
	std::string command = ".\\" + filePath;
	size_t status = (size_t)ShellExecute(NULL, "open", command.c_str(), NULL, NULL, windowState);
	if (status != SHELL_EXECUTE_SUCCESS)
	{
		std::cerr << "Error occurred in 'HelperFunctions::run()' function: incorrect execute command.\n";
		return false;
	}
	return true;
}
