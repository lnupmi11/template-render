#pragma once
#include <iostream>
#include "../Utils/Functions.h"
#include "../Utils/RenderError.h"
#include "../Utils/Constants.h"
#include "Parser.h"
#include <regex>

class TemplateRender
{
public:

	// Info:
	// Renders the template.
	static void render(const std::string& templatePath, const std::string& htmlPath, ContextBase* data = nullptr)
	{
		try
		{
			std::string templateHTML = HelperFunctions::readTemplate(CONSTANT::TEMPLATE_DIR + templatePath);
			if (data)
			{
				templateHTML = Parser::parseVariables(templateHTML, data);
			}
			std::string completedHTML = HelperFunctions::parse(templateHTML, data);
			HelperFunctions::createHTML(completedHTML, CONSTANT::ENDPOINT_DIR + htmlPath);
			std::cout << "\nCompleted!";
		}
		catch (const RenderError& exc)
		{
			std::cerr << exc.what();
		}
		catch (const std::exception& exc)
		{
			std::cerr << "\nException occurred: " << exc.what() << '.';
		}
		catch (...)
		{
			std::cerr << "\nException occurred: unknown.";
		}
	}
};