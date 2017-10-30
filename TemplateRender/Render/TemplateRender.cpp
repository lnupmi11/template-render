#pragma once
#include "TemplateRender.h"
#include "../Utils/Functions.h"
#include "../Render/Parser.h"
#include"Compile.h"

string TemplateRender::getFileContent(const string htmlPagePath)
{
	string content = HelperFunctions::getCppHtmlCode(htmlPagePath);

	return content;
}

string TemplateRender::getCppCode(const string htmlPagePath)
{
	string content = getFileContent(htmlPagePath);
	string cppCode = Parser::parseToCpp(content);
	return cppCode;
}

string TemplateRender::completedCppCode(string code)
{
	string cppCode = HelperFunctions::createCompletedCppCode(code);

	return cppCode;
}

void TemplateRender::render(const string& htmlPagePath)
{
	string parsedCppCode = getCppCode(htmlPagePath);	
	string cppCode = completedCppCode(parsedCppCode);

	ofstream ofs;
	ofs.open("Render//Compile.h", ios_base::out | ios_base::trunc);
	ofs << cppCode;
	ofs.close();

	compile();
}