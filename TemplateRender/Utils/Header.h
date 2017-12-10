#pragma once
#include "../Render/TemplateRender.h"
#include "../BL/Regex.h"
#include "../Config/Config.h"

/*
	Required to include to a file where 'TemplateRender::render()' is used.

	Libraries which are included in 'Header.h':
		* <string>
		* <vector>
		* <map>
		* <unistd.h> - Linux
		* <direct.h> - Windows
*/
