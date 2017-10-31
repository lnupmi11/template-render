#include "Render\TemplateRender.h"
using namespace std;

int main()
{
	DataObject data;
	TemplateRender::render("Tests\\TestCppHtmlPage.htm" , data);
	system("pause");
	return 0;
}