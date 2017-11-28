#pragma once
/*
#include "TemplateRender.h"
#include "../Utils/Functions.h"
#include <iostream>
#include "../Utils/RenderError.h"

template <typename dataType>
void TemplateRender::render(const std::string& templatePath, const std::string& htmlPath, Context<dataType>* data)
{
	try
	{
		std::string templateHTML = HelperFunctions::readTemplate(CONSTANT::TEMPLATE_DIR + templatePath);
		std::string completedHTML = HelperFunctions::parse<dataType>(templateHTML, data);
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
}*/
