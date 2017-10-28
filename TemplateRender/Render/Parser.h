#pragma once
#include<iostream>
using namespace std; 

class Parser
{
private:
	static bool regexCheck(const string & str, const string & regexStr);
public:
	/// <summary>
	/// <see cref="parseToCpp"/>
	/// </summary>
	static string parseToCpp(string& cppHtmlCode);
	/// <summary>
	/// <see cref="isLoop"/>
	/// </summary>
	static bool isLoop(const string& str);
	/// <summary>
	/// <see cref="removeGapsAndTabsBeforeCode"/>
	/// </summary>
	static void removeGapsAndTabsBeforeCode(string& code);
	/// <summary>
	/// <see cref="erase"/>
	/// </summary>
	static string erase(string& cppHtmlCode, string::size_type pos1, string::size_type pos2);
	/// <summary>
	/// <see cref="isVariableDeclaration"/>
	/// </summary>
	static bool isVariableDeclaration(const string& str);
	/// <summary>
	/// <see cref="isCppHtmlTagsValid"/>
	/// </summary>
	static bool isCppHtmlTagsValid(string::size_type start, string::size_type end);

};

