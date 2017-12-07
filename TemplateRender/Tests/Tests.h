#include "../Render/TemplateRender.h"
#include <time.h>
#include <iostream>

void TEST_CASE()
{
	std::cout << "Rendering...";
	clock_t start, finish;
	start = clock();

	std::vector<std::pair<std::string, std::string>> context = {
		{ "first_author", "Yuriy Lisovskiy" },
		{ "second_author", "Yuriy Vasko" },
		{ "third_variable", "third``" },
		{ "title", "Index Page" },
		{ "text_in_snippet_1", "First text for testing '#include' tag." },
		{ "text_in_snippet_2", "Second text for testing '#include' tag." }
	};
	
	TemplateRender::render("index.html", "completed.html", new Context<std::string>(context));

	finish = clock();
	std::cout << "\nRendering time: " << ((float)finish - (float)start) / CLOCKS_PER_SEC << " sec. ";
}
