#pragma once
#include <string>

namespace CONSTANT
{
	// If you run program from x64/Debug use next defines:
	//const std::string TEMPLATE_PATH("..\\..\\TemplateRender\\Tests\\TestCppHtmlPage.htm");
	//const std::string MINGW_PATH("..\\..\\TemplateRender\\MinGW\\bin");

	// If you run program from Visual Studio debugger or simply Ctrl+F5 use next defines:
	const std::string TEMPLATE_PATH("Tests\\TestCppHtmlPage.htm");
	const std::string MINGW_PATH("MinGW\\bin");

	const std::string TEMP_DIR("_tempdir_");
}