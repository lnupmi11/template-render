#include "Tests/Tests.h"
#include "DTO\DataManager.h"
#include "Render\TemplateRender.h"
using namespace std;

int main()
{
	TemplateRender::render("Tests\\TestCppHtmlPage.htm");
	system("pause");
	return 0;
}