#include "Models.h"

block::block() : code(""), before(""), after("") {};
block::block(const std::string& code, const std::string& before, const std::string& after) :
	code(code), before(before), after(after) {};
