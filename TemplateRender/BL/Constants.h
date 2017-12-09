#pragma once
#include <string>

namespace CONSTANT
{
	const std::string FOR_REGEX("for\\s*\\(\\s*(auto|size_t|int)\\s*[a-z]{1,}\\s*=\\s*\\d{1,}\\s*;\\s*[a-z]{1,}\\s*(<|>|==|!=)\\s*\\d{1,}\\s*;\\s*[a-z]{1,}((\\+\\+)|(\\-\\-))\\s*\\)");
	const std::string IF_REGEX("if\\s*\\(\\s*((\\w+)|(\\w+\\s*(<|>|==|!=|<=|>=)\\s*\\w+))\\s*\\)");
	const std::string VAR_REGEX("\\{\\{\\s*\\w*\\s*\\}\\}");
	const std::string ELSE_REGEX("\\{\\s*%\\s*\\else\\s*%\\s*\\}");
	const std::string BEGIN_IF_REGEX("\\{\\s*%\\s*" + IF_REGEX + "\\s*%\\s*\\}");
	const std::string BEGIN_FOR_REGEX("\\{\\s*%\\s*" + FOR_REGEX + "\\s*%\\s*\\}");
	const std::string BEGIN_COMMENT_REGEX("\\{\\s*%\\s*comment\\s*\".*\"\\s*%\\s*\\}");
	const std::string BEGIN_TAG_REGEX("(" + BEGIN_FOR_REGEX + ")|(" + BEGIN_COMMENT_REGEX + ")|(" + BEGIN_IF_REGEX + ")");
	const std::string END_TAG_REGEX("\\{\\s*%\\s*end(for|if|comment)\\s*%\\s*\\}");
	const std::string COMPARISON_SYMBOL_REGEX("\\s*(<|>|==|!=|<=|>=)\\s*");
	const std::string INCLUDE_TAG_REGEX("\\{\\s*%\\s*#include\\s*\"\\w+\\.(html|htm)\"\\s*%\\s*\\}");
	const std::string TAG_REGEX("(" + BEGIN_TAG_REGEX + ")|(" + END_TAG_REGEX + ")");

	// Info:
	// Location of template.
	const std::string TEMPLATE_DIR("Tests/Templates/");

	// Info:
	// Location of rendered HTML document.
	const std::string ENDPOINT_DIR("Tests/");
}
