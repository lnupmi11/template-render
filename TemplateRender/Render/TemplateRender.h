#pragma once
#include <string>

class TemplateRender
{
public:
	static void render(const std::string& templatePath, const std::string& htmlPath);
};