#pragma once
#include "TemplateRender.h"
#include "../Utils/Functions.h"
#include "../Render/Parser.h"
#include"../Data/Data.h"

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

void TemplateRender::createCppFile(const string cppCode, const string fileName)
{
	if (!HelperFunctions::createCpp(cppCode, fileName))
	{
		string errorMessage = fileName + " isn't created.";
		throw exception(errorMessage.c_str());
	}
}

void TemplateRender::compileCppFile(const string fileName)
{
	if (!HelperFunctions::compile(fileName))
	{
		string errorMessage = fileName + " isn't compiled.";
		throw exception(errorMessage.c_str());
	}
}

void TemplateRender::run(const string filePath)
{
	if (!HelperFunctions::run(filePath))
	{
		string errorMessage = filePath + " cann't run.";
		throw exception(errorMessage.c_str());
	}
}

//void TemplateRender::createDeleteFilesBat(vector<string> deleteList, const string fileName)
//{
//	if (!HelperFunctions::createBat(deleteList, fileName))
//	{
//		string errorMessage = "Cannot create bat file";
//		throw exception(errorMessage.c_str());
//	}
//}

void TemplateRender::deleteDirectory(const string path)
{
	HelperFunctions::run("rmdir /S /Q " + path);
}

void TemplateRender::render(const string htmlPagePath)
{
	const string folderPath = "_cpptemp_";
	const string cppFileName = "temp.cpp";
	const string exeFileName = "temp.exe";
//	const string batFileName = "sd.bat";

	try
	{
		string parsedCppCode = getCppCode(htmlPagePath);
		string cppCode = completedCppCode(parsedCppCode);

		//vector<string> deleteList;
		//deleteList.push_back(cppFileName);
		//deleteList.push_back(exeFileName);
		//createDeleteFilesBat(deleteList, batFileName);

		createCppFile(cppCode, cppFileName);
		compileCppFile(cppFileName);
		run(folderPath + "\\" + cppFileName);
	}
	catch (exception ex)
	{
		cout << ex.what();
	}

	deleteDirectory(folderPath);

	if (HelperFunctions::directoryExists("Rendered_HTML_Page"))
	{
		HelperFunctions::run("Rendered_HTML_Page\\index.html");
	}
}