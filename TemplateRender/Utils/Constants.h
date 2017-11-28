#pragma once
#include <string>

namespace CONSTANT
{
	const std::string FOR_REGEX("\\s*for\\s*\\(\\s*(auto|size_t|int)\\s*[a-z]{1,}\\s*=\\s*\\d{1,}\\s*;\\s*[a-z]{1,}\\s*(<|>|==|!=)\\s*\\d{1,}\\s*;\\s*[a-z]{1,}((\\+\\+)|(\\-\\-))\\s*\\)");
	const std::string IF_REGEX("\\s*if\\s*\\(\\s*((\\w+)|(\\w+\\s*(<|>|==|!=|<=|>=)\\s*\\w+))\\s*\\)");
	const std::string VAR_REGEX("\\{\\{\\s*\\w*\\s*\\}\\}");
	const std::string BEGIN_IF_REGEX("\\{\\s*%" + IF_REGEX + "\\s*%\\s*\\}");
	const std::string BEGIN_FOR_REGEX("\\{\\s*%" + FOR_REGEX + "\\s*%\\s*\\}");
	const std::string BEGIN_COMMENT_REGEX("\\{\\s*%\\s*comment\\s*\".*\"\\s*%\\s*\\}");
	const std::string BEGIN_TAG_REGEX("(" + BEGIN_FOR_REGEX + ")|(" + BEGIN_COMMENT_REGEX + ")|(" + BEGIN_IF_REGEX + ")");
	const std::string END_TAG_REGEX("\\{\\s*%\\s*end(for|if|comment)\\s*%\\s*\\}");

	// Info:
	// Location of template.
	const std::string TEMPLATE_DIR("Tests/");

	// Info:
	// Location of rendered HTML document.
	const std::string ENDPOINT_DIR("Tests/");
}