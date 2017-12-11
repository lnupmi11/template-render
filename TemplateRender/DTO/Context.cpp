#include "Context.h"

Context::Context(const std::vector<std::pair<std::string, std::string>>& data)
{
	for (size_t i = 0; i < data.size(); i++)
	{
		this->list[data[i].first] = data[i].second;
	}
}

std::string Context::getByKey(const std::string& key)
{
	std::string result("");
	if (this->list.find(key) != this->list.end())
	{
		result = this->list[key];
	}
	return result;
}
