#pragma once
#include <string>

namespace CONSTANT
{
	const std::string FOR_REGEX("\\s*for\\s*\\(\\s*auto | \\s*size_t |\\s*int \\s*[a-z]{1,}\\s*=\\s*\\d{1,}\\s*;\\s*[a-z]{1,}\\s*<\\s*\\d{1,}\\s*;\\s*[a-z]{1,}\\+\\+\\s*\\)");
	//const std::string FOREACH_REGEX = "\\s*for\\s*\\(\\s*auto\\s*[a-z]{1,}\\s*\\:\\s*[a-z]{1,}\\s*\\)";
	const std::string IF_REGEX("\\s*if\\s*\\(\\s*[a-z]{1,}\\s*< |\\s*> \\s*[a-z]{1,}\\s*\\)");

	const std::string END_FOR_REGEX("{% endfor %}");	// TODO:
	const std::string END_IF_REGEX("{% endif %}");		// TODO:
}