#pragma once
#include "TemplateRender.h"
#include "../Utils/Functions.h"
#include <iostream>

void TemplateRender::render(const std::string& templatePath, const std::string& htmlPath)
{
	try
	{
		std::string templateHTML = HelperFunctions::readTemplate(CONSTANT::TEMPLATE_DIR + templatePath);
		std::string completedHTML = HelperFunctions::parse(templateHTML);
		HelperFunctions::createHTML(completedHTML, CONSTANT::ENDPOINT_DIR + htmlPath);
		std::cout << "\nCompleted!";
	}
	catch (const std::exception& exc)
	{
		std::cerr << exc.what();
	}
	catch (...)
	{
		std::cerr << "An unknown error occurred.";
	}
}
