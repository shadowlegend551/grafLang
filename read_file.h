#include <string>
#include <fstream>
#include <sstream>

std::string read_file(std::string filename)
{
    std::ifstream file(filename);
    std::stringstream contents;
    contents << file.rdbuf();
    file.close();

    return contents.str();
}