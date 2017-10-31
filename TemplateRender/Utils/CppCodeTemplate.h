#include<iostream>
using namespace std;


static const string programBegin =
" #include <iostream>\n "
" #include <string>\n "
" #include <list> \n "
" #include <fstream>\n "
" void compile(DataObject& Model)\n "
"{\n "
"std::ofstream file;\n"
"file.open(\"Rendered_HTML_Page//Index.html\" , ios_base::out | ios_base::trunc  );\n"
"if (file.is_open())\n "
"{\n";


static const string programEnd = "}\n"
"else\n"
"{\n"
"	throw ofstream::failure(\"can not write to file ..\"); \n"
"}\n"
"file.close();\n"
"}\n";