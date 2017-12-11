#pragma once
#include <string>
#if defined(_WIN32) || defined(_WIN64)
#include <direct.h>
#define ROOT_DIR std::string(_getcwd(0, 0)) + "/"
#elif defined(__unix) || defined(__unix__) || defined(__APPLE__) || defined(__MACH__) || defined(__linux__) || defined(__FreeBSD__)
#include <unistd.h>
#define ROOT_DIR std::string(getcwd(0, 0)) + "/"
#endif

namespace CONFIG
{
	// Info:
	// Location of template.
	static const std::string TEMPLATE_DIR(ROOT_DIR + "Tests/Templates/");

	// Info:
	// Location of rendered HTML document.
	static const std::string ENDPOINT_DIR(ROOT_DIR + "Tests/");

	// Info:
	// Location of all media files.
	static const std::string MEDIA_DIR(ROOT_DIR + "Tests/Media/");
}