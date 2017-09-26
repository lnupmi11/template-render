#pragma once
#include<iostream>
using namespace std; 

class Parser
{
public:
	static string parseToCpp(string& cppHtmlCode);
	static bool isLoop(const string& str);
	static bool isForeach(const string& str);
	static void removeGapsAndTabsBeforeCode(string& code);
	static string erase(string& cppHtmlCode, string::size_type pos1, string::size_type pos2);
};

