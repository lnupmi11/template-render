#pragma once
#include <string>

namespace REGEX
{
	static const std::string FOR_REGEX("for\\s*\\(\\s*(auto|size_t|int)\\s*[a-z]{1,}\\s*=\\s*\\d{1,}\\s*;\\s*[a-z]{1,}\\s*(<|>|==|!=)?\\s*\\d{1,}\\s*;\\s*[a-z]{1,}((\\+\\+)?|(\\-\\-)?)\\s*\\)");
	static const std::string IF_REGEX("if\\s*\\(\\s*((\\w+)|(\\w+\\s*(<|>|==|!=|<=|>=)\\s*\\w+))\\s*\\)");
	static const std::string VAR_REGEX("\\{\\{\\s*\\w*\\s*\\}\\}");
	static const std::string ELSE_REGEX("\\{\\s*%\\s*\\else\\s*%\\s*\\}");
	static const std::string BEGIN_IF_REGEX("\\{\\s*%\\s*" + IF_REGEX + "\\s*%\\s*\\}");
	static const std::string BEGIN_FOR_REGEX("\\{\\s*%\\s*" + FOR_REGEX + "\\s*%\\s*\\}");
	static const std::string BEGIN_COMMENT_REGEX("\\{\\s*%\\s*comment\\s*\".*\"\\s*%\\s*\\}");
	static const std::string BEGIN_TAG_REGEX("(" + BEGIN_FOR_REGEX + ")|(" + BEGIN_COMMENT_REGEX + ")|(" + BEGIN_IF_REGEX + ")");
	static const std::string END_TAG_REGEX("\\{\\s*%\\s*end(for|if|comment)\\s*%\\s*\\}");
	static const std::string COMPARISON_SYMBOL_REGEX("\\s*(<|>|==|!=|<=|>=)\\s*");
	static const std::string INCLUDE_TAG_REGEX("\\{\\s*%\\s*#include\\s*\"\\w+\\.(html|htm)\"\\s*%\\s*\\}");
	static const std::string BLOCK_TAG_REGEX("(" + BEGIN_TAG_REGEX + ")|(" + END_TAG_REGEX + ")");
	static const std::string STATIC_TAG_REGEX("\\{\\s*%\\s*#(?!include)\\w*\\s*'?\\w+(\\.\\w+)?'?\\s*%\\s*\\}");
	static const std::string INLINE_TAG_REGEX("(" + VAR_REGEX + ")|(" + INCLUDE_TAG_REGEX + ")|(" + STATIC_TAG_REGEX + ")");
}
