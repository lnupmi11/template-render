#pragma once
#include "../BL/Parser.h"

class TemplateRender
{
public:

	// Info:
	// Renders the template.
	static void render(const std::string& templatePath, const std::string& htmlPath, Context* data = nullptr);
};