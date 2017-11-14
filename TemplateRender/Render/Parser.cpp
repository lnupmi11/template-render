#include "Parser.h"

//info 
// function which create code for compilation (without including libraries and without standard start of the progarms and the end) 
// also include nested cycles
// but now work only for loop for (to changes this we need to add more checks in isLoop() function ) 


string Parser::parseToCpp(string& cppHtmlCode)
{
	static string cppCode("");
	string::size_type cppCodeBegin, cppCodeEnd;
	string::size_type commentStart, commentEnd;

	removeGapsAndTabsInCode(cppHtmlCode);
	static  string result("");

	commentStart = cppHtmlCode.find("<!--");
	commentEnd = cppHtmlCode.find("-->");

	cppCodeBegin = cppHtmlCode.find("<%");
	cppCodeEnd = cppHtmlCode.find("%>");

	while (cppCodeBegin < commentEnd && cppCodeBegin > commentStart && cppCodeEnd < commentEnd)
	{
		cppCodeBegin = cppHtmlCode.find("<%", commentEnd);
		cppCodeEnd = cppHtmlCode.find("%>", commentEnd);
	}

	if (cppCodeBegin != 0 && cppCodeBegin != -1)
	{
		result.append("file << \" ");
		append(result, cppHtmlCode.substr(0, cppCodeBegin));
		result.append(" \";  ");
		cppHtmlCode.erase(0, cppCodeBegin);
	}

	while (cppCodeBegin != -1 || cppCodeEnd != -1)
	{
		if (!isCppHtmlTagsValid(cppCodeBegin, cppCodeEnd))
		{
			throw exception("invald cppHtml syntaxes at html file \n");
		}

		cppCode = erase(cppHtmlCode, 0, cppCodeEnd - cppCodeBegin);

		if (isLoop(cppCode))
		{
			append(result, cppCode);
			parseToCpp(cppHtmlCode);
		}
		else
		{
			if (cppCode != "{" && cppCode != "}")
			{
				if (isVariableDeclaration(cppCode))
				{
					result.append(cppCode);
				}
				else
				{
					result.append(" file <<  ");
					append(result, cppCode);
					result.append(";");
				}
			}
			if (cppCode == "{" || cppCode == "}")
			{
				append(result, cppCode);
			}
			parseToCpp(cppHtmlCode);
		}
		cppCodeBegin = cppHtmlCode.find("<%");
		cppCodeEnd = cppHtmlCode.find("%>");
	}

	if (cppCodeBegin == -1 && cppCodeEnd == -1 && cppHtmlCode != "")
	{
		result.append("file << \" ");
		append(result, cppHtmlCode.substr(0, cppCodeBegin));
		result.append(" \";  ");
		cppHtmlCode.erase(0, cppCodeBegin);
		result.erase(remove(result.begin(), result.end(), '\n'), result.end());
	}

	return result;
}



void Parser::append(string& str, const string& subStr)
{
	for (size_t i = 0; i < subStr.size(); ++i)
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


bool Parser::isLoop(const string& str)
{
	const string forRegex = "\\s*for\\s*\\(\\s*auto \\s*[a-z]{1,}\\s*=\\s*\\d{1,}\\s*;\\s*[a-z]{1,}\\s*<\\s*\\d{1,}\\s*;\\s*[a-z]{1,}\\+\\+\\s*\\)\\s*";
	const string forRegex2 = "\\s*for\\s*\\(\\s*auto\\s*[A-z]{1,}\\s*=\\s*\\d{1,}\\s*;\\s*[A-z]{1,}\\s*<\\s*[A-z]{1,}\\.[A-z]{1,}\\(\\s*\\)\\s*;\\s*[A-z]{1,}\\+\\+\\s*\\)\\s*";
	const string foreachRegex = "\\s*for\\s*\\(\\s*auto\\s*[A-z]{1,}\\s*\\:\\s*[A-z]{1,}\\s*\\)\\s*";
	const string foreachRegex2 = "\\s*for\\s*\\(\\s*auto&\\s*[A-z]{1,}\\s*\\:\\s*[A-z]{1,}\\s*\\)\\s*";
	const string foreachEnumeratorRegex = "\\s*for\\s*\\(\\s*auto\\s*[A-z]{1,}\\s*\\:\\s*[A-z]{1,}\\.[A-z]{1,}\\(\\s*\\)\\s*\\)\\s*";

	bool isFor = regexCheck(str, forRegex);
	bool isFor2 = regexCheck(str, forRegex2);
	bool isForeach = regexCheck(str, foreachRegex);
	bool isForeach2 = regexCheck(str, foreachRegex2);
	bool isForeachEnumerator = regexCheck(str, foreachEnumeratorRegex);
	return isFor || isForeach || isForeach2 || isForeachEnumerator || isFor2;
}


bool Parser::regexCheck(const string& str, const string& regexStr)
{
	regex expr(regexStr);
	bool result;
	result = false;
	if (regex_match(str.begin(), str.end(), expr))
	{
		result = true;
	}
	return result;
}


//// Info
//// delete spaces and tabs before code 
void Parser::removeGapsAndTabsInCode(string& code)
{
	while (code[0] == ' ' || code[0] == '\n')
	{
		code.erase(0, 1);
	}
}


// Info
// get only cpp code from string(from pos1 to pos2 ) and delete this string from cppHtmlCode
string Parser::erase(string& cppHtmlCode, string::size_type pos1, string::size_type pos2)
{
	removeGapsAndTabsInCode(cppHtmlCode);
	string result;
	result = cppHtmlCode.substr(pos1, pos2 + 2);
	cppHtmlCode.erase(pos1, pos2 + 2);
	result.erase(result.find("<%"), 2);
	result.erase(result.find("%>"), 2);

	return result;
}


// info
// check if part of cpp code is a variable declaration 
bool Parser::isVariableDeclaration(const string& str)
{
	const string varDeclarRegex = "\\s*auto\\s{1,}[A-Za-z]{1,}\\s{1,}=\\s{1,}([A-Za-z]{1,}|[0-9]{1,})\\s*;\\s*";
	bool isVarDeclar = regexCheck(str, varDeclarRegex);
	
	return isVarDeclar;
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

