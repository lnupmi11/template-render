#include "../Render/TemplateRender.h"
#include <time.h>

void TEST_CASE()
{
	std::cout << "Rendering...";
	clock_t start, finish;
	start = clock();

	std::vector<std::pair<std::string, std::string>> context = {
		{ "first_author", "Yuriy Lisovskiy" },
		{ "second_author", "Yuriy Vasko" },
		{ "third_variable", "third``" },
		{ "title", "Index Page" }
	};
	
	TemplateRender::render("index.html", "completed.html", new Context<std::string>(context));

	finish = clock();
	std::cout << "\nRendering time: " << ((float)finish - (float)start) / CLOCKS_PER_SEC << " sec. ";
}
