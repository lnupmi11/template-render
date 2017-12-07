#pragma once
#include <string>

class HTML
{
public:
	// Info:
	// Reads template from file.
	static std::string read(const std::string& templateName);

	// Info:
	// Creates rendered HTML document.
	static void write(const std::string& html, const std::string& htmlPath);
};
