#include "Functions.h"

string HelperFunctions::getCppHtmlCode(const string& fileName)
{
	validateFileName(fileName);

	ifstream file;
	file.open(fileName);
	if (!file.is_open())
	{
		string exceptionMessage = "can not open file " + fileName;
		throw ifstream::failure(exceptionMessage.c_str());
	}
	string result((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
	file.close();

	return result;
}

string HelperFunctions::createCompletedCppCode(const string& ñppCode)
{
	string result(HelperFunctions::PROGRAMBEGIN);
	result += ñppCode;
	result += HelperFunctions::PROGRAMEND;
	return result;
}

string HelperFunctions::getFileContent(const string & path)
{
	ifstream file(path);
	string result;
	if (file.is_open())
	{
		istream_iterator<char> begin(file), end;
		result = string(begin, end);
	}
	return result;
}

bool HelperFunctions::isStateModified(const string & previousVersion, const string & currentVersion)
{
	bool result;
	result = previousVersion != currentVersion;
	return result;
}

void HelperFunctions::validateFileName(const string& fileName)
{
	if (fileName.size() == 0)
	{
		throw invalid_argument("File name is empty.");
	}
}
