#include "Render\TemplateRender.h"
using namespace std;
#include"Utils\Functions.h"

int main()
{
	DataObject data;
	TemplateRender::render("..\\TemplateRender\\Tests\\TestCppHtmlPage.htm", data);
	return 0;
}