#include "Render\TemplateRender.h"
using namespace std;

int main()
{
	Model data;
	data.read(string("data.txt"));
	TemplateRender::render("Tests\\TestCppHtmlPage.htm" , data);
	system("pause");
	return 0;
}