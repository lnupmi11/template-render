#pragma once
#include <string>

class RenderError : public std::exception
{
private:
	std::string message;
	std::string codeSnippet;
public:
	RenderError(const std::string& message, const std::string& file, const int line, const std::string& errorLine = "");
	~RenderError() = default;
	const char* what() const;
	static std::string TEMPLATE;
private:
	std::string getError(const std::string& errorLine);
};
