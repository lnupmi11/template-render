#include "TemplateRender.h"
#include "Parser.h"
#include "../BL/HTML.h"
#include "../BL/LoopStatement.h"
#include "../BL/Regex.h"
#include "../Config/Config.h"
#include <iostream>

void TemplateRender::render(const std::string& templatePath, const std::string& htmlPath, ContextBase* data)
{
	try
	{
		std::string templateHTML = HTML::read(CONFIG::TEMPLATE_DIR + templatePath);
		RenderError::TEMPLATE = templateHTML;
		std::string completedHTML = Parser::parseInline(templateHTML, data);
		completedHTML = Parser::parseTemplate(completedHTML, data);
		HTML::write(completedHTML, CONFIG::ENDPOINT_DIR + htmlPath);
		std::cout << "\nCompleted!";
	}
	catch (RenderError& exc)
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
