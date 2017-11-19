#include <iostream>
#include <string>
#include <list> 
#include <fstream>
void compile(Model& Model)
 {
 std::ofstream file;
file.open(INDEXHTMLFILEPATH, ios_base::out | ios_base::trunc);
if (file.is_open())
 {
file << " <HTML><HEAD>    <META NAME=\"GENERATOR\" Content=\"Microsoft Visual Studio\">    <TITLE></TITLE></HEAD><BODY>     ";  for(auto& elem : Model) file <<  elem;for(auto k =0; k < 10 ; k++){file << " Hello world     ";  }file << " </BODY></HTML> ";  }
else
{
	throw ofstream::failure("can not write to file .."); 
}
file.close();
}
