/*
#pragma once
#include <iostream>
#include <Windows.h>
#include "../Utils/Functions.h"
#include "../Render/Parser.h"

using namespace std;


void testParseToCpp()
{
	string result = Parser::parseToCpp(HelperFunctions::getCppHtmlCode("Tests/TestCppHtmlPage.htm"));
	string cppProgram = HelperFunctions::createCompletedCppCode(result);
}

void CREATE_AND_COMPILE_CPP()
{
	cout << "Running test: CREATE_AND_COMPILE_CPP()...";
	string parsedToCpp = Parser::parseToCpp(HelperFunctions::getCppHtmlCode(CONSTANT::TEMPLATE_PATH));
	if (parsedToCpp.size() == 0)
	{
		return;
	}
	string cppCode = HelperFunctions::createCompletedCppCode(parsedToCpp);
	if (cppCode.size() == 0)
	{
		return;
	}
	if (!HelperFunctions::createCpp(cppCode, "temp.cpp"))
	{
		HelperFunctions::run("rmdir /S /Q " + CONSTANT::TEMP_DIR);
		return;
	}
	if (!HelperFunctions::compile("temp.cpp"))
	{
		HelperFunctions::run("rmdir /S /Q " + CONSTANT::TEMP_DIR);
		return;
	}
	if (!HelperFunctions::run(CONSTANT::TEMP_DIR + "\\temp.exe"))
	{
		HelperFunctions::run("rmdir /S /Q " + CONSTANT::TEMP_DIR);
		return;
	}
	if (HelperFunctions::directoryExists(CONSTANT::TEMP_DIR))
	{
		HelperFunctions::run("rmdir /S /Q " + CONSTANT::TEMP_DIR);
	}
	if (HelperFunctions::directoryExists("Rendered_HTML_Page"))
	{
		HelperFunctions::run("Rendered_HTML_Page\\index.html");
	}
	cout << " OK\n";
}*/

#include "../Render/TemplateRender.h"
#include <iostream>
#include <time.h>

void TEST_CASE()
{
	std::cout << "Rendering...";

	clock_t start, finish;
	start = clock();

	TemplateRender::render("index.html", "completed.html");

	finish = clock();
	float difference((float)finish - (float)start);
	std::cout << "\nRendering time: " << difference / CLOCKS_PER_SEC << " sec. ";
}
