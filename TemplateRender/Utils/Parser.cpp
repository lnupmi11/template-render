#include "Parser.h"
#include<regex>
#include<algorithm>




//Info
/// <summary><c>append</c> is a method in the static class <c>Parser</c> .
/// Function which add \ before "  for compilation without errors (invalid synatax)  
/// </summary>
void append(std::string &str, const std::string &subStr) 
{
	for (int i = 0; i<subStr.size(); ++i) 
	{
		if (subStr[i] == '"') 
		{
			if (i != 0 && subStr[i-1] == char(92)) 
			{
				str+=subStr[i];
			}
			str+=char(92); // ascii code of '\'
			str+='"';
		}
		else 
		{
			str+=subStr[i];
		}
	}
}

///
//info 
// function which create code for compilation (without including libraries and without standard start of the progarms and the end) 
// also include nested cycles
// but now work only for loop for (to changes this we need to add more checks in isLoop() dunction ) 
string Parser::parseToCpp(string& cppHtmlCode)
{
	static string cppCode("");
	string::size_type startPos, endPos;

	// useful function  , but delete all spaces , so simple text in html page will be changed
	//cppHtmlCode.erase(remove_if(cppHtmlCode.begin(), cppHtmlCode.end(), isspace), cppHtmlCode.end());

	removeGapsAndTabsBeforeCode(cppHtmlCode);
	static  string ForCompilation = "";

	startPos = cppHtmlCode.find("<%");
	endPos = cppHtmlCode.find("%>");

	if (startPos != 0 && startPos != -1)
	{
		ForCompilation.append("file << \" ");
		append(ForCompilation, cppHtmlCode.substr(0, startPos));
		ForCompilation.append(" \";  ");
		cppHtmlCode.erase(0, startPos);
	}

	while (startPos != -1 || endPos != -1)
	{
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
				ForCompilation.append(" file <<  ");
				append(ForCompilation, cppCode);
				ForCompilation.append(";");
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
		ForCompilation.erase(remove(ForCompilation.begin(),ForCompilation.end(), '\n'), ForCompilation.end());
	}

	return ForCompilation;
}

///
bool Parser::isLoop(const string & str)
{
	bool result;
	result = false;
	regex loopForExpr("\\s*for\\s*\\(\\s*int \\s*[a-z]{1,}\\s*=\\s*\\d{1,}\\s*;\\s*[a-z]{1,}\\s*<\\s*\\d{1,}\\s*;\\s*[a-z]{1,}\\+\\+\\s*\\)");
	if (regex_search(str.begin(), str.end(), loopForExpr))
	{
		result = true;
	}
	return result;
}

// TODO : transfer regex from this method to to isLoop method .  
bool Parser::isForeach(const string & str)
{
	//for(auto n : nums)
	regex loopForExpr("\\s*for\\s*\\(\\s*auto\\s*[a-z]{1,}\\s*\\:\\s*[a-z]{1,}\\s*\\)");
	if (regex_search(str.begin(), str.end(), loopForExpr))
	{
		return true;
	}

	return false;
}

///
//// Info
//// delete spaces and tabs before code 
void Parser::removeGapsAndTabsBeforeCode(string & code)
{
	
	while (code[0] == ' ' || code[0] == '\n')
	{
		code.erase(0, 1);
	}
	/*regex anySymbol("[^\\s] ");
	regex_replace(code, anySymbol, "");*/
}

///
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

