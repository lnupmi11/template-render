#include "Context.h"
#include <sstream>

std::string Context<>::getByKey(const std::string& key)
{
	std::string result("");
	if (this->list.find(key) != this->list.end())
	{
		std::ostringstream stream;
		stream << this->list[key];
		result = stream.str();
	}
	return result;
}
