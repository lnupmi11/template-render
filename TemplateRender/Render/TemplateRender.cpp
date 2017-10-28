#pragma once
#include "TemplateRender.h"
#include "../Utils/Functions.h"
#include "../Render/Parser.h"
#include"../Data/Data.h"

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

void TemplateRender::render(const string htmlPagePath)
{
	string parsedCppCode = getCppCode(htmlPagePath);
	Data::object;
	string cppCode = completedCppCode(parsedCppCode);
}