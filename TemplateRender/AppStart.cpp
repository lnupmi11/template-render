#include "Render\TemplateRender.h"
#include"GlobalVariables.h"
#include"Utils\Functions.h"

using namespace std;

int main()
{
	Model data;
	TemplateRender::render(CPPHTMFILEPATH, data);
	system("pause");
	return 0;
}