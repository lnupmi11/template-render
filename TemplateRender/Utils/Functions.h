#include<iostream>
#include <string>
#include<iterator>
#include <fstream>
using namespace std;


class HelperFunctions
{
private:

	static void validateFileName(const string& fileName);

	static constexpr const char*  PROGRAMBEGIN =
		" #include <iostream>\n "
		" #include <string>\n "
		" #include <list> \n "
		" #include <fstream>\n "
		" void compile(Model& Model)\n "
		"{\n "
		"std::ofstream file;\n"
		"file.open(\"Rendered_HTML_Page//Index.html\" , ios_base::out | ios_base::trunc  );\n"
		"if (file.is_open())\n "
		"{\n";

	static constexpr const char* PROGRAMEND = 
		"}\n"
		"else\n"
		"{\n"
		"	throw ofstream::failure(\"can not write to file ..\"); \n"
		"}\n"
		"file.close();\n"
		"}\n";


public:

	// Info
	// Get all from cpphtml(simple html page with our cpp code) page     
	static string getCppHtmlCode(const string& fileName);
	// Info
	// Add  begin(also libraries) and end to cpp code;
	static string createCompletedCppCode(const string& ñppCode);

	static string getFileContent(const string& path);

	static bool isStateModified(const string& previousVersion, const string& currentVersion);
};