#include<iostream>
#include<fstream>
#include<Windows.h>
#include"../DTO/Model.h"
using namespace std;


class TemplateRender {
private:

#define COMPILEDCPPFILEPATH "../TemplateRender/Render/Compile.h"
#define DEVPROMPTPATH "%comspec% /k \"C:\\Program Files\\Microsoft Visual Studio\\2017\\Community\\Common7\\Tools\\VsDevCmd.bat\" && cd /d "  
#define EXEFILEPATH " && cd .. && devenv TemplateRender.sln /build && cd Debug && TemplateRender.exe && exit"
#define COMPILEDCPPHTMLFILEPATH " && cd .. && cd TemplateRender && cd Rendered_HTML_Page && index.html"


	static string getCppCode(const string& path);
	static void createCompileFunction(const string& cppCode, const string& outputPath);
public:
	static void render(const string& htmlPagePath, Model& data);
};