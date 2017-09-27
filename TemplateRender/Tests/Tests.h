#pragma once
#include <iostream>
#include <Windows.h>
#include <direct.h>
#include "../Utils/Functions.h"
#include "../Utils/Parser.h"

using namespace std;


void testParseToCpp()
{
	string result = Parser::parseToCpp(HelperFunctions::getCppHtmlCode("Tests/TestCppHtmlPage.htm"));
	string cppProgram = HelperFunctions::createCompletedCppCode(result);
}


// Used in CREATE_AND_COMPILE_CPP() test to prevent code duplication.
void returnFunction()
{
	HelperFunctions::run("_cppcache_/sd.bat", SW_HIDE);
	Sleep(500);
	_rmdir("_cppcache_");
}

void CREATE_AND_COMPILE_CPP()
{
	cout << "Running test: CREATE_AND_COMPILE_CPP()...\n";
	string parsedToCpp = Parser::parseToCpp(HelperFunctions::getCppHtmlCode("Tests/TestCppHtmlPage.htm"));
	if (parsedToCpp.size() == 0)
	{
		return;
	}
	string cppCode = HelperFunctions::createCompletedCppCode(parsedToCpp);
	if (cppCode.size() == 0)
	{
		return;
	}
	vector<string> deleteList;
	deleteList.push_back("a.cpp");
	deleteList.push_back("a.exe");
	if (!HelperFunctions::createBat(deleteList, "sd.bat"))
	{
		_rmdir("_cppcache_");
		return;
	}
	if (!HelperFunctions::createCpp(cppCode, "a.cpp"))
	{
		returnFunction();
		return;
	}
	if (!HelperFunctions::compile("a.cpp"))
	{
		returnFunction();
		return;
	}
	if (!HelperFunctions::run("_cppcache_\\a.exe", SW_HIDE))
	{
		returnFunction();
		return;
	}
	cout << "Trash is removed.\n";
	Sleep(500);
	_rmdir("_cppcache_");
	HelperFunctions::run("Rendered_HTML_Page\\index.html", SW_SHOWDEFAULT);
}
