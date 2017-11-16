#include "Render\TemplateRender.h"
using namespace std;
#include"Utils\Functions.h"

int main()
{

	Model data;
	//data.read(string("data.txt"));
	TemplateRender::render("..\\TemplateRender\\Tests\\TestCppHtmlPage.htm", data);
	system("pause");
	return 0;
}