#pragma once
#include <iostream>
#include <Windows.h>
#include "../Utils/Functions.h"
#include "../Render/Parser.h"

// If you run program from x64/Debug use next defines:
//#define TEMPLATE_PATH "..\\..\\TemplateRender\\Tests\\TestCppHtmlPage.htm"
//#define MINGW_PATH "..\\..\\TemplateRender\\MinGW"

// If you run program from Visual Studio debugger or simply Ctrl+F5 use next defines:
#define TEMPLATE_PATH "Tests\\TestCppHtmlPage.htm"
#define MINGW_PATH "MinGW"

using namespace std;


void testParseToCpp()
{
	string result = Parser::parseToCpp(HelperFunctions::getCppHtmlCode("Tests/TestCppHtmlPage.htm"));
	string cppProgram = HelperFunctions::createCompletedCppCode(result);
}


// Used in CREATE_AND_COMPILE_CPP() test to prevent code duplication.
void returnFunction()
{
	if (HelperFunctions::directoryExists("_cpptemp_"))
	{
		HelperFunctions::run("_cpptemp_/sd.bat");
		HelperFunctions::run("rmdir _cpptemp_");
	}
}

void CREATE_AND_COMPILE_CPP()
{
	if (/*HelperFunctions::installMinGW(MINGW_PATH)*/1)
	{
		cout << "Running test: CREATE_AND_COMPILE_CPP()...\n";
		string parsedToCpp = Parser::parseToCpp(HelperFunctions::getCppHtmlCode(TEMPLATE_PATH));
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
			if (HelperFunctions::directoryExists("_cpptemp_"))
			{
				HelperFunctions::run("rmdir _cpptemp_");
			}
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
		if (!HelperFunctions::run("_cpptemp_\\a.exe"))
		{
			returnFunction();
			return;
		}
		if (HelperFunctions::directoryExists("_cpptemp_"))
		{
			HelperFunctions::run("_cpptemp_\\sd.bat");
			cout << "Temporary files were removed.\n";
			HelperFunctions::run("rmdir _cpptemp_");
		}
		if (HelperFunctions::directoryExists("Rendered_HTML_Page"))
		{
			HelperFunctions::run("Rendered_HTML_Page\\index.html");
		}
	}
}
