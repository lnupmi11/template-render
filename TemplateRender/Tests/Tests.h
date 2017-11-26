#include "../Render/TemplateRender.h"
#include <iostream>
#include <time.h>

void TEST_CASE()
{
	std::cout << "Rendering...";

	clock_t start, finish;
	start = clock();

	TemplateRender::render("index.html", "completed.html");

	finish = clock();
	float difference((float)finish - (float)start);
	std::cout << "\nRendering time: " << difference / CLOCKS_PER_SEC << " sec. ";
}
