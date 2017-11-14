#include "../Utils/Functions.h"
#include "../Render/Parser.h"
#include "TemplateRender.h"
#include "Compile.h"

string TemplateRender::getCppCode(const string& htmlPagePath)
{
	string result;
	string htmlFileContent;
	htmlFileContent = HelperFunctions::getCppHtmlCode(htmlPagePath);
	string cppCode;
	cppCode = Parser::parseToCpp(htmlFileContent);
	if (cppCode.size() == 0)
	{
		throw exception("Parsed file is empty.");
	}
	result = HelperFunctions::createCompletedCppCode(cppCode);

	return result;
}

void TemplateRender::createCompileFunction(const string& cppCode, const string& outputPath)
{
	ofstream ofs;
	ofs.open(outputPath, ios_base::out | ios_base::trunc);
	ofs << cppCode;
	ofs.close();
}

void TemplateRender::render(const string& htmlPagePath, Model& Model)
{
	try
	{
		string cppCode;
		cppCode = getCppCode(htmlPagePath);
		
		if (HelperFunctions::isStateModified(cppCode, HelperFunctions::getFileContent("Render//Compile.h")))
		{
			createCompileFunction(cppCode, COMPILEDCPPFILEPATH);
		}
		compile(Model);
	}
	catch (const ofstream::failure& e)
	{
		cout << "Exception opening/reading file \n" << e.what() << "\n";
	}
	catch (const exception& e)
	{
		cout << e.what() << "\n";
	}
	catch (...)
	{
		cout << "UNKNOWN ERROR \n";
	}
}