#pragma once
#include <string>

class RenderError : public std::exception
{
private:
	std::string message;
	std::string codeSnippet;
public:
	RenderError(const std::string& message, const std::string& file, const int line, const std::string& codeSnippet = "");
	~RenderError() = default;
	const char* what() const;
};
