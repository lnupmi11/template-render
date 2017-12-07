#include "RenderError.h"
#include <iostream>

RenderError::RenderError(const std::string& message, const std::string& file, const int line)
{
	this->message = "\nException occurred:\n File: '" + file + "', Line: " + std::to_string(line) + "\n Message: '" + message + "'\n";
}

const char* RenderError::what() const
{
	return this->message.c_str();
}
