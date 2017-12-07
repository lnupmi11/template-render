#pragma once
#include "../Utils/Parameters.h"

class LoopStatement
{
public:
	// Info:
	// Analyzes loop's parameters and returns loop body.
	static std::string parse(const std::string& code, forLoopParams& parameters);

	// Info:
	// Executes 'for' loop statement.
	static std::string execute(const std::string& loopBody, const forLoopParams& parameters);
};