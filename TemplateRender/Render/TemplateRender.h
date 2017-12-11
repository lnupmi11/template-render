#pragma once
#include "../BL/Parser.h"
#include <sstream>

class TemplateRender
{
public:

	// Info:
	// Renders the template.
	static void render(const std::string& templatePath, const std::string& htmlPath, Context* data = nullptr);

	// Info:
	// Compose string form given variable.
	template <typename dataType>
	static std::string str(const dataType& var)
	{
		std::ostringstream stream;
		stream << var;
		return stream.str();
	}

	// Info:
	// Compose string form given collection.
	template <typename dataType>
	static std::string str(const std::vector<dataType>& collection)
	{
		std::ostringstream stream;
		for (const auto object : collection)
		{
			stream << "~~|(" << object << ")|~~\n";
		}
		return stream.str();
	}
};