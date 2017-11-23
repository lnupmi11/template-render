#pragma once
#include <string>

namespace CONSTANT
{
	const std::string FOR_REGEX("\\s*for\\s*\\(\\s*(auto|size_t|int)\\s*[a-z]{1,}\\s*=\\s*\\d{1,}\\s*;\\s*[a-z]{1,}\\s*<\\s*\\d{1,}\\s*;\\s*[a-z]{1,}\\+\\+\\s*\\)");
	//const std::string FOREACH_REGEX = "\\s*for\\s*\\(\\s*auto\\s*[a-z]{1,}\\s*\\:\\s*[a-z]{1,}\\s*\\)";
	const std::string IF_REGEX("\\s*if\\s*\\(\\s*[a-z]{1,}\\s*< |\\s*> \\s*[a-z]{1,}\\s*\\)");

	const std::string BEGIN_TAG_REGEX("\\{\\s*%\\s*for\\s*\\(\\s*(auto|size_t|int)\\s*[a-z]{1,}\\s*=\\s*\\d{1,}\\s*;\\s*[a-z]{1,}\\s*<\\s*\\d{1,}\\s*;\\s*[a-z]{1,}\\+\\+\\s*\\)\\s*%\\s*\\}");
	const std::string END_TAG_REGEX("\\{\\s*%\\s*end(for|if)\\s*%\\s*\\}");

//	const std::string BEGIN_TAG_REGEX("\\{\\s*%\\s*(for|if)\\s*\\(\\s*\\)\\s*%\\s*\\}");
//	const std::string END_TAG_REGEX("\\{\\s*%\\s*end(for|if)\\s*%\\s*\\}");

	const std::string TEMPLATE_DIR("Tests/");
	const std::string ENDPOINT_DIR("Tests/");
}