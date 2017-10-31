#include<iostream>
#include<fstream>
#include"../DTO/DataManager.h"
using namespace std;


class TemplateRender {
private:
	static string getCppCode(const string path);
	static void createCompileFunction(const string& cppCode, const string & outputPath);
public:
	static void render(const string& htmlPagePath , DataObject& data);
};