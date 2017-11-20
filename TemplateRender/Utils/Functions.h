/*#pragma once
#include <string>
#include "CppCodeTemplate.h"
#include "Constants.h"

class HelperFunctions
{
public:

	// Info
	// Get all from cpphtml(simple html page with our cpp code) page     
	static std::string getCppHtmlCode(const std::string& fileName);

	// Info
	// Create a final html page
	static bool createHtmlPage(const std::string& htmlCode , const std::string& fileName);
	
	// Info
	// Creates .cpp file from string variable
	static bool createCpp(const std::string& cppCode, const std::string& fileName);

	// Info
	// Add  begin(also libraries) and end to cpp code;
	static std::string createCompletedCppCode(const std::string& mainPartOfCppCode);

	// Info
	// Compiles c++ code using g++ compiler
	static bool compile(const std::string& cppFilePath);

	// Info
	// Runs cmd commands
	static bool run(const std::string& command);

	// Info
	// Check if directory exists
	static bool directoryExists(const std::string& directory);

};*/

#pragma once
#include <string>


class HelperFunctions
{
public:

	static std::string retrieveBodyForLoop(const std::string& code, int& numberOfIteration, bool& increment, bool& fewer);

	static size_t codeType(const std::string& code);

	static std::string runCode(const std::string& code);

	static std::string parse(const std::string& code);

	static std::string readTemplate(const std::string& templateName);

	static void createHTML(const std::string& html, const std::string& htmlPath);

	static void render(const std::string& templatePath, const std::string& htmlPath);

	static void forLoop(const std::string& loopBody, std::string& result, const int& numberOfIteration,const bool& increment,const bool& fewer);

};
