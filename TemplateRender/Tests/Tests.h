#include "../Render/TemplateRender.h"
#include <time.h>

void TEST_CASE()
{
	std::cout << "Rendering...";
	clock_t start, finish;
	start = clock();

	std::vector<std::string> keys;
	keys.push_back("first_author");
	keys.push_back("second_author");
	keys.push_back("third_variable");
	keys.push_back("title");
	std::vector<std::string> values;
	values.push_back("Yuriy Lisovskiy");
	values.push_back("Yuriy Vasko");
	values.push_back("third``");
	values.push_back("Index Page");
	
	TemplateRender::render("index.html", "completed.html", new Context<std::string>(keys, values));

	finish = clock();
	float difference((float)finish - (float)start);
	std::cout << "\nRendering time: " << difference / CLOCKS_PER_SEC << " sec. ";
}
