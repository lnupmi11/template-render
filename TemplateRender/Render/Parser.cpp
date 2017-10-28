#include "Parser.h"
#include<regex>
#include<algorithm>

void append(string &str, const string &subStr)
{
	for (int i = 0; i < subStr.size(); ++i)
	{
		if (subStr[i] == '"')
		{
			if (i != 0 && subStr[i - 1] == char(92))
			{
				str += subStr[i];
			}
			str += char(92); // ascii code of '\'
			str += '"';
		}
		else
		{
			str += subStr[i];
		}
	}
}


//info 
// function which create code for compilation (without including libraries and without standard start of the progarms and the end) 
// also include nested cycles
// but now work only for loop for (to changes this we need to add more checks in isLoop() dunction ) 
string Parser::parseToCpp(string& cppHtmlCode)
{
	static string cppCode("");
	string::size_type startPos, endPos;
	string::size_type commentStart, commentEnd;

	removeGapsAndTabsBeforeCode(cppHtmlCode);
	static  string ForCompilation = "";

	commentStart = cppHtmlCode.find("<!--");
	commentEnd = cppHtmlCode.find("-->");

	startPos = cppHtmlCode.find("<%");
	endPos = cppHtmlCode.find("%>");

	while (startPos < commentEnd && startPos > commentStart && endPos < commentEnd)
	{
		startPos = cppHtmlCode.find("<%", commentEnd);
		endPos = cppHtmlCode.find("%>", commentEnd);
	}

	if (startPos != 0 && startPos != -1)
	{
		ForCompilation.append("file << \" ");
		append(ForCompilation, cppHtmlCode.substr(0, startPos));
		ForCompilation.append(" \";  ");
		cppHtmlCode.erase(0, startPos);
	}

	while (startPos != -1 || endPos != -1)
	{
		if (!isCppHtmlTagsValid(startPos, endPos))
		{
			throw exception("invald cppHtml syntaxes at html file \n");
		}

		cppCode = erase(cppHtmlCode, 0, endPos - startPos);

		if (isLoop(cppCode))
		{
			append(ForCompilation, cppCode);
			parseToCpp(cppHtmlCode);
		}
		else
		{
			if (cppCode != "{" && cppCode != "}")
			{
				if (isVariableDeclaration(cppCode))
				{
					ForCompilation.append(cppCode);
				}
				else
				{
					ForCompilation.append(" file <<  ");
					append(ForCompilation, cppCode);
					ForCompilation.append(";");
				}
			}
			if (cppCode == "{" || cppCode == "}")
			{
				append(ForCompilation, cppCode);
			}
			parseToCpp(cppHtmlCode);
		}
		startPos = cppHtmlCode.find("<%");
		endPos = cppHtmlCode.find("%>");
	}

	if (startPos == -1 && endPos == -1 && cppHtmlCode != "")
	{
		ForCompilation.append("file << \" ");
		append(ForCompilation, cppHtmlCode.substr(0, startPos));
		ForCompilation.append(" \";  ");
		cppHtmlCode.erase(0, startPos);
		ForCompilation.erase(remove(ForCompilation.begin(), ForCompilation.end(), '\n'), ForCompilation.end());
	}

	return ForCompilation;
}


bool Parser::isLoop(const string & str)
{
	const string forRegex = "\\s*for\\s*\\(\\s*auto \\s*[a-z]{1,}\\s*=\\s*\\d{1,}\\s*;\\s*[a-z]{1,}\\s*<\\s*\\d{1,}\\s*;\\s*[a-z]{1,}\\+\\+\\s*\\)";
	const string foreachRegex = "\\s*for\\s*\\(\\s*auto\\s*[a-z]{1,}\\s*\\:\\s*[a-z]{1,}\\s*\\)";

	bool checkFor = regexCheck(str, forRegex);
	bool checkForeach = regexCheck(str, foreachRegex);

	return checkFor || checkForeach;
}


bool Parser::regexCheck(const string & str, const string & regexStr)
{
	regex expr(regexStr);
	if (regex_search(str.begin(), str.end(), expr))
	{
		return true;
	}
	return false;
}


//// Info
//// delete spaces and tabs before code 
void Parser::removeGapsAndTabsBeforeCode(string & code)
{
	while (code[0] == ' ' || code[0] == '\n')
	{
		code.erase(0, 1);
	}
}


// Info
// get only cpp code from string(from pos1 to pos2 ) and delete this string from cppHtmlCode
string Parser::erase(string & cppHtmlCode, string::size_type pos1, string::size_type pos2)
{
	removeGapsAndTabsBeforeCode(cppHtmlCode);
	string tmp = cppHtmlCode.substr(pos1, pos2 + 2);
	cppHtmlCode.erase(pos1, pos2 + 2);
	tmp.erase(tmp.find("<%"), 2);
	tmp.erase(tmp.find("%>"), 2);
	return tmp;
}


// info
// check if part of cpp code is a variable declaration 
bool Parser::isVariableDeclaration(const string & str)
{
	bool result;
	result = false;
	regex varDeclar("auto\\s{1,}[A-Za-z]{1,}\\s{1,}=\\s{1,}([A-Za-z]{1,}|[0-9]{1,})\\s*;");
	if (regex_match(str, varDeclar))
	{
		result = true;
	}
	return result;
}


// info
// check if it is not exist unc
bool Parser::isCppHtmlTagsValid(string::size_type start, string::size_type end)
{
	bool result;
	result = true;
	if (start > end)
	{
		result = false;
	}
	return result;
}

