#pragma once
#include <string>
#include <vector>
#include"CppCodeTemplate.h"

class HelperFunctions
{
private:
	static void validateFileName(const std::string& fileName);
public:

	// Info
	// Get all from cpphtml(simple html page with our cpp code) page     
	static std::string getCppHtmlCode(const std::string& fileName);

	// Info
	// Create a final html page
	static bool createHtmlPage(const std::string& htmlCode , const std::string& fileName);
	
	// Info
	// Add  begin(also libraries) and end to cpp code;
	static std::string createCompletedCppCode(const std::string& mainPartOfCppCode);

};