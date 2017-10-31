#pragma once
#include<iostream>
#include <vector>
using namespace std;


class TemplateRender {
private:
	static string getFileContent(const string path);
	static string getCppCode(const string path);
	static string completedCppCode(const string path);
	static void createCppFile(const string cppCode, const string fileName);
	static void compileCppFile(const string fileName);
	static void run(const string filePath);
//	static void createDeleteFilesBat(vector<string> deleteList, const string fileName);
	static void deleteDirectory(const string path);
public:
	static void render(const string htmlPagePath);
};