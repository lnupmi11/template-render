#include "../Utils/Functions.h"
#include "../Render/Parser.h"
#include "TemplateRender.h"
#include "Compile.h"


string TemplateRender::getCppCode(const string htmlPagePath)
{
	string content = HelperFunctions::getCppHtmlCode(htmlPagePath);
	string cppCode = Parser::parseToCpp(content);

	if (cppCode.size() == 0)
	{
		throw exception("Parsed file is empty.");
	}

	return cppCode;
}

void TemplateRender::createCompileFunction(const string & cppCode, const string & outputPath)
{
	ofstream ofs;
	ofs.open(outputPath, ios_base::out | ios_base::trunc);
	ofs << cppCode;
	ofs.close();
}

void TemplateRender::render(const string& htmlPagePath, DataObject& Model)
{
	const string outputCppFilePath = "Render//Compile.h";
	try
	{
		string parsedCppCode = getCppCode(htmlPagePath);
		string cppCode = HelperFunctions::createCompletedCppCode(parsedCppCode);
		createCompileFunction(cppCode, outputCppFilePath);
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