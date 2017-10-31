#include<iostream>
#include<fstream>
#include"../DTO/DataManager.h"
using namespace std;


class TemplateRender {
private:
	static string getFileContent(const string path);
	static string getCppCode(const string path);
	static string completedCppCode(const string path);
	static void createCompileFunction(const string& cppCode);
public:
	static void render(const string& htmlPagePath , DataObject& data);
};