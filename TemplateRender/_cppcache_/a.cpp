#include <Windows.h>
#include <fstream>
#include <direct.h>
int main()
{
ShowWindow(GetConsoleWindow(), SW_HIDE);
_mkdir("Rendered_HTML_Page");
std::ofstream file;
file.open("Rendered_HTML_Page/index.html");
if (file.is_open())
{
file << "<h2>Index Page!</h2>\n";for (size_t i = 0; i < 10; i++)
{
file << "<p>Paragraph " << (i + 1) << "</p>\n";
}
file.close();
}
ShellExecute(NULL, NULL, ".\\_cppcache_\\sd.bat", NULL, NULL, SW_SHOWDEFAULT);return 0;
}

