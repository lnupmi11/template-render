#include "../Render/TemplateRender.h"
#include <iostream>
#include <time.h>

void TEST_CASE()
{
	std::cout << "Rendering...";

	std::vector<std::string> keys;
	keys.push_back("first_author");
	keys.push_back("second_author");
	keys.push_back("third_variable");
	std::vector<std::string> values;
	values.push_back("Yuriy Lisovskiy");
	values.push_back("Yuriy Vasko");
	values.push_back("third``");

	clock_t start, finish;
	start = clock();

	TemplateRender::render("index.html", "completed.html", new Context<std::string>(keys, values));

	finish = clock();
	float difference((float)finish - (float)start);
	std::cout << "\nRendering time: " << difference / CLOCKS_PER_SEC << " sec. ";
}
