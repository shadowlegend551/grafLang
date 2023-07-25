#include <iostream>
#include <fstream>
#include <sstream>

#include "tokenizer.hpp"
#include "read_file.h"

int main()
{
    std::string filename = "code.txt";
    std::string code = read_file(filename);

    std::vector<Token> tokens = tokenize(code);

    for(Token i : tokens)
    {
        std::cout << i.type << ' ' << i.value << std::endl;
    }

    
    return 0;
}