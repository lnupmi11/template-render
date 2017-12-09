#include "RenderError.h"
#include "../BL/Constants.h"
#include <iostream>

RenderError::RenderError(const std::string& message, const std::string& file, const int line, const std::string& codeSnippet)
{
	this->message = "\nException occurred:\n File: '" + file + "', Line: " + std::to_string(line) + "\n Message: '" + message + "'\n";
	if (codeSnippet.size() > 0)
	{
		this->message += " Template: " + codeSnippet + '\n';
	}
}

const char* RenderError::what() const
{
	return this->message.c_str();
}
