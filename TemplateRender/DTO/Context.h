#pragma once
#include "../Utils/RenderError.h"
#include <map>
#include <vector>

class ContextBase
{
public:
	virtual std::string getByKey(const std::string& key) = 0;
};

template <class dataType = std::string>
class Context : public ContextBase
{
private:
	std::map<std::string, dataType> list;
public:
	Context(const std::vector<std::pair<std::string, dataType>>& data)
	{
		for (size_t i = 0; i < data.size(); i++)
		{
			this->list[data[i].first] = data[i].second;
		}
	}
	std::string getByKey(const std::string& key);

};
