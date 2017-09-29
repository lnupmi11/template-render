#include "Functions.h"
#include <fstream>
#include <Windows.h>

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
	if (!HelperFunctions::directoryExists("_cpptemp_"))
	{
		if (!HelperFunctions::run("mkdir _cpptemp_"))
		{
			std::cerr << "Error occurred in 'HelperFunctions::createCpp()' function: can not create folder.\n";
			return false;
		}
	}
	std::ofstream file;
	file.open("_cpptemp_/" + fileName);
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
	if (!HelperFunctions::directoryExists("_cpptemp_"))
	{
		if (!HelperFunctions::run("mkdir _cpptemp_"))
		{
			std::cerr << "Error occurred in 'HelperFunctions::createBat()' function: can not create folder.\n";
			return false;
		}
	}
	std::ofstream file;
	file.open("_cpptemp_/" + fileName);
	if (!file.is_open())
	{
		std::cerr << "Error occurred in 'HelperFunctions::createBat()' function: file was not opened for writting.\n";
		return false;
	}
	file << "@echo off\n";
	file << "cd \"_cpptemp_\"\n";
	if (filesToDelete.size() != 0)
	{
		for (std::vector<std::string>::iterator i = filesToDelete.begin(); i != filesToDelete.end(); i++)
		{
			file << "del \"" + *i + "\"\n";
		}
	}
	file << "del \"%~f0\"";
	file.close();
	std::cout << "File '" + fileName + "' is created.\n";
	return true;
}

bool HelperFunctions::compile(const std::string& cppFilePath)
{
	if (cppFilePath.size() == 0)
	{
		std::cerr << "Error occurred in 'HelperFunctions::compile()' function: path to cpp file is none.\n";
		return false;
	}
	std::string command = "g++ _cpptemp_/" + cppFilePath + " -o _cpptemp_/" + cppFilePath.substr(0, cppFilePath.size() - 4);
	if (!HelperFunctions::run(command))
	{
		std::cerr << "Error occurred in 'HelperFunctions::compile()' function: compilation error.\n";
		return false;
	}
	std::cout << "File '" + cppFilePath + "' is compiled.\n";
	return true;
}

bool HelperFunctions::run(const std::string& command)
{
	if (command.size() == 0 || command.find_first_not_of(' ') == std::string::npos)
	{
		std::cerr << "Error occurred in 'HelperFunctions::run()' function: incorrect command.\n";
		return false;
	}
	STARTUPINFO startupInfo;
	PROCESS_INFORMATION processInfo;
	ZeroMemory(&startupInfo, sizeof(startupInfo));
	startupInfo.cb = sizeof(startupInfo);
	ZeroMemory(&processInfo, sizeof(processInfo));
	if (!CreateProcess(NULL, const_cast<char*>(("cmd /c " + command).c_str()), NULL, NULL, FALSE, 0, NULL, NULL, &startupInfo, &processInfo))
	{
		std::cerr << "Error occurred in 'HelperFunctions::run()' function: process '" << command << "' was not executed.\n";
		return false;
	}
	WaitForSingleObject(processInfo.hProcess, INFINITE);
	if (CloseHandle(processInfo.hProcess))
	{
		if (CloseHandle(processInfo.hThread))
		{
			return true;
		}
		else
		{
			std::cerr << "Error occurred in 'HelperFunctions::run()' function: thread of process '" << command << "' was not closed properly.\n";
		}
	}
	else
	{
		std::cerr << "Error occurred in 'HelperFunctions::run()' function: process '" << command << "' was not closed properly.\n";
	}
	return false;
}

bool HelperFunctions::directoryExists(const std::string& directory)
{
	DWORD dirAttributes = GetFileAttributesA(directory.c_str());
	if (dirAttributes == INVALID_FILE_ATTRIBUTES)
	{
		return false;
	}
	if (dirAttributes && FILE_ATTRIBUTE_DIRECTORY)
	{
		return true;
	}
	return false;
}
