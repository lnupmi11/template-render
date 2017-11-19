#include<iostream>
#include<fstream>
#include<Windows.h>
#include"../DTO/Model.h"
using namespace std;

class TemplateRender {
private:

	static string getCppCode(const string& path);
	static void createCompileFunction(const string& cppCode, const string& outputPath);
	static void setVSLocation();
	static void presetVariables();
public:
	static void render(const string& htmlPagePath, Model& data);
};