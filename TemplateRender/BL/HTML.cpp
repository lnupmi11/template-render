#include "HTML.h"
#include "../Utils/RenderError.h"
#include <fstream>


std::string HTML::read(const std::string& templateName)
{
	std::ifstream read(templateName);
	std::string result("");
	if (read.is_open())
	{
		result.assign((std::istreambuf_iterator<char>(read)), std::istreambuf_iterator<char>());
		read.close();
	}
	else
	{
		throw RenderError("HTML::read(): template '" + templateName + "' does not exist.", __FILE__, __LINE__);
	}
	return result;
}

void HTML::write(const std::string& html, const std::string& htmlPath)
{
	std::ofstream file(htmlPath);
	if (file.is_open())
	{
		file << html;
		file.close();
	}
	else
	{
		throw RenderError("HTML::write(): can not open file '" + htmlPath + "' for writting.", __FILE__, __LINE__);
	}
}
