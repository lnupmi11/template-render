#include "../Utils/Functions.h"
#include "../Render/Parser.h"
#include "TemplateRender.h"
#include "../GlobalVariables.h"
#include "Compile.h"

string VSWHEREPATH = "C:\\Program Files (x86)\\Microsoft Visual Studio\\Installer\\vswhere.exe";
string VSLOCATION = "";

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

void TemplateRender::presetVariables()
{
	HelperFunctions::createPaths();
	HelperFunctions::setArchitecture();
	if (is32Bit)
	{
		VSWHEREPATH =  "C:\\Program Files\\Microsoft Visual Studio\\Installer\\vswhere.exe";
	}
}

void TemplateRender::setVSLocation()
{
	const string command = "%comspec% /c call \"" + VSWHEREPATH + "\" -property installationPath > " + VSPATH;

	HelperFunctions::execute(command);

	ifstream ifs;
	ifs.open(VSPATH);
	if (ifs.fail())
	{
		throw ios_base::failure(TMPDATAPATH);
	}
	getline(ifs, VSLOCATION);
	ifs.close();

	DEVPROMPTPATH = VSLOCATION + "\\Common7\\Tools\\VsDevCmd.bat";
}


void TemplateRender::render(const string& htmlPagePath, Model& Model)
{
	try
	{
		presetVariables();

		string cppCode;
		cppCode = getCppCode(htmlPagePath);


		string previousCompiledCpp;
		previousCompiledCpp = HelperFunctions::getFileContent(COMPILEDCPPFILEPATH);

		string currentCpp;
		currentCpp = cppCode;

		currentCpp.erase(remove_if(currentCpp.begin(), currentCpp.end(), isspace), currentCpp.end());
		remove_if(previousCompiledCpp.begin(), previousCompiledCpp.end(), isspace);

		setVSLocation();

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
				ShellExecute(NULL, "open", const_cast<char*>((EXEFILEPATH).c_str()), NULL, NULL, SW_SHOWDEFAULT);
				exit(0);
			}
			case 1:
			{
				ofs << 2;
				string tmp = EXEFILEPATH;
				tmp.resize(tmp.length() - 19);
				const string command = "%comspec% /k call \"" + DEVPROMPTPATH + "\" && cd /d " + ROOTFOLDERPATH + " && devenv TemplateRender.sln /build && cd /d " + tmp + " && TemplateRender.exe && exit" ;
				HelperFunctions::execute(command);
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

		cout << "\n" << INDEXHTMLFILEPATH;
		ShellExecute(0, "open", INDEXHTMLFILEPATH.c_str(),
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