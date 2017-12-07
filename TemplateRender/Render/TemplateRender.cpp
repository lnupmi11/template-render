#include "TemplateRender.h"
#include "Parser.h"
#include "../Utils/HTML.h"
#include <iostream>

void TemplateRender::render(const std::string& templatePath, const std::string& htmlPath, ContextBase* data)
{
	try
	{
		std::string templateHTML = HTML::read(CONSTANT::TEMPLATE_DIR + templatePath);
		std::string completedHTML = Parser::parseTemplate(templateHTML, data);
		completedHTML = Parser::parseVariables(completedHTML, data);
		HTML::write(completedHTML, CONSTANT::ENDPOINT_DIR + htmlPath);
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
