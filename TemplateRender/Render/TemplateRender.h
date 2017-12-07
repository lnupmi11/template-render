#pragma once
#include "../Utils/Constants.h"
#include "Parser.h"

class TemplateRender
{
public:

	// Info:
	// Renders the template.
	static void render(const std::string& templatePath, const std::string& htmlPath, ContextBase* data = nullptr);
};