#include "../Render/TemplateRender.h"
#include "../BL/Constants.h"
#include <time.h>
#include <iostream>
#include <fstream>

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
		{ "text_in_snippet_1", "'If' text for testing '#include' tag." },
		{ "text_in_snippet_2", "'Else' text for testing '#include' tag." },
		{ "test_image", "test.png" }
	};
	
	TemplateRender::render("index.html", "completed.html", new Context<std::string>(context));

	finish = clock();
	float renderingTime = (float)(finish - start) / CLOCKS_PER_SEC;
	std::cout << "\nRendering time: " << renderingTime << " sec. ";

	time_t t = time(nullptr);
	struct tm now;
	localtime_s(&now, &t);
	std::ofstream logFile(CONFIG::ENDPOINT_DIR + "log.txt", std::ios::app);
	logFile << "[" << now.tm_hour << ':' << now.tm_min << ':' << now.tm_sec << "] Rendering time: " << renderingTime << " sec.\n";
	logFile.close();
}
