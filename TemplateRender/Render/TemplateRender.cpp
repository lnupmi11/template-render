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

string ExePath() {
	char buffer[MAX_PATH];
	GetModuleFileName(NULL, buffer, MAX_PATH);
	string::size_type pos = string(buffer).find_last_of("\\/");
	return string(buffer).substr(0, pos);
}

void TemplateRender::render(const string& htmlPagePath, DataObject& Model)
{
	try
	{
		string cppCode;
		cppCode = getCppCode(htmlPagePath);

		string previousCompiledCpp;
		previousCompiledCpp = HelperFunctions::getFileContent(COMPILEDCPPFILEPATH);

		string currentCpp;
		currentCpp = cppCode;

		currentCpp.erase(remove_if(currentCpp.begin(), currentCpp.end(), isspace), currentCpp.end());
		remove_if(previousCompiledCpp.begin(), previousCompiledCpp.end(), isspace);

		ifstream ifs("log.txt");
		size_t state;
		ifs >> state;
		ifs.close();

		if (HelperFunctions::isStateModified(previousCompiledCpp, currentCpp) || state == 1 || state == 2)
		{
			if (state != 1 && state != 2)
			{
				state = 0;
			}
			ofstream ofs;
			ofs.open("log.txt", ios_base::out | ios_base::trunc);
			switch (state)
			{
			case 0:
			{
				createCompileFunction(cppCode, COMPILEDCPPFILEPATH);
				ofs << 1;
				ShellExecute(NULL, "open", const_cast<char*>((ExePath()+"\\TemplateRender.exe" ).c_str()),  NULL, NULL, SW_SHOWDEFAULT);
				exit(0);
			}
			case 1:
			{
				ofs << 2;
				HelperFunctions::execute(DEVPROMPTPATH + ExePath() + EXEFILEPATH);
				exit(0);
			}
			case 2:
			{
				ofs << 3;
				cout << "\n\t\t Compiling model . Press enter to continue  ... \n";
				cin.get();
				compile(Model);
				break;
			}
			}
			ofs.close();
		}
		
		string path = ExePath();
		path.resize(path.length() - 5);
		path += "TemplateRender\\Rendered_HTML_Page\\index.html";
		cout <<"\n" <<path;
		ShellExecute(0, "open", path.c_str(),
			NULL,
			NULL, SW_NORMAL);

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