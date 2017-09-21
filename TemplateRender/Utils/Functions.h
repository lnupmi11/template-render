#pragma once
#include <string>
#include <vector>

class HelperFunctions
{
public :

	// Info
	// Get all from cpphtml(simple html page with our cpp code) page     
	static std::string getCppHtmlCode(const std::string& fileName);

	// Info
	// Create a final html page
	static void createHtmlPage(const std::string& htmlCode , const std::string& fileName);
	
	// Info
	// Creates .cpp file from string variable
	static void createCpp(const std::string& cppCode, const std::string& fileName);

	// Info
	// Creates .bat file for deleting unnecessary files
	static void createBat(std::vector<std::string> filesToDelete, const std::string& fileName);

	// Info
	// Compiles .cpp file using g++
	static void compile(const std::string& cppFilePath);

	// Info
	// Runs files
	static void run(const std::string& filePath);

};