#pragma once
#include <string>
#include <list>
#include "Constants.h"
#include "Models.h"
#include "../DTO/Context.h"


class HelperFunctions
{
public:

	static std::string retrieveBodyForLoop(const std::string& code, forLoopParams& parameters);

	static std::string retrieveBodyIf(const std::string& code, ifParams& parameters);

	static int getTypeOfIFCondition(const std::string& condition);

	static size_t codeType(const std::string& code);

	static block findBlock(size_t& pos, const std::string& code);

	static void findAllBlocks(std::list<block>& blocks, const std::string& code);

	static std::string runCode(const std::string& code, ContextBase* context);

	static std::string parse(const std::string& code, ContextBase* context);

	static std::string readTemplate(const std::string& templateName);

	static void createHTML(const std::string& html, const std::string& htmlPath);

	static std::string forLoop(const std::string& loopBody, const forLoopParams& parameters);

	static std::string ifStatement(const std::string& body, const ifParams& parameters, ContextBase* context);

	static void findTag(const std::string& str, blockParams& params);

};
