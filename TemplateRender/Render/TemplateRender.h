#include<iostream>
#include<fstream>
#include"../DTO/DataObject.h"

using namespace std;


class TemplateRender {
private:
	static string getFileContent(const string path);
	static string getCppCode(const string path);
	static string completedCppCode(const string path);
public:
	static void render(const string& htmlPagePath, const DataObject& data);
};