#include <iostream>
#include "../Utils/Functions.h"
#include "../Render/Parser.h"

using namespace std;


void testParseToCpp()
{
	string result = Parser::parseToCpp(HelperFunctions::getCppHtmlCode("Tests/TestCppHtmlPage.htm"));
	string cppProgram = HelperFunctions::createCompletedCppCode(result);
}

