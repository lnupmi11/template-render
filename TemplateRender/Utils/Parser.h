#pragma once
#include<iostream>
using namespace std; 

class Parser
{
public:
	/// <summary>
	/// <see cref="parseToCpp"/>
	/// </summary>
	static string parseToCpp(string& cppHtmlCode);
	/// <summary>
	/// <see cref="isLoop"/>
	/// </summary>
	static bool isLoop(const string& str);
	
	static bool isForeach(const string& str);
	/// <summary>
	/// <see cref="removeGapsAndTabsBeforeCode"/>
	/// </summary>
	static void removeGapsAndTabsBeforeCode(string& code);
	/// <summary>
	/// <see cref="erase"/>
	/// </summary>
	static string erase(string& cppHtmlCode, string::size_type pos1, string::size_type pos2);
};

