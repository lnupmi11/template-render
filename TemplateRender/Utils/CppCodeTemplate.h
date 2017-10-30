#include<iostream>
using namespace std;


static const string programBegin = "#pragma once\n"
"#include <Windows.h>\n "
" #include <iostream>\n "
" #include <string>\n "
" #include <list> \n "
" #include <fstream>\n "
" #include <direct.h>\n "
" void compile()\n "
"{\n "
" _mkdir(\"Rendered_HTML_Page\");"
"\n std::ofstream file;\n"
" file.open(\"Rendered_HTML_Page//Index.html\" , ios_base::out | ios_base::trunc  );\n"
" if (file.is_open())\n "
"{\n";



static const string programEnd = "}\n"
"file.close();\n"
"}\n";