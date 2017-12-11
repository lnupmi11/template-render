#pragma once
#include "../BL/Parameters.h"
#include "../DTO/Context.h"

class LoopStatement
{
public:
	// Info:
	// Analyzes loop's parameters and returns loop body.
	static std::string parseForLoop(const std::string& code, forLoopParams& parameters);

	// Info:
	// Executes 'for' loop statement.
	static std::string executeForLoop(const std::string& loopBody, const forLoopParams& parameters);

	// Info:
	// Analyzes loop's parameters and returns loop body.
	static std::string parseForeachLoop(const std::string& code, foreachLoopParams& parameters);

	// Info:
	// Executes 'foreach' loop statement.
	static std::string executeForeachLoop(const std::string& loopBody, const foreachLoopParams& parameters, Context* context);
};