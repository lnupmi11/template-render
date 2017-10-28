#pragma once
#include<iostream>
using namespace std;


class TemplateRender {
private:
	static string getFileContent(const string path);
	static string getCppCode(const string path);
	static string completedCppCode(const string path);
public:
	static void render(const string htmlPagePath);
};