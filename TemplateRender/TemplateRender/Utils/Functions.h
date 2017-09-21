#pragma once
#include <string>
#include <vector>

// Info
//		Creates .cpp file from string variable
void createCpp(const std::string& cppCode, const std::string& fileName);

// Info
//		Creates .bat file for deleting unnecessary files
void createBat(std::vector<std::string> filesToDelete, const std::string& fileName);

// Info
//		Compiles .cpp file using g++
void compile(const std::string& cppFilePath);

// Info
//		Runs files
void run(const std::string& filePath);
