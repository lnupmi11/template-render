#include "Functions.h"
#include"..//GlobalVariables.h"
#include<Windows.h>


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


void HelperFunctions::execute(const string& command)
{
	auto se = ShellExecute(0, "open", "cmd.exe",
		const_cast<char*>((command).c_str()),
		0, SW_NORMAL);
	
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

bool is64Bit = false;
bool is32Bit = false;
string ROOTFOLDERPATH;
string TMPDATAPATH;
string EXEFILEPATH;
string COMPILEDCPPFILEPATH;
string INDEXHTMLFILEPATH;
string CPPHTMFILEPATH;
string DEVPROMPTPATH;
string VSPATH;

void HelperFunctions::createPaths()
{
	char buffer[MAX_PATH];
	GetModuleFileName(NULL, buffer, MAX_PATH);
	EXEFILEPATH = string(buffer);
	size_t rootPos = EXEFILEPATH.rfind("template-render") + 15;
	ROOTFOLDERPATH = EXEFILEPATH.substr(0, rootPos);
	TMPDATAPATH = ROOTFOLDERPATH + "\\TemplateRender\\tmpData.txt";
	VSPATH = ROOTFOLDERPATH + "\\TemplateRender\\vspath.txt";
	COMPILEDCPPFILEPATH = ROOTFOLDERPATH + "\\TemplateRender\\Render\\Compile.h";
	INDEXHTMLFILEPATH = ROOTFOLDERPATH + "\\TemplateRender\\Rendered_HTML_Page\\index.html";
	CPPHTMFILEPATH = ROOTFOLDERPATH + "\\TemplateRender\\Tests\\TestCppHtmlPage.htm";
//	DEVPROMPTPATH = "C:\\Program Files\\Microsoft Visual Studio\\2017\\Community\\Common7\\Tools\\VsDevCmd.bat";
}

void HelperFunctions::setArchitecture()
{
	execute("%comspec% /c \" wmic os get osarchitecture > " + TMPDATAPATH + "\"");
	ifstream ifs;
	ifs.open(TMPDATAPATH);
	if (ifs.fail())
	{
		throw ifstream::failure(TMPDATAPATH);
	}
	char ch;
	while (!ifs.eof())
	{
		ifs >> ch;
		if (ch == '6')
		{
			is64Bit = true;
			break;
		}
		else if(ch == '3')
		{
			is32Bit = true;
			break;
		}
	}
	ifs.close();
}
