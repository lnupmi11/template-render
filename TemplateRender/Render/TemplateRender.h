#include<iostream>
#include<fstream>
#include"../DTO/Model.h"
using namespace std;


class TemplateRender {
private:
	#define COMPILEDCPPFILEPATH "Render//Compile.h"

	static string getCppCode(const string& path);
	static void createCompileFunction(const string& cppCode, const string& outputPath);
public:
	static void render(const string& htmlPagePath, Model& data);
};