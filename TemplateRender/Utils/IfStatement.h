#pragma once
#include "Parameters.h"
#include "../DTO/Context.h"

class IfStatement
{
public:
	// Info:
	// Analyzes 'if' statemet's parameters and returns its body.
	static std::string parse(const std::string& code, ifParams& parameters);

	// Info:
	// Executes 'if' statement.
	static std::string execute(const std::string& body, const ifParams& parameters, ContextBase* context);

private:
	// Info:
	// Analyzes condition and returns its type.
	static conditionType type(const std::string& condition);

	// Info:
	// Checks the condition and returns its result.
	template<typename dataType>
	static bool condition(const dataType& left, const dataType& right, const ifParams& parameters, ContextBase* context)
	{
		bool result = false;
		switch (parameters.type)
		{
		case conditionType::less:
			result = (left < right);
			break;
		case conditionType::greater:
			result = (left > right);
			break;
		case conditionType::lessAndEquals:
			result = (left <= right);
			break;
		case conditionType::greaterAndEquals:
			result = (left >= right);
			break;
		case conditionType::equals:
			result = (left == right);
			break;
		case conditionType::notEquals:
			result = (left != right);
			break;
		case conditionType::none:
			if (std::regex_replace(context->getByKey(parameters.firstVar), std::regex("\\s+"), "") != "")
			{
				result = true;
			}
			break;
		default:
			throw RenderError("IfStatement::condition(): incorrect condition.", __FILE__, __LINE__);
		}
		return result;
	}
};
