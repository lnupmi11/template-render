#include "Parameters.h"

block::block() : code(""), before(""), after("") {};
block::block(const std::string& code, const std::string& before, const std::string& after) :
	code(code), before(before), after(after) {};

blockParams::blockParams(size_t foundPos, size_t offset, bool begin, bool end) :
	foundPos(foundPos), offset(offset), begin(begin), end(end) {};

forLoopParams::forLoopParams() : numberOfIteration(0), increment(false), fewer(false) {};

ifParams::ifParams() : type(0), firstVar(""), secondVar("") {};