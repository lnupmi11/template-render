#include<iostream>
#include<regex>
#include<algorithm>
using namespace std;

class Parser
{
private:
	static bool isLoop(const string& str);
	static void removeGapsAndTabsInCode(string& code);
	static void append(string& str, const string& subStr);
	static string erase(string& cppHtmlCode, string::size_type pos1, string::size_type pos2);
	static bool isVariableDeclaration(const string& str);
	static bool isCppHtmlTagsValid(string::size_type start, string::size_type end);
	static bool regexCheck(const string&str, const string& regexStr);
public:

	static string parseToCpp(string& cppHtmlCode);
};

