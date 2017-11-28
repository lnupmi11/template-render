#pragma once
#include <string>
#include <iostream>
#include "../Utils/Functions.h"
#include "../Utils/RenderError.h"
#include "../DTO/Context.h"
#include <algorithm>
#include <regex>

class TemplateRender
{
public:
	template <typename dataType = size_t>
	static void render(const std::string& templatePath, const std::string& htmlPath, Context<dataType>* data = nullptr)
	{
		try
		{
			std::string templateHTML = HelperFunctions::readTemplate(CONSTANT::TEMPLATE_DIR + templatePath);
			if (data)
			{
				templateHTML = TemplateRender::parseVariables(templateHTML, data);
			}
			std::string completedHTML = HelperFunctions::parse(templateHTML);
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

	template <typename dataType>
	static std::string parseVariables(const std::string& code, Context<dataType>* data)
	{
		std::string result("");
		if (code.find("{{") == std::string::npos)
		{
			result = code;
		}
		else
		{
			std::regex expression(CONSTANT::VAR_REGEX);
			std::sregex_iterator begin(code.begin(), code.end(), expression), end;
			size_t pos = 0;
			for (auto it = begin; it != end; it++)
			{
				for (size_t i = pos; i < (size_t)it->position(); i++)
				{
					result += code[i];
				}
				pos = it->position() + it->str().size();
				result += data->getByKey(std::regex_replace(it->str(), std::regex("\\s+|\\{|\\}"), ""));
			}
			for (size_t i = pos; i < code.size(); i++)
			{
				result += code[i];
			}			
		}
		return result;
	}
};