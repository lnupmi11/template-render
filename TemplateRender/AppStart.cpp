#include "Render\TemplateRender.h"
#include"../TemplateRender/Render/GlobalVariables.h"
#include"Utils\Functions.h"

using namespace std;

int main()
{
	Model data;
	TemplateRender::render(CPPHTMFILEPATH, data);
	return 0;
}