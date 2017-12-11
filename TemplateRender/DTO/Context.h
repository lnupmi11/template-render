#pragma once
#include "../Utils/RenderError.h"
#include <map>
#include <vector>

class Context
{
private:
	std::map<std::string, std::string> list;
public:
	Context(const std::vector<std::pair<std::string, std::string>>& data);
	std::string getByKey(const std::string& key);
};
