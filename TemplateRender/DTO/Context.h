#pragma once
#include "../Utils/RenderError.h"
#include <map>
#include <vector>

template <class dataType>
class Context
{
private:
	std::map<std::string, dataType> list;
public:
	Context(const std::vector<std::string>& keys, const std::vector<dataType>& values)
	{
		if (keys.size() == values.size())
		{
			for (size_t i = 0; i < keys.size(); i++)
			{
				this->list[keys[i]] = values[i];
			}
		}
		else
		{
			throw RenderError("Context::Context(): invalid context data.", __FILE__, __LINE__);
		}
	}
	std::string getByKey(const std::string key)
	{
		if (this->list.find(key) != this->list.end())
		{
			return std::to_string(this->list[key]);
		}
		else
		{
			throw RenderError("Context::getByKey(): invalid key.", __FILE__, __LINE__);
		}
	}
};
