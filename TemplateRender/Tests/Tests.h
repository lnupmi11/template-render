#pragma once
#include <iostream>
#include <Windows.h>
#include <direct.h>
#include "../Utils/Functions.h"

using namespace std;

string composedCppCode()
{
	std::string result = "#include <Windows.h>\n";
	result += "#include <fstream>\n";
	result += "#include <direct.h>\n";
	result += "int main()\n";
	result += "{\n";
	result += "ShowWindow(GetConsoleWindow(), SW_HIDE);\n";
	result += "_mkdir(\"Rendered_HTML_Page\");\n";
	result += "std::ofstream file;\n";
	result += "file.open(\"Rendered_HTML_Page/index.html\");\n";
	result += "if (file.is_open())\n";
	result += "{\n";
	result += "file << \"<h2>Index Page!</h2>\\n\";";
	result += "for (size_t i = 0; i < 10; i++)\n";
	result += "{\n";
	result += "file << \"<p>Paragraph \" << (i + 1) << \"</p>\\n\";\n";
	result += "}\n";
	result += "file.close();\n";
	result += "}\n";
	result += "ShellExecute(NULL, NULL, \".\\\\_cppcache_\\\\sd.bat\", NULL, NULL, SW_SHOWDEFAULT);";
	result += "return 0;\n";
	result += "}\n";
	return result;
}

void CREATE_AND_COMPILE_CPP()
{
	cout << "Running test: CREATE_AND_COMPILE_CPP()...\n";
	HelperFunctions hp;
	hp.createCpp(composedCppCode(), "a.cpp");
	hp.compile("a.cpp");
	vector<string> deleteList;
	deleteList.push_back("a.cpp");
	deleteList.push_back("a.exe");
	hp.createBat(deleteList, "sd.bat");
	hp.run("_cppcache_\\a.exe");
	cout << "Trash is removed.\n";
	Sleep(500);
	_rmdir("_cppcache_");
	hp.run("Rendered_HTML_Page\\index.html");
	cout << "\n";
	system("pause");
}