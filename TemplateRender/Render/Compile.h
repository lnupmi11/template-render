 #include <iostream>
  #include <string>
  #include <list> 
  #include <fstream>
  void compile(DataObject& Model)
 {
 std::ofstream file;
file.open("..//TemplateRender//Rendered_HTML_Page//Index.html" , ios_base::out | ios_base::trunc  );
if (file.is_open())
 {
file << " <HTML><HEAD>    <META NAME=\"GENERATOR\" Content=\"Microsoft Visual Studio\">    <TITLE></TITLE></HEAD><BODY>       ";  for(auto i= 0 ; i < Model.getSize(); i++  ){ file <<   Model[i] ;}for(auto k =0; k < 10 ; k++){file << " hello     ";  }file << " </BODY></HTML> ";  }
else
{
	throw ofstream::failure("can not write to file .."); 
}
file.close();
}
