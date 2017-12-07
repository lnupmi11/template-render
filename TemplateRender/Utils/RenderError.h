#pragma once
#include <string>

class RenderError : public std::exception
{
private:
	std::string message;
public:
	RenderError(const std::string& message, const std::string& file, const int line);
	~RenderError() = default;
	const char* what() const;
};
