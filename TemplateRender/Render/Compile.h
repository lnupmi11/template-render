#pragma once
#include <Windows.h>
  #include <iostream>
  #include <string>
  #include <list> 
  #include <fstream>
  #include <direct.h>
  void compile()
 {
  _mkdir("Rendered_HTML_Page");
 std::ofstream file;
 file.open("Rendered_HTML_Page//Index.html" , ios_base::out | ios_base::trunc  );
 if (file.is_open())
 {
file << " <HTML><HEAD>    <META NAME=\"GENERATOR\" Content=\"Microsoft Visual Studio\">    <TITLE></TITLE></HEAD><BODY>       ";  for(auto k =0; k < 10 ; k++){file << " t     ";  }file << " </BODY></HTML> ";  }
file.close();
}
