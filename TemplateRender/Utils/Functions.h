#pragma once
#include <string>
#include <vector>
#include"CppCodeTemplate.h"

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
	// Creates .bat file for deleting unnecessary files
	static bool createBat(std::vector<std::string> filesToDelete, const std::string& fileName);

	// Info
	// Compiles c++ code using g++ compiler
	static bool compile(const std::string& cppFilePath);

	// Info
	// Runs cmd commands
	static bool run(const std::string& command);

};