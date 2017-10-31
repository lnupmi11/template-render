#include "../Utils/Functions.h"
#include "../Render/Parser.h"
#include"Compile.h"
#include "TemplateRender.h"

string TemplateRender::getFileContent(const string htmlPagePath)
{
	string content = HelperFunctions::getCppHtmlCode(htmlPagePath);
	if (content.size() == 0)
	{
		throw exception("File is empty.");
	}

	return content;
}

string TemplateRender::getCppCode(const string htmlPagePath)
{
	string content = getFileContent(htmlPagePath);
	string cppCode = Parser::parseToCpp(content);

	if (cppCode.size() == 0)
	{
		throw exception("Parsed file is empty.");
	}

	return cppCode;
}

string TemplateRender::completedCppCode(string code)
{
	string cppCode = HelperFunctions::createCompletedCppCode(code);
	return cppCode;
}

	

void TemplateRender::render(const string& htmlPagePath , DataObject& data )
{
	string parsedCppCode = getCppCode(htmlPagePath);
	string cppCode = completedCppCode(parsedCppCode);

	ofstream ofs;
	ofs.open("Render//Compile.h", ios_base::out | ios_base::trunc);
	ofs << cppCode;
	ofs.close();

	compile();

}