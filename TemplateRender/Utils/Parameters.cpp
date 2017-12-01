#include "Parameters.h"

block::block() : code(""), before(""), after("") {};
block::block(const std::string& code, const std::string& before, const std::string& after) :
	code(code), before(before), after(after) {};

blockParams::blockParams(size_t foundPos, size_t offset, bool first, bool second, std::string regexFirst, std::string regexSecond) :
	foundPos(foundPos), offset(offset), first(first), second(second), regexFirst(regexFirst), regexSecond(regexSecond) {};

forLoopParams::forLoopParams() : numberOfIteration(0), increment(false), fewer(false), iteratorName("") {};

ifParams::ifParams() : type(0), firstVar(""), secondVar(""), elseString("") {};