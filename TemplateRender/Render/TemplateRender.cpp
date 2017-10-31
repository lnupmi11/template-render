#include "../Utils/Functions.h"
#include "../Render/Parser.h"
#include "TemplateRender.h"
#include"Compile.h"


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

void TemplateRender::createCompileFunction(const string & cppCode)
{
	ofstream ofs;
	ofs.open("Render//Compile.h", ios_base::out | ios_base::trunc);
	ofs << cppCode;
	ofs.close();
}



void TemplateRender::render(const string& htmlPagePath, DataObject& Model)
{
	string parsedCppCode = getCppCode(htmlPagePath);
	string cppCode = completedCppCode(parsedCppCode);
	createCompileFunction(cppCode);
	try
	{
		compile(Model);
	}
	catch (const ofstream::failure& e)
	{
		cout << "Exception opening/reading file \n" << e.what() << "\n";
	}
	catch (const exception& e)
	{
		cout << e.what()<<"\n";
	}
	catch (...)
	{
		cout << "UNKNOWN ERROR \n";
	}

}